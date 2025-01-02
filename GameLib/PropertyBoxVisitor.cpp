/**
 * @file PropertyBoxVisitor.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "PropertyBoxVisitor.h"

#include "Product.h"

/**
 * Function to visit the PropertyBox and change the state of the
 * Pin based on if the color or inside properties match or not.
 *
 * @param box the Property Box being visited
 */
void PropertyBoxVisitor::VisitPropertyBox(PropertyBox* box)
{
 if((box->GetInside() == mInside && !mInside.empty()) || box->GetColour() == mColour || (box->GetInside() == mShape && !mShape.empty()))
 {
  box->GetPin()->SetState(PinState::ONE);
 }
 else
 {
  box->GetPin()->SetState(PinState::ZERO);
 }
}
