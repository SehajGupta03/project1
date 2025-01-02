/**
* @file AndGateTest.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include <pch.h>
#include <gtest/gtest.h>
#include <Game.h>
#include <OrGate.h>

/**
 * Test class for Or Gate
 */
class OrGateTest : public ::testing::Test
{
protected:
	Game game;
	OrGate gate;

	OrGateTest() : gate(&game) {}
};

// Test when both inputs are true
TEST_F(OrGateTest, BothInputsTrue)
{
	auto input = gate.GetInputPins();
	input[0]->SetState(PinState::ONE);
	input[1]->SetState(PinState::ONE);
	auto output = gate.GetOutputPins();
	gate.calculate();
	EXPECT_EQ(output[0]->GetState(), PinState::ONE);
}

// Test when both inputs are false
TEST_F(OrGateTest, BothInputsFalse)
{
	auto input = gate.GetInputPins();
	input[0]->SetState(PinState::ZERO);
	input[1]->SetState(PinState::ZERO);
	auto output = gate.GetOutputPins();
	gate.calculate();
	EXPECT_EQ(output[0]->GetState(), PinState::ZERO);
}

// Test when A is true and B is false
TEST_F(OrGateTest, ATrueBFalse)
{
	auto input = gate.GetInputPins();
	input[0]->SetState(PinState::ONE);
	input[1]->SetState(PinState::ZERO);
	auto output = gate.GetOutputPins();
	gate.calculate();
	EXPECT_EQ(output[0]->GetState(), PinState::ONE);
}

// Test when A is false and B is true
TEST_F(OrGateTest, AFalseBTrue)
{
	auto input = gate.GetInputPins();
	input[1]->SetState(PinState::ONE);
	input[0]->SetState(PinState::ZERO);
	auto output = gate.GetOutputPins();
	gate.calculate();
	EXPECT_EQ(output[0]->GetState(), PinState::ONE);
}

// Test when inputs are unknown
TEST_F(OrGateTest, UnknownInput)
{
	gate.calculate();
	auto output = gate.GetOutputPins();
	EXPECT_EQ(output[0]->GetState(), PinState::UNKNOWN);
}