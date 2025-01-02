/**
 * @file Item.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */
#include "pch.h"
#include "Item.h"
#include "Game.h"
#include <wx/graphics.h>
#include <string>

#include "ConveyorVisitor.h"

using namespace std;

/**
 * Destructor
 */
Item::~Item()
{
}

/**
 * Test to see if we hit this object with a mouse.
 * Due to there not being an image anymore this can't be used.
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit.
 */
bool Item::HitTest(int x, int y)
{
    return false;
}

/**
 * Draw this item. This does nothing for now,
 * but if shared behavior is found it will be added here
 * @param gc Device context to draw on
 */
void Item::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode* node)
{
    node->GetAttribute(L"x", L"0").ToDouble(&mX);
    node->GetAttribute(L"y", L"0").ToDouble(&mY);
}


void Item::SetLocation(double x, double y)
{
 ConveyorVisitor visitor;
 this->Accept(&visitor);
 bool type = visitor.GetType();
 if(!type)
 {
  mX = x;
  mY = y;
 }
}