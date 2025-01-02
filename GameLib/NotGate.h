/**
 * @file NotGate.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 *
 */

#ifndef NOTGATE_H
#define NOTGATE_H
#include "Gate.h"
#include "Item.h"
#include "Pin.h"

/**
 * class for not gate, inherits from gate
 */
class NotGate : public Gate
{
private:
	/// member for size of gate
	const wxSize mSize = wxSize(50, 50);

	/// Pins
	//std::vector<std::shared_ptr<Pin>> mPins;

public:
	NotGate() = delete;
	NotGate(const NotGate& gate) = delete;
	void operator=(const NotGate& gate) = delete;

	/**
	* constructor for not gate
	* @param game object of which the gate belongs to
	*/
	NotGate(Game* game);
	void Draw(std::shared_ptr<wxGraphicsContext> gc) override;

	void calculate() override;

	/**
	* virtual function to get size of gate
	* @return size of gate
	*/
	const wxSize GetSize() override { return mSize; };

};


#endif //NOTGATE_H
