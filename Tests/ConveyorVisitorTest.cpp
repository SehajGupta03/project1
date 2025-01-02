/**
 * @file ConveyorVisitorTest.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include <pch.h>
#include <gtest/gtest.h>
#include <ConveyorVisitor.h>
#include <ItemVisitor.h>

#include <Conveyor.h>
#include <Game.h>

TEST(ConveyorVisitorTest, TestConveyorVisitor)
{
    Game game;
    std::shared_ptr<Conveyor> conveyor = std::make_shared<Conveyor>(&game);
    game.Add(conveyor);
    ConveyorVisitor visitor = ConveyorVisitor();
    game.Accept(&visitor);

    EXPECT_EQ(visitor.GetConveyor(), conveyor.get());
}
