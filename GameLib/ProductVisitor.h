/**
 * @file ProductVisitor.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * Visitor to find a product
 */

#ifndef PRODUCTVISITOR_H
#define PRODUCTVISITOR_H
#include "ItemVisitor.h"
#include "Product.h"

/// Visitor to find a product
class ProductVisitor : public ItemVisitor
{
private:
    /// The y height to search for a product
    double mY = 0;
    /// The x coord to search for a product
    double mX = 0;
    /// Filter for the products based on the y height
    bool mFilter = false;
    /// Vector of products at this location
    std::vector<Product*> mProducts;
    /// The size of the sensor check
    double mRange = ProductDefaultSize;

public:
    /**
     * Constructor for finding products at a specific y height
     *
     * @param y The y height to search for a product
     * @param x The x coord to search for a product
     * @param range The size of the check
     */
    ProductVisitor(double y, double x, double range=ProductDefaultSize) : mY(y), mFilter(true), mX(x), mRange(range)
    {
    };
    /// Constructor for all products
    ProductVisitor()
    {
    };
    void VisitProduct(Product* product) override;

    /**
     * Gets the products found during the visitation
     *
     * @return The products found
     */
    std::vector<Product*> GetProducts()
    {
        return mProducts;
    }
};


#endif //PRODUCTVISITOR_H
