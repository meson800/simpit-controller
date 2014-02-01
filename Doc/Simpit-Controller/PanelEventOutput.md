PanelEventOutput
================
Responds to recieving certain events by simulating mouse clicks on certain
2D virtual panel areas.
Useful to allow a simpit to control vessel-specific panel buttons (like 
the APU on an XR vehicle).

**Although the configuration syntax is set up in such a way that one can
manually set up this submodule, it can be confusing.  I recommend that 
anyone wanting to use this module use PanelEventRecorderOutput in
"auto-record" mode, which automatically generates this configuration.  Then,
the configuration can be manually edited if any edits are needed.**

Options
-------
**Name Token**: PANEL_EVENT_OUTPUT

**************************************

**vessel_name**: String that defines which vessel that PanelEventOutput should 
generate mouse clicks for.  PanelEventOutput will not generate any mouse clicks
if the specified vessel does not exist.

Example:
```
vessel_name = GL-01
```
PanelEventOutput will simulate mouse clicks on GL-01's panel.

**************************************

*user_def*: A user definition which stores information, linked to an ID,
about the state of an event which determines when it is fired, the coordinates
of the mouse click on a panel area, and the "mouse event" which determines which
type of mouse click(left button down/up, right button down/up) to simulate.

Value is in the form of a single integer, which is the ID of the user definition,
followed by any number of sets of four integers.  The first integer in the set is
the state in which to fire the mouse click, the second and third numers is the x
and y coordinate of the mouse click, respectivly, and the forth number is the mouse
event.

Any number of these can be defined.

Example:
```
user_def = 1 0 10 10 1
```
The above user definition, with an ID of one, will simulate a mouse click
at coordinates (10,10) with a mouse event of 1(left button down), when a linked event's
state is 0.

```
user_def = 2 0 10 10 1 1 30 10 1
```
The above user definition, with an ID of 2, will take the same action as above when a 
linked event's state is 0.  However, when the linked event's state is 1, this user definition
simulates a mouse click at coordinates (30,10) with a mouse event of 1.

***************************************

*state_dependent*: Adds a condition to a certain user-def; the specified user definition will
only simulate a mouse click when the named event (with the correct ID and state) has been
fired previously.

Value consists of three integers; the first is the ID number of the user definition, the second is the
desired event ID, and the third is the desired event state.

```
state_dependent = 2 10 1
```
The above makes user definition #2 only simulate a mouse click when the most recent event with 
an ID=10 had a state of 1.  This is useful, depending on the simpit setup, to simualte multi-
position switches.

***************************************

*event*: Specifies when a specific user definition should be called; also contains information
about which panel area should be clicked.

Value consists of three integers:
The first is the event ID to trigger on; when an event of
that ID is sent to PanelMouseEvent, the coorsponding user definition is checked.  If the event's
state matches one of the state definitions, then that mouse event is simulated.  
The second is the panel area ID which uniquly specifies an area on a 2D panel.  This can be found
using PanelClickRecorderOutput.  
The third is the user definition ID to link this event to.

Example:
```
event = 10 53 1
```
The above links event ID 10 with user definition 1.  When an event with ID=10 is triggered, user
definition 1 is checked.  If there is a set handling that event's state, a mouse click is simulated
at the user definition's coordinates on panel area #53.