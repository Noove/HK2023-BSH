// Includes
#include <Drivers/Matrix.h>
#include <Drivers/Sensor.h>
#include <Drivers/Animation.h>
// #include <CommandHandler.h>

// CommandHandler SerialCommandHandler;

void GUI()
{
    Serial.println("Hello world");
}

bool gui_mode;

void setup()
{
    Serial.begin(115200);

    // Devices
    Wire.begin();
    Matrix::begin();
    Sensor::begin();
    Matrix::set_brightness(20);

    // SerialCommandHandler.addCommand ("GUI", GUI);
}

void loop()
{
    // SerialCommandHandler.processSerial(Serial);

    if(gui_mode)
    {
        Serial.println("Hello world");
    }
    else
    {
    }
    Animation::runAnimation("right");

}