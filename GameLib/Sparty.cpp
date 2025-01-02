/**
 * @file Sparty.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "Sparty.h"
#include "Pin.h"
#include <wx/display.h>

#include "Conveyor.h"
#include "ConveyorVisitor.h"
#include "Game.h"
#include "Product.h"
#include "ProductVisitor.h"

/// Color to use for drawing a zero connection wire
const wxColour ConnectionColorZero = *wxBLACK;

/// Color to use for drawing a one connection wire
const wxColour ConnectionColorOne = *wxRED;

/// Color to use for drawing an unknown state connection wire
const wxColour ConnectionColorUnknown = wxColour(128, 128, 128);


/**
 * Loads the Sparty from an XML node.
 *
 * This function loads the Sparty's x location, y location, kick duration, and kick speed from an XML node.
 * @param node The XML node containing the Sparty's attributes
 */
void Sparty::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);
    node->GetAttribute(L"kickDuration", L"0.25").ToDouble(&mKickDuration);
    mAnimationProgress = mKickDuration;
    node->GetAttribute(L"kickSpeed", L"1000").ToDouble(&mKickSpeed);
    node->GetAttribute(L"height", L"100").ToInt(&mHeight);
}

/**
 * Draws Sparty on the given graphics context.
 *
 * The drawing is done so that the Sparty is centered on the x and y location given in the XML.
 * The drawing of the boot is animated so that it looks like it
 * is kicking. The animation is currently just a placeholder and the time since the last kick is
 * hardcoded to 0.
 *
 * @param gc The graphics context to draw on
 */
void Sparty::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    // Input pin line drawing
    // Choose the color based on the connection state
    wxColour lineColor;
    switch (mPin->GetState())
    {
    case PinState::ZERO:
        lineColor = ConnectionColorZero; // Black
        break;
    case PinState::ONE:
        lineColor = ConnectionColorOne; // Red
        break;
    default:
        lineColor = ConnectionColorUnknown; // Grey
        break;
    }

    wxPen pen(lineColor, 3);
    gc->SetPen(pen);

    // First line (right)
    gc->StrokeLine(GetX() - 10, GetY(), GetX() + 80, GetY());
    // Second line (up)
    gc->StrokeLine(GetX() + 80, GetY(), GetX() + 80, 25);
    // Third line (right)
    gc->StrokeLine(GetX() + 80, 25, 1130, 25);
    // Fourth line (down)
    gc->StrokeLine(1130, 25, 1130, 400);
    // Fifth line (left)
    //gc->StrokeLine(1130, 400, 1110, 400);
    mPin->Draw(gc);

    // sparty drawing
    double animation = mAnimationProgress / mKickDuration;
    if (animation > 1)
    {
        animation = 0;
    }
    else if (animation > 0.5) // The second half of the animation is the inverse of the first
    {
        animation = 1 - animation;
    }
    animation *= 2; // The animation is now between 0 and 1

    // Gets the width and height of the images to scale them
    double width = mBootBitmap->GetWidth();
    double height = mBootBitmap->GetHeight();
    double scale = mHeight / height;
    width *= scale;
    height *= scale;

    gc->PushState();
    gc->Translate(GetX() - width / 2, GetY() - height / 2);
    gc->DrawBitmap(*mFrontBitmap, 0, 0, width, height);
    gc->DrawBitmap(*mBackBitmap, 0, 0, width, height);

    // Rotates boot around pivot and draws it
    double SpartyBootPivotX = SpartyBootPivot.m_x * width;
    double SpartyBootPivotY = SpartyBootPivot.m_y * height;
    gc->Translate(SpartyBootPivotX, SpartyBootPivotY);
    gc->Rotate(animation * SpartyBootMaxRotation);
    gc->Translate(-SpartyBootPivotX, -SpartyBootPivotY);
    gc->DrawBitmap(*mBootBitmap, 0, 0, width, height);

    gc->PopState();
}

/**
 * Updates the animation progress of Sparty.
 *
 * This function increments the animation progress by the elapsed time
 * since the last update, allowing the kick animation to proceed over time.
 *
 * @param elapsed The time elapsed since the last update
 */
void Sparty::Update(double elapsed)
{
    ConveyorVisitor visitorConveyor;
    GetGame()->Accept(&visitorConveyor);
    bool conveyorRunning = false;
    if (visitorConveyor.GetConveyor() != nullptr )
    {
        conveyorRunning = visitorConveyor.GetConveyor()->IsRunning();
    }
    // Check if the pin state went from ZERO to ONE and the conveyor is running to initiate kick
    if (mPin->GetState() == PinState::ONE && mAnimationProgress >= mKickDuration && mPreviousPinState != PinState::ONE
        && conveyorRunning)
    {
        Kick();
    }
    mPreviousPinState = mPin->GetState();

    double timeUntilNextKick = mKickDuration*SpartyKickPoint - mAnimationProgress;
    mAnimationProgress += elapsed;
    // Kick animation should now hit a product
    if (mAnimationProgress > mKickDuration*SpartyKickPoint && mAnimationProgress - elapsed < mKickDuration*SpartyKickPoint)
    {
        ConveyorVisitor visitorConveyor;
        GetGame()->Accept(&visitorConveyor);
        double y = GetKickY();
        double x = 0;
        if (visitorConveyor.GetConveyor() != nullptr)
        {
            x = visitorConveyor.GetConveyor()->GetX();
            y += visitorConveyor.GetConveyor()->GetSpeed() * timeUntilNextKick; // Correction due to lag for where the product should have been at the kick
        }
        ProductVisitor visitor(y, x);
        GetGame()->Accept(&visitor);
        auto products = visitor.GetProducts();
        for (auto product : products)
        {
            product->Kick(mKickSpeed);
        }
    }
    mPin->UpdateGatePosition(1130, 400);
}

/**
 * Initiates the kick animation for Sparty.
 *
 * This function sets the animation progress to zero,
 * preparing Sparty to start the kick animation.
 * It is expected that a product will be kicked when found
 * but this is not yet implemented.
 */
void Sparty::Kick()
{
    mAnimationProgress = 0;
}

/**
 * Gets the y location of the kick point of Sparty.
 *
 * @return The y location of the kick point
 */
double Sparty::GetKickY()
{
    return GetY() + mHeight * (SpartyBootPercentage - 0.5);
}


/**
 * Function to check if there is a Pin at
 * the given Coordinates (x,y)
 * @param x X Coordinate
 * @param y Y coordinate
 * @return Pointer to Pin object if found nullptr otherwise
 */
std::shared_ptr<Pin> Sparty::PinHitTest(int x, int y)
{
    if (mPin->HitTest(x, y))
    {
        return mPin;
    }
    return nullptr;
}
