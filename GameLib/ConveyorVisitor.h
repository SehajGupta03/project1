/**
 * @file ConveyorVisitor.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * Used to find the conveyor in the game
 */

#ifndef CONVEYORVISITOR_H
#define CONVEYORVISITOR_H
#include "ItemVisitor.h"

/// Visitor to get the conveyor
class ConveyorVisitor : public ItemVisitor
{
private:
    /// Stores the pointer to the found conveyor
    Conveyor* mConveyor = nullptr;
    /// variable to store if the passed object is conveyor or not
    bool mType = false;

public:
    /**
     * When visiting a conveyor it stores it.
     *
     * @param conveyor The conveyor being visited
     */
    void VisitConveyors(Conveyor* conveyor) override
    {
        mConveyor = conveyor;
        mType = true;
    }

    /**
     * Getter for the conveyor that was found
     *
     * @return Pointer to the conveyor, nullptr if not found
     */
    Conveyor* GetConveyor()
    {
        return mConveyor;
    }

    /**
     * Getter of mType
     * @return true or false
     */
    bool GetType() { return mType; }
};


#endif //CONVEYORVISITOR_H
