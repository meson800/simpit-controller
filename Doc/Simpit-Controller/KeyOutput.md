KeyOutput
=========
Simulates keyboard input in Orbiter when a specified event is called.

Options
--------
**Name Token**: KEY_OUTPUT

*****************************

*output*: When a specified event is passed to KeyOutput, a keystroke/combination
of keystrokes are sent to Orbiter.  Value consists of two
integers and a string, with an optional string on the end.  The first
two integers define the event ID and state to trigger on, the string
sets which keystrokes should be passed to Orbiter, and the optional
string defines an Orbiter vessel class.

Keystrokes are defined by a set of characters, with the following
modifiers:
* ! -- Sends an ALT keystroke  
* + -- Sends a SHIFT keystroke  
* ^ -- Sends a CONTROL keystroke  
* # -- Sends a WIN keystroke  

If the vessel class is omitted, keystrokes are sent regardless of the
current focus vessel.
If there is a vessel class defined, keystrokes are only sent if the
focus vessel is of the class defined.

Any number of these may be defined.

Example:
```
output = 10 2 ^p
```
When KeyOutput recieves an event (ID=10, state=2), the keystrokes
"CONTROL+p" (pause/unpause) are sent to Orbiter.

```
output = 11 1 k DeltaGliderIV
```
When KeyOutput recieves an event (ID=11, state=1) *and* a DGIV is
focused, the keystroke "k" is sent to Orbiter.