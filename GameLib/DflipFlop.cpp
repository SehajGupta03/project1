/**
 * @file DflipFlop.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "DflipFlop.h"


using namespace std;


/// Gap between the edge of the flip flop and the labels
const int DFlipFlopLabelMargin = 3;

/// Gap between the top edge of the flip flop and the labels
const int DFlipFlopLabelMarginFromTop = 10;

/// Width of the font
const int FontWidth = 15;

/// How large the clock input triagle is in pixels width and height
const int DFlipFlopClockSize = 10;

/// boundaryX contant for the inputpin 1
const double Input = 0.2;

/// constant to add to boundaryX
const double Input1Const = 7.7;

/// constant to add to boundaryX for second pin
const double Input2Const = 7;

/// Constant to multiply the height by 4
const double Mul4 = 0.25;

/// constant 35 to add to height of pins
const int Add35 = 35;

/// Constant 42 to add to the height of the pins
const int Add42 = 42;

DflipFlop::DflipFlop(Game* game) : Gate(game)
{
	auto inputPin1 = make_shared<Pin>(game, PinType::INPUT, -(mSize.GetWidth() * Input) + Input1Const,
									-(mSize.GetHeight() * Mul4) + Add35);
	auto inputPin2 = make_shared<Pin>(game, PinType::INPUT, -mSize.GetWidth() * Input + Input2Const,
									mSize.GetHeight() * Mul4 + Add42);
	auto outputPin1 = make_shared<Pin>(game, PinType::OUTPUT, mSize.GetWidth(),
										-mSize.GetHeight() * Mul4 + Add35, PinState::ZERO);
	auto outputPin2 = make_shared<Pin>(game, PinType::OUTPUT, mSize.GetWidth(),
										mSize.GetHeight() * Mul4 + Add42, PinState::ONE);

	mPins.push_back(inputPin1);
	mPins.push_back(inputPin2);
	mPins.push_back(outputPin1);
	mPins.push_back(outputPin2);
}


/**
 * The draw function for the D Flip Flop
 * @param gc The device context to draw on
 */
void DflipFlop::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
	gc->SetPen(*wxBLACK_PEN); ///> Setting the pen color

	gc->SetBrush(*wxWHITE_BRUSH);

	///> Font to be used on the gate
	auto font = gc->CreateFont(15, L"Arial", wxFONTFLAG_BOLD, *wxBLACK);
	gc->SetFont(font);

	///> Location and size
	/// addjust the drawing to match hit box
	auto x = GetX() - 25;
	auto y = GetY() - 37;
	auto w = GetSize().GetWidth();
	auto h = GetSize().GetHeight();

	///> Draw the flip flop rectangle
	gc->DrawRectangle(x, y, w, h);

	gc->DrawText("D", x + DFlipFlopLabelMargin, y + DFlipFlopLabelMarginFromTop); ///> D Text
	gc->DrawText("Q", x + w - FontWidth - DFlipFlopLabelMargin, y + DFlipFlopLabelMarginFromTop); ///> Q text
	gc->DrawText("Q'", x + w - FontWidth - DFlipFlopLabelMargin,
				y + h - FontWidth - DFlipFlopLabelMarginFromTop); ///> Q' Text

	// Draw the clock input triangle
	wxPoint2DDouble clockPoints[3] = {
		wxPoint2DDouble(x, y + h - DFlipFlopClockSize - DFlipFlopLabelMarginFromTop),
		wxPoint2DDouble(x + DFlipFlopClockSize, y + h - DFlipFlopClockSize / 2 - DFlipFlopLabelMarginFromTop),
		wxPoint2DDouble(x, y + h - DFlipFlopLabelMarginFromTop)
	};
	gc->DrawLines(3, clockPoints); ///> Draws the lines that connects the three points leading to a triangle

	for (auto pin : mPins)
	{
		// adjust drawing to match the rectangle
		pin->Draw(gc);
	}
}

/**
 * Decides the output state of the gate
 */
void DflipFlop::calculate()
{
	vector<shared_ptr<Pin>> InputPins = GetInputPins();
	vector<shared_ptr<Pin>> OutputPins = GetOutputPins();

	if (InputPins.size() > 1 && InputPins[0] && InputPins[1] &&
		OutputPins.size() > 1 && OutputPins[0] && OutputPins[1])
	{

		PinState D = InputPins[0]->GetState();
		PinState Clk = InputPins[1]->GetState();

		shared_ptr<Pin> Output_Q = OutputPins[0];
		shared_ptr<Pin> Output_Q_Bar = OutputPins[1];

		PinState tempQState = D;
		PinState tempQBarState = (D == PinState::ONE) ? PinState::ZERO : PinState::ONE;


		if (mPrevClkState == PinState::ZERO && Clk == PinState::ONE)
		{
			mLastQState = tempQState;
			mLastQBarState = tempQBarState;
		}

		SetOutput(Output_Q, mLastQState);
		SetOutput(Output_Q_Bar, mLastQBarState);

		mPrevClkState = Clk;
	}
}


/**
 * Updates the D Flip Flop gate, adjusting the absolute positions of its pins.
 *
 * @param elapsed The time elapsed since the last update
 */
void DflipFlop::Update(double elapsed)
{
	Gate::Update(elapsed);
	for (auto pin : mPins)
	{
		pin->UpdateGatePosition(GetX() - 25, GetY() - 37);
	}
}
