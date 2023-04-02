// Includes
#include <Drivers/Matrix.h>
#include <Drivers/Sensor.h>

int r = 0;
int g = 0;
int b = 0;

void setColor(int red, int green, int blue)
{
    Matrix::set_pixel(0, 0, red, green, blue);

    // while (r != red || g != green || b != blue)
    // {
    //     if (r < red)
    //         r += 1;
    //     if (r > red)
    //         r -= 1;

    //     if (g < green)
    //         g += 1;
    //     if (g > green)
    //         g -= 1;

    //     if (b < blue)
    //         b += 1;
    //     if (b > blue)
    //         b -= 1;
    //     Matrix::set_pixel(0, 0, r, g, b);
    //     delay(10);
    // }
}

void setup()
{
    Serial.begin(115200);

    // Devices
    Wire.begin();
    Matrix::begin();
    Sensor::begin();

    for (uint8_t x = 0; x < 4; x++)
    {
        for (uint8_t y = 0; y < 4; y++)
            Matrix::set_pixel(x, y, 255, 192, 203);
    }
    
    for (uint8_t x = 100; x > 0; x -= 25)
    {
        Serial.println(x);
        Matrix::set_brightness(x);
        delay(500);
    }
    
    // while(true){}

    // Matrix::set_brightness(5);
}

void loop()
{
    // make a rainbow sequence
    setColor(255, 0, 0);
    setColor(255, 0, 255);
    setColor(0, 0, 255);
    setColor(0, 255, 255);
    setColor(0, 255, 0);
    setColor(255, 255, 0);
}

