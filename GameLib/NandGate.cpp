/**
 * @file NandGate.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */
#include "pch.h"
#include "NandGate.h"

using namespace std;


/// How far the Bezier control points are for the AND
/// gate to the right of ends of the curve as a percentage
/// of the gate height.
const double AndGateControlPointOffset = 0.75;

/// const 0.5
const double Half = 0.5;

/// const 0.25
const double Quarter = 0.25;

/// const 2
const int Two = 2;


NandGate::NandGate(Game* game) : Gate(game)
{
	auto inputPin1 = make_shared<Pin>(game, PinType::INPUT, -mSize.GetWidth() * Half,
									-mSize.GetHeight() * Quarter);
	auto inputPin2 = make_shared<Pin>(game, PinType::INPUT, -mSize.GetWidth() * Half,
									mSize.GetHeight() * Quarter);
	auto outputPin1 = make_shared<Pin>(game, PinType::OUTPUT, mSize.GetWidth(), 0);

	mPins.push_back(inputPin1);
	mPins.push_back(inputPin2);
	mPins.push_back(outputPin1);
}


/**
 * Function to draw And gate
 * @param graphics graphics to use
 */
void NandGate::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	// Create a path to draw the gate shape
	auto path = graphics->CreatePath();

	// The the location and size
	auto x = GetX();
	auto y = GetY();
	auto w = GetSize().GetWidth();
	auto h = GetSize().GetHeight();

	// Draw the rectangular base first
	path.MoveToPoint(x - w * Half, y + h * Half); // Start bottom left
	path.AddLineToPoint(x - w * Half, y - h * Half); // Left vertical line
	path.AddLineToPoint(x + w * Half, y - h * Half); // Top horizontal line

	// Add the arc on the right side
	path.AddArc(x + w * Half, // x center of arc
				y, // y center of arc
				h * Half, // radius
				-M_PI * Half, // start angle (-90 degrees)
				M_PI * Half, // end angle (90 degrees)
				true); // clockwise

	// Complete the shape by returning to start
	path.AddLineToPoint(x - w * Half, y + h * Half); // Bottom line back to start

	// Control points used to create the Bezier curves
	auto controlPointOffset1 = wxPoint2DDouble(h * Half, 0);
	auto controlPointOffset2 = wxPoint2DDouble(h * 0.75, 0);
	auto controlPointOffset3 = wxPoint2DDouble(h * 0.2, 0);

	path.CloseSubpath();

	// Draw the path
	graphics->SetPen(*wxBLACK_PEN);
	graphics->SetBrush(*wxWHITE_BRUSH);
	graphics->DrawPath(path);

	double circleRadius = 5; // Adjust the size of the circle
	graphics->SetBrush(*wxWHITE_BRUSH); // Fill with white
	graphics->DrawEllipse(x + (w * Half) + (h * Half), y - circleRadius, circleRadius * Two, circleRadius * Two);

	// drawing pins
	for (auto pin : mPins)
	{
		pin->Draw(graphics);
	}
}


/**
 * Decides the output state of the gate
 */
void NandGate::calculate()
{
	vector<shared_ptr<Pin>> InputPins = GetInputPins();
	vector<shared_ptr<Pin>> OutputPins = GetOutputPins();

	if (InputPins.size() > 0 && InputPins[0] && InputPins[1])
	{
		PinState A = InputPins[0]->GetState();
		PinState B = InputPins[1]->GetState();

		shared_ptr<Pin> OutputPin = OutputPins[0];

		if (A <= PinState::UNKNOWN || B <= PinState::UNKNOWN || A > PinState::ONE || B > PinState::ONE)
		{
			SetOutput(OutputPin,PinState::UNKNOWN);
		}

		else if (A == PinState::ONE && B == PinState::ONE)
		{
			SetOutput(OutputPin,PinState::ZERO);
		}

		else if (A == PinState::ZERO || B == PinState::ZERO)
		{
			SetOutput(OutputPin,PinState::ONE);
		}

		else
		{
			SetOutput(OutputPin,PinState::UNKNOWN);
		}
	}
}
