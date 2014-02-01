PanelEventRecorderOutput
========================
Records mouse events processed by a vessel, and can generate configurations
for PanelEventOutput

Options
-------
**Name Token**: PANEL_EVENT_RECORDER

***************************************

**vessel_name**: String that defines which vessel's panel click's are recorded

Example:
```
vessel_name = GL-01
```
Records the mouse events from the vessel named "GL-01"

****************************************

*event_log_name*: File path, surrounded by quotation marks, if the user wants to log
to a non-default file-path.

Defaults to orbiterroot/Modules/Plugin/SimpitRecorderLog.log

Example:
```
event_log_name = "recorder_log.log"
```
Moves the log to orbiterroot/recorder_log.log

******************************************

*auto_record*: If 1, enables auto-config generation for PanelEventOutput

Defaults to 0

Example:
```
auto_record = 1
```
Enables auto-config generation

******************************************

*recording_log_name*: File path, surrounded by quotation marks, if the user wants to change
the location of the recorded config-file generated file.

Defaults to orbiterroot/EventRecorderOutput.log

Example:
```
recording_log_name = "auto_config_file.log"
```
Moves the generated config file to orbiterroot/auto_config_file.log

******************************************

*starting_record_id*: Integer that starts auto-config generation on a different starting user definition ID

Defaults to 1

If one already has some user definitions in PanelEventOutput, if the auto-generated file starts
at one, there will be multiple conflicting user definitions with ID=1.  Use this to start ID
numbering at another integer.

Example:
```
starting_record_id = 15
```
Starts user definitions at ID = 15.

Usage
------
Without auto-record on, mouse events will be logged to the event log in the following format:
```
panel_area_id mouse_event x_coordinate y_coordinate
```

With auto-record on, each sim-click and physical event will be logged in the following format
into the recorder log:
```
user_def = user_def_id mouse_event x_coordinate y_coordinate
event = event_id user_def_id panel_area_id
```
These lines are suitable to be copy/pasted directly into the config for PanelEventOutput.