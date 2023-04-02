#pragma once

// Includes
#include <Drivers/Matrix.h>
#include <Drivers/Sensor.h>

String s= 
    "0    000  0    "
    "000  0    000  "
    "0 0   00  0 0  "
    "000  000  0 0  "
    "               "
    "000  0    0    "
    "0    000  000  "
    " 00  0 0  0 0  "
    "000  0 0  000  "
    "               "
    "0    0    000  "
    "000  000  0    "
    "0 0  0 0   00  "
    "0 0  000  000  "
    "               ";

int mod(int n, int m) {
    return (n % m + m) % m;
}

int dx = 0, dy = 0;

class Animation {
public:
    // Paints whole canvas in one color
    static void setColor(int red, int green, int blue)
    {
        for(int x = 0; x < 4; x++)
        {
            for(int y = 0; y < 4; y++) Matrix::set_pixel(x, y, red, green, blue);
        }
    }

    static void runAnimation()
    {
        for(int y = 0; y < 4; y++) {
            for(int x = 0; x < 4; x++) {
                if(s[mod(y + dy, 15) * 15 + mod(x + dx, 15)] == '0')
                {
                    Matrix::set_pixel(x, y, 255, 0, 0);
                }
                else {
                    Matrix::set_pixel(x, y, 0, 255, 255);
                }
            }
        }

        int8_t level[2];
        Sensor::get_level(level);

        if(abs(level[0]) > 10 || abs(level[1]) > 10)
        {
            if (abs(level[0]) > abs(level[1]) && level[0] > 0) // up
            {
                dy++;
                delay(2000 / abs(level[0]));
            }
            else if (abs(level[0]) > abs(level[1]) && level[0] < 0) // down
            {
                dy--;
                delay(2000 / abs(level[0]));
            }
            else if (abs(level[0]) < abs(level[1]) && level[1] > 0) // left
            {
                Matrix::set_brightness(Matrix::get_brightness() - 5);
            }
            else if (abs(level[0]) < abs(level[1]) && level[1] < 0) // right
            {
                Matrix::set_brightness(Matrix::get_brightness() + 5);
            }
        }

        Sensor::detect_shake();  
    }

private:
    // Canvas instance
    static int canvas[4][4][3];

    // Draws on canvas from array
    // static void drawCanvas(int input[4][4][3]) {
    //     Sensor::detect_shake();
    //     for (int x = 0; x < 4; x++) {
    //         for (int y = 0; y < 4; y++) {
    //             Matrix::set_pixel(y, x, input[x][y][0], input[x][y][1], input[x][y][2]);
    //         }
    //     }
    // }

    // Erases canvas content
    // static void clearCanvas() {
    //     for (int x = 0; x < 4; x++) {
    //         for (int y = 0; y < 4; y++) {
    //             canvas[x][y][0] = 0;
    //             canvas[x][y][1] = 0;
    //             canvas[x][y][2] = 0;
    //         }
    //     }
    // }
};

// Initialize canvas
// int Animation::canvas[4][4][3] = {
//     {{0, 100, 100}, {0, 100, 100}, {0, 100, 100}, {0, 100, 100}},
//     {{0, 100, 100}, {0, 100, 100}, {0, 100, 100}, {0, 100, 100}},
//     {{0, 100, 100}, {0, 100, 100}, {0, 100, 100}, {0, 100, 100}},
//     {{0, 100, 100}, {0, 100, 100}, {0, 100, 100}, {0, 100, 100}}
// };