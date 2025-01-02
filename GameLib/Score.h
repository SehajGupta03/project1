/**
 * @file Score.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 *
 */

#ifndef SCORE_H
#define SCORE_H

/**
 * Class to keep track of scores
 */
class Score
{
private:
    /// The score value of a good event
    int mGood = 10;
    /// The score value of a bad event
    int mBad = -5;
    /// Currrent level score
    int mLevelScore = 0;
    /// Game total score
    int mGameScore = 0;

public:
    /// Constructor
    Score()
    {
    }

    /// Function to set level score back to 0
    void ResetLevelScore() { mLevelScore = 0; }

    /// Function to reset score completely
    void ResetScore()
    {
        mLevelScore = 0;
        mGameScore = 0;
    }

    // function to change level score based on if the kick was correct
    void UpdateLevelScore(bool success);

    // adds level score to game
    void AddGameScore();

    /**
     * Getter for level score
     * @return an int that is the current level score
     */
    int GetLevelScore() { return mLevelScore; }

    /**
     * Getter for game score
     * @return an int that is the current game score
     */
    int GetGameScore() { return mGameScore; }

    /**
     * Sets the point value for a good move
     * @param good new int value of the points
     */
    void SetGoodScore(int good) { mGood = good; }

    /**
     * Sets the point value for a bad move
     * @param bad new int value of the points
     */
    void SetBadScore(int bad) { mBad = bad; }
};


#endif //SCORE_H
