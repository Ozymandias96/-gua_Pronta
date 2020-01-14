# Agua_Pronta
To make tea we need to put water in a kettle and then wait for the water in the kettle to boil. 
In this project we inteded to start this process remotely.

The system must monitor the water level. 
When commanded to do so, the water heating must be started by the system and its completion detected.


The smartphone must have an indication of the state of the kettle: 
 - without water;
 - with water and available;
 - to heat and in this case for how many teas gives the water placed;
 
If available and with a minimum water level, it should be possible to start heating the water through smartphone's commands.
If the water is not available or there is not enough water the process cannot start.
If there is still enough free water for tea, it should be possible to reserve this water on your smartphone.

When the heating is over, a signal should be sent to the multiple smartphones that have successfully reserved water for tea.

For the implementation of a functional kettle, 
we made use of the Arduino system for collecting and processing the data passed to it by the sensors in use,
in this case a waterproof temperature sensor (DS18B20) and a load cell with capacity to measure weights up to 5 kg.

The Raspberry Pi acts as a our web server, which interconnects between the kettle and the end client, 
which in the case of this project is an android client.


The raspberry pi should periodically request temperature and weight sensor data to understand how much water is available 
at that time and if the temperature is desirable.
The Android client will allow you to understand the state of the kettle (ready for heating, or not enough water ready to collect).



This project was a group project from the class Sistemas Embutidos, where i was responsible for the implementation of the Arduino system.
I had to collect data from sensors and connect to the Raspberry Pi server to be able to provide the data.
