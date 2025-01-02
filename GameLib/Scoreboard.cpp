/**
 * @file Scoreboard.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "Scoreboard.h"

using namespace std;


/**
* Constructor
* @param game the item to initialize the scoreboard for
*/
Scoreboard::Scoreboard(Game* game) : Item(game)
{
	mScore = GetGame()->GetScore();
}

/**
 * Function to load data from a saved XML file
 * @param node The Xml node we are loading the item from
 */
void Scoreboard::XmlLoad(wxXmlNode* node)
{
	Item::XmlLoad(node);

	node->GetAttribute(L"good", L"10").ToInt(&mGood);
	node->GetAttribute(L"bad", L"-5").ToInt(&mBad);

	mGoal.Clear();  // Clear any previous goal content

	wxXmlNode* child = node->GetChildren();
	while (child)
	{
		if (child->GetType() == wxXML_TEXT_NODE)
		{
			mGoal += child->GetContent();  // Append the text content
		}
		else if (child->GetName() == "br")
		{
			mGoal += "\n";  // Handle <br/> as a newline
		}
		child = child->GetNext();
	}
}

/**
 * Draws the scoreboard
 * @param graphics graphics context shared pointer
 */
void Scoreboard::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

	// Drawing a rectangle that is the scoreboard
	wxBrush background(*wxWHITE);
	graphics->SetBrush(background);

	wxPen borderPen(*wxBLACK, 2);
	graphics->SetPen(borderPen);

	graphics->DrawRectangle(GetX(), GetY(), ScoreboardSize.x, ScoreboardSize.y);

	// Contents of the scoreboard
	int levelScore = mScore->GetLevelScore();
	int gameScore = mScore->GetGameScore();

	// Set the font for the scores
	wxGraphicsFont font = graphics->CreateFont(25, L"Arial", wxFONTFLAG_BOLD, wxColour(24, 69, 59));
	graphics->SetFont(font);

	// Display the level score
	wxString levelScoreText = wxString::Format(L"Level: %d", levelScore);
	graphics->DrawText(levelScoreText, GetX() + 10, GetY() + 10);

	// Display the game score
	wxString gameScoreText = wxString::Format(L"Game: %d", gameScore);
	graphics->DrawText(gameScoreText, GetX() + 10 + spacingBetweenScores, GetY() + 10);

	// Set the font for the goal
	font = graphics->CreateFont(15, L"Arial", wxFONTFLAG_BOLD, *wxBLACK);

	graphics->SetFont(font);

	wxArrayString goalLines = wxSplit(mGoal, '\n');

	// Display each line of the goal text
	int yOffset = GetY() + SpacingScoresToInstructions;
	for (size_t i = 0; i < goalLines.size(); ++i)
	{
		graphics->DrawText(goalLines[i], GetX() + 10, yOffset);
		yOffset += SpacingInstructionLines;
	}

}

