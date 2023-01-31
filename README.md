# STARR-Payload
STARR Code for Arduino interface with sensors and control systems. University of Alberta Rocketry Team.

# To Do's:

 - Make function inside loop that assigns and collects all i2c sensors
 - Make a relable function to intiate data logging on lift off as well as sets time(maybe store extra data before launch)
 - Make a function that gets activated if redudancy is needed 
 - Make a data logging loop for sd card and write sensor data, and large events
 - Make a function that looks for altimeter pulses 
 - Buzzer function that activates on landing and gives debug info 

# Assigned Tasks:

- Software team to make sd comverter feel free to use any language i just randomly made a .py file
- Christiaan to do code for runme and testers 


# Problems:

- i2c datasheet for all sensors 


# Components that require code:

- I^2C Bus components
- Solenoid Valves
- Altimeter 
- buzzer for debug since lcd would require way too many pins


# Dont Do's:

- Connect IO pin to ground
- Connect 2 IO pins
- When pins are output be super careful 
- Overvolting IO pins
