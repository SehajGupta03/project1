/**
 * @file ProductVisitor.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "ProductVisitor.h"

#include "Product.h"

/**
 * Visits a product and adds it to the list of products
 * if the product is touching that y coordinate or all of them if the filter is disabled
 *
 * @param product The product to visit
 */
void ProductVisitor::VisitProduct(Product* product)
{
    if (!mFilter)
    {
        mProducts.push_back(product);
        return;
    }
    if (abs(product->GetY() + product->GetYOffset() - mY) < mRange / 2 && abs(
            product->GetX() + product->GetXOffset() - mX) <
        mRange / 2)
    {
        mProducts.push_back(product);
    }
}
