#pragma once

// Includes
#include <Arduino.h>
#include <LSM6DSOSensor.h>

LSM6DSOSensor AccGyr(&Wire);

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