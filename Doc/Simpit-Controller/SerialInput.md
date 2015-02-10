SerialCommunication
===========
Connects to a serial port (possibly a USB serial port) at 9600 baud rate
and interprets messages as events.  Intercepted events are passed on to the
main SimpitManager and then onto various submodules.

Options
--------
**Name Token**: SERIAL_COMMUNICATION

******************************************

**com_port**: String describing which com port to connect to.
Always uses a baud rate of 9600.
Example:
```
com_port = COM3
```

******************************************

**format_string**: String defining a [scanf format string](http://www.cplusplus.com/reference/cstdio/scanf/) which tells SerialInput
how to interpret messages over the serial port.

SerialInput expects a format string which includes two integer (%i) values. The first is
event ID, the second is the state.
Avoid whitespace in format string.

Examples:
```
format_string = .%i,%i/
```
The above interprets the following serial port messages:
```
.10,1/.15,0/.12,2/.25,0/
```
as four events(the first with an ID of 10 and a state of 1, the second 
with an ID of 15 and a state of 0, the third with an ID of 12 and a state of 2,
and the forth with an ID of 25 and a state of 0).
  
  
```
format_string = /%i,%i\
```
The above would interpret
```
/10,1\/15,0\
```
as the first two events described above.

*****************************************

**event**: Two integers and a string that define strings to be sent over the serial port.

The first integer is the event ID to trigger on, and the second is the state to trigger on.

The string, which must be included in quotes, is sent over the serial port after being expanded by MacroExpander.

Example:
```
event = 1 1 "/<fuel_percent 0>,<fuel_percent 1>/"
```
The above would send the first two fuel tank percentages over the serial port when it receives an event with ID=1 and state=1

For example, if the first fuel tank has 98.4% and the second has 65.5% fuel, the following would be sent over the serial port:
```
/.984,.655/
```
