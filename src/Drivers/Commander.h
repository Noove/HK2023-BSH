// Includes
#include <SerialCommands.h>

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

void cmd_gui_on(SerialCommands* sender)
{
  sender->GetSerial()->println("GUI is on.");
}

void cmd_gui_off(SerialCommands* sender)
{
  sender->GetSerial()->println("GUI is off.");
}

// Command init
SerialCommand cmd_gui_on_("EnableGUI", cmd_gui_on);
SerialCommand cmd_gui_off_("DisableGUI", cmd_gui_off);

class Commander {
public:
    static void begin()
    {
        serial_commands_.SetDefaultHandler(cmd_unrecognized);
        serial_commands_.AddCommand(&cmd_gui_on_);
        serial_commands_.AddCommand(&cmd_gui_off_);
    }
};