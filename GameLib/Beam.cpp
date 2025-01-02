/**
 * @file Beam.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "Beam.h"
#include "Game.h"
#include "ProductVisitor.h"


using namespace std;

/// boundaryX constant for the pin
const int XConstant = 20;

/// zero constant
const int Zero = 0;

/// Length for the pin wire
const int Len = 80;

/// Color for laser 1
const wxColour laser1_colour = wxColour(255, 200, 200, 100);
/// Color for laser 2
const wxColour laser2_colour =wxColour(255, 0, 0, 175);
/// Offset for product detection
const int YOffset = 5;

/**
 * Constructor
 * @param game the game this item is a part of
 */
Beam::Beam(Game* game) : Item(game)
{
	mLeftSideRed = std::make_shared<wxImage>(BeamRedImage);
	mLeftSideGreen = std::make_shared<wxImage>(BeamGreenImage);

	// Mirror for the other side
	mRightSideRed = std::make_shared<wxImage>(mLeftSideRed->Mirror(true));
	mRightSideGreen = std::make_shared<wxImage>(mLeftSideGreen->Mirror(true));

	mPin = make_shared<Pin>(game, PinType::OUTPUT, XConstant, Zero, PinState::ZERO , Len);

}


/**
 * Function to load data from XML file
 * @param node The Xml node we are loading the item from
 */
void Beam::XmlLoad(wxXmlNode* node)
{
	Item::XmlLoad(node);

	// storing the sender value
	node->GetAttribute(L"sender", L"0").ToInt(&mSender);

}

/**
 * Draw function for the beam
 * @param graphics the graphics pointer
 */
void Beam::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	// Get beam's center position from Item (set during XmlLoad)
	double x = GetX();
	double y = GetY();

	// Dimensions of the left side image
	double beamWidth = mLeftSideRed->GetWidth();
	double beamHeight = mLeftSideRed->GetHeight();

	// Calculate X positions for left and right sides using sender offset
	double beamLeftX = x - beamWidth / 2 + mSender;
	double beamRightX = x + beamWidth + mBeamLength + mSender;

	// Vertically center the beam
	double beamY = y - beamHeight / 2;

	// for the laser in the middle
	double leftCenterX = beamLeftX + beamWidth / 2;
	double rightCenterX = beamRightX + beamWidth / 2;
	double beamCenterY = beamY + beamHeight / 2;

	// Drawing the laser
	wxPen laser1(laser1_colour, 8);
	wxPen laser2(laser2_colour, 4);


	graphics->SetPen(laser1);
	graphics->StrokeLine(leftCenterX, beamCenterY, rightCenterX, beamCenterY);
	graphics->SetPen(laser2);
	graphics->StrokeLine(leftCenterX, beamCenterY, rightCenterX, beamCenterY);


	// Drawing the images
	if (!mBeamCrossed) {
		// Left side
		graphics->DrawBitmap(*mLeftSideGreen, beamLeftX, beamY, beamWidth, beamHeight);
		// Right side
		graphics->DrawBitmap(*mRightSideGreen, beamRightX, beamY, beamWidth, beamHeight);
	} else {
		// Left side
		graphics->DrawBitmap(*mLeftSideRed, beamLeftX, beamY, beamWidth, beamHeight);
		// Right side
		graphics->DrawBitmap(*mRightSideRed, beamRightX, beamY, beamWidth, beamHeight);
	}

	mPin->Draw(graphics);
}

/**
 * Updater for beam
 * @param elapsed time since last update
 */
void Beam::Update(double elapsed)
{
	double x = GetX();
	double y = GetY();

	// Dimensions of the left side image
	double beamWidth = mLeftSideRed->GetWidth();

	// Calculate the center position for detection, as done in Draw
	double beamLeftX = x - beamWidth / 2 + mSender;
	double beamRightX = x + beamWidth + mBeamLength + mSender;
	double beamCenterX = (beamLeftX + beamRightX) / 2;
	double beamCenterY = y;

	ProductVisitor visitor(beamCenterY + YOffset, beamCenterX);
	GetGame()->Accept(&visitor);

	mBeamCrossed = !visitor.GetProducts().empty();

	if (mBeamCrossed)
	{
		mPin->SetState(PinState::ONE);
	}
	else
	{
		mPin->SetState(PinState::ZERO);
	}
    mPin->UpdateGatePosition(GetX(), GetY());
	mPin->Update();

}


/**
 * Function to get the pin at (x,y) if found,
 * nullptr otherwise
 * @param x X coordinate
 * @param y Y coordinate
 * @return Pointer to Pin object if found at (x,y),
 * nullptr otherwise
 */
std::shared_ptr<Pin> Beam::PinHitTest(int x, int y)
{
    if (mPin->HitTest(x, y))
    {
        return mPin;
    }

    return nullptr;
}