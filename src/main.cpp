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
    Matrix::set_brightness(10);
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


long last_shake;

int clear_row[4][3]  = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

void loop()
{
    // make a rainbow sequence
    // for(int i = 0; i < 255; i++) setColor(255 - i, 0, i);
    // for(int r = 0; r < 255; r++) setColor(0, r, 255 - r);     
    // for(int r = 0; r < 255; r++) setColor(r, 255 -r, 0);
    
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
            {{0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
            {{0, 0, 255}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}},
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

        Serial.println(Sensor::get_all());

        if(Sensor::get_all() > 1250 && last_shake + 1250 < millis())
        {
            Matrix::toggle_subpixel(LED1202_GLOBAL_ADDR, (uint16_t)0x0FFFU, false);
            delay(1000);
            while(Sensor::get_all() < 2000) {}
            last_shake = millis();
        }
    }
}