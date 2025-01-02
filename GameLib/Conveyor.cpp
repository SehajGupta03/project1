/**
 * @file Conveyor.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "Conveyor.h"
#include "Product.h"
#include "ProductVisitor.h"
#include "Sparty.h"
#include "SpartyVisitor.h"


/**
 * @brief Constructor for Conveyor
 * @param game The game the conveyor will be associated with
 */
Conveyor::Conveyor(Game* game) : Item(game)
{
    mBackgroundImage = std::make_unique<wxImage>(ConveyorBackgroundImage, wxBITMAP_TYPE_ANY);
    mBackgroundBitmap = std::make_unique<wxBitmap>(*mBackgroundImage);

    mBeltImage = std::make_unique<wxImage>(ConveyorBeltImage, wxBITMAP_TYPE_ANY);
    mBeltBitmap = std::make_unique<wxBitmap>(*mBeltImage);

    mPanelStoppedImage = std::make_unique<wxImage>(ConveyorPanelStoppedImage, wxBITMAP_TYPE_ANY);
    mPanelStoppedBitmap = std::make_unique<wxBitmap>(*mPanelStoppedImage);

    mPanelStartedImage = std::make_unique<wxImage>(ConveyorPanelStartedImage, wxBITMAP_TYPE_ANY);
    mPanelStartedBitmap = std::make_unique<wxBitmap>(*mPanelStartedImage);
}

/**
 * Loads the conveyor from an XML node.
 *
 * @param node The XML node containing the conveyor's attributes
 */
void Conveyor::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    node->GetAttribute(L"speed", L"0.0").ToDouble(&mSpeed);
    node->GetAttribute(L"height", L"0").ToInt(&mHeight);
    wxString coordinateString = node->GetAttribute(L"panel", L"0,0");
    coordinateString.BeforeFirst(L',').ToInt(&mPanelX);
    coordinateString.AfterFirst(L',').ToInt(&mPanelY);
    // Load the products
    auto product = node->GetChildren();
    /// Stores the previous producst y coordinate offset from the conveyor belt
    double yCoordOffset = 0;
    for (; product; product = product->GetNext())
    {
        if (product->GetName() == L"product")
        {
            std::shared_ptr<Product> prod = std::make_shared<Product>(Item::GetGame(), yCoordOffset);
            GetGame()->Add(prod);
            prod->XmlLoad(product);
            yCoordOffset = prod->GetY();
            prod->SetLocation(this->GetX(), prod->GetY() + this->GetY());
        }
    }
    // Calculates out how far that the conveyor has to travel for the game to end
    SpartyVisitor visitor;
    GetGame()->Accept(&visitor);
    double spartyKickY = 0;
    if (visitor.GetSparty() != nullptr)
    {
        spartyKickY = visitor.GetSparty()->GetKickY();
    }
    mDistanceToEnd = spartyKickY - yCoordOffset + mSpeed * LastProductDelay + ProductDefaultSize;
}

/**
 * Draw the conveyor belt and panel.
 *
 * @param gc The graphics context to draw on
 */
void Conveyor::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    double offset = fmod(mOffset, mHeight);
    double width = mBackgroundBitmap->GetWidth();
    double height = mBackgroundBitmap->GetHeight();
    double scale = mHeight / height;
    width *= scale;
    height *= scale;

    // Draw the background
    gc->DrawBitmap(*mBackgroundBitmap,
                   this->GetX() - width / 2,
                   this->GetY() - height / 2,
                   width, height);

    // Draw two copies of the belt with the current offset
    gc->DrawBitmap(*mBeltBitmap,
                   this->GetX() - width / 2,
                   this->GetY() - height / 2 + offset,
                   width, height);

    gc->DrawBitmap(*mBeltBitmap,
                   this->GetX() - width / 2,
                   this->GetY() - 3 * height / 2 + offset,
                   width, height);

    // Draw the control panel
    wxCoord coordX = GetX() + mPanelX;
    wxCoord coordY = GetY() + mPanelY;

    if (mRunning)
    {
        width = mPanelStartedBitmap->GetWidth();
        height = mPanelStartedBitmap->GetHeight();
        gc->DrawBitmap(*mPanelStartedBitmap, coordX, coordY, width, height);
    }
    else
    {
        width = mPanelStoppedBitmap->GetWidth();
        height = mPanelStoppedBitmap->GetHeight();
        gc->DrawBitmap(*mPanelStoppedBitmap, coordX, coordY, width, height);
    }
}

/**
 * Function to check if the start or the stop button have been clicked
 * @param x The x location of the mouse click
 * @param y The y location of the mouse click
 * @return True or False if the item has been clicked
 */
bool Conveyor::HitTest(int x, int y)
{
    /// Size of the start button
    double startWidth = StartButtonRect.GetSize().GetWidth();
    double startHeight = StartButtonRect.GetSize().GetHeight();

    /// Location of the start button
    double startX = GetX() + mPanelX + StartButtonRect.x;
    double startY = GetY() + mPanelY + StartButtonRect.y;

    // Check if virtual point (x,y) is within the start button bounds
    if (x >= startX && x <= (startX + startWidth) &&
        y >= startY && y <= (startY + startHeight) && !mRunning)
    {
        mRunning = true;
        ResetPosition();
    }

    /// Size of the stop button
    double stopWidth = StopButtonRect.GetSize().GetWidth();
    double stopHeight = StopButtonRect.GetSize().GetHeight();

    /// Location of the stop button
    double stopX = GetX() + mPanelX + StopButtonRect.GetX(); // Fixed: Don't subtract x from stopX
    double stopY = GetY() + mPanelY + StopButtonRect.GetY();

    // Check if virtual point (x,y) is within the stop button bounds
    if (x >= stopX && x <= (stopX + stopWidth) &&
        y >= stopY && y <= (stopY + stopHeight))
    {
        mRunning = false;
    }

    return false;
}


/**
 * Function to make the belt move
 * @param elapsed time elapsed since last update
 */
void Conveyor::Update(double elapsed)
{
    if (mRunning)
    {
        mOffset += mSpeed * elapsed;
    }
}

/**
 * Resets the conveyor belt to its initial position and
 * resets all the products that are on the conveyor to their
 * initial positions.
 */
void Conveyor::ResetPosition()
{
    mOffset = 0;
    ProductVisitor visitor;
    GetGame()->Accept(&visitor);
    for (auto product : visitor.GetProducts())
    {
        product->ResetPosition();
    }
    GetGame()->GetScore()->ResetLevelScore();
}

/**
 * Checks if the level is done
 *
 * The level is done if the conveyor has moved the full distance
 *
 * @return true if the level is done, false if not
 */
bool Conveyor::IsLevelDone()
{
    return mOffset >= mDistanceToEnd;
}
