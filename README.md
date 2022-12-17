# Bessie-Localisation-Rover-

Adding localisation capibilities to a DFRobot Rover.

Current sensor list:
- Ultrasonic Distance Sensor - HC-SR04
- Photoresistor
- Microphone array

Rover uses light intensity sensor to find light source in local environment. Rover then moves the target and stops when distance sensor registers it is in range. While moving, the rover will self-correct if the target is lost.
