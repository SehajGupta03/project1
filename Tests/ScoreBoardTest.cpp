/**
 * @file ScoreBoardTest.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include <pch.h>
#include <Scoreboard.h>
#include <gtest/gtest.h>
#include <Game.h>

using namespace std;

/**
 * Testing XmlLoad of Scoreboard Class
 */
TEST(ScoreBoardTest, TestScoreBoard)
{
 // initializing game object
 Game game;
 Scoreboard scoreboard(&game);

 auto node = new wxXmlNode(wxXML_ELEMENT_NODE, L"scoreboard");




 // adding good attribute to the node
 node->AddAttribute(L"good", "20");

 // adding bad attribute to the node
 node->AddAttribute(L"bad", "");

 scoreboard.XmlLoad(node);

 // testing if the default value is set right
 ASSERT_NE(scoreboard.GetGood(), 0);

 // testing default values
 ASSERT_NE(scoreboard.GetGood(), 10);
 ASSERT_EQ(scoreboard.GetGood(), 20);
 ASSERT_EQ(scoreboard.GetBad(), -5);

 auto new_node = new wxXmlNode(wxXML_ELEMENT_NODE, L"scoreboard");
 auto child = new wxXmlNode(wxXML_TEXT_NODE, "", L"Hi");

 new_node->AddChild(child);
 scoreboard.XmlLoad(new_node);
 // testing the default value of message
 ASSERT_TRUE(scoreboard.GetGoal() == L"Hi");

 delete new_node;
 delete node;

}
