/**
 * @file SRFlipFlopTest.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include <pch.h>
#include <gtest/gtest.h>
#include <SRFlipFlop.h>
#include <Game.h>
#include <memory>
#include <Gate.h>

using namespace std;

class SRFlipFlopTest : public ::testing::Test
{
protected:
	Game mGame;
	std::shared_ptr<SRFlipFlop> gate;

	void SetUp() override
	{
		gate = make_shared<SRFlipFlop>(&mGame);
		mGame.Add(gate);
	}
};

// Test when both inputs S and R are 0 (No change)
TEST_F(SRFlipFlopTest, BothInputsZero)
{
	auto input = gate->GetInputPins();
	auto output = gate->GetOutputPins();
	input[0]->SetState(PinState::ZERO); // S
	input[1]->SetState(PinState::ZERO); // R
	gate->calculate();
	// Expect no change in outputs, so Q and Q' retain their initial state
	EXPECT_EQ(output[1]->GetState(), PinState::ONE); // Q'
	EXPECT_EQ(output[0]->GetState(), PinState::ZERO);  // Q
}

// Test when S is 1 and R is 0 (Set state)
TEST_F(SRFlipFlopTest, SetState)
{
	auto input = gate->GetInputPins();
	auto output = gate->GetOutputPins();
	input[0]->SetState(PinState::ZERO); // R
	input[1]->SetState(PinState::ONE);  // S
	gate->calculate();
	ASSERT_EQ(output[1]->GetState(), PinState::ONE);  // Q'
	ASSERT_EQ(output[0]->GetState(), PinState::ZERO); // Q
}

// Test when S is 0 and R is 1 (Reset state)
TEST_F(SRFlipFlopTest, ResetState)
{
	auto input = gate->GetInputPins();
	auto output = gate->GetOutputPins();
	input[0]->SetState(PinState::ZERO);  // S
	input[1]->SetState(PinState::ONE); // R
	gate->calculate();
	ASSERT_EQ(output[1]->GetState(), PinState::ONE); // Q'
	ASSERT_EQ(output[0]->GetState(), PinState::ZERO);  // Q
}

// Test when both S and R are 1 (Invalid state)
TEST_F(SRFlipFlopTest, InvalidState)
{
	auto input = gate->GetInputPins();
	auto output = gate->GetOutputPins();
	input[0]->SetState(PinState::ONE); // S
	input[1]->SetState(PinState::ONE); // R
	gate->calculate();
	ASSERT_EQ(output[1]->GetState(), PinState::UNKNOWN);  // Q'
	ASSERT_EQ(output[0]->GetState(), PinState::UNKNOWN);  // Q
}

