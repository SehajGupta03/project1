/**
 * @file Gate.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * Including item.h to make this class derive from the item class
 *
 * Class for the gate item
 */

#ifndef GATE_H
#define GATE_H

#include "Item.h"
#include "Pin.h"
#include <vector>

/// Define the states of the gates
enum GateState { LOW = 0, HIGH = 1, UNKNOWN = -1, INVALID = -2 };


class Game;

/**
 * This class represents the gate used in the game
 * Derived from item class
 */
class Gate : public Item
{
private:
    /// The Game that these gates are contained in
    Game* mGame;

protected:
    /// Vector of the Pins of a gate
    std::vector<std::shared_ptr<Pin>> mPins;

public:
    /**
    * Constructor
    * @param game the game object
    */
    Gate(Game* game) : Item(game)
    {
    };


    bool HitTest(int x, int y) override;

    /**
    * pure virtual for size
    * @return wxSize object holding size info of gate
    */
    virtual const wxSize GetSize() = 0;


    std::vector<std::shared_ptr<Pin>> GetInputPins();

    std::vector<std::shared_ptr<Pin>> GetOutputPins();

    virtual void SetOutput(std::shared_ptr<Pin>& pin, PinState state);

    /**
     * Getter for the pins of the gate
     * @return Vector of Pins
     */
    std::vector<std::shared_ptr<Pin>> GetPins() { return mPins; }

    /**
     * Getter for gate pointer
     * @return Gate pointer
     */
    Gate* AsGate() override { return this; }

    /**
     * Calculates the output of a gate
     */
    virtual void calculate() = 0;

    std::shared_ptr<Pin> PinHitTest(int x, int y) override;
    void Update(double elapsed) override;
};


#endif //GATE_H
