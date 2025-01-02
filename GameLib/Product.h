/**
 * @file Product.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * Class for a product
 */

#ifndef PRODUCT_H
#define PRODUCT_H

#include "Game.h"
#include "Item.h"
#include "ItemVisitor.h"

/// Default product size in pixels
const int ProductDefaultSize = 80;

/// Size to draw content relative to the product size
const double ContentScale = 0.8;

/// Color green declaration moved to Game.h

/// Delay after last product has left beam or
/// been kicked before we end the level.
const double LastProductDelay = 3;
/// Enum of Colors
enum class Color { Red, Green, Blue, White };

/// Enum of Shapes
enum class Shape { Circle, Square, Diamond };

/// Enum of Content
enum class Content { Izzo, Smith, Football, Basketball, None };

/// Class for a product
class Product : public Item
{
private:

    /// Stores the color
    Color mColor = Color::Red;
    /// Stores the shape
    Shape mShape = Shape::Circle;
    /// Stores the content
    Content mContent = Content::None;
    /// Stores the image for the content
    std::shared_ptr<wxImage> mImage = nullptr;
    /// Stores the bitmap for the content
    std::shared_ptr<wxBitmap> mBitmap = nullptr;
    /// If this product should be kicked
    bool mKick = false;

    void ChangeContent(const wxString& content);

    /// The y coordinate offset of the previous product
    double mPrevProdYCoord = 0;

    /// The movement in the y direction
    double mOffsetY = 0;

    /// The movement in the x direction
    double mOffsetX = 0;

    /// The kick speed set when the product is kicked
    double mKickSpeed = 0;

public:
    /**
     * @brief Constructor
     * @param game The game the product belongs to
     * @param y The y coordinate offset of the previous product
     */
    Product(Game* game, double y)
        : Item(game)
    {
        mPrevProdYCoord = y;
    }

    void XmlLoad(wxXmlNode* node) override;
    void Draw(std::shared_ptr<wxGraphicsContext> gc) override;

    /**
     * Accepts a visitor for the product.
     *
     * This tells the visitor that this was a conveyor.
     *
     * @param visitor Pointer to the ItemVisitor to be used
     */
    void Accept(ItemVisitor* visitor) override
    {
        visitor->VisitProduct(this);
    };

    void Kick(double speed);

    double GetYOffset();

    /**
     * Getter for the x offset of the product
     * @return The x offset of the product
     */
    double GetXOffset()
    {
        return mOffsetX;
    };

    void Update(double elapsed) override;

    /// Resets the position of the product
    void ResetPosition()
    {
        mOffsetY = 0;
        mOffsetX = 0;
        mKickSpeed = 0;
    }

    /**
     * Getter to get the color of this Product
     * @return color of this Product of type enum Color
     */
    Color GetColor() {return mColor;}

    /**
     * Getter to get the shape of this Product
     * @return Shape of this Product of type enum Shape
     */
    Shape GetShape() {return mShape;}

    /**
     * Getter for the content of this Product
     * @return Content of this Product
     */
    Content GetContent() {return mContent;}
};


#endif //PRODUCT_H
