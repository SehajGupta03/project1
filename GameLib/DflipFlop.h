/**
 * @file DflipFlop.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * Including the gate class so this class can be derived from it
 *
 * This is a class that represents the D Flip Flop Gate
 */

#ifndef DFLIPFLOP_H
#define DFLIPFLOP_H
#include "Gate.h"
#include "Pin.h"


/**
 * This class represents the D Flip Flop Gate
 */
class DflipFlop : public Gate
{
private:
	/// size of the gate
	const wxSize mSize = wxSize(50, 75);

	/// state of the Pin on last click
	PinState mPrevClkState = PinState::ZERO;

	/// State of Q the last time clock was high
	PinState mLastQState = PinState::ZERO;

	/// state of Q! last time clock was high
	PinState mLastQBarState = PinState::ONE;

public:
	DflipFlop() = delete;
	DflipFlop(const DflipFlop& gate) = delete;
	void operator=(const DflipFlop& gate) = delete;

	/**
	* Constructor
	* @param game instance of game where this gate is located
	*/
	DflipFlop(Game* game);

	void Draw(std::shared_ptr<wxGraphicsContext> gc) override;


	/**
	* Getter function that returns the size of the gate
	* @return Size of the gate
	*/
	const wxSize GetSize() override { return mSize; };

	void calculate() override;
	void Update(double elapsed) override;
};


#endif //DFLIPFLOP_H
