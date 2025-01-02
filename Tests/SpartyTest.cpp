/**
 * @file SpartyTest.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include <pch.h>
#include <gtest/gtest.h>

#include <Game.h>
#include <Sparty.h>

TEST(SpartyTest, XmlLoad)
{
    Game game;
    Sparty sparty(&game);
    auto node = new wxXmlNode(wxXML_ELEMENT_NODE, L"sparty");
    node->AddAttribute(L"x", L"200");
    node->AddAttribute(L"y", L"500");
    sparty.XmlLoad(node);
    EXPECT_EQ(sparty.GetX(), 200);
    EXPECT_EQ(sparty.GetY(), 500);
    delete node;
}