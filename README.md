Orbiter Simpit Controller
=================

An Orbiter Module which enables Orbiter to interact with the physical world; this is useful in creating simpits.

What is it?
-----------
[Orbiter](http://orbit.medphys.ucl.ac.uk/) is a highly accurate spaceflight simulator.
Several addon developers have created additional vessels, from the Space Shuttle to the futuristic DeltaGlider IV.

The module creates an interface for Orbiter users to the outside world.  Now, external devices (for example, an
Arduino connected to outside switches/buttons) can be used to trigger mouse clicks, MFD clicks, or other inputs.

What can this be used for?
--------------------------
This module is initially set up with an empty configuration, but can be configured to make a simple or complex system.

Some uses are:  
*    Positioning those pesky External MFD's automatically at simualtion start instead of doing it manually. 
*    Outputting certain state items to a screen (such as fuel state, local dynamic pressure, etc).
*    Connecting physical switches to an Arduino/microcomputer, and having physical switches trigger virtual Orbiter
mouse clicks.
*    Running a full simpit, with physical switches, several external MFD's, and state-controlled lighting.  

Installation
------------
1. Get the latest version, either through Git or a zip file.
    * Git Method
        1. Clone the repo into an empty folder

            ```
            git clone https://github.com/meson800/simpit-controller.git
            ```
        2. Install Orbiter by unzipping the Orbiter zip file into the same folder as the cloned repo 
        3. Pull the latest version of the repo to ensure no files were overwritten
        
            ```
            git pull
            ```
    * Zip Method
        1. Download the zip file containing the latest revision (should reside at
[master.zip](https://github.com/meson800/simpit-controller/archive/master.zip))
        2. Unzip into an Orbiter installation.  

2. In Orbiter, under the Modules tab, enable "Simpit".  
3. Edit Config/simpit_config.cfg to set up the module in the desired way.  See the [documentation](/Doc/Simpit-Controller/index.md)
for more information.  

How does it work?
-----------------
The module sets up an internal event handling system.  Events are defined by two numbers; a
event ID and the event's state.  

Submodules either fire events, handle events, or even do both.  When one submodule fires an event, all submodules
have the chance to handle the event.


Contributing Information
---------------------
Users can submit bug reports and issues to help improve SimpitController.  
Developers can add their own sub-modules to add additional input/output modules to extend the capabilities of the modules  
See [CONTRIBUTING](/Doc/Simpit-Controller/CONTRIBUTING.md) for more information

License
-------
Copyright (c) 2013 Christopher Johnstone

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
