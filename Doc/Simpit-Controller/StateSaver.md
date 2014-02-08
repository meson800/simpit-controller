StateSaver
==========
On scenario start, if the information is available in the scenario file,
events are blocked from reaching the rest of the submodules until all of
the events recorded have been sent to StateSaver.
On scenario end, the latest events recieved are saved into the scenario
file.

Useful in automatically saving sync info into scenarios and syncronizing
physical simpits with a virtual vessel.

Options
-------
**Name Token**: STATE_SAVER

******************************

*range*: Defines the range of events that will be tracked during a scenario
and saved/loaded.  Value is two integers, the first is the starting ID of
the range, and the second is the ending ID in the range.

Any number of these may be defined.

Example:
If an Arduino reports physical switch events with ID's from 1 to 150, the
following config
```
range = 1 150
```
would make StateSaver track the states of those events.  On scenario save,
the latest states of these events would be saved into the scenario file, and
on load, StateSaver would block events until it recieved events with the same
states as the saved information.

*******************************

*mapping*:By default, StateSaver shows a dialog box with the events that have
not been recieved yet, and displays each event by it's ID.  Mapping allows a
"friendly name" to be attached to events, so the user knows which events still
need to be syncronized.

Value is an integer followed by a string.  The integer is the event ID, and the
string is the "friendly name"; no spaces are allowed in the name.

Any number of these may be defined

Example:
```
mapping = 11 Main_fuel_dump
```
Instead of StateSaver displaying "11" as an unsyncronized event, it displays
"Main_fuel_dump", and the user knows which physical switch to flip to continue
syncronization.