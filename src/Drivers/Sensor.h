#pragma once

// Includes
#include <Arduino.h>
#include <LSM6DSOSensor.h>

LSM6DSOSensor AccGyr(&Wire);
long last_shake;

class Sensor {
public:
    static void begin()
    {
        AccGyr.begin();
        AccGyr.Enable_X();  
        AccGyr.Enable_G();
    }

    static int get_all()
    {
        int32_t accelerometer[3];
        AccGyr.Get_X_Axes(accelerometer);
        return sqrt(pow(accelerometer[0],2) + pow(accelerometer[1],2) + pow(accelerometer[2],2));
    }

    static void detect_shake()
    {
        if(get_all() > 1250 && last_shake + 1250 < millis())
        {
            Matrix::toggle_subpixel(LED1202_GLOBAL_ADDR, (uint16_t)0x0FFFU, false);
            delay(1000);
            while(Sensor::get_all() < 2000) {}
            last_shake = millis();
        }
    }

    static void get_level(int8_t *level)
    {
        // Measure raw data
        int32_t accelerometer[3];
        AccGyr.Get_X_Axes(accelerometer);  
        
        // Calculate the Pitch angle (rotation around Y-axis)
        level[0] = atan(-1 * accelerometer[2] / sqrt(pow(accelerometer[0], 2) + pow(accelerometer[1], 2))) * 180 / PI;
        
        // Calculate the Roll angle (rotation around X-axis)
        level[1] = atan(-1 * accelerometer[1] / sqrt(pow(accelerometer[0], 2) + pow(accelerometer[2], 2))) * 180 / PI;
    }
};