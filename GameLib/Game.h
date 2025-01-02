/**
 * @file Game.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * Class for drawing the game
 */

#ifndef GAME_H
#define GAME_H

#include <complex.h>
#include <memory>
#include <wx/graphics.h>

#include "Gate.h"
#include "Item.h"
#include "Score.h"
#include <vector>

/// Color to use for "green"
const wxColour MSUGreen = wxColour(24, 69, 59);

/// Level notices duration in seconds
const double LevelNoticeDuration = 2.0;

/// Size of notices displayed on screen in virtual pixels
const int NoticeSize = 100;

/// Color to draw the level notices
const auto LevelNoticeColor = wxColour(24, 69, 59);

/// Color to draw a rectangle enclosing the level notice text
const wxColour LevelNoticeBackground = wxColour(255, 255, 255, 200);

/// Padding to add to the left and right side of the level
/// notice background rectangle in virtual pixels
const double LevelNoticePadding = 20;
/**
* Base class for the game itself
*/
class Game
{
private:
    /// frame scale for virtual pixels
    double mScale;

    /// offset amount for x position for virtual pixels
    double mXOffset;

    /// offset amount for y position for virtual pixels
    double mYOffset;

    /// All items to populate our game
    std::vector<std::shared_ptr<Item>> mItems;

    /// The initial size of the game x value
    double mXInitialSize;

    /// The initial size of the game y value
    double mYInitialSize;

    /// Pointer to score object
    std::shared_ptr<Score> mScore;

    /// Stores the current level
    int mLevel;

    /// The current state of the game
    enum GameStates { ENDING, STARTING, PLAYING };

    /// Stores the state of the game
    GameStates mState = PLAYING;
    /// Stores the time until next state change
    double mStateTime = 0;

    /// Bool to  check if control points are on or off
    bool mControlPoints = false;

public:
    /// Constructor
    Game();

    /// Draw event for window
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    /// Event for left click press
    std::pair<double, double> OnLeftDown(int x, int y);

    /// Adds the item to the game view
    void Add(std::shared_ptr<Item> item);

    void Load(int level);

    void NextLevel();

    void Clear();
    void XmlItem(wxXmlNode* node);
    void XmlLevel(wxXmlNode* node);
    std::shared_ptr<Item> HitTest(int x, int y);
    std::shared_ptr<Pin> PinHitTest(int x, int y);
    void MoveBack(std::shared_ptr<Item> item);

    /**
     * Getter for XOffset
     * @return const double of the x offset
     */
    const double GetXOffset() { return mXOffset; }


    /**
     * Getter for YOffset
     * @return const double of the y offset
     */
    const double GetYOffset() { return mYOffset; }

    /**
     * Getter for scale
     * @return scale of the game
     */
    const double GetScale() { return mScale; }

    void Update(double elapsed, bool always_update=false);

    void Accept(ItemVisitor* visitor);

    void ComputeAllGates(const std::vector<std::shared_ptr<Item>>& items);

    /**
     * Gets the current score object
     * @return The current score object
     */
    std::shared_ptr<Score> GetScore() { return mScore; }

    /**
     * Setter for mControlPoints
     *
     * Used in GameView to set it to true or  false
     * @param show Bool that tells the game to show the control points or not
     */
    void SetControlPoints(bool show){mControlPoints = show;}

    /**
     * Getter for mControlPoints
     *
     * Used in Pin to check if Control Points are on or off
     * @return bool value that tells the pins to show control points or not
     */
    bool GetControlPoints(){return mControlPoints;}
};


#endif //GAME_H
