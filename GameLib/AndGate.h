/**
 * @file AndGate.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * class that represents and gate
 */

#ifndef ANDGATE_H
#define ANDGATE_H
#include "Gate.h"
#include "Pin.h"


/**
 * class that represents and gate
 * Inherits from Gate class
 */
class AndGate : public Gate
{
private:
	 /// Size of the AND gate in pixels
	 const wxSize mSize =  wxSize (55, 50);

	 /// Vector to hold 3 pins of And Gate
	 //std::vector<std::shared_ptr<Pin>> mPins;

public:
	 // deleting default constructors
	 AndGate() = delete;
	 AndGate(const AndGate &) = delete;
	 void operator=(const AndGate &) = delete;

	 /**
	  * constructor for and gate
	  * @param game object of which the gate belongs to
	  */
	 AndGate(Game *game);

	// Function to draw the gate
	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
	/**
	* virtual function to get size of gate
	* @return size of gate
	*/
	const wxSize GetSize() override { return mSize; };

	void calculate() override;

	//std::vector<std::shared_ptr<Pin>> GetPins() {return mPins;}


};


#endif //ANDGATE_H
