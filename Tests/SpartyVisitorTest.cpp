/**
 * @file SpartyVisitorTest.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include <pch.h>
#include <gtest/gtest.h>
#include <SpartyVisitor.h>
#include <ItemVisitor.h>

#include <Sparty.h>
#include <Game.h>

TEST(SpartyVisitorTest, TestSpartyVisitor)
{
    Game game1;
    SpartyVisitor visitor1;
    game1.Accept(&visitor1);

    EXPECT_EQ(visitor1.GetSparty(), nullptr);

    Game game2;
    std::shared_ptr<Sparty> sparty = std::make_shared<Sparty>(&game2);
    sparty->SetLocation(0, 100);
    game2.Add(sparty);

    SpartyVisitor visitor2;
    game2.Accept(&visitor2);

    EXPECT_EQ(visitor2.GetSparty(), sparty.get());
}
