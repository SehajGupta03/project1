/**
 * @file GameView.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 *
 */

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "Game.h"

/**
 * Base class for the viewing window
 */
class GameView : public wxWindow
{
private:
    ///Paint the background
    void OnPaint(wxPaintEvent& event);

    /// Event handlers
    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnSize(wxSizeEvent& event);
	void OnAddAndGate(wxCommandEvent& event);
	void OnAddOrGate(wxCommandEvent& event);
    void OnAddNotGate(wxCommandEvent& event);
	void OnAddDflipFlop(wxCommandEvent& event);
	void OnAddSRFlipFlop(wxCommandEvent& event);
	void OnAddNandGate(wxCommandEvent& event);
    void OnToggleControl(wxCommandEvent& event);
    void OnLevelLoad(wxCommandEvent& event, int level);

	/// An object that describes our game
    Game mGame;

    /// A pointer to an item that has been grabbed
    std::shared_ptr<Item> mGrabbedItem;


	/// The timer that allows for animation
	wxTimer mTimer;

	/// Stopwatch used to measure elapsed time
	wxStopWatch mStopWatch;

	/// The last stopwatch time
	long mTime = 0;

	/// Bool for ensuring the control points are
	bool mControlPointsOn = false;


public:
    /// Initialize
    void Initialize(wxFrame* parent);
	void OnTimer(wxTimerEvent& event);
	void OnClose(wxCloseEvent& event);


};


#endif //GAMEVIEW_H
