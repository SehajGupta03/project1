/**
 * @file DFlipFlopTest.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include <pch.h>
#include <gtest/gtest.h>
#include <DflipFlop.h>
#include <Game.h>
#include <memory>
#include <Gate.h>

using namespace std;

class DflipFlopTest : public ::testing::Test
{
protected:
    Game mGame;
    std::shared_ptr<DflipFlop> gate;

    void SetUp() override
    {
        gate = make_shared<DflipFlop>(&mGame);
        mGame.Add(gate);
    }
};

// Test when D is 1 and clock goes from 0 to 1
TEST_F(DflipFlopTest, SetOnClockRise)
{
    auto input = gate->GetInputPins();
    auto output = gate->GetOutputPins();

    input[0]->SetState(PinState::ONE);   // Set D to 1
    input[1]->SetState(PinState::ZERO);  // Set Clock to 0 initially
    gate->calculate();


    input[1]->SetState(PinState::ONE);   // Clock rising edge
    gate->calculate();

    ASSERT_EQ(output[0]->GetState(), PinState::ONE);  // Q should be 1
    ASSERT_EQ(output[1]->GetState(), PinState::ZERO); // Q' should be 0
}


// Test when D is 0 and clock rises from 0 to 1
TEST_F(DflipFlopTest, ResetOnClockRise)
{
    auto input = gate->GetInputPins();
    auto output = gate->GetOutputPins();

    input[0]->SetState(PinState::ZERO);  // Set D to 0
    input[1]->SetState(PinState::ZERO);  // Set Clock to 0 initially
    gate->calculate();

    input[1]->SetState(PinState::ONE);   // Clock rising edge
    gate->calculate();

    ASSERT_EQ(output[0]->GetState(), PinState::ZERO); // Q should be 0
    ASSERT_EQ(output[1]->GetState(), PinState::ONE);  // Q' should be 1
}

// Test when clock remains low (no change should happen)
TEST_F(DflipFlopTest, NoChangeOnClockLow)
{
    auto input = gate->GetInputPins();
    auto output = gate->GetOutputPins();

    input[0]->SetState(PinState::ONE);   // Set D to 1
    input[1]->SetState(PinState::ZERO);  // Clock stays low
    gate->calculate();

    // The outputs should retain their initial state (assuming Q=0, Q'=1 at start)
    ASSERT_EQ(output[0]->GetState(), PinState::ZERO); // Q should be 0
    ASSERT_EQ(output[1]->GetState(), PinState::ONE);  // Q' should be 1
}

// Test when D and clock remain unchanged
TEST_F(DflipFlopTest, NoChangeOnStableClock)
{
    auto input = gate->GetInputPins();
    auto output = gate->GetOutputPins();

    input[0]->SetState(PinState::ONE);   // Set D to 1
    input[1]->SetState(PinState::ONE);   // Clock stays high initially
    gate->calculate();

    input[0]->SetState(PinState::ZERO);  // Change D to 0 without clock transition
    gate->calculate();

    ASSERT_EQ(output[0]->GetState(), PinState::ONE); // Q should still be previous state
    ASSERT_EQ(output[1]->GetState(), PinState::ZERO);  // Q' should still be opposite
}
