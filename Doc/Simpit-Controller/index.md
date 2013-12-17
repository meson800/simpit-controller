Simpit-Controller
=================
Overview
--------
This module uses an event system and submodules to connect the physical
world to Orbiter.  

Events have two integer properties, an id and a state.

Submodules fire or recieve events, and they are capable both firing and recieving events.  
Events are not normally "blocked", and several submodules can recieve the same event.
StateSaver is the exception, as it does not make sense to process events until the simpit 
is syncronized with the virtual Orbiter world.

Quickstart
---------------
One of the simplest uses of Simpit-Controller is the auto-placement of external MFDs.
To auto-create an external MFD, add the following to the bottom of Config/simpit_config.cfg
```
BEGIN SIMPIT_MFD
POSITION x1 y1 x2 y2
END SIMPIT_MFD
```
Replace x1 and y1 with the upper left corner of where you want the MFD placed, and
replace x2 and y2 with the lower right corner.  
Simpit-controller will now automatically place and resize an external MFD in the desired location!

Avaliable Submodules
---------------------
[SerialInput](./SerialInput.md)  
[TimeBasedInput](./TimeBasedInput.md)  
[PanelEventOutput](./TimeEventOutput.md)  
[PanelEventRecorderOutput](./PanelEventRecorderOutput.md)  
[ExternalOutput](./ExternalOutput.md)  
[SimpitMFD](./SimpitMFD.md)  
