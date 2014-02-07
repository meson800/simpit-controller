ExternalOutput
==============
Allows SimpitController to call other programs/scripts in response to
an event.

Options
--------
**Name Token**: EXTERNAL_OUTPUT

**********************************

*output*: Value consists of two integers followed by two strings surrounded
by quotation marks.

The first two define the event.  The first is the event ID, and the second is
the event state.

The first string defines the program that will be called, and the second defines
the command line arguments that will be sent to the program.  Either can use the
[macro expander](MacroExpander.md).

Also, relative paths do not work well when defining the executable to run.

Any number of these can be defined.

Example:
```
output = 10 2 "C:\simpit_lighting.exe" "-n 1"
```
When the above recieves an event (ID=10, state=2), the program
C:\simpit_lighting.exe will be executed with the command line arguments "-n 1"

```
output = 1001 1 "C:\sim2.exe" "1 <fuel_percent 0 i 4>"
```
When the above recieves an event (ID=1001, state=1), it executes the program
C:\sim2.exe.  The command line arguments are run through the MacroExpander; in this
case, the remaining fuel in fuel tank 0 is multiplied by 1000 and rounded to an int
before being sent as a commnand line argument.
For example, if the main fuel tank(fuel tank 0) had 94.5% fuel remaining, "1 945"
would be sent to C:\sim2.exe as the command line argument.