/**
 * @file SensorVisitor.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "SensorVisitor.h"
#include "Sensor.h"

/**
 * Function to visit the sensor
 * Upon visiting, it stores the sensor object
 * @param sensor sensor being visited
 */
void SensorVisitor::VisitSensor(Sensor* sensor)
{
 mSensor = sensor;
}
