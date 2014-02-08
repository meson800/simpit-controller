How to Contribute
==================

Submitting Bugs
---------------
Either report bugs in the development [thread](http://orbiter-forum.com/showthread.php?t=32882)

or report it through GitHub:
* Make sure you have a [GitHub account](https://github.com/signup/free)
* Submit a ticket for your issue, assuming one does not already exist.
  * Clearly describe the issue including steps to reproduce when it is a bug.
  * Make sure you fill in the earliest version that you know has the issue.
* Fork the repository on GitHub by clicking on the "Clone in Windows" button or 
run the following command in a git shell.
```
git clone https://github.com/meson800/simpit-controller.git
```
* To build the project you will need to have some version of Visual Studio 2012 installed
* If you are debugging in Release mode, you must change the Debug command to include your path
to orbiter.exe.  For some reason, Visual Studio does not allow this to be a relative path.

Adding Submodules
-----------------
* Create new header/cpp files to contain your class.
* Decide which class you want to inherit from:
  * Most submodules should inherit from IO if it is doing basic firing/recieving events
  * If your submodule acts on Orbiter Core when it recieves an event, inherit from threadSafeOutput
* Override the load and handleEvent (threadSafeHandleEvent if you inherited from threadSafeOutput)
as a minimum
* If your submodule needs to fire events, include SimpitObserver.h and call SimpitObserver.handleEvent
to send an event to the rest of the submodules.
* In ModuleFactory.h, add an include to your submodule.
* In ModuleFactory.cpp, add lines of code inside createModules to create your submodule, you should be
able to figure out the patter from the existing code.
* Add documentation similar to the other documentation in Doc/Simpit-Controller
* Submit a patch to me via email (meson800@gmail.com) or submit a pull request.

Git-Making Changes
------------------

* Create a topic branch off develop (don't work directly on develop).
* Make commits of logical units.
* Provide descriptive commit messages in the proper format (GitHub for Windows 
  helps get the format correct).

Git-Submitting Changes
-----------------------

* Push your changes to a topic branch in your fork of the repository.
* Submit a pull request. Note what issue/issues your patch fixes.

