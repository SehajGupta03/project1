/**
 * @file SRFlipFlop.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "SRFlipFlop.h"

using namespace std;

/// Gap between the edge of the flip flop and the labels
const int SRFlipFlopLabelMargin = 3;

/// Gap between the top edge of the flip flop and the labels
const int SRFlipFlopLabelMarginFromTop = 10;

/// Width of the font
const int FontWidth = 15;

/// const 1/4
const double Quarter = 0.25;

/// const 35
const int ThirtyFive = 35;


/// const 40
const int Fourty = 40;

/// const 8
const int Eight = 8;


SRFlipFlop::SRFlipFlop(Game* game) : Gate(game)
{
	auto inputPin1 = make_shared<Pin>(game, PinType::INPUT, -(mSize.GetWidth()) * Quarter + Eight,
									-(mSize.GetHeight() * Quarter) + ThirtyFive);
	auto inputPin2 = make_shared<Pin>(game, PinType::INPUT, -mSize.GetWidth() * Quarter + Eight,
									mSize.GetHeight() * Quarter + Fourty);
	auto outputPin1 = make_shared<Pin>(game, PinType::OUTPUT, mSize.GetWidth(),
										-mSize.GetHeight() * Quarter + ThirtyFive, PinState::ZERO);
	auto outputPin2 = make_shared<Pin>(game, PinType::OUTPUT, mSize.GetWidth(),
										mSize.GetHeight() * Quarter + Fourty, PinState::ONE);

	mPins.push_back(inputPin1);
	mPins.push_back(inputPin2);
	mPins.push_back(outputPin1);
	mPins.push_back(outputPin2);
}



/**
 * The Draw function for the SR Flip Flop
 * @param gc the graphics context to draw on
 */
void SRFlipFlop::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
	gc->SetPen(*wxBLACK_PEN); ///> Setting the pen color

	gc->SetBrush(*wxWHITE_BRUSH);

	///> Font to be used on the gate
	auto font = gc->CreateFont(15, L"Arial", wxFONTFLAG_BOLD, *wxBLACK);
	gc->SetFont(font);

 ///> Location and size
 /// adjust x and y postions so they are in the middle of the gate
 auto x = GetX()-25;
 auto y = GetY()-37;
 auto w = GetSize().GetWidth();
 auto h = GetSize().GetHeight();

	///> Draw the flip flop rectangle
	gc->DrawRectangle(x, y, w, h);

	gc->DrawText("S", x + SRFlipFlopLabelMargin, y + SRFlipFlopLabelMarginFromTop); ///> S Text
	gc->DrawText("Q", x + w - FontWidth - SRFlipFlopLabelMargin, y + SRFlipFlopLabelMarginFromTop); ///> Q text
	gc->DrawText("R", x + SRFlipFlopLabelMargin, y + h - FontWidth - SRFlipFlopLabelMarginFromTop); ///> R text
	gc->DrawText("Q'", x + w - FontWidth - SRFlipFlopLabelMargin,
				y + h - FontWidth - SRFlipFlopLabelMarginFromTop); ///> Q' Text

	for (auto pin : mPins)
	{
		pin->Draw(gc);
	}
}

/**
 * Decides the output state of the gate
 */
void SRFlipFlop::calculate()
{
	vector<shared_ptr<Pin>> InputPins = GetInputPins();
	vector<shared_ptr<Pin>> OutputPins = GetOutputPins();

	if (InputPins.size() > 0 && InputPins[0] && InputPins[1]){
		PinState S = InputPins[1]->GetState();
		PinState R = InputPins[0]->GetState();

		shared_ptr<Pin> Output_Q = OutputPins[1];
		shared_ptr<Pin> Output_Q_Bar = OutputPins[0];

		// SR Flip-Flop truth table logic
	    if (S == PinState::ONE && R == PinState::ONE)
	    {
	        // Invalid state (typically not allowed in SR flip-flops)
	        SetOutput(Output_Q, PinState::UNKNOWN);
	        SetOutput(Output_Q_Bar, PinState::UNKNOWN);
	    }
		else if (R == PinState::ONE)
		{
			// Reset the flip-flop
			SetOutput(Output_Q, PinState::ZERO);
			SetOutput(Output_Q_Bar, PinState::ONE);
		}
		else if (S == PinState::ONE)
		{
			// Set the flip-flop
			SetOutput(Output_Q, PinState::ONE);
			SetOutput(Output_Q_Bar, PinState::ZERO);
		}
	}
}

/**
 * Updates the SR Flip Flop gate, adjusting the absolute positions of its pins.
 *
 * @param elapsed The time elapsed since the last update
 */
void SRFlipFlop::Update(double elapsed)
{
    Gate::Update(elapsed);
    for (auto pin : mPins)
    {
        pin->UpdateGatePosition(GetX()-25, GetY()-37);
    }
}
