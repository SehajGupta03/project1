/**
 * @file GameView.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "GameView.h"
#include "Game.h"
#include <wx/dcbuffer.h>

#include "AndGate.h"
#include "NandGate.h"
#include "DflipFlop.h"
#include "Gate.h"
#include "ids.h"
#include "OrGate.h"
#include "MainFrame.h"
#include "Scoreboard.h"
#include "NotGate.h"
#include "SRFlipFlop.h"


using namespace std;

// /// level0 Xml file path
// const wxString level0 = L"levels/level0.xml";
// /// level 1 Xml file path
// const wxString level1 = L"levels/level1.xml";
// /// level 2 Xml File path
// const wxString level2 = L"levels/level2.xml";
// /// level 3 Xml File path
// const wxString level3 = L"levels/level3.xml";
// /// level 4 Xml File path
// const wxString level4 = L"levels/level4.xml";
// /// level 5 Xml file path
// const wxString level5 = L"levels/level5.xml";
// /// level 6 Xml File path
// const wxString level6 = L"levels/level6.xml";
// /// level 7 Xml File path
// const wxString level7 = L"levels/level7.xml";

/// Frame duration in milliseconds
const int FrameDuration = 30;


/**
 * Initialize the game view class.
 * @param parent The parent window for this class
 */
void GameView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY,
           wxDefaultPosition, wxDefaultSize,
           wxFULL_REPAINT_ON_RESIZE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // Bind the paint event
    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    Bind(wxEVT_TIMER, &GameView::OnTimer, this);

    // Bind the resize event to handle window resizing
    Bind(wxEVT_SIZE, &GameView::OnSize, this);

    // Bind the on left up event to handel left click done
    Bind(wxEVT_LEFT_UP, &GameView::OnLeftUp, this);

    // Bind the left mouse button down event
    Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);

    // Bind the on mouse move event
    Bind(wxEVT_MOTION, &GameView::OnMouseMove, this);

    // Bind timer event
    //Bind(wxEVT_TIMER, &GameView::OnTimer, this);


    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddAndGate, this, IDM_ADDANDGATE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddOrGate, this, IDM_ADDORGATE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddNotGate, this, IDM_ADDNOTGATE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddDflipFlop, this, IDM_ADDDFLIPFLOP);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddSRFlipFlop, this, IDM_ADDSRFLIPFLOP);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddNandGate, this, IDM_ADDNANDGATE);
    // Level loading handlers
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event) { OnLevelLoad(event, 0); }, IDM_LEVEL_0);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event) { OnLevelLoad(event, 1); }, IDM_LEVEL_1);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event) { OnLevelLoad(event, 2); }, IDM_LEVEL_2);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event) { OnLevelLoad(event, 3); }, IDM_LEVEL_3);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event) { OnLevelLoad(event, 4); }, IDM_LEVEL_4);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event) { OnLevelLoad(event, 5); }, IDM_LEVEL_5);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event) { OnLevelLoad(event, 6); }, IDM_LEVEL_6);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event) { OnLevelLoad(event, 7); }, IDM_LEVEL_7);
				parent->Bind(wxEVT_COMMAND_MENU_SELECTED, [this](wxCommandEvent& event) { OnLevelLoad(event, 8); }, IDM_LEVEL_8);
    // binding close operation to the parent
    parent->Bind(wxEVT_CLOSE_WINDOW, &GameView::OnClose, this);

    // bind control points toggle
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnToggleControl, this, IDM_CONTROL_POINTS);

    // Default starting level is level 1
    mGame.Load(1);

    // to calculate elapsed time
    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);

    mStopWatch.Start();
}


/**
 * Paint event, draws the window.
 * @param event wxCommandEvent
 */
void GameView::OnPaint(wxPaintEvent& event)
{
    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    mGame.Update(elapsed);

    // Create a double-buffered display context
    wxAutoBufferedPaintDC dc(this);

    // Clear the image to black
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto gc =
        std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    // Tell the game class to draw
    wxRect rect = GetRect();
    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());
}


/**
 * Handle the left mouse button down event
 * @param event The mouse click event
 */
void GameView::OnLeftDown(wxMouseEvent& event)
{
    std::pair<double, double> cord = mGame.OnLeftDown((event.GetX()), event.GetY());
    mGrabbedItem = mGame.HitTest(cord.first, cord.second);
    if (mGrabbedItem != nullptr)
    {
        mGame.MoveBack(mGrabbedItem);
        Refresh();
    }
}

/**
* Handle the left mouse button up event
* @param event
*/
void GameView::OnLeftUp(wxMouseEvent& event)
{
    OnMouseMove(event);
}

/**
* Handle the left mouse button down event
* @param event
*/
void GameView::OnMouseMove(wxMouseEvent& event)
{
    // See if an item is currently being moved by the mouse
    if (mGrabbedItem != nullptr)
    {
        // If an item is being moved, we only continue to
        // move it while the left button is down.
        if (event.LeftIsDown())
        {
            std::pair<double, double> cord = mGame.OnLeftDown((event.GetX()), event.GetY());
            mGrabbedItem->SetLocation(cord.first, cord.second);
        }
        else
        {
            // When the left button is released, we release the
            // item.
            mGrabbedItem->Release();
            mGrabbedItem = nullptr;
        }

        // Force the screen to redraw
        Refresh();
    }
}

/**
 * Handles the window size event
 * @param event The size event
 */
void GameView::OnSize(wxSizeEvent& event)
{
    Refresh(); // Window gets redrawn
    event.Skip(); // Allow the default handler to run
}

/**
 * Menu handler for the Add Gate -> And Gate
 * @param event Mouse event
 */
void GameView::OnAddAndGate(wxCommandEvent& event)
{
    auto gate = make_shared<AndGate>(&mGame);
    mGame.Add(gate);
    Refresh();
}

/**
 * Menu handler for the Add Gate -> Or Gate
 * @param event Mouse event
 */
void GameView::OnAddOrGate(wxCommandEvent& event)
{
    auto gate = make_shared<OrGate>(&mGame);
    mGame.Add(gate);
    Refresh();
}

/**
	* Menu handler for the Add Gate -> Not Gate
	* @param event Mouse event
	*/
void GameView::OnAddNotGate(wxCommandEvent& event)
{
    auto gate = make_shared<NotGate>(&mGame);
    mGame.Add(gate);
    Refresh();
}

/**
 * Menu handler for the Add Gate -> D Flip Flop
 * @param event Mouse event
 */
void GameView::OnAddDflipFlop(wxCommandEvent& event)
{
    auto gate = make_shared<DflipFlop>(&mGame);
    mGame.Add(gate);
    Refresh();
}

/**
 * Menu handler for the Add Gate -> SR Flip Flop
 * @param event Mouse event
 */
void GameView::OnAddSRFlipFlop(wxCommandEvent& event)
{
    auto gate = make_shared<SRFlipFlop>(&mGame);
    mGame.Add(gate);
    Refresh();
}


/**
 * Handles the logic for which level was selected to load
 * @param event The menu selection event
 * @param level The level selected
 */
void GameView::OnLevelLoad(wxCommandEvent& event, int level)
{
    mGame.GetScore()->ResetScore();
    mGame.Load(level);
    Refresh();
}


/**
 * function to refresh the screen as per the timer
 * @param event Timer event
 */
void GameView::OnTimer(wxTimerEvent& event)
{
    Refresh();
}

/**
 * Function to stop the timer
 * and close the window
 * @param event the close event
 */
void GameView::OnClose(wxCloseEvent& event)
{
    mTimer.Stop();
    event.Skip();
}


/**
 * Menu handler for Add Gate > Nand Gate
 * @param event Mouse event
 */
void GameView::OnAddNandGate(wxCommandEvent& event)
{
    auto gate = make_shared<NandGate>(&mGame);
    mGame.Add(gate);
    Refresh();
}

/**
 * function to toggle on/off control points when user selects to do so
 * @param event mouse event
 */
void GameView::OnToggleControl(wxCommandEvent& event)
{
	mControlPointsOn = !mControlPointsOn;
	mGame.SetControlPoints(mControlPointsOn);
	Refresh();
}
