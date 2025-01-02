/**
 * @file Scoreboard.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * This class will represent the scoreboard for
 * each level
 */

#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include "Item.h"
#include "Game.h"
#include "Score.h"

/// Size of the scoreboard in virtual pixels
const wxSize ScoreboardSize = wxSize(380, 100);

/// The spacing from the scores to the instructions presentation
/// in virtual pixels
const int SpacingScoresToInstructions = 40;

/// The spacing between the instruction lines in virtual pixels.
const int SpacingInstructionLines = 17;

/// Define spacing between the two scores (adjust this value if needed)
const int spacingBetweenScores = 150;


/**
 * Class to represent the scoreboard
 * Inherited from Item class
 */
class Scoreboard : public Item
{
private:
	/// Score to add if the circuit works as expected
	int mGood = 10;

	/// Score to add if the circuit does not work as expected
	int mBad = -5;

	/// The object of the level
	wxString mGoal;

	/// The pointer to the score object
	std::shared_ptr<Score> mScore;

public:
	// deleting the constructors
	Scoreboard(const Scoreboard&) = delete;
	void operator=(const Scoreboard&) = delete;

	Scoreboard(Game* game);

	// function to load data from XML file
	void XmlLoad(wxXmlNode* node) override;

	// function to draw scoreboard
	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

	/**
	 * getter for mGood
	 * @return mGood value
	 */
	double GetGood() {return mGood;}

	/**
	 * Getter for mBad
	 * @return mBad value
	 */
	double GetBad() {return mBad;}

	/**
	 * Getter for the text in the scoreboard
	 * @return Goal string
	 */
	wxString GetGoal() {return mGoal;}
};


#endif //SCOREBOARD_H
