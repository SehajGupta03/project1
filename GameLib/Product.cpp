/**
 * @file Product.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "Product.h"

#include "Conveyor.h"
#include "ConveyorVisitor.h"
#include "ProductVisitor.h"
#include "Sensor.h"
#include "SensorVisitor.h"
#include "Sparty.h"
#include "SpartyVisitor.h"


/// Color to use for "red"
const wxColour OhioStateRed = wxColour(187, 0, 0);

/// Color to use for "blue"
const wxColour UofMBlue = wxColour(0, 39, 76);

/**
 * @brief Loads the product from an XML node
 * @param node The XML node containing the product's attributes
 */
void Product::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);
    auto shape = node->GetAttribute(L"shape");
    if (shape == L"circle")
    {
        mShape = Shape::Circle;
    }
    else if (shape == L"square")
    {
        mShape = Shape::Square;
    }
    else if (shape == L"diamond")
    {
        mShape = Shape::Diamond;
    }
    auto color = node->GetAttribute(L"color");
    if (color == L"red")
    {
        mColor = Color::Red;
    }
    else if (color == L"green")
    {
        mColor = Color::Green;
    }
    else if (color == L"blue")
    {
        mColor = Color::Blue;
    }
    else if (color == L"white")
    {
        mColor = Color::White;
    }
    auto content = node->GetAttribute(L"content");
    ChangeContent(content);

    auto kick = node->GetAttribute(L"kick");
    if (kick == L"yes")
    {
        mKick = true;
    }
    else
    {
        mKick = false;
    }
    double y = 0;
    auto placement = node->GetAttribute(L"placement");
    placement.ToDouble(&y);
    // Checks if relative or absolute positioning
    if (placement[0] == '+')
    {
        SetLocation(GetX(), mPrevProdYCoord - y);
    }
    else
    {
        SetLocation(GetX(), -y);
    }
}

/**
 * Draw the products.
 *
 * @param gc The graphics context to draw on
 */
void Product::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    /// Stores the offset in the up down direction
    double offsetY = GetYOffset();
    gc->SetPen(*wxTRANSPARENT_PEN);
    if (mColor == Color::Red)
    {
        gc->SetBrush(OhioStateRed);
    }
    else if (mColor == Color::Green)
    {
        gc->SetBrush(MSUGreen);
    }
    else if (mColor == Color::Blue)
    {
        gc->SetBrush(UofMBlue);
    }
    else if (mColor == Color::White)
    {
        gc->SetBrush(*wxWHITE_BRUSH);
    }

    if (mShape == Shape::Circle)
    {
        gc->DrawEllipse(GetX() - ProductDefaultSize / 2 + mOffsetX, GetYOffset() + GetY() - ProductDefaultSize / 2,
                        ProductDefaultSize,
                        ProductDefaultSize);
    }
    else if (mShape == Shape::Square)
    {
        gc->DrawRectangle(GetX() - ProductDefaultSize / 2 + mOffsetX, GetYOffset() + GetY() - ProductDefaultSize / 2,
                          ProductDefaultSize,
                          ProductDefaultSize);
    }
    else if (mShape == Shape::Diamond)
    {
        gc->PushState();
        gc->Translate(GetX() + mOffsetX, offsetY + GetY() - SQRT2 * ProductDefaultSize / 2);
        gc->Rotate(PI / 4);
        gc->DrawRectangle(0, 0, ProductDefaultSize, ProductDefaultSize);
        gc->PopState();
    }
    if (mBitmap != nullptr)
    {
        double width = ProductDefaultSize * ContentScale;
        double height = ProductDefaultSize * ContentScale;
        gc->DrawBitmap(*mBitmap, GetX() - width / 2 + mOffsetX, GetYOffset() + GetY() - height / 2, width, height);
    }
}

/**
 * @brief Simulates kicking the product with a specified speed.
 *
 * This function sets the kick speed for the product, indicating how
 * fast the product should move when kicked.
 *
 * @param speed The speed at which the product is kicked.
 */
void Product::Kick(double speed)
{
    mKickSpeed = speed;
    GetGame()->GetScore()->UpdateLevelScore(mKick);
}

/**
 * @brief Changes the content of the product
 * @param content The new content of the product as a string
 *
 * If the content is "izzo", "smith", "football", or "basketball", the image
 * associated with that content will be displayed. Otherwise, the image will be
 * cleared.
 */
void Product::ChangeContent(const wxString& content)
{
    if (content == L"izzo")
    {
        mContent = Content::Izzo;
    }
    else if (content == L"smith")
    {
        mContent = Content::Smith;
    }
    else if (content == L"football")
    {
        mContent = Content::Football;
    }
    else if (content == L"basketball")
    {
        mContent = Content::Basketball;
    }
    else
    {
        mContent = Content::None;
        mImage = nullptr;
        mBitmap = nullptr;
    }
    if (mContent != Content::None)
    {
        mImage = std::make_shared<wxImage>(L"images/" + content + L".png");
        mBitmap = std::make_shared<wxBitmap>(*mImage);
    }
}

/**
 * @brief Get the y offset of the product
 *
 * This returns the y offset of the conveyor that this product is on.
 * @return The y offset of the conveyor
 */
double Product::GetYOffset()
{
    return mOffsetY;
}

/**
 * @brief Updates the product's position based on elapsed time.
 *
 * This function determines the movement of the product depending on whether it
 * has been kicked or not. If the product has been kicked, it will move in the x
 * direction at the speed specified by mKickSpeed. Otherwise, it will update its
 * y offset to match the conveyor's offset.
 *
 * @param elapsed The time elapsed since the last update
 */
void Product::Update(double elapsed)
{
    SensorVisitor visit;
    GetGame()->Accept(&visit);
    auto sensor = visit.GetSensor();
    if(sensor != nullptr)
    {
        sensor->PropertyBoxState(this);
    }

    // If the product has been kicked, move it in the kick direction
    if (mKickSpeed > 0)
    {
        mOffsetX -= mKickSpeed * elapsed;
    }
    // If the product has not been kicked the conveyor is the only source of movement
    else
    {
        // Update the y offset
        double oldYOffset = mOffsetY;
        ConveyorVisitor visitor;
        GetGame()->Accept(&visitor);
        Conveyor* conveyor = visitor.GetConveyor();
        if (conveyor != nullptr)
        {
            mOffsetY = conveyor->GetOffset();
        }
        // Checks if the product is past where sparty can kick
        SpartyVisitor spartyVisitor;
        GetGame()->Accept(&spartyVisitor);
        Sparty* sparty = spartyVisitor.GetSparty();
        if (sparty != nullptr)
        {
            /// Stores sparty's kick y relative to the products y offset
            double spartyKickYOffset = sparty->GetKickY() - GetY() + ProductDefaultSize / 2;
            // This means that this has just passed by sparty
            if (mOffsetY > spartyKickYOffset && oldYOffset <= spartyKickYOffset)
            {
                GetGame()->GetScore()->UpdateLevelScore(!mKick);
            }
        }

    }
}
