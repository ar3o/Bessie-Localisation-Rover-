# Bessie-Localisation-Rover-

Adding localisation capibilities to a DFRobot Rover.

Current sensor list:
- Ultrasonic Distance Sensor - HC-SR04
- Photoresistor
- Microphone array

The rover uses a light intensity sensor to find the most intense light source in the local environment. Rover then moves the target and stops when the distance sensor registers it is in range. While moving, the rover will self-correct if the target is lost.
