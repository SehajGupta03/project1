/**
 * @file SensorVisitor.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * Visitor to visit Sensor in the game
 */
 
#ifndef SENSORVISITOR_H
#define SENSORVISITOR_H
#include "ItemVisitor.h"

/**
 * Visitor class to visit the sensor in the
 * game
 */
class SensorVisitor : public ItemVisitor {
private:
 /// Sensor object to store the sensor
 Sensor* mSensor = nullptr;

public:

 void VisitSensor(Sensor* sensor) override;

 /**
  * Getter for the sensor
  * @return Pointer to sensor object
  */
 Sensor* GetSensor() {return mSensor;};
};



#endif //SENSORVISITOR_H
