/**
 * @file Beam.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * This class represents the beam on the belt
 */

#ifndef BEAM_H
#define BEAM_H
#include "Item.h"
#include "Pin.h"

/// Image for the beam sender and receiver when red
const std::wstring BeamRedImage = L"images/beam-red.png";

/// Image for the beam sender and receiver when green
const std::wstring BeamGreenImage = L"images/beam-green.png";

/// X offset for the beam pin in pixels
/// This is larger than normal to get it past Sparty's feet
const int BeamPinOffset = 80;

/**
 * Represents the beam on the belt
 * Inherits from Item class
 */
class Beam : public Item
{
private:
	/// Distance to the left to place the beam sender image
	int mSender = 0;
	/// The image for left side red
	std::shared_ptr<wxImage> mLeftSideRed;
	/// The image for left side green
	std::shared_ptr<wxImage> mLeftSideGreen;
	/// The image for right side red
	std::shared_ptr<wxImage> mRightSideRed;
	/// The image for right side green
	std::shared_ptr<wxImage> mRightSideGreen;

	/// The length of the beam
	int mBeamLength = 110;

	/// output pin
	std::shared_ptr<Pin> mPin;

	/// If a product breaks the beam
	bool mBeamCrossed = false;

public:
	// deleting default constructors
	Beam(const Beam& beam) = delete;
	void operator=(const Beam& beam) = delete;

	Beam(Game* game);

	// function to load data from XML file
	void XmlLoad(wxXmlNode* node) override;

	// Draw function
	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

	void Update(double elapsed) override;

    std::shared_ptr<Pin> PinHitTest(int x, int y) override;
};


#endif //BEAM_H
