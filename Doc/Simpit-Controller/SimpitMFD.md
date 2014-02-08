SimpitMFD
=========
Allows placement of an external MFD and interaction with it through
events.

Options
-------
**Name Token**: SIMPIT_MFD

*******************************

**position**: Value consists of four integers. The first pair is the
coordinates of the upper left corner, and the second pair is the
coordinates of the lower right corner.

Note: Negative values are allowed to allow for placement of External
MFD's on secondary monitors.  Also, the aspect ratio of the external
MFD is *always* fixed; if a combination of position coordinates make
create a width/height that is not of the correct aspect ratio, Orbiter
will resize the ExternalMFD to be as large as possible.  
Think of the position coordinates as defining a box; the largest
External MFD that can be placed will be placed in the box.

Example:
```
position = 10 10 300 500
```
Places an External MFD, with the upper left corner at screen coordinates
(10,10) and the lower-right corner at (300,500).

*************************************

*region*: Defines a "clip" region, in local window coordinates; only the
part of the MFD inside the clip region will be drawn.  Value is also four
integers, in the same format as position (upper left corner, then lower
right corner)

Useful for "cutting" off the non-MFD surface (with the dialog buttons) in
a simpit.

Example:
```
region = 70 70 300 500
```
Only displays the area in the MFD between the coordinates (70,70) and
(300,500), in local window coordinates.

**************************************

*event*: Simulates a mouse-click on one of the MFD buttons when a
certain event is recieved.  Three integers, defining the event ID
to trigger on, the event state to trigger on, and the button to
click on the MFD, respectivly.  An additional, optional integer
can be edited to make different events trigger mouse down/up events.

The buttons on the MFD are defined in the following way:
* Buttons 0-5 run down the left side of the MFD, with 0 at the top
and 5 at the bottom.  
* Buttons 6-11 run down the right side of the MFD, with 6 at the top
and 11 at the bottom.  
* Button 12 simulates PWR  
* Button 13 simulates SEL
* Button 14 simulates MNU

If the fourth integer is 1, then that event triggers a mouse down event.  
If the fourth integer is 0, then that event triggers a mouse up event.  
If there is no fourth integer, then a mouse click event is triggered.

Example:
```
event = 22 0 12
```
When an event (ID=22, state=0) is passed to SimpitMFD, a mouse click event
will be generated on the PWR button.
```
event = 35 1 1 1
event = 35 0 1 0
```
When event (ID=35) is passed to SimpitMFD, the state determines the action.
If state=1, a mouse down event is simulated on the second MFD button on the left,
and if state=0, a mouse up event is simulated on the same button.
