/**
 * @file NotGateTest.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */
#include <pch.h>
#include <gtest/gtest.h>
#include <NotGate.h>
#include <Game.h>
#include <memory>
#include <Gate.h>

using namespace std;

class NotGateTest : public ::testing::Test
{
protected:
	Game mGame;
	std::shared_ptr<NotGate> gate;

	void SetUp() override
	{
		gate = make_shared<NotGate>(&mGame);
		mGame.Add(gate);
	}
};

// Test when input is true (1)
TEST_F(NotGateTest, InputTrue)
{
	auto input = gate->GetInputPins();
	auto output = gate->GetOutputPins();
	input[0]->SetState(PinState::ONE);
	gate->calculate();
	ASSERT_EQ(output[0]->GetState(), PinState::ZERO);
}

// Test when input is false (0)
TEST_F(NotGateTest, InputFalse)
{
	auto input = gate->GetInputPins();
	auto output = gate->GetOutputPins();
	input[0]->SetState(PinState::ZERO);
	gate->calculate();
	ASSERT_EQ(output[0]->GetState(), PinState::ONE);
}

// Test when input is unknown
TEST_F(NotGateTest, InputUnknown)
{
	auto input = gate->GetInputPins();
	auto output = gate->GetOutputPins();
	input[0]->SetState(PinState::UNKNOWN);
	gate->calculate();
	ASSERT_EQ(output[0]->GetState(), PinState::UNKNOWN);
}
