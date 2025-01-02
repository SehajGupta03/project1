/**
 * @file Sparty.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * Class for Sparty
 */

#ifndef SPARTY_H
#define SPARTY_H
#include "Item.h"
#include "ItemVisitor.h"
#include "Pin.h"
class Game;

/// Image for the sparty background, what is behind the boot
const std::wstring SpartyBackImage = L"images/sparty-back.png";

/// Image for the Sparty boot
const std::wstring SpartyBootImage = L"images/sparty-boot.png";

/// Image for the Sparty front, what is in front of the boot
const std::wstring SpartyFrontImage = L"images/sparty-front.png";

/// Pivot point for the Sparty boot image as a fraction of
/// the width and height.
const wxPoint2DDouble SpartyBootPivot = wxPoint2DDouble(0.5, 0.55);

/// The maximum rotation for Sparty's boot in radians
const double SpartyBootMaxRotation = 0.8;

/// The point in the kick animation when the product
/// actually is kicked. If the kick duration is 0.25,
/// we kick when 0.25 * 0.35 seconds have elapsed.
const double SpartyKickPoint = 0.35;

/// What percentage of the way down Sparty do we find the tip of his boot?
/// This means the location of the boot when kicking is 80% of the
/// way from the top of the Sparty image.
const double SpartyBootPercentage = 0.80;

/// Class for Sparty
class Sparty : public Item
{
private:
    /// The duration of the kick
    double mKickDuration = 0.25;
    /// The speed of the kick
    double mKickSpeed = 1000;
    /// Sparty's height
    int mHeight = 100;
    /// The current animation progress
    double mAnimationProgress = 0;

    /// The image for the sparty boot
    std::shared_ptr<wxImage> mBootImage;
    /// The bitmap for the sparty boot
    std::shared_ptr<wxBitmap> mBootBitmap;
    /// The image for the sparty front
    std::shared_ptr<wxImage> mFrontImage;
    /// The bitmap for the sparty front
    std::shared_ptr<wxBitmap> mFrontBitmap;
    /// The image for the sparty background
    std::shared_ptr<wxImage> mBackImage;
    /// The bitmap for the sparty background
    std::shared_ptr<wxBitmap> mBackBitmap;

    /// Input Pin
    std::shared_ptr<Pin> mPin;

    /// Stores the previous pin state
    PinState mPreviousPinState = PinState::UNKNOWN;

public:
    /**
     * @brief Constructor
     * @param game The game that Sparty belongs to
     */
    Sparty(Game* game) : Item(game)
    {
        mBackImage = std::make_shared<wxImage>(SpartyBackImage);
        mBackBitmap = std::make_shared<wxBitmap>(*mBackImage);
        mBootImage = std::make_shared<wxImage>(SpartyBootImage);
        mBootBitmap = std::make_shared<wxBitmap>(*mBootImage);
        mFrontImage = std::make_shared<wxImage>(SpartyFrontImage);
        mFrontBitmap = std::make_shared<wxBitmap>(*mFrontImage);
        mPin = std::make_shared<Pin>(game, PinType::INPUT ,0, 0);
    }

    void XmlLoad(wxXmlNode* node) override;
    void Draw(std::shared_ptr<wxGraphicsContext> gc) override;
    void Update(double elapsed) override;
    void Kick();
    double GetKickY();
    std::shared_ptr<Pin> PinHitTest(int x, int y) override;

    /**
     * Accept a visitor for this item.
     *
     * This function is used to call the item specific visit function
     * for the visitor provided. The visitor is responsible for knowing
     * how to handle the item.
     *
     * @param visitor The visitor to accept
     */
    void Accept(ItemVisitor* visitor) override
    {
        visitor->VisitSparty(this);
    };
};


#endif //SPARTY_H
