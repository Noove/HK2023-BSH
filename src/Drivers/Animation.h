// Includes
#include <Drivers/Matrix.h>
#include <Drivers/Sensor.h>

// Empty canvas instance
int clear_row[4][3]  = {{0, 100, 100}, {0, 100, 100}, {0, 100, 100}, {0, 100, 100}};

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
        for (int lett = 0; lett < 3; lett++) {
            int letters[3][4][4][3] = {
                {
                {{255, 0, 0}, {0, 100, 100}, {0, 100, 100}, {0, 100, 100}},
                {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 100, 100}},
                {{255, 0, 0}, {0, 100, 100}, {255, 0, 0}, {0, 100, 100}},
                {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 100, 100}}
                },
                {
                {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 100, 100}},
                {{255, 0, 0}, {0, 100, 100}, {0, 100, 100}, {0, 100, 100}},
                {{0, 100, 100}, {255, 0, 0}, {255, 0, 0}, {0, 100, 100}},
                {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 100, 100}}
                },
                {
                {{255, 0, 0}, {0, 100, 100}, {0, 100, 100}, {0, 100, 100}},
                {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 100, 100}},
                {{255, 0, 0}, {0, 100, 100}, {255, 0, 0}, {0, 100, 100}},
                {{255, 0, 0}, {0, 100, 100}, {255, 0, 0}, {0, 100, 100}}
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
                delay(200);
            }
            for (int x = 0; x < 4; x++) {
                memcpy(canvas[3], canvas[2], sizeof(canvas[0]));
                memcpy(canvas[2], canvas[1], sizeof(canvas[0]));
                memcpy(canvas[1], canvas[0], sizeof(canvas[0]));
                memcpy(canvas[0], clear_row, sizeof(canvas[0]));
                drawCanvas(canvas);
                delay(200);
            }
            Sensor::detect_shake();
        }
    }

private:
    // Canvas instance
    static int canvas[4][4][3];

    // Draws on canvas from array
    static void drawCanvas(int input[4][4][3]) {
        Sensor::detect_shake();
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                Matrix::set_pixel(y, x, input[x][y][0], input[x][y][1], input[x][y][2]);
            }
        }
    }

    // Erases canvas content
    static void clearCanvas() {
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                canvas[x][y][0] = 0;
                canvas[x][y][1] = 0;
                canvas[x][y][2] = 0;
            }
        }
    }
};

// Initialize canvas
int Animation::canvas[4][4][3] = {
    {{0, 100, 100}, {0, 100, 100}, {0, 100, 100}, {0, 100, 100}},
    {{0, 100, 100}, {0, 100, 100}, {0, 100, 100}, {0, 100, 100}},
    {{0, 100, 100}, {0, 100, 100}, {0, 100, 100}, {0, 100, 100}},
    {{0, 100, 100}, {0, 100, 100}, {0, 100, 100}, {0, 100, 100}}
};