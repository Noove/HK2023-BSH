#pragma once

// Includes
#include <SerialCommands.h>
#include <Drivers/Animation.h>

// Config
char serial_command_buffer_[32];
SerialCommands serial_commands_(&Serial, serial_command_buffer_, sizeof(serial_command_buffer_), "\r\n", " ");

/* -------------------------------------------------------------------------- */
/*                              Command Callbacks                             */
/* -------------------------------------------------------------------------- */

void cmd_unrecognized(SerialCommands* sender, const char* cmd)
{
  sender->GetSerial()->print("Unrecognized command [");
  sender->GetSerial()->print(cmd);
  sender->GetSerial()->println("]");
}

bool gui_mode = false;

void cmd_gui_on(SerialCommands* sender)
{
    sender->GetSerial()->println("GUI is on.");
    Matrix::toggle_subpixel(LED1202_GLOBAL_ADDR, (uint16_t)0x0FFFU, false);
    gui_mode = true;
}

void cmd_gui_off(SerialCommands* sender)
{
    sender->GetSerial()->println("GUI is off.");
    gui_mode = false;
}

void cmd_set_panel(SerialCommands* sender)
{
    char* r_str = sender->Next();
    char* g_str = sender->Next();
    char* b_str = sender->Next();

    int r = atoi(r_str);
    int g = atoi(g_str);
    int b = atoi(b_str);

    Animation::setColor(r, g, b);
}

void cmd_set_brightness(SerialCommands* sender)
{
    char* brt_str = sender->Next();
    int brightness = atoi(brt_str);

    Matrix::set_brightness(brightness);
}

// Command init
SerialCommand cmd_set_panel_("SetPanel", cmd_set_panel);
SerialCommand cmd_gui_on_("EnableGUI", cmd_gui_on);
SerialCommand cmd_gui_off_("DisableGUI", cmd_gui_off);
SerialCommand cmd_set_brightness_("SetBrightness", cmd_set_brightness);

/* -------------------------------------------------------------------------- */
/*                               Commander Class                              */
/* -------------------------------------------------------------------------- */

class Commander {
public:
    static void begin()
    {
        serial_commands_.SetDefaultHandler(cmd_unrecognized);
        serial_commands_.AddCommand(&cmd_gui_on_);
        serial_commands_.AddCommand(&cmd_gui_off_);
        serial_commands_.AddCommand(&cmd_set_panel_);
        serial_commands_.AddCommand(&cmd_set_brightness_);
    }
};