TimeBasedInput
==============
Passes events to SimpitManager and other submodules at either simulation start,
simulation end, or after a certain amount of simulation/real time has elapsed.

Options
-------
**Name Token**: TIME_BASED_INPUT

******************************************

*simulation_start*: Value is two integers seperated by a space.  At simulation
start, an event with an ID equal to the first integer, and a state equal to the second,
is fired and passed on.

Any number of these may be defined

Example:
```
simulation_start = 170 1
```
Fires an event (ID=170, state=1) at simulation start.

******************************************

*simulation_end*: Value is the same as the above, except event is fired at simulation end.

Any number of these may be defined

Example:
```
simulation_end = 12 0
```
Fires an event (ID=12, state=0) at simulation end.

******************************************

*real_time*: Value is a decimal followed by two integers.
The decimal defines how often, in real-time seconds, an event should be fired.
The two integers define an event as described above.

Any number of these may be defined

Example:
```
real_time = 1.5 54 1
```
Fires an event (ID=54, state=1) every 1.5 real seconds

******************************************

*sim_time*: Value is the same as the real_time option, except the decimal determines,
in simulation-time seconds, how often the event should be fired.

Any number of these may be defined

Example:
```
sim_time = 5.8 72 2
```
Fires an event(ID=72, state=2) every 5.8 seconds of simulation time.