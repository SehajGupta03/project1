/**
 * @file AndGateTest.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include <pch.h>
#include <gtest/gtest.h>
#include <AndGate.h>
#include <Game.h>
#include <memory>
#include <Gate.h>

using namespace std;

class AndGateTest : public ::testing::Test
{
protected:
	Game mGame;

	std::shared_ptr<AndGate> gate;

	void SetUp() override
	{
		gate = make_shared<AndGate>(&mGame);
		mGame.Add(gate);
	}
};

// Testing to make sure pins are populated
TEST_F(AndGateTest, BothInputsTrue)
{
	ASSERT_EQ(gate->GetPins().size(), 3);
}

//Test when both inputs are false (0)
TEST_F(AndGateTest, BothInputsFalse)
{
	auto pins = gate->GetInputPins();
	pins[0]->SetState(PinState::ZERO);
	pins[1]->SetState(PinState::ZERO);
	auto output = gate->GetOutputPins();
	gate->calculate();
	ASSERT_EQ(output[0]->GetState(), PinState::ZERO);
}

// Test when A is true and B is false
TEST_F(AndGateTest, ATrueBFalse)
{
	auto pins = gate->GetInputPins();
	auto output = gate->GetOutputPins();
	pins[0]->SetState(PinState::ONE);
	pins[1]->SetState(PinState::ZERO);
	gate->calculate();
	EXPECT_EQ(output[0]->GetState(), PinState::ZERO);
}

//Test when A is false and B is true
TEST_F(AndGateTest, AFalseBTrue)
{
	auto input = gate->GetInputPins();
	input[0]->SetState(PinState::ZERO);
	input[1]->SetState(PinState::ONE);
	auto output = gate->GetOutputPins();
	gate->calculate();
	EXPECT_EQ(output[0]->GetState(), PinState::ZERO);
}

// Test when inputs are unknown
TEST_F(AndGateTest, UnknownInput)
{
	auto input = gate->GetInputPins();
	input[0]->SetState(PinState::UNKNOWN);
	input[1]->SetState(PinState::UNKNOWN);
	auto output = gate->GetOutputPins();
	gate->calculate();
	EXPECT_EQ(output[0]->GetState(), PinState::UNKNOWN);
}