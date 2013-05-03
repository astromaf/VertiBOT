VertiBOT
========

VertiBOT is an educational project to investigate and understand sensor fusion using kalman and complementary filter algorithm and PID control in an unstable system.

VertiBOT is an inverted pendulum platform that remains balanced by means of two tiny motors, located in the bottom of the structure. The battery is attached in the top of the main body, while the electronics board is located near the rotation axis.
The feedback signal is provided by an IMU 6Dof composed by an accelerometer and a gyro. One ATmega 328 microcontroller execute the main loop every 10 milliseconds. A wireless communication over bluetooth is used to tune and check the signal response in a Graphical User Interface software.

// Based on:
     // VARESANO's Free IMU library. The hard work is done. Fabio, We won't forget you! http://www.varesano.net/projects/hardware/FreeIMU
     // Brett Beauregard. Introducing the Pid.Good PID library and good guide http://goo.gl/QKANE
     // Patrick Olsson.X-firm System Projects. Best, Balancing guide. http://www.x-firm.com/
     // Jason Dorweiler http://www.jddorweiler.appspot.com/electronics.html
     // Much of the code is adapted from http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1284738418/all
     // and http://www.kerrywong.com/2012/03/08/a-self-balancing-robot-i
     // Bildr 6Dof IMu notes and library.http://bildr.org/2012/03/stable-orientation-digital-imu-6dof-arduino/
     // C. J.Fisher. Using and accelerometer for inclination sensing. Analog Device. AN-1057
     // Shane Colton. A Simple solution for Balance Filter. MIT. June 2007
     // J.A. Shaw. PID Algorithm & Tuning Methods. Rochester,NY.
     
     // Code,parts, video, and diagrams available in: http://madebyfrutos.wordpress.com/2013/05/02/vertibot/
 
     // Made(by)Frutos http://madebyfrutos.wordpress.com/
     // Ocero El Bierzo, Mayo'13
