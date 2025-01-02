/**
 * @file Conveyor.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * Class for the conveyor
 */

#ifndef CONVEYOR_H
#define CONVEYOR_H
#include "Item.h"
#include "ItemVisitor.h"


/// Image for the background (base) of the conveyor
const std::wstring ConveyorBackgroundImage = L"images/conveyor-back.png";

/// Image for the conveyor belt
const std::wstring ConveyorBeltImage = L"images/conveyor-belt.png";

/// Image for the conveyor control panel when stopped.
const std::wstring ConveyorPanelStoppedImage = L"images/conveyor-switch-stop.png";

/// Image for the conveyor control panel when started.
const std::wstring ConveyorPanelStartedImage = L"images/conveyor-switch-start.png";

/// Rectangle representing the location of the start button relative to the panel
const wxRect StartButtonRect = wxRect(35, 29, 95, 36);

/// Rectangle representing the location of the stop button relative to the panel
const wxRect StopButtonRect = wxRect(35, 87, 95, 36);


/// Class for the conveyor
class Conveyor : public Item
{
private:
    /// The speed of the conveyor
    double mSpeed = 0.0;

    /// The x location of the panel relative to the conveyor
    wxCoord mPanelX = 0;
    /// The y location of the panel relative to the conveyor
    wxCoord mPanelY = 0;

    /// The height of the conveyor belt
    int mHeight = 800;

    /// The background image for the conveyor belt
    std::unique_ptr<wxImage> mBackgroundImage;
    /// The background bitmap for the conveyor belt
    std::unique_ptr<wxBitmap> mBackgroundBitmap;

    /// The image of the conveyor belt itself
    std::unique_ptr<wxImage> mBeltImage;
    /// The bitmap of the conveyor belt itself
    std::unique_ptr<wxBitmap> mBeltBitmap;

    /// The image of the control panel when the conveyor is stopped
    std::unique_ptr<wxImage> mPanelStoppedImage;
    /// The bitmap of the control panel when the conveyor is stopped
    std::unique_ptr<wxBitmap> mPanelStoppedBitmap;

    /// The image of the control panel when the conveyor is started
    std::unique_ptr<wxImage> mPanelStartedImage;
    /// The bitmap of the control panel when the conveyor is started
    std::unique_ptr<wxBitmap> mPanelStartedBitmap;

    /// The variable for running the conveyor belt
    bool mRunning = false;

    /// offset value for belt
    double mOffset = 0.0;

    /// Distance conveyor can move until level ends
    double mDistanceToEnd = 0.0;

public:
    Conveyor(Game* game);

    void XmlLoad(wxXmlNode* node) override;

    void Draw(std::shared_ptr<wxGraphicsContext> gc) override;

    bool HitTest(int x, int y) override;

    void Update(double) override;
    void ResetPosition();
    bool IsLevelDone();

    /**
     * Accepts a visitor for the conveyor.
     *
     * This tells the visitor that this was a conveyor.
     *
     * @param visitor Pointer to the ItemVisitor to be used
     */
    void Accept(ItemVisitor* visitor) override
    {
        visitor->VisitConveyors(this);
    };

    /**
     * Getter for the offset value of the conveyor belt
     *
     * @return The offset value of the conveyor belt
     */
    double GetOffset() { return mOffset; }

    /**
     * Getter for if the conveyor belt is running
     *
     * @return true if the belt is running, false if not
     */
    bool IsRunning() { return mRunning; }

    /**
     * Getter for the speed of the conveyor belt
     *
     * @return The speed of the conveyor belt
     */
    double GetSpeed() { return mSpeed; }
};


#endif //CONVEYOR_H
