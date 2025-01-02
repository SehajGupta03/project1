/**
 * @file PropertyBox.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "PropertyBox.h"

using namespace std;


/// const half
const double Half = 0.5;

/// const for smith iamge
const wstring smithImage = L"images/smith.png";

/// const for izzo
const wstring izzoImage = L"images/izzo.png";

/// const for basketball
const wstring basketballImage = L"images/basketball.png";


PropertyBox::PropertyBox(Game* game, const wxColour& colour, std::wstring extrashape) : Item(game), mColour(colour),
                                                                                       mInside(extrashape)
{
 mPin = make_shared<Pin>(game, PinType::OUTPUT, mSize.GetWidth(), mSize.GetHeight() * Half,
  PinState::ZERO);
}




/**
 * draw the property box
 * @param gc graphics context pointer 
 */
void PropertyBox::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
 // Set the brush
 wxBrush brush(mColour);
 gc->SetBrush(brush);

 // Set a black pen for the rectangle outline
 wxPen pen(*wxBLACK, 1);
 gc->SetPen(pen);

 // Get the location and size of the box
 double x = GetX();
 double y = GetY();

 // Draw the rectangle using the current color
 gc->DrawRectangle(x, y, mSize.GetWidth(), mSize.GetHeight());

 if (mInside.length()!=0)
 {
  // Make new brush for shapes inside
  wxBrush brush2(*wxWHITE);
  gc->SetBrush(brush2);
  // make new pen for shapes inside
  wxPen pen2(*wxBLACK, 1); // Black outline with 1-pixel width
  gc->SetPen(pen);
  if (mInside == "Circle")
  {
   // draw circle with radius = 15
   gc->DrawEllipse((x + mSize.GetWidth() * Half) - 15, (y + mSize.GetHeight() * Half) - 15, 2 * 15, 2 * 15);
  }
  else if (mInside == "Square")
  {
   // draw a square
   gc->DrawRectangle(x+35, y+5, 30, 30);
  }
  else if (mInside == "Diamond")
  {
   // Define the center of the square (diamond)
   double centerX = x + 50; // Adjust as needed
   double centerY = y + 20; // Adjust as needed

   // Define half the side length of the square
   double halfSide = 15;

   // Create a path for the diamond shape
   wxGraphicsPath path = gc->CreatePath();
   path.MoveToPoint(centerX, centerY - halfSide);          // Top vertex
   path.AddLineToPoint(centerX + halfSide, centerY);       // Right vertex
   path.AddLineToPoint(centerX, centerY + halfSide);       // Bottom vertex
   path.AddLineToPoint(centerX - halfSide, centerY);       // Left vertex
   path.CloseSubpath();                                    // Close the path

   // Draw the path (diamond)
   gc->StrokePath(path); // Outline the diamond
   gc->FillPath(path);   // Fill the diamond (optional
  }
  else if (mInside == "Smith")
  {
   // draw coach smith
   mImage = std::make_shared<wxImage>(smithImage);
   mBitmap = std::make_shared<wxBitmap>(*mImage);
   gc->DrawBitmap(*mBitmap,x+35, y+5, 30, 30);
  }
  else if (mInside == "Izzo")
  {
   // draw coach izzo
   mImage = std::make_shared<wxImage>(izzoImage);
   mBitmap = std::make_shared<wxBitmap>(*mImage);
   gc->DrawBitmap(*mBitmap,x+35, y+5, 30, 30);
  }
  else if (mInside == "Basketball")
  {
   // draw a basketball
   mImage = std::make_shared<wxImage>(basketballImage);
   mBitmap = std::make_shared<wxBitmap>(*mImage);
   gc->DrawBitmap(*mBitmap,x+35, y+5, 30, 30);
  }
 }

 mPin->Draw(gc);
}


/**
 * Function to update box and associated Pin
 * @param elapsed The time elapsed since last update
 */
void PropertyBox::Update(double elapsed)
{
 mPin->UpdateGatePosition(GetX(), GetY());
 mPin->Update();
}


/**
 * Function to check if there is a Pin at the passed
 * coordinates
 * @param x x coordinate
 * @param y y coordinate
 * @return Pointer to Pin object at (x,y)
 */
std::shared_ptr<Pin> PropertyBox::PinHitTest(int x, int y)
{
 if (mPin->HitTest(x, y))
 {
  return mPin;
 }
    return nullptr;
}