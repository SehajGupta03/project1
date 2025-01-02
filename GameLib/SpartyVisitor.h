/**
 * @file SpartyVisitor.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * Visitor class for finding sparty
 */

#ifndef SPARTYVISITOR_H
#define SPARTYVISITOR_H
#include "ItemVisitor.h"

/// Visitor class for finding sparty
class SpartyVisitor : public ItemVisitor
{
private:
    /// Pointer to the sparty
    Sparty* mSparty = nullptr;

public:
    /// Constructor for all products
    SpartyVisitor()
    {
    };
    /**
     * Visits a Sparty object and stores a pointer to it.
     *
     * This function overrides the VisitSparty method in the ItemVisitor class.
     * It is used to store a pointer to the Sparty object being visited.
     *
     * @param sparty Pointer to the Sparty object being visited
     */
    void VisitSparty(Sparty* sparty) override { mSparty = sparty; }

    /**
     * Returns the pointer to the sparty object.
     *
     * @return Pointer to the sparty object
     */
    Sparty* GetSparty() { return mSparty; }
};


#endif //SPARTYVISITOR_H
