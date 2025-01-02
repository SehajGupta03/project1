/**
 * @file ConveyorTest.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include <pch.h>
#include <gtest/gtest.h>

#include <Game.h>
#include <Conveyor.h>

TEST(ConveyorTest, TestConveyor) {
    Game game;
    std::shared_ptr<Conveyor> conveyor = std::make_shared<Conveyor>(&game);
    auto node = new wxXmlNode(wxXML_ELEMENT_NODE, L"conveyor");
    node->AddAttribute(L"x", L"300");
    node->AddAttribute(L"y", L"200");
    node->AddAttribute(L"speed", L"100");
    conveyor->XmlLoad(node);

    EXPECT_EQ(conveyor->GetX(), 300);
    EXPECT_EQ(conveyor->GetY(), 200);
    delete node;
}