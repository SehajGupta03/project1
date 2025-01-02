/**
 * @file NandGate.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 *
 */

#ifndef NandGate_H
#define NandGate_H

#include "Gate.h"
#include "Pin.h"

/**
 * Nand gate class, inherits from gate
 */
class NandGate : public Gate
{
private:
	/// Size of the NAND gate in pixels
	const wxSize mSize = wxSize(75, 50);

	/// The output variable that stores the output value of the gate
	int mOutput = GateState(UNKNOWN);

	/// vector to store pins
	//std::vector<std::shared_ptr<Pin>> mPins;

public:
	// deleting default constructors
	NandGate() = delete;
	NandGate(const NandGate&) = delete;
	void operator=(const NandGate&) = delete;

	/**
	* constructor for nand gate
	* @param game object of which the gate belongs to
	*/
	NandGate(Game* game);

	/// Function to draw the gate
	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

	/// Function to calculate the output value of the gate
	void calculate() override;

	/**
	* virtual function to get size of gate
	* @return size of gate
	*/
	const wxSize GetSize() override { return mSize; };


};


#endif //NNandGate_H
