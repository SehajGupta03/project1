/**
 * @file Sensor.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */


#include "pch.h"
#include "Sensor.h"
#include "Game.h"
#include "Pin.h"
#include "Product.h"
#include "ProductVisitor.h"
#include "PropertyBox.h"
#include "PropertyBoxVisitor.h"

/// Color to use for "red"
const wxColour OhioStateRed = wxColour(187, 0, 0);

/// Color to use for "blue"
const wxColour UofMBlue = wxColour(0, 39, 76);

using namespace std;

/**
  * Constructor
  * @param game The game that sensor belongs to
  */
Sensor::Sensor(Game* game) : Item(game)
{
    mCameraImage = std::make_shared<wxImage>(SensorCameraImage);
    mCableImage = std::make_shared<wxImage>(SensorCableImage);
}

/**
 * Load the Sensor from xml
 * @param node current node in xml file
 */
void Sensor::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    wxXmlNode* child = node->GetChildren();

    double x = GetX();
    double y = GetY();

    // Get the cable image dimensions
    double cableWidth = mCableImage->GetWidth();
    double cableHeight = mCableImage->GetHeight();

    // Position the top of the cable to align with the bottom of the camera
    double cableX = x - cableWidth / 2;
    double cableY = y - cableHeight / 2;
    // get the location of the bottom right of the cord
    double startX = cableX + cableWidth;
    double startY = (cableY + cableHeight) - 30;
    while (child != nullptr)
    {
        std::shared_ptr<PropertyBox> propBox = nullptr;
        auto name = child->GetName();
        if (name == L"white")
        {
            propBox = make_shared<PropertyBox>(GetGame(), *wxWHITE);
            propBox->SetX(startX);
            propBox->SetY(startY);
            //move the next box down by the height of the box 40 pixles
            startY += 40;
        }
        if (name == L"red")
        {
            propBox = make_shared<PropertyBox>(GetGame(), OhioStateRed);
            propBox->SetX(startX);
            propBox->SetY(startY);
            //move the next box down by the height of the box 40 pixles
            startY += 40;
        }
        else if (name == L"green")
        {
            propBox = make_shared<PropertyBox>(GetGame(), MSUGreen);
            propBox->SetX(startX);
            propBox->SetY(startY);
            //move the next box down by the height of the box 40 pixles
            startY += 40;
        }
        else if (name == L"blue")
        {
            propBox = make_shared<PropertyBox>(GetGame(), UofMBlue);
            propBox->SetX(startX);
            propBox->SetY(startY);
            //move the next box down by the height of the box 40 pixles
            startY += 40;
        }
        else if (name == L"circle")
        {
            propBox = make_shared<PropertyBox>(GetGame(), *wxLIGHT_GREY, L"Circle");
            propBox->SetX(startX);
            propBox->SetY(startY);
            //move the next box down by the height of the box 40 pixles
            startY += 40;
        }
        else if (name == L"square")
        {
            propBox = make_shared<PropertyBox>(GetGame(), *wxLIGHT_GREY, L"Square");
            propBox->SetX(startX);
            propBox->SetY(startY);
            //move the next box down by the height of the box 40 pixles
            startY += 40;
        }
        else if (name == L"izzo")
        {
            propBox = make_shared<PropertyBox>(GetGame(), *wxLIGHT_GREY, L"Izzo");
            propBox->SetX(startX);
            propBox->SetY(startY);
            //move the next box down by the height of the box 40 pixles
            startY += 40;
        }
        else if (name == L"smith")
        {
            propBox = make_shared<PropertyBox>(GetGame(), *wxLIGHT_GREY, L"Smith");
            propBox->SetX(startX);
            propBox->SetY(startY);
            //move the next box down by the height of the box 40 pixles
            startY += 40;
        }
        else if (name == L"basketball")
        {
            propBox = make_shared<PropertyBox>(GetGame(), *wxLIGHT_GREY, L"Basketball");
            propBox->SetX(startX);
            propBox->SetY(startY);
            //move the next box down by the height of the box 40 pixles
            startY += 40;
        }


        if (propBox)
        {
            GetGame()->Add(propBox);
            mBoxes.push_back(propBox);
        }
        child = child->GetNext();
    }
}

/**
 * Draws the sensor
 * @param graphics the graphics pointer for virtual pixels
 */
void Sensor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Get the sensor position
    double x = GetX();
    double y = GetY();

    // Get the camera image dimensions
    double cameraWidth = mCameraImage->GetWidth();
    double cameraHeight = mCameraImage->GetHeight();
    double cameraX = x - cameraWidth / 2;
    double cameraY = y - cameraHeight / 2;

    // Get the cable image dimensions
    double cableWidth = mCableImage->GetWidth();
    double cableHeight = mCableImage->GetHeight();

    // Position the top of the cable to align with the bottom of the camera
    double cableX = x - cableWidth / 2;
    double cableY = y - cableHeight / 2;

    // Draw cable
    graphics->DrawBitmap(*mCableImage, cableX, cableY, cableWidth, cableHeight);

    // Draw camera 2nd to make sure it is on top
    graphics->DrawBitmap(*mCameraImage, cameraX, cameraY, cameraWidth, cameraHeight);
}


/**
 * Function to change the state of the Pins
 * of the Property Boxes based on the
 * properties of Product and Property Boxes.
 * @param product The Product on the Belt that sensor is watching
 */
void Sensor::PropertyBoxState(Product* product)
{
    double range = SensorRange[1] - SensorRange[0] + ProductDefaultSize;
    double y = GetY() - (SensorRange[0] + SensorRange[1]) / 2;
    double x = GetX();

    if (abs(product->GetY() + product->GetYOffset() - y) < range / 2 && abs(
            product->GetX() + product->GetXOffset() - x) <
        range / 2)
	{
		wxColour color = *wxLIGHT_GREY;
		if(product->GetColor() == Color::Blue)
		{
			color = UofMBlue;
		}
		else if(product->GetColor() == Color::Green)
		{
			color = MSUGreen;
		}
		else if(product->GetColor() == Color::Red)
		{
			color = OhioStateRed;
		}
		else if(product->GetColor() == Color::White)
		{
			color = *wxWHITE;
		}

		std::wstring inside = L"";
        std::wstring shape = L"";
		if(product->GetContent() == Content::Basketball)
		{
			inside = L"Basketball";
		}
		else if(product->GetContent() == Content::Smith)
		{
			inside = L"Smith";
		}
		else if(product->GetContent() == Content::Izzo)
		{
			inside = L"Izzo";
		}
		if(product->GetShape() == Shape::Circle)
		{
			shape = L"Circle";
		}
		else if(product->GetShape() == Shape::Square)
		{
			shape = L"Square";
		}
		else if(product->GetShape() == Shape::Diamond)
		{
			shape = L"Diamond";
		}
		PropertyBoxVisitor visitor(inside, shape, color);
		for(auto box : mBoxes)
		{
			box->Accept(&visitor);
		}
	}

	ProductVisitor visitor(y, x, range);
	GetGame()->Accept(&visitor);
	if(visitor.GetProducts().empty())
	{
		Reset();
	}
}

/**
 * Function to reset the state of all the Pins
 * for all the Property Boxes
 */
void Sensor::Reset()
{
	for(auto box : mBoxes)
	{
		box->GetPin()->SetState(PinState::ZERO);
	}
}
