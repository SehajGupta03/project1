/**
 * @file SRFlipFlop.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * Including the gate class so this class can be derived from it
 *
 * This is a class that represents the SR Flip Flop Gate
 */

#ifndef SRFLIPFLOP_H
#define SRFLIPFLOP_H

#include "Gate.h"
#include "Pin.h"

/**
 * This class represents the SR Flip Flop Gate
 */


class SRFlipFlop : public Gate
{
private:
	/// size of the gate
	const wxSize mSize = wxSize(50, 75);

	/// Vector of Pins
	//std::vector<std::shared_ptr<Pin>> mPins;

public:
	SRFlipFlop() = delete;
	SRFlipFlop(const SRFlipFlop&) = delete;
	void operator=(const SRFlipFlop&) = delete;

	/**
	* Constructor
	* @param game instance of the game where this gate is located
	*/
	SRFlipFlop(Game* game);

	void Draw(std::shared_ptr<wxGraphicsContext> gc) override;

	void calculate() override;

	/**
	* Getter function for the size of the gate
	* @return size of the gate
	*/
	const wxSize GetSize() override { return mSize; }
    void Update(double elapsed) override;
};


#endif //SRFLIPFLOP_H
