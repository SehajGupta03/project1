/**
 * @file Sensor.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * This class represents the sensor of the game
 */
 
#ifndef SENSOR_H
#define SENSOR_H
#include "Item.h"
#include "PropertyBox.h"

/// The image file for the sensor cable
const std::wstring SensorCableImage = L"images/sensor-cable.png";

/// The image file for the sensor camera
const std::wstring SensorCameraImage = L"images/sensor-camera.png";

/// How far below Y location of the sensor system is the panel top?
const int PanelOffsetY = 87;

/// How much space for each property
const wxSize PropertySize = wxSize(100, 40);

/// Size of a shape as a property in virtual pixels
const double PropertyShapeSize = 32;

/// Range where a product is viewed by the sensor relative
/// to the Y coordinate of the sensor.
const int SensorRange[] = {-40, 15};

/// The background color to draw the sensor panel
const wxColour PanelBackgroundColor = wxColour(128, 128, 128);


/**
 * This class represents the sensor of the game.
 * One item can activate atmost 3 output pins at a time.
 * Inherited from Item
 * Can have variable number of supported outputs
 */
class Sensor : public Item {
private:
 /// The image for the camera
 std::shared_ptr<wxImage> mCameraImage;

 /// The image for the cable
 std::shared_ptr<wxImage> mCableImage;

 /// Vector of all the Property Boxes
 std::vector<std::shared_ptr<PropertyBox>> mBoxes;


public:
 Sensor() = delete;
 Sensor(const Sensor &) = delete;
 void operator=(const Sensor &) = delete;

 Sensor(Game* game);

 void XmlLoad(wxXmlNode* node) override;
 void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

 /**
  * Function to call appropriate function on visitor
  * @param visitor ItemVisitor
  */
 void Accept(ItemVisitor* visitor) override {visitor->VisitSensor(this);};

 void PropertyBoxState(Product* product);
 void Reset();
};



#endif //SENSOR_H
