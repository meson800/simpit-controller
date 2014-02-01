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

Basic Setup
-----------
Configuration is done by editing the file orbiter_root/Config/simpit_config.cfg

Inside the config file, submodule configuration sections are seperated by BEGIN/END blocks
similar to standard Orbiter scenario files.  

The "name token" (SIMPIT_MFD in the following example) is generally the name of the module,
written in all uppercase letters with a underscore seperating words.

For example:
```
BEGIN SIMPIT_MFD
option_name = value
END
```
Avaliable Submodules
---------------------
See below for a list of modules; each module page has more information on individual options.
Options are in **bold** if required, and are in *italics* if optional.

[SerialInput](./SerialInput.md)  
[TimeBasedInput](./TimeBasedInput.md)  
[PanelEventOutput](./PanelEventOutput.md)  
[PanelEventRecorderOutput](./PanelEventRecorderOutput.md)  
[ExternalOutput](./ExternalOutput.md)  
[SimpitMFD](./SimpitMFD.md)  
