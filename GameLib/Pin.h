/**
 * @file Pin.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * Included the class item so that this class can be derived from that
 *
 * Class for the pin item
 */

#ifndef PIN_H
#define PIN_H

#include "Item.h"

class Game;
class Gate;

/// Enum class for PinType
enum class PinType
{
    INPUT,
    OUTPUT
};

/// Enum class for the state of the Pin
enum class PinState
{
    ZERO = 0, ONE = 1, UNKNOWN = -1
};

/**
 * Class that represents the pin item
 */
class Pin : public Item, public std::enable_shared_from_this<Pin>
{
private:
    // Gate boundary reference points
    double mGateBoundaryX; ///< X coordinate where line meets gate
    double mGateBoundaryY; ///< Y coordinate where line meets gate

    /// Line with for drawing lines between pins
    static const int LineWidth = 3;

    /// Default length of line from the pin
    static const int DefaultLineLength = 20;

    /// Pin Type
    PinType mType;

    /// relative x position
    double mRelativeX;
    /// relative Y position
    double mRelativeY;

    /// state of the pin
    PinState mState = PinState::ONE;

    /// length of the line
    int mLineLength;

    /// Pointer to the Gate this pin belongs to
    Gate* mSourceGate = nullptr;

    /// Gate X coordinate
    double mGateX;
    /// Gate Y coordinate
    double mGateY;

    /// All Pins connected to this pin
    std::vector<std::shared_ptr<Pin>> mConnectedPins;

public:
    // deleting default constructors
    Pin() = delete;
    Pin(const Pin&) = delete;
    void operator=(const Pin&) = delete;

    /**
     * == Operator to compare pin states
     * @param rhs Pinstate to compare to
     * @return bool
     */
    bool operator==(PinState& rhs) { return this->GetState() == rhs; }

    // Constructor to use
    Pin(Game* game, PinType type, double boundaryX, double boundaryY, PinState state = PinState::UNKNOWN, int len = 20);

    // Draw function
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void SetState(PinState state);

    /**
    * Function to get the state of the Pin
    * @return the state of the Pin
    */
    PinState GetState() { return mState; }

    /**
     * Getter to get the Gate to which this Pin
     * belongs to
     * @return Pointer to Gate this Pin belongs to
     */
    Gate* getSourceGate() const { return mSourceGate; }

    /**
     * Function to set the source gate of
     * this Pin
     * @param gate The Gate this Pin belongs to
     */
    void setSourceGate(Gate* gate) { mSourceGate = gate; }

    /**
    * Getter for pin type
    * @return Type of the pin
    */
    PinType GetType() { return mType; };

    bool HitTest(int x, int y) override;
    void Release() override;
    void ClearConnectedPins();
    void RemoveConnectedPin(Pin* pin);
    double GetAbsoluteX();
    double GetAbsoluteY();
    void UpdateGatePosition(double x, double y);
    void AddConnectedPin(std::shared_ptr<Pin> pin);
    void Update();
};


#endif //PIN_H
