/**
 * @file ProductVisitorTest.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include <pch.h>
#include <gtest/gtest.h>
#include <ProductVisitor.h>
#include <ItemVisitor.h>

#include <Product.h>
#include <Game.h>

TEST(ProductVisitorTest, TestProductVisitor)
{
    Game game;
    std::shared_ptr<Product> product1 = std::make_shared<Product>(&game, 0);
    game.Add(product1);
    product1->SetLocation(0, 100);
    std::shared_ptr<Product> product2 = std::make_shared<Product>(&game, 0);
    product2->SetLocation(0, 1000);
    game.Add(product2);

    ProductVisitor visitor = ProductVisitor(100, 0);
    game.Accept(&visitor);

    EXPECT_EQ(visitor.GetProducts().size(), 1);
    EXPECT_EQ(visitor.GetProducts()[0]->GetY(), 100);
}
