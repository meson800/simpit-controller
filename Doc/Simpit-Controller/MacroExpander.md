MacroExpander
=============
Allows information to be passed on to other modules throug the use of
macros.  Macros are expanded to their latest values every time they
are used.

Format
------
** denotes required item, * denotes optional item:
```
<**macro name** **macro option** *i* *numDecimalPlaces*>
```

If an "i" is specified after the macro option, the output of the macro
is converted to an integer, and is multiplied by 10^(numDecimalPlaces)
before conversion.

Macros
------
**fuel_percent**: Converts into a number from 0 to 1, representing the
amount of fuel left in the tank determined by the macro option.

Example:
```
<fuel_percent 0>
```
If fuel tank 0 is 74.2 percent full, the macro is turned into .742

```
<fuel_percent 1 i 4>
```
If fuel tank 1 is 58.2 percent full, the macro is turned into 582

*****************************************

**fuel_mass**: Converts into the remaining fuel mass, in kilograms.
If the option is equal to -1, the total remaining fuel mass is used;
otherwise, the remaining fuel in the specified fuel tank is used.

Example:
```
<fuel_mass 0>
```
Turns into 3850, if 3850 kg of fuel remain in fuel tank 0
