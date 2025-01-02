/**
 * @file Game.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "Game.h"
#include <algorithm>
#include <utility>
#include <memory>
#include "Beam.h"
#include "Conveyor.h"
#include "ConveyorVisitor.h"
#include "Scoreboard.h"
#include "Sensor.h"
#include "Sparty.h"
#include "DependencyGraph.h"

using namespace std;

/// level0 Xml file path
const wxString level0 = L"levels/level0.xml";
/// level 1 Xml file path
const wxString level1 = L"levels/level1.xml";
/// level 2 Xml File path
const wxString level2 = L"levels/level2.xml";
/// level 3 Xml File path
const wxString level3 = L"levels/level3.xml";
/// level 4 Xml File path
const wxString level4 = L"levels/level4.xml";
/// level 5 Xml file path
const wxString level5 = L"levels/level5.xml";
/// level 6 Xml File path
const wxString level6 = L"levels/level6.xml";
/// level 7 Xml File Path
const wxString level7 = L"levels/level7.xml";
/// level 8 Xml File Path
const wxString level8 = L"levels/level8.xml";
/// Initial item x location
const int InitialX = 200;

/// Initial item y location
const int InitialY = 200;

/// Maximum number of levels
const int maxLevel = 8;

/**
 * Game Constructor
 */
Game::Game()
{
    mScore = std::make_shared<Score>();
}

/**
 * Draw the game
 * @param graphics Graphics device to draw on
 * @param width Width of the window
 * @param height Height of the window
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    // Determine the size of the playing area in pixels
    int pixelWidth = mXInitialSize;

    int pixelHeight = mYInitialSize;

    //
    // Automatic Scaling
    //
    auto scaleX = double(width) / double(pixelWidth);
    auto scaleY = double(height) / double(pixelHeight);


    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = 0;

    if (height > pixelHeight * mScale)
    {
        mYOffset = (double)((height - pixelHeight * mScale) / 2.0);
    }

    graphics->PushState();

    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);

    //
    // Drawing a rectangle that is the playing area size
    //
    wxBrush background(MSUGreen);
    graphics->SetBrush(background);
    graphics->DrawRectangle(0, 0, pixelWidth, pixelHeight);

    // Redraw all items
    for (auto item : mItems)
    {
        item->Draw(graphics);
    }
    // Draws the notice if not in playing state
    if (mState != PLAYING)
    {
        // Sets the correct text
        wxString text = L"";
        if (mState == STARTING)
        {
            text = L"Level " + std::to_wstring(mLevel) + L" Begin";
        }
        else if (mState == ENDING)
        {
            text = L"Level Complete!";
        }
        graphics->PushState();
        graphics->Translate(pixelWidth / 2, pixelHeight / 2);
        wxFont noticeFont(wxSize(0, NoticeSize),
                          wxFONTFAMILY_SWISS,
                          wxFONTSTYLE_NORMAL,
                          wxFONTWEIGHT_BOLD);
        graphics->SetFont(noticeFont, LevelNoticeColor);
        double wid, hit;
        graphics->GetTextExtent(text, &wid, &hit);
        graphics->SetBrush(LevelNoticeBackground);
        graphics->SetPen(wxTransparentColor);
        double x = -wid / 2;
        double y = -hit / 2;
        graphics->DrawRectangle(x - LevelNoticePadding / 2, y - LevelNoticePadding / 2, wid + LevelNoticePadding,
                                hit + LevelNoticePadding);
        graphics->DrawText(text, x, y);
        graphics->PopState();
    }
    graphics->PopState();
    // Draw the top banner rectangle
    // Using a different color to distinguish it from the game area
    wxBrush topBanner(*wxBLACK); // Or any color you prefer
    graphics->SetBrush(topBanner);
    graphics->DrawRectangle(0, 0, width, mYOffset);


    // Draw the bottom banner rectangle
    wxBrush bottomBanner(*wxBLACK); // Use a different color for distinction if needed
    graphics->SetBrush(bottomBanner);

    // The bottom rectangle's position should be just below the game area
    double bottomY = mYOffset + pixelHeight * mScale; // Calculate Y position at the bottom

    // Draw the bottom rectangle
    graphics->DrawRectangle(0, bottomY, width, height - bottomY);
}


/**
 * get the adjusted x and y coordinates based on virtual pixel calculation
 * @param x original x cord
 * @param y original y cord
 * @return pair of doubles with new x cord first and ney y cord second
 */
std::pair<double, double> Game::OnLeftDown(int x, int y)
{
    double virtualX = (x - mXOffset) / mScale;
    double virtualY = (y - mYOffset) / mScale;
    return std::make_pair(virtualX, virtualY);
}

/**
 * Add an item to the game
 * @param item New item to add to the game
 */
void Game::Add(std::shared_ptr<Item> item)
{
    //item->SetLocation(InitialX, InitialY);
    mItems.push_back(item);
}

/**
 * Load the level based on a number.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param level The level to load.
 */
void Game::Load(int level)
{
    mLevel = level;
    wxString filename;
    switch (level)
    {
    case 0:
        filename = level0;
        break;
    case 1:
        filename = level1;
        break;
    case 2:
        filename = level2;
        break;
    case 3:
        filename = level3;
        break;
    case 4:
        filename = level4;
        break;
    case 5:
        filename = level5;
        break;
    case 6:
        filename = level6;
        break;
    case 7:
        filename = level7;
        break;
    case 8:
        filename = level8;
        break;
    }
    wxXmlDocument xmlDoc;
    if (!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Level file");
        return;
    }

    Clear();
    mState = STARTING;
    mStateTime = LevelNoticeDuration;

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    if (root->GetName() != L"level")
    {
        wxMessageBox(L"Invalid level file");
        return;
    }
    XmlLevel(root);

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    auto itemsNode = root->GetChildren();
    while (itemsNode)
    {
        if (itemsNode->GetName() == L"items")
        {
            auto itemNode = itemsNode->GetChildren();
            while (itemNode)
            {
                XmlItem(itemNode);
                itemNode = itemNode->GetNext();
            }
        }
        itemsNode = itemsNode->GetNext();
    }
    Update(0, true); // Makes sure that all the items will be in the right spot
}

/**
 * Advances to the next level
 *
 * Increments the current level and loads the game data from the XML file.
 */
void Game::NextLevel()
{
    mLevel++;
    // Cap the level
    if (mLevel > maxLevel)
    {
        mLevel = maxLevel;
    }
    mScore->AddGameScore();
    Load(mLevel);
}

/**
 * Clear the level data.
 *
 * Deletes all known items in the game.
 */
void Game::Clear()
{
    mItems.clear();
}

/**
 * Handle a node of type item.
 * @param node XML node
 */
void Game::XmlItem(wxXmlNode* node)
{
    // A pointer for the item we are loading
    std::shared_ptr<Item> item;

    // We have an item. What type?
    auto type = node->GetName();
    if (type == L"sensor")
    {
        item = std::make_shared<Sensor>(this);
    }
    if (type == L"conveyor")
    {
        item = std::make_shared<Conveyor>(this);
    }
    if (type == L"beam")
    {
        item = std::make_shared<Beam>(this);
    }
    if (type == L"sparty")
    {
        item = std::make_shared<Sparty>(this);
    }
    if (type == L"scoreboard")
    {
        item = std::make_shared<Scoreboard>(this);
    }


    if (item)
    {
        Add(item);
        item->XmlLoad(node);
    }
}


/**
 * Function to get the size information from
 * Xml file
 * @param node node in the Xml file
 */
void Game::XmlLevel(wxXmlNode* node)
{
    wxString size = node->GetAttribute(L"size", L"");
    if (!size.IsEmpty())
    {
        wxArrayString sizeParts = wxSplit(size, ',');

        if (sizeParts.size() == 2) // Ensure we have two parts
        {
            sizeParts[0].ToDouble(&mXInitialSize);
            sizeParts[1].ToDouble(&mYInitialSize);
        }
    }
}

/**
 * Test an x,y click location to see if it clicked
 * on some item in the Game
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Item> Game::HitTest(int x, int y)
{
    // Only in playing state does a click do anything
    if (mState != PLAYING)
    {
        return nullptr;
    }
    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return PinHitTest(x, y);
}

/**
 * Test an x,y click location to see if pin clicked
 * on some item in the Game
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Pin> Game::PinHitTest(int x, int y)
{
    // Only in playing state does a click do anything
    if (mState != PLAYING)
    {
        return nullptr;
    }
    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        auto pin = (*i)->PinHitTest(x, y);
        if (pin)
        {
            return pin;
        }
    }

    return nullptr;
}

/**
 * move item to end of Item list
 * @param item item to move to the end of mItems
 */
void Game::MoveBack(std::shared_ptr<Item> item)
{
    auto loc = find(begin(mItems), end(mItems), item);
    if (loc != end(mItems))
    {
        mItems.erase(loc);
        mItems.push_back(item);
    }
}


/**
 * Function to update all the items in the game
 * @param elapsed time since last update
 * @param always_update if true, always update even when the game is not in the playing state
 */
void Game::Update(double elapsed, bool always_update)
{
    // If the game is not in the playing state only change the duration of the notice and do not run the update function on each item
    if (mState != PLAYING)
    {
        mStateTime -= elapsed;
        if (mStateTime <= 0)
        {
            if (mState == STARTING)
            {
                mState = PLAYING;
            }
            else if (mState == ENDING)
            {
                NextLevel();
                mState = STARTING;
                mStateTime = LevelNoticeDuration;
            }
        }
        if (!always_update)
        {
            return;
        }
    }
    for (auto item : mItems)
    {
        item->Update(elapsed);
    }

    ComputeAllGates(mItems);


    // Checks if the level is done
    ConveyorVisitor visitor;
    Accept(&visitor);
    if (visitor.GetConveyor() != nullptr && visitor.GetConveyor()->IsLevelDone())
    {
        mState = ENDING;
        mStateTime = LevelNoticeDuration;
    }
}

/**
 * Accept a visitor for all items in the game.
 *
 * This function iterates through all the items in the game and calls
 * their individual Accept method, passing the provided visitor. The
 * visitor can perform operations on each item.
 *
 * @param visitor Pointer to the ItemVisitor to be used
 */
void Game::Accept(ItemVisitor* visitor)
{
    for (auto item : mItems)
    {
        item->Accept(visitor);
    }
}

/**
 * Sorts the gates and computes their outputs
 * @param items a vector of items(similar to mItems in some classes)
 */
void Game::ComputeAllGates(const vector<shared_ptr<Item>>& items)
{
    std::vector<Gate*> gates;

    for (const auto item : items)
    {
        Gate* gate = item->AsGate();
        if (gate)
        {
            gates.push_back(gate);
        }
    }

    DependencyGraph depGraph;
    depGraph.BuildDependencyGraph(gates);
    std::vector<Gate*> sortedGates = depGraph.TopologicalSort(gates);

    for (Gate* gate : sortedGates)
    {
        gate->calculate();
    }
}
