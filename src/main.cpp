// Includes
#include <Arduino.h>

/* -------------------------------------------------------------------------- */
/*                                    Audio                                   */
/* -------------------------------------------------------------------------- */

#include "amogus.h"
#include "megalovania.h"
#include "audio_1.h"

uint32_t current_sample = 0;
uint32_t start = 0;

void play_audio(const uint8_t *data, uint32_t samplerate, uint32_t num_cells)
{
    double elapsed_secs = (micros() - start) / 1000000.0f;
    current_sample = elapsed_secs * samplerate;

    uint8_t sample_value = data[current_sample];
    if (current_sample < num_cells)
        analogWrite(13, sample_value);
}

/* -------------------------------------------------------------------------- */
/*                              7 segment display                             */
/* -------------------------------------------------------------------------- */

#define LATCH_PIN 4
#define CLK_PIN 7
#define DATA_PIN 8

// inverted character table for common anode displays
const byte INVERTED_NUMBERS[] = {
    // ABCDEFG
    B11000000, // 0
    B11111001, // 1
    B10100100, // 2
    B10110000, // 3
    B10011001, // 4
    B10010010, // 5
    B10000010, // 6
    B11111000, // 7
    B10000000, // 8
    B10010000  // 9
};

const byte LETTERS[] = {
    // ABCDEFG
    B11101110, // a
    B00111110, // b
    B10011100, // c
    B01111010, // d
    B10011110, // e
    B10001110, // f
    B10111100, // g
    B01101110, // h
    B00001100, // i
    B01111000, // j
    B10101110, // k
    B00011100, // l
    B11101100, // m
    B00101010, // n
    B00111010, // o
    B11001110, // p
    B11100110, // q
    B10001100, // r
    B10110110, // s
    B00011110, // t
    B00111000, // u
    B01111100, // v
    B01111110, // w
    B01101100, // x
    B01110110, // y
    B11011010  // z
};

// reverse bit order in inverted letters
const byte INVERTED_LETTERS_REVERSED[] = {
    // ABCDEFG
    B10001000, // a
    B10000011, // b
    B11000110, // c
    B10100001, // d
    B10000110, // e
    B10001110, // f
    B11000010, // g
    B10001001, // h
    B11001111, // i
    B11100001, // j
    B10001010, // k
    B11000111, // l
    B11001000, // m
    B10101011, // n
    B10100011, // o
    B10001100, // p
    B10011000, // q
    B11001110, // r
    B10010010, // s
    B10001111, // t
    B11100011, // u
    B11000001, // v
    B10000001, // w
    B11001001, // x
    B11001001, // y
    B10100100  // z
};

uint32_t last_update = 0;
const byte SEGMENT_SELECT[] = {0xF1, 0xF2, 0xF4, 0xF8};

void SendDataToSegment(byte Segment_no, byte hexValue)
{
    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, hexValue);
    shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, Segment_no);
    digitalWrite(LATCH_PIN, HIGH);
}

void setDisplay(byte digit1, byte digit2, byte digit3, byte digit4)
{
    if (micros() - last_update < 5000)
        return;

    SendDataToSegment(SEGMENT_SELECT[0], digit1);
    SendDataToSegment(SEGMENT_SELECT[1], digit2);
    SendDataToSegment(SEGMENT_SELECT[2], digit3);
    SendDataToSegment(SEGMENT_SELECT[3], digit4);

    // Clean
    SendDataToSegment(0x00, 0xFF);

    last_update = micros();
}

/* -------------------------------------------------------------------------- */
/*                                 LED Output                                 */
/* -------------------------------------------------------------------------- */

// LED output
void setLEDs(byte leds)
{
    digitalWrite(10, !(leds & 0b001));
    digitalWrite(11, !(leds & 0b010));
    digitalWrite(12, !(leds & 0b100));
}

/* -------------------------------------------------------------------------- */
/*                               Wave Generator                               */
/* -------------------------------------------------------------------------- */

enum WaveType
{
    SQUARE,
    SAWTOOTH,
    TRIANGLE,
    SINE
};

WaveType current_wave = SQUARE;

void generateWave(WaveType type, uint16_t freq)
{
    uint8_t sample_value = 0;
    uint32_t period, elapsed_micros;

    // Calculate wave width
    period = 1000000 / freq;

    // Calculate offset time
    elapsed_micros = (micros() - start);

    switch (type)
    {
    case SAWTOOTH:
        // Calculate current value of a sawtooth wave with given frequency at current time
        sample_value = 255 * 2 * abs(int16_t((elapsed_micros % period) - period)) / period;
        setDisplay(INVERTED_LETTERS_REVERSED[18], INVERTED_LETTERS_REVERSED[0], INVERTED_LETTERS_REVERSED[22], 0xFF);
        break;
    case SQUARE:
        // Calculate square wave value
        sample_value = (elapsed_micros % period) < period / 2 ? 0 : 255;
        setDisplay(INVERTED_LETTERS_REVERSED[18], INVERTED_LETTERS_REVERSED[17], INVERTED_LETTERS_REVERSED[18], 0xFF);
        break;
    case TRIANGLE:
        sample_value = 255 * 2 * abs(int16_t((elapsed_micros % period) - period / 2)) / period;
        setDisplay(INVERTED_LETTERS_REVERSED[19], INVERTED_LETTERS_REVERSED[17], INVERTED_LETTERS_REVERSED[6], 0xFF);
        break;
    case SINE:
        // Calculate sine wave value
        sample_value = 127 + 127 * sin(2 * PI * freq * elapsed_micros / 1000000);
        setDisplay(INVERTED_LETTERS_REVERSED[18], INVERTED_LETTERS_REVERSED[8], INVERTED_LETTERS_REVERSED[13], 0xFF);
        break;
    }

    // Output sample
    analogWrite(13, sample_value);
}

/* -------------------------------------------------------------------------- */
/*                               Program routine                              */
/* -------------------------------------------------------------------------- */

enum Program
{
    SIG,
    REC,
    VOC,
};

Program program = SIG;

void btn1()
{
    program = SIG;
    current_wave = (WaveType)((current_wave + 1) % 4);

    // Start wave
    current_sample = 0;
    start = micros();
}
void btn2()
{
    program = REC;

    // Reset audio
    current_sample = 0;
    start = micros();
}
void btn3()
{
    program = VOC;
}

/* -------------------------------------------------------------------------- */
/*                                Initialiation                               */
/* -------------------------------------------------------------------------- */

void setup()
{
    // Initialize interface
    Serial.begin(115200);

    // Initialize DAC & PWM
    analogWriteResolution(8);

    // Initialize seven segment
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);

    // Initialize buttons
    attachInterrupt(digitalPinToInterrupt(A0), btn1, FALLING);
    attachInterrupt(digitalPinToInterrupt(A2), btn2, FALLING);
    attachInterrupt(digitalPinToInterrupt(A3), btn3, FALLING);

    // Initialize LEDs
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
}

/* -------------------------------------------------------------------------- */
/*                              Voice Synthesizer                             */
/* -------------------------------------------------------------------------- */

#include "Talkie.h"
#include "Vocab_US_Large.h"

Talkie voice;

void whoop_sound()
{
    current_sample = 0;
    start = micros();

    uint32_t whoop_start = millis();
    uint32_t i = 0, offset = 0;

    while (millis() - whoop_start < 500)
    {
        if (i % 50 == 0)
            offset++;
        generateWave(SQUARE, 300 + offset);
        i++;
    }
}

void voiceDemo()
{
    for (int i = 0; i < 2; i++)
    {
        whoop_sound();
        delay(250);
    }

    voice.say(sp2_DANGER);
    delay(500);
    voice.say(sp2_PULL);
    voice.say(sp2_UP);
    delay(1000);
}

/* -------------------------------------------------------------------------- */
/*                                Program Loop                                */
/* -------------------------------------------------------------------------- */

void loop()
{
    switch (program)
    {
    case SIG:
        generateWave(current_wave, 440);
        setLEDs(0b100);
        break;
    case REC:
        setLEDs(0b010);
        setDisplay(INVERTED_LETTERS_REVERSED[17], INVERTED_LETTERS_REVERSED[14], INVERTED_LETTERS_REVERSED[2], 0xFF);
        // play_audio(amogus_DATA, amogus_SAMPLERATE, amogus_NUM_CELLS);
        play_audio(AUDIO_DATA, AUDIO_SAMPLERATE, AUDIO_NUM_CELLS);
        break;
    case VOC:
        setLEDs(0b001);
        setDisplay(INVERTED_LETTERS_REVERSED[21], INVERTED_LETTERS_REVERSED[14], INVERTED_LETTERS_REVERSED[2], 0xFF);
        voiceDemo();
        break;
    }
}