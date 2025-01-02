/**
 * @file PropertyBoxVisitor.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * Visitor for Property Boxes
 */
 
#ifndef PROPERTYBOXVISITOR_H
#define PROPERTYBOXVISITOR_H
#include "ItemVisitor.h"
#include "Product.h"
#include "PropertyBox.h"



/**
 * Visitor class for Property Boxes
 */
class PropertyBoxVisitor : public ItemVisitor {
private:
 /// String to store the image of the product
 std::wstring mInside;

 /// Variable to store the color of the Product
 wxColour mColour;

 /// Variable to store the shape
 std::wstring mShape;

public:
 // deleting default constructor
 PropertyBoxVisitor() = delete;

 /**
  * Constructor
  * @param inside contents on the inside of the product
  * @param shape the shape of the product
  * @param colour the color of the product
  */
 PropertyBoxVisitor(std::wstring inside, std::wstring shape, wxColour colour) : mInside(inside),mShape(shape), mColour(colour) {};
 void VisitPropertyBox(PropertyBox* box) override;
};



#endif //PROPERTYBOXVISITOR_H
