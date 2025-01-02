/**
 * @file PropertyBox.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * Class for Property box
 */
 
#ifndef INPUTPIN_H
#define INPUTPIN_H
#include "Item.h"
#include "ItemVisitor.h"
#include "Pin.h"

/**
 * class for propery box
 */
class PropertyBox : public Item
{
private:
 ///size of box
 const wxSize mSize = wxSize(100, 40);
 ///Colour of box
 wxColour mColour;

 /// What is inside the box
 std::wstring mInside;

 /// Stores the image for the content
 std::shared_ptr<wxImage> mImage = nullptr;
 /// Stores the bitmap for the content
 std::shared_ptr<wxBitmap> mBitmap = nullptr;

 /// Output Pin
 std::shared_ptr<Pin> mPin;

;
public:
 /**
  * construct the property box
  * @param game game ptr to game the box belongs to
  * @param colour the color to fill the box
  * @param extrashape the name of the extra shape/image within the box
  */
 PropertyBox(Game* game, const wxColour& colour , std::wstring extrashape = L"");
 void Draw(std::shared_ptr<wxGraphicsContext> gc) override;
 void Update(double elapsed) override;
 std::shared_ptr<Pin> PinHitTest(int x, int y) override;

 /**
  * Getter to get the associated Pin
  * @return Pointer to Pin associated with this Property Box
  */
 std::shared_ptr<Pin> GetPin() {return mPin;};

 /**
  * Function to accept visitor and pass it to appropriate function
  * @param visitor ItemVisitor
  */
 void Accept(ItemVisitor* visitor) override { visitor->VisitPropertyBox(this);}

 /**
  * Getter for the color of the Property Box
  * @return the color of the Property Box
  */
 wxColour GetColour() {return mColour;}

 /**
  * Getter for inside of the Product
  * @return Inside of the Product
  */
 std::wstring GetInside() {return mInside;}
};



#endif //INPUTPIN_H
