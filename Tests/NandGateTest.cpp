/**
 * @file NandGateTest.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include <pch.h>
#include <gtest/gtest.h>
#include <NandGate.h>
#include <Game.h>

class NandGateTest : public ::testing::Test
{
protected:
 Game game;
 NandGate gate;

 NandGateTest() : gate(&game) {}
};

/// Test when both the inputs are 1
TEST_F(NandGateTest, BothInputsOne)
{
 gate.calculate();
 auto output = gate.GetOutputPins();

 ASSERT_EQ(output[0]->GetState(), PinState::UNKNOWN);
}

/// Test when both the inputs are 0
TEST_F(NandGateTest, BothInputsZero)
{
 auto input = gate.GetInputPins();
 input[0]->SetState(PinState::ZERO);
 input[1]->SetState(PinState::ZERO);
 auto output = gate.GetOutputPins();
 gate.calculate();
 ASSERT_EQ(output[0]->GetState(), PinState::ONE);
}

/// Test when both the inputs are -1
TEST_F(NandGateTest, BothInputsNegativeOne)
{
 auto input = gate.GetInputPins();
 input[0]->SetState(PinState::UNKNOWN);
 input[1]->SetState(PinState::UNKNOWN);
 auto output = gate.GetOutputPins();
 gate.calculate();
 ASSERT_EQ(output[0]->GetState(), PinState::UNKNOWN);
}

/// Test when both the inputs are not equal to each other
TEST_F(NandGateTest, MismatchedInputs)
{
 auto input = gate.GetInputPins();
 input[0]->SetState(PinState::ONE);
 input[1]->SetState(PinState::ZERO);
 auto output = gate.GetOutputPins();
 gate.calculate();
 ASSERT_EQ(output[0]->GetState(), PinState::ONE);

 input[0]->SetState(PinState::ZERO);
 input[1]->SetState(PinState::ONE);
 gate.calculate();
 ASSERT_EQ(output[0]->GetState(), PinState::ONE);

 input[0]->SetState(PinState::ZERO);
 input[1]->SetState(PinState::UNKNOWN);
 gate.calculate();
 ASSERT_EQ(output[0]->GetState(), PinState::UNKNOWN);
}