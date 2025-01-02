/**
 * @file OrGate.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 *
 */

#ifndef ORGATE_H
#define ORGATE_H
#include "Gate.h"
#include "Item.h"
#include "Pin.h"

/**
 * class for or gate inherits from gate
 */
class OrGate : public Gate
{
private:
	/// Size of the Or gate in pixels
	const wxSize mSize = wxSize(75, 50);

	/// Vector to hold 3 pins of And Gate
	//std::vector<std::shared_ptr<Pin>> mPins;

public:
	// deleting default constructors
	OrGate() = delete;
	OrGate(const OrGate& gate) = delete;
	void operator=(const OrGate& gate) = delete;

	/**
	* constructor for not gate
	* @param game object of which the gate belongs to
	*/
	OrGate(Game* game);
	void Draw(std::shared_ptr<wxGraphicsContext> gc) override;

	void calculate() override;

	/**
	* virtual function to get size of gate
	* @return size of gate
	*/
	const wxSize GetSize() override { return mSize; }

};


#endif //ORGATE_H
