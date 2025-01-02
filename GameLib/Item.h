/**
 * @file Item.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * Base class for all the items
 */

#ifndef ITEM_H
#define ITEM_H

#include "Score.h"


class ItemVisitor;
class Game;
class Gate;
class Pin;

/// Base class for all the items
class Item
{
protected:
    /**
     * Constructor
     * @param game The game this item is a member of
     */
    Item(Game* game)
    {
        mGame = game;
    };

private:
    /// Game we are using
    Game* mGame;

    double mX = 500; ///< X location for the center of the item
    double mY = 500; ///< Y location for the center of the item


public:
    virtual ~Item();

    /**
     * Get the pointer to the Game object
     * @return Pointer to Game object
     */
    Game* GetGame() { return mGame; }


    /**
    * The X location of the item
    * @return X location in pixels
    */
    double GetX() const { return mX; }

    /**
    * The Y location of the item
    * @return Y location in pixels
    */
    double GetY() const { return mY; }

    /**
    * Set the item location
    * @param x X location in pixels
    * @param y Y location in pixels
    */
    void SetLocation(double x, double y);
    // {
    //     // mX = x;
    //     // mY = y;
    // }

    /**
    * Set the item x location
    * @param x X location in pixels
    */
    void SetX(int x) { mX = x; }
    /**
    * Set the item y location
    * @param y Y location in pixels
    */
    void SetY(int y) { mY = y; }

    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item&) = delete;


    /// Assignment operator
    void operator=(const Item&) = delete;

    virtual void Draw(std::shared_ptr<wxGraphicsContext> gc);

    virtual void XmlLoad(wxXmlNode* node);

    virtual bool HitTest(int x, int y);


    /**
     * Function to update items based on timer
     * @param elapsed time elapsed
     */
    virtual void Update(double elapsed)
    {
    };
    /**
     * Function to accept a visitor
     *
     * @param visitor The visitor to accept
     */
    virtual void Accept(ItemVisitor* visitor)
    {
    };

    /**
     * Getter for gate pointer
     * @return null for most items
     */
    virtual Gate* AsGate() { return nullptr; }

    /**
     * Event when item is released
     */
    virtual void Release()
    {
    }

    /**
     * Test if a pin is hit at a given point.
     * @param x X coordinate of the point
     * @param y Y coordinate of the point
     * @return Pointer to the pin if it is hit, nullptr otherwise
     */
    virtual std::shared_ptr<Pin> PinHitTest(int x, int y)
    {
        return nullptr;
    }
};


#endif //ITEM_H
