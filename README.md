# Arduino Stabilizer

### Background
This is a follow-up project based on the PHYS 159 lab of creating an ohmmeter using only resistors and a voltmeter.

### Project Goal
Build a device that will balance a small object on a rocking platform.

### Hardware 
- Arduino UNO
- Servo motor
- Sonar sensor
- LED's

### Design

The servo motor is used to keep the object platform horizontal relative to the ground, and the sonar sensor is used for orientation input to control the servo motor. Distance values from the sonar sensor are mapped to the servo motor. LED's were used to indicate the degree of tilt relative to the ground.

![GitHub Dark](https://github.com/mark-andrew-tan/Arduino_Stabalizer/blob/main/images/Connections%20to%20Arduino.png)

![GitHub Dark](https://github.com/mark-andrew-tan/Arduino_Stabalizer/blob/main/images/tilt.png)

### Problems with design

With the way the sonar sensor is attached to the rocking surface, the rate of change of distance of the sonar sensor to the ground is only approximately constant when the |angle of rocking surface relative to ground| < 40.

The sonar is attached to the left side of the rocking surface, and as the surface rotates clockwise, the distance seen by the sonar sensor will begin to rise rapidly and become infinite at a 90 degree rotation angle.

Since the angle of rotation of the servo motor is mapped proportionally to the distance values output from the sonar sensor, this leads to chaotic behaviour of the object platform when |angle of rocking surface relative to ground| > 50 degrees.
