/**
 * @file Gate.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "Gate.h"

using namespace std;

/**
 *
 * @param x x coordinate of mouse click
 * @param y y coordinate of mouse click
 * @return
 */
bool Gate::HitTest(int x, int y)
{
    // Implement hit test logic for Gate
    double width = GetSize().GetWidth();
    double height = GetSize().GetHeight();

    double testX = x - GetX();
    double testY = y - GetY();
    return (abs(testX) <= width / 2 && abs(testY) <= height / 2);
}

/**
 * Getter for input pins only
 * @return input pins for the gate
 */
std::vector<std::shared_ptr<Pin>> Gate::GetInputPins()
{
    std::vector<std::shared_ptr<Pin>> inputPins;
    for (const auto pin : mPins)
    {
        if (pin->GetType() == PinType::INPUT)
        {
            inputPins.push_back(pin);
        }
    }
    return inputPins;
}

/**
 * Getter for output pin only
 * @return output pin for the gate
 */
std::vector<std::shared_ptr<Pin>> Gate::GetOutputPins()
{
    std::vector<std::shared_ptr<Pin>> outputPins;
    for (const auto pin : mPins)
    {
        if (pin->GetType() == PinType::OUTPUT)
        {
            outputPins.push_back(pin);
        }
    }
    return outputPins;
}

/**
 * Setter for output Pin
 * @param pin The Pin to set
 * @param state The State for Output
 */
void Gate::SetOutput(shared_ptr<Pin>& pin, PinState state)
{
    if (pin)
    {
        pin->SetState(state);
    }
}

/**
* Virtual function to test if a pin is hit at a given point
* @param x X coordinate of the point
* @param y Y coordinate of the point
* @return Pointer to the pin if it is hit, nullptr otherwise
*/
std::shared_ptr<Pin> Gate::PinHitTest(int x, int y)
{
    for (const auto pin : mPins)
    {
        if (pin->HitTest(x, y))
        {
            return pin;
        }
    }
    return nullptr;
}

/**
 * Updates the absolute positions of all pins in this gate
 * @param elapsed time since last update
 */
void Gate::Update(double elapsed)
{
    this->calculate();
    for (auto pin : mPins)
    {
        pin->UpdateGatePosition(GetX(), GetY());
        if(pin->GetType() ==PinType::OUTPUT)
        {
            pin->Update();
        }
    }
}
