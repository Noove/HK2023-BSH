// Includes
#include <Drivers/Matrix.h>
#include <Drivers/Sensor.h>

int r = 0;
int g = 0;
int b = 0;

void setColor(int red, int green, int blue)
{
    for(int x = 0; x < 4; x++)
    {
        for(int y = 0; y < 4; y++) Matrix::set_pixel(x, y, red, green, blue);
    }
}

void setup()
{
    Serial.begin(115200);

    // Devices
    Wire.begin();
    Matrix::begin();
    Sensor::begin();

    // for (uint8_t x = 0; x < 4; x++)
    // {
    //     for (uint8_t y = 0; y < 4; y++)
    //         Matrix::set_pixel(x, y, 255, 192, 203);
    // }
    
    // for (uint8_t x = 100; x > 0; x -= 25)
    // {
    //     Serial.println(x);
    //     Matrix::set_brightness(x);
    //     delay(500);
    // }
    

    // setColor(255, 0, 0);
    
    // Matrix::set_brightness(10);
    
    // while(true){}

}
int canvas[4][4][3] = {
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
};

void clearCanvas() {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            canvas[x][y][0] = 0;
            canvas[x][y][1] = 0;
            canvas[x][y][2] = 0;
        }
    }
}

void drawCanvas(int input[4][4][3]) {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            Matrix::set_pixel(y, x, input[x][y][0], input[x][y][1], input[x][y][2]);
        }
    }
}



int clear_row[4][3]  = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

void loop()
{
    // make a rainbow sequence

    // for(int i = 0; i < 255; i++) setColor(255 - i, 0, i);
    // for(int r = 0; r < 255; r++) setColor(0, r, 255 - r);     
    // for(int r = 0; r < 255; r++) setColor(r, 255 -r, 0);
    
    // int8_t level[2];
    // Sensor::get_level(level);
    // Serial.print(level[0]);
    // Serial.print(",");
    // Serial.println(level[0]);
    // delay(100);

    // LETTERS
    for (int lett = 0; lett < 3; lett++) {
        int letters[3][4][4][3] = {
            {
            {{0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
            {{0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
            {{0, 0, 255}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}},
            {{0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}}
            },
            {
            {{0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
            {{0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
            {{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
            {{0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}}
            },
            {
            {{0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
            {{0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
            {{0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
            {{0, 0, 255}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}}
            }
        };
        for (int x = 0; x < 4; x++) {
            if(x == 1) {
                memcpy(canvas[1], canvas[0], sizeof(canvas[0]));
            } else if(x == 2) {
                memcpy(canvas[2], canvas[1], sizeof(canvas[0]));
                memcpy(canvas[1], canvas[0], sizeof(canvas[0]));
            } else if(x == 3) {
                memcpy(canvas[3], canvas[2], sizeof(canvas[0]));
                memcpy(canvas[2], canvas[1], sizeof(canvas[0]));
                memcpy(canvas[1], canvas[0], sizeof(canvas[0]));
            }
            memcpy(canvas[0], letters[lett][3-x], sizeof(canvas[0]));
            drawCanvas(canvas);
            delay(100);
        }
        for (int x = 0; x < 4; x++) {
            memcpy(canvas[3], canvas[2], sizeof(canvas[0]));
            memcpy(canvas[2], canvas[1], sizeof(canvas[0]));
            memcpy(canvas[1], canvas[0], sizeof(canvas[0]));
            memcpy(canvas[0], clear_row, sizeof(canvas[0]));
            drawCanvas(canvas);
            delay(100);
        }
        delay(500);
    }
    
    // setColor(255, 0, 255);
    // setColor(0, 0, 255);
    // setColor(0, 255, 255);
    // setColor(0, 255, 0);
    // setColor(0, 255, 0);

    // for(int i = 0; i < 765; i++)    // red to green
    // {
    //     if (i < 255)
    //         setColor(255-i, i, 0);
    //     else if (i < 510)
    //         setColor(0, 255-i, i-255);
    //     else
    //         setColor(i-510, 0, 765-i);
    // }
}

