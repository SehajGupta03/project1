/**
 * @file Pin.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "Pin.h"
#include "Game.h"

#include <algorithm>

/// Diameter to draw the pin in pixels
const int PinSize = 10;

/// Color to use for drawing a zero connection wire
const wxColour ConnectionColorZero = *wxBLACK;

/// Color to use for drawing a one connection wire
const wxColour ConnectionColorOne = *wxRED;

/// Color to use for drawing an unknown state connection wire
const wxColour ConnectionColorUnknown = wxColour(128, 128, 128);

/// Maximum offset of Bezier control points relative to line ends
static const int BezierMaxOffset = 200;


/**
 * Constructor
 * @param game the game pin is a part of
 * @param type type of the Pin - INPUT or OUTPUT
 * @param x x coordinate
 * @param y y coordinate
 * @param state state of the pin - ONE, ZERO or UNKNOWN
 * @param len length of the line
 */
Pin::Pin(Game* game, PinType type, double x, double y, PinState state, int len) : Item(game)
{
    mGateBoundaryX = x;
    mGateBoundaryY = y;
    // Calculate pin circle position based on boundary point
    if (type == PinType::INPUT)
    {
        // Input pins are to the left of boundary
        mRelativeX = mGateBoundaryX - len;
    }
    else
    {
        // Output pin is to the right of boundary
        mRelativeX = mGateBoundaryX + len;
    }
    mRelativeY = mGateBoundaryY;
    mState = state;
    mType = type;

    mLineLength = len;
    SetLocation(-1, -1); // When the location is not -1, -1 the mouse is dragging it
}


/**
 * Function to draw the Pin
 * @param graphics gc context to draw on
 */
void Pin::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Calculate absolute positions
    double pinX = mGateX + mRelativeX;
    double pinY = mGateY + mRelativeY;
    double boundaryX = mGateX + mGateBoundaryX;
    double boundaryY = mGateY + mGateBoundaryY;

    // Draw the connection line first (from gate boundary to pin)
    auto linePath = graphics->CreatePath();

    linePath.MoveToPoint(boundaryX, boundaryY); // Start at gate boundary
    linePath.AddLineToPoint(pinX, pinY); // End at pin center

    // Set up line appearance
    if (mState == PinState::UNKNOWN)
    {
        graphics->SetPen(wxPen(ConnectionColorUnknown, LineWidth));
        graphics->SetBrush(wxBrush(ConnectionColorUnknown));
    }

    else if (mState == PinState::ONE)
    {
        graphics->SetPen(wxPen(ConnectionColorOne, LineWidth));
        graphics->SetBrush(wxBrush(ConnectionColorOne));
    }

    else if (mState == PinState::ZERO)
    {
        graphics->SetPen(wxPen(ConnectionColorZero, LineWidth));
        graphics->SetBrush(wxBrush(ConnectionColorZero));
    }
    graphics->DrawPath(linePath);

    if (mType == PinType::OUTPUT)
    {
        if (GetX() != -1 && GetY() != -1)
        {
            wxPoint p1(pinX, pinY); // Start point (output pin)
            wxPoint p4(GetX(), GetY()); // End point (mouse position while dragging)

            // Calculate offset for p2 and p3
            int distance = std::min(BezierMaxOffset, std::abs(p4.x - p1.x));

            // Set control points p2 and p3 based on distance
            wxPoint p2(p1.x + distance, p1.y); // p2 to the right of p1
            wxPoint p3(p4.x - distance, p4.y); // p3 to the left of p4

            // Create the path for the Bézier curve
            auto linePath = graphics->CreatePath();
            linePath.MoveToPoint(p1);
            linePath.AddCurveToPoint(p2, p3, p4);
            graphics->StrokePath(linePath);

            if (GetGame()->GetControlPoints())
            {
                // Draw control points as small circles
                const double crossSize = 10.0;
                const double pinTextOffset = 5.0;
                graphics->SetBrush(*wxRED_BRUSH); // Use red color for control points
                graphics->SetPen(*wxRED_PEN);
                wxGraphicsFont font = graphics->CreateFont(12, L"Arial", wxFONTFLAG_BOLD, *wxBLACK);
                graphics->SetFont(font);

                graphics->StrokeLine(p1.x - crossSize, p1.y, p1.x + crossSize, p1.y);
                graphics->StrokeLine(p1.x, p1.y - crossSize, p1.x, p1.y + crossSize);
                graphics->DrawText("p1", p1.x+pinTextOffset, p1.y+pinTextOffset);

                graphics->StrokeLine(p2.x - crossSize, p2.y, p2.x + crossSize, p2.y);
                graphics->StrokeLine(p2.x, p2.y - crossSize, p2.x, p2.y + crossSize);
                graphics->DrawText("p2", p2.x+pinTextOffset, p2.y+pinTextOffset);

                graphics->StrokeLine(p3.x - crossSize, p3.y, p3.x + crossSize, p3.y);
                graphics->StrokeLine(p3.x, p3.y - crossSize, p3.x, p3.y + crossSize);
                graphics->DrawText("p3", p3.x+pinTextOffset, p3.y+pinTextOffset);

                graphics->StrokeLine(p4.x - crossSize, p4.y, p4.x + crossSize, p4.y);
                graphics->StrokeLine(p4.x, p4.y - crossSize, p4.x, p4.y + crossSize);
                graphics->DrawText("p4", p4.x+pinTextOffset, p4.y+pinTextOffset);

                graphics->SetPen(*wxGREEN_PEN);

                // Rectangle drawing
                graphics->StrokeLine(p1.x, p1.y, p2.x, p2.y);
                graphics->StrokeLine(p1.x, p1.y, p3.x, p3.y);
                graphics->StrokeLine(p3.x, p3.y, p4.x, p4.y);
                graphics->StrokeLine(p4.x, p4.y, p2.x, p2.y);
            }
        }

        for (auto pin : mConnectedPins)
        {
            wxPoint p1(pinX, pinY);
            wxPoint p4(pin->GetAbsoluteX(), pin->GetAbsoluteY());

            int distance = std::min(BezierMaxOffset, static_cast<int>(std::abs(p4.x - p1.x)));

            wxPoint p2(p1.x + distance, p1.y);
            wxPoint p3(p4.x - distance, p4.y);

            auto linePath = graphics->CreatePath();
            linePath.MoveToPoint(p1);
            linePath.AddCurveToPoint(p2, p3, p4);
            graphics->StrokePath(linePath);

            if (GetGame()->GetControlPoints())
            {
                // Draw control points as small circles
                const double crossSize = 10.0;
                const double pinTextOffset = 5.0;
                graphics->SetBrush(*wxRED_BRUSH); // Use red color for control points
                graphics->SetPen(*wxRED_PEN);
                wxGraphicsFont font = graphics->CreateFont(12, L"Arial", wxFONTFLAG_BOLD, *wxBLACK);
                graphics->SetFont(font);

                graphics->StrokeLine(p1.x - crossSize, p1.y, p1.x + crossSize, p1.y);
                graphics->StrokeLine(p1.x, p1.y - crossSize, p1.x, p1.y + crossSize);
                graphics->DrawText("p1", p1.x+pinTextOffset, p1.y+pinTextOffset);

                graphics->StrokeLine(p2.x - crossSize, p2.y, p2.x + crossSize, p2.y);
                graphics->StrokeLine(p2.x, p2.y - crossSize, p2.x, p2.y + crossSize);
                graphics->DrawText("p2", p2.x+pinTextOffset, p2.y+pinTextOffset);

                graphics->StrokeLine(p3.x - crossSize, p3.y, p3.x + crossSize, p3.y);
                graphics->StrokeLine(p3.x, p3.y - crossSize, p3.x, p3.y + crossSize);
                graphics->DrawText("p3", p3.x+pinTextOffset, p3.y+pinTextOffset);

                graphics->StrokeLine(p4.x - crossSize, p4.y, p4.x + crossSize, p4.y);
                graphics->StrokeLine(p4.x, p4.y - crossSize, p4.x, p4.y + crossSize);
                graphics->DrawText("p4", p4.x+pinTextOffset, p4.y+pinTextOffset);

                graphics->SetPen(*wxGREEN_PEN);

                // Rectangle drawing
                graphics->StrokeLine(p1.x, p1.y, p2.x, p2.y);
                graphics->StrokeLine(p1.x, p1.y, p3.x, p3.y);
                graphics->StrokeLine(p3.x, p3.y, p4.x, p4.y);
                graphics->StrokeLine(p4.x, p4.y, p2.x, p2.y);
            }
        }
    }

    // Draw the pin circle
    auto circlePath = graphics->CreatePath();
    circlePath.AddCircle(pinX, pinY, PinSize / 2);

    // Set up circle appearance
    graphics->SetPen(wxPen(wxColor(0, 0, 0)));

    // Draw the circle
    graphics->DrawPath(circlePath);
}


/**
 * Function to set the Pin state
 * @param state the state to be set of the pin
 */
void Pin::SetState(PinState state)
{
    mState = state;
    if (mType == PinType::OUTPUT)
    {
        for (auto pin : mConnectedPins)
        {
            pin->SetState(state);
        }
    }
}

/**
 * Virtual function to test if a pin is hit at a given relative point
 * @param x Relative X coordinate of the point
 * @param y Relative Y coordinate of the point
 * @return True if the pin is hit
 */
bool Pin::HitTest(int x, int y)
{
    return abs(x - GetAbsoluteX()) < PinSize && abs(y - GetAbsoluteY()) < PinSize;
}

/**
 * Releases the pin from any dragging, setting its location to -1, -1
 */
void Pin::Release()
{
    // Does nothing if it is an input pin
    if (mType == PinType::INPUT)
    {
        return;
    }
    auto pin = GetGame()->PinHitTest(GetX(), GetY());
    // Insures that the pin is an input that connection attempt is on
    if (pin && pin->GetType() == PinType::INPUT)
    {
        pin->ClearConnectedPins();
        mConnectedPins.push_back(pin);
        auto self = shared_from_this();
        pin->AddConnectedPin(shared_from_this());
    }

    SetLocation(-1, -1);
}

/**
 * Clear any connected pins from this pin's list of connected pins
 */
void Pin::ClearConnectedPins()
{
    for (auto pin : mConnectedPins)
    {
        pin->RemoveConnectedPin(this);
    }
    mConnectedPins.clear();
}


/**
 * Function to remove all the Pins connected to
 * this Pin
 * @param pin Pointer to pin to remove all the connected pins
 */
void Pin::RemoveConnectedPin(Pin* pin)
{
    auto idx = -1;
    for (size_t i = 0; i < mConnectedPins.size(); i++)
    {
        if (mConnectedPins[i].get() == pin)
        {
            idx = i;
            break;
        }
    }
    if (idx == -1)
    {
        return;
    }
    mConnectedPins.erase(mConnectedPins.begin() + idx);
}

/**
 * Getter for absolute X position of the Pin
 * @return X coordinate of the Pin
 */
double Pin::GetAbsoluteX()
{
    return mGateX + mRelativeX;
}

/**
 * Getter for absolute Y position of the Pin
 * @return Y coordinate of the Pin
 */
double Pin::GetAbsoluteY()
{
    return mGateY + mRelativeY;
}

/**
 * Update the absolute position of the pin based on the given coordinates.
 * @param x X coordinate of the reference point
 * @param y Y coordinate of the reference point
 */
void Pin::UpdateGatePosition(double x, double y)
{
    mGateX = x;
    mGateY = y;
}


/**
 * Function to add Pin to the collection of
 * ConnectedPins for this Pin
 * @param pin Pointer to Pin
 */
void Pin::AddConnectedPin(std::shared_ptr<Pin> pin)
{
    mConnectedPins.push_back(pin);
    this->SetState(pin->GetState());
}


/**
 * Function to update all the connected Pins as per
 * state of this Pin
 */
void Pin::Update()
{
    for(auto pin : mConnectedPins)
    {
        pin->SetState(this->GetState());
    }
}
