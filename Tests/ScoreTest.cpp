/**
 * @file ScoreTest.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */
#include <pch.h>
#include <gtest/gtest.h>

#include <Game.h>
#include <Score.h>

using namespace std;

TEST(ScoreTest, TestScore)
{
 Game game;
 shared_ptr<Score> score = make_shared<Score>();
 score->UpdateLevelScore(true);
 score->UpdateLevelScore(false);
 score->UpdateLevelScore(true);
 score->UpdateLevelScore(true);

 ASSERT_EQ(score->GetLevelScore(), 25);

 score->AddGameScore();

 ASSERT_EQ(score->GetLevelScore(), 0);
 ASSERT_EQ(score->GetGameScore(), 25);

 score->SetBadScore(-10);
 score->SetGoodScore(100);

 score->ResetLevelScore();

 ASSERT_EQ(score->GetLevelScore(), 0);

 score->UpdateLevelScore(true);
 score->UpdateLevelScore(false);
 score->UpdateLevelScore(true);

 score->AddGameScore();

 ASSERT_EQ(score->GetLevelScore(), 0);
 ASSERT_EQ(score->GetGameScore(), 215);



}
