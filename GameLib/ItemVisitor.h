/**
 * @file ItemVisitor.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * Base visitor class for all the Items
 *
 */

#ifndef ITEMVISITOR_H
#define ITEMVISITOR_H

class Beam;
class Conveyor;
class Gate;
class Item;
class Pin;
class Product;
class Scoreboard;
class Sensor;
class Sparty;
class PropertyBox;

/**
 * Base visitor class for all the items
 */
class ItemVisitor {
protected:
 /**
  * Constructor
  * made it protected to make it purely
  * abstract class
  */
 ItemVisitor() {};
private:

public:
 /**
  * Virtual desctructor
  */
 virtual ~ItemVisitor() {};

 /**
  * Virtual function to visit gates
  * @param gate gates being visited
  */
 virtual void VisitGates(Gate* gate) {};

 /**
  * Virtual function to visit conveyors
  * @param conveyor conveyors being visited
  */
 virtual void VisitConveyors(Conveyor* conveyor) {};

 /**
  * Virtual function to visit products
  * @param product product being visited
  */
 virtual void VisitProduct(Product* product) {};

 /**
  * Virtual function to visit sparty
  * @param sparty sparty being visited
  */
 virtual void VisitSparty(Sparty* sparty) {};

 /**
  * Visitor to visit Property Boxes
  * @param box the property box being visited
  */
 virtual void VisitPropertyBox(PropertyBox* box) {};

 /**
  * 
  * @param sensor the sensor in the game
  */
 virtual void VisitSensor(Sensor* sensor) {};

};



#endif //ITEMVISITOR_H
