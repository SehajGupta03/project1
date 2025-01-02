/**
 * @file AndGate.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "AndGate.h"


using namespace std;


/// How far the Bezier control points are for the AND
/// gate to the right of ends of the curve as a percentage
/// of the gate height.
const double AndGateControlPointOffset = 0.75;

/// Input pin width constant
const double WidthConstant = 0.5;

/// Height constant
const double HeightConstant = 0.25;

/// Zero constant
const int Zero = 0;


AndGate::AndGate(Game* game) : Gate(game)
{
	auto inputPin1 = make_shared<Pin>(game, PinType::INPUT, -mSize.GetWidth() * WidthConstant,
									-mSize.GetHeight() * HeightConstant);
	auto inputPin2 = make_shared<Pin>(game, PinType::INPUT, -mSize.GetWidth() * WidthConstant,
									mSize.GetHeight() * HeightConstant);
	auto outputPin1 = make_shared<Pin>(game, PinType::OUTPUT, mSize.GetWidth(), Zero);

	mPins.push_back(inputPin1);
	mPins.push_back(inputPin2);
	mPins.push_back(outputPin1);

}


/**
 * Function to draw And gate
 * @param graphics graphics to use
 */
void AndGate::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	// Create a path to draw the gate shape
	auto path = graphics->CreatePath();

	// The location and size
	auto x = GetX();
	auto y = GetY();
	auto w = GetSize().GetWidth();
	auto h = GetSize().GetHeight();

	// Draw the rectangular base first
	path.MoveToPoint(x - w / 2, y + h / 2); // Start bottom left
	path.AddLineToPoint(x - w / 2, y - h / 2); // Left vertical line
	path.AddLineToPoint(x + w / 2, y - h / 2); // Top horizontal line

	// Add the arc on the right side
	path.AddArc(x + w / 2, // x center of arc
				y, // y center of arc
				h / 2, // radius
				-M_PI / 2, // start angle (-90 degrees)
				M_PI / 2, // end angle (90 degrees)
				true); // clockwise

	// Complete the shape by returning to start
	path.AddLineToPoint(x - w / 2, y + h / 2); // Bottom line back to start

	// Control points used to create the Bézier curves
	auto controlPointOffset1 = wxPoint2DDouble(h * 0.5, 0);
	auto controlPointOffset2 = wxPoint2DDouble(h * 0.75, 0);
	auto controlPointOffset3 = wxPoint2DDouble(h * 0.2, 0);

	path.CloseSubpath();

	// Draw the path
	graphics->SetPen(*wxBLACK_PEN);
	graphics->SetBrush(*wxWHITE_BRUSH);
	graphics->DrawPath(path);


	for (auto pin : mPins)
	{
		pin->Draw(graphics);
	}
}


/**
 * Decides the output state of the gate
 */
void AndGate::calculate()
{
	vector<shared_ptr<Pin>> inputPins = GetInputPins();


	if (inputPins.size() >= 2 && inputPins[0] && inputPins[1])
	{
		PinState A = inputPins[0]->GetState();
		PinState B = inputPins[1]->GetState();
		shared_ptr<Pin> outputPin = GetOutputPins()[0];

		if (A == PinState::UNKNOWN || B == PinState::UNKNOWN)
		{
			SetOutput(outputPin, PinState::UNKNOWN);
		}
		else if (A == PinState::ONE && B == PinState::ONE)
		{
			SetOutput(outputPin, PinState::ONE);
		}
		else
		{
			SetOutput(outputPin, PinState::ZERO);
		}
	}
}