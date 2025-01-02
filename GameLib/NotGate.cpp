/**
 * @file NotGate.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */
#include "pch.h"
#include "NotGate.h"

using namespace std;
/// Size of the Not gate in pixels


/// Const half
const double Half = 0.5;

/// Const 12.8
const double WidthConst = 12.8;


NotGate::NotGate(Game* game) : Gate(game)
{
	auto inputPin1 = make_shared<Pin>(game, PinType::INPUT, -mSize.GetWidth() * Half, 0);
	auto outputPin1 = make_shared<Pin>(game, PinType::OUTPUT, mSize.GetWidth() - WidthConst, 0);

	mPins.push_back(inputPin1);
	mPins.push_back(outputPin1);
}


/**
 * Draw the not gate
 * @param graphics graphics context pointer
 */
void NotGate::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	// Create a path to draw the gate shape
	auto path = graphics->CreatePath();

	// The location and size
	auto x = GetX();
	auto y = GetY();
	auto w = GetSize().GetWidth();
	auto h = GetSize().GetHeight();

	// The three corner points of Not gate

	wxPoint2DDouble p1(x + (w * Half), y);
	wxPoint2DDouble p2(x - (w * Half), y + (h * Half));
	wxPoint2DDouble p3(x - (w * Half), y - (h * Half));

	// Create the path for the triangle
	path.MoveToPoint(p1);
	path.AddLineToPoint(p2);
	path.AddLineToPoint(p3);
	path.AddLineToPoint(p1);
	path.CloseSubpath();

	// Draw the path
	graphics->SetPen(*wxBLACK_PEN);
	graphics->SetBrush(*wxWHITE_BRUSH);
	graphics->DrawPath(path);

	double circleRadius = 5; // Adjust the size of the circle
	graphics->SetBrush(*wxWHITE_BRUSH); // Fill with white
	graphics->DrawEllipse(p1.m_x, p1.m_y - circleRadius, circleRadius * 2, circleRadius * 2);

	for (auto pin : mPins)
	{
		pin->Draw(graphics);
	}
}

/**
 * Decides the output state of the gate
 */
void NotGate::calculate()
{
	vector<shared_ptr<Pin>> InputPins = GetInputPins();

	if (InputPins.size() > 0 && InputPins[0])
	{
		PinState A = InputPins[0]->GetState();

		shared_ptr<Pin> OutputPin = GetOutputPins()[0];

		if (A == PinState::ZERO)
		{
			SetOutput(OutputPin, PinState::ONE);
		}
		else if (A == PinState::ONE)
		{
			SetOutput(OutputPin, PinState::ZERO);
		}
		else
		{
			SetOutput(OutputPin, PinState::UNKNOWN);
		}
	}
}
