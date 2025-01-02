/**
 * @file Score.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "Score.h"

/**
 * Updates the score total
 * @param success if a kick was supposed to happen
 */
void Score::UpdateLevelScore(bool success)
{
	if (success)
	{
		mLevelScore += mGood;
	}
	else
	{
		mLevelScore += mBad;
	}
}

/**
 * Add level score to game score and resets the level score
 */
void Score::AddGameScore()
{
	mGameScore += mLevelScore;
	ResetLevelScore();
}
