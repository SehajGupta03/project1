/**
 * @file ProductTest.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include <pch.h>
#include <gtest/gtest.h>

#include <Game.h>
#include <Product.h>

TEST(ProductTest, XmlLoad)
{
    Game game;
    // Tests absolute positioning
    auto node = new wxXmlNode(wxXML_ELEMENT_NODE, L"product");
    node->AddAttribute(L"placement", L"200");

    Product product(&game, 0);
    product.XmlLoad(node);
    EXPECT_EQ(product.GetY(), -200);

    Product product2(&game, 200);
    product2.XmlLoad(node);
    EXPECT_EQ(product2.GetY(), -200);

    delete node;

    // Tests relative positioning
    auto node2 = new wxXmlNode(wxXML_ELEMENT_NODE, L"product");
    node2->AddAttribute(L"placement", L"+300");

    Product product3(&game, 0);
    product3.XmlLoad(node2);
    EXPECT_EQ(product3.GetY(), -300);

    Product product4(&game, 200);
    product4.XmlLoad(node2);
    EXPECT_EQ(product4.GetY(), -100);

    delete node2;
}
