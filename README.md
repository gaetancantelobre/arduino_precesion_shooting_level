# arduino_precesion_shooting_level
Code and hardware for an Arduino Nano based electronic level for precision shooting.

Hardware :
- Ardunio Nano (i used a clone)
- PCB or Wires / Jumper Cables
- 5x 220 ohm resistors
- 5x 5v THT LEDS
- AXL345 or MPU6050
If you going for power through a LiPo : 12v schottky diode and connector of your choice.
Max consummption : 90mA

Level used for competitive shooting but can be use for airsoft players, close range shooting or whatever you want. Could even be used as an actual level.
It is important to test and change the "angle_offset" variable as the components are not always well produced so the IC can be tilted as well as when you mount it on the PCB.
If you are to change the angle range on which the LED be careful in the if conditions to avoid situations where NO LED will light up : 
EXAMPLE : if(angle < 30)
{
...
}
if( angle > 31)
{
...
}
 at value 30 it wont light up.

 If you are interested in the wiring and making PCB the schematic is just under here and the gerbers are in the repo.*

 ![image](https://github.com/gaetancantelobre/arduino_precesion_shooting_level/assets/29492892/dc5a155f-c48e-4663-b52f-4ce3f3b73a25)

 
