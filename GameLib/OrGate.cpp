/**
 * @file OrGate.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "OrGate.h"

#include "Pin.h"

using namespace std;

/// const half
const double Half = 0.5;

/// Const quarter
const double Quarter = 0.25;

/// const 7.1
const double WidthConst = 7.1;

/// const 35.8
const double WidthConst2 = 35.8;

OrGate::OrGate(Game* game) : Gate(game)
{
	auto inputpin1 = make_shared<Pin>(game, PinType::INPUT, -mSize.GetWidth() * Half + WidthConst,
									-mSize.GetHeight() * Quarter);
	auto inputpin2 = make_shared<Pin>(game, PinType::INPUT, -mSize.GetWidth() * Half + WidthConst,
									mSize.GetHeight() * Quarter);
	auto outputpin2 = make_shared<Pin>(game, PinType::OUTPUT, mSize.GetWidth() - WidthConst2, 0);

	mPins.push_back(inputpin1);
	mPins.push_back(inputpin2);
	mPins.push_back(outputpin2);
}


/**
 * Function to draw Or gate
 * @param graphics graphics to use
 */
void OrGate::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	// Create a path to draw the gate shape
	auto path = graphics->CreatePath();

	// The  location and size
	auto x = GetX();
	auto y = GetY();
	auto w = GetSize().GetWidth();
	auto h = GetSize().GetHeight();

	// The three corner points of an OR gate
	wxPoint2DDouble p1(x - (w * Half), y + (h * Half)); // Bottom left
	wxPoint2DDouble p2(x + (w * Half), y); // Center right
	wxPoint2DDouble p3(x - (w * Half), y - (h * Half)); // Top left

	// Control points used to create the Bézier curves
	auto controlPointOffset1 = wxPoint2DDouble(w * Half, 0);
	auto controlPointOffset2 = wxPoint2DDouble(w * 0.75, 0);
	auto controlPointOffset3 = wxPoint2DDouble(w * 0.2, 0);

	// Create the path for the gate
	path.MoveToPoint(p1);
	path.AddCurveToPoint(p1 + controlPointOffset1, p1 + controlPointOffset2, p2);
	path.AddCurveToPoint(p3 + controlPointOffset2, p3 + controlPointOffset1, p3);
	path.AddCurveToPoint(p3 + controlPointOffset3, p1 + controlPointOffset3, p1);
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
void OrGate::calculate()
{
	vector<shared_ptr<Pin>> InputPins = GetInputPins();
	vector<shared_ptr<Pin>> OutputPins = GetOutputPins();

	if (InputPins.size() > 0 && InputPins[0] && InputPins[1])
	{
		PinState A = InputPins[0]->GetState();
		PinState B = InputPins[1]->GetState();

		shared_ptr<Pin> OutputPin = OutputPins[0];

		if (A == PinState::UNKNOWN || B == PinState::UNKNOWN)
		{
			// Unknowns
			SetOutput(OutputPin, PinState::UNKNOWN);
		}
		else if (A == PinState::ONE || B == PinState::ONE)
		{
			// True
			SetOutput(OutputPin, PinState::ONE);
		}
		else if (A == PinState::ZERO && B == PinState::ZERO)
		{
			// False
			SetOutput(OutputPin, PinState::ZERO);
		}
		else
		{
			// Default
			SetOutput(OutputPin, PinState::UNKNOWN);
		}
	}
}
