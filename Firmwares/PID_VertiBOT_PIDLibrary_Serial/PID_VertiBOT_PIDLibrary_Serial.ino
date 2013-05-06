    /********************************************************
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
     
     ********************************************************/
#include <PID_v1.h>

#include <SoftwareSerial.h>
#include <PololuQik.h>

#include <FreeSixIMU.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <Wire.h>

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Define the aggressive and conservative Tuning Parameters
double aggKp=66, aggKi=4, aggKd=4;
double consKp=1, consKi=0.05, consKd=0.5;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);

unsigned long serialTime=0; //this will help us know when to talk with processing
PololuQik2s9v1 qik(2, 3, 4);

float angles[3]; // yaw pitch roll

// Set the FreeSixIMU object
FreeSixIMU sixDOF = FreeSixIMU();
int a= 1;
int buttonState = 0;

void setup()
{
   Serial.begin(9600);
  pinMode(7, INPUT); 
  pinMode(13, OUTPUT); 
  Setpoint =89;
  qik.init();
  myPID.SetOutputLimits(-127, 127); //[-127, 127]//tell the PID to range between motor PWM response
  myPID.SetSampleTime(10);  // Ensure that the PID is called at regular interval  
  //turn the PID on
  myPID.SetMode(MANUAL);
  Wire.begin();
  
  delay(5);
  sixDOF.init(); //begin the IMU
 
}

void loop()
{
  //Input = analogRead(A0); //read angle[2]
  sensor();
 /*Change the tuning parameters: use Conservative Tuning Parameters when we're near
  setpoint and more agressive Tuning Parameters when we're farther away*/ 
   double gap = abs(Setpoint-Input); //distance away from setpoint
    if(gap<10)
    {  //we're close to setpoint, use conservative tuning parameters
      myPID.SetTunings(consKp, consKi, consKd);
    }
    else
    {
       //we're far from setpoint, use aggressive tuning parameters
       myPID.SetTunings(aggKp, aggKi, aggKd);
    }
   
  myPID.Compute();
  motores();
 // analogWrite(5,Output); //write the motor response
//Serial.println(Output);
  //send-receive with processing if it's time
  if(millis()>serialTime)
  { boton();
    ajuste();
    SerialReceive();
    SerialSend();
    serialTime+=500;
  }
  
} //END LOOP

void motores(){
  qik.setSpeeds(-Output,-Output);
  //delay(5);
}

double sensor(){
sixDOF.getEuler(angles);
Input=abs(angles[2]);

//Serial.print(Input);
//Serial.print("   ");
}

void ajuste(){
    consKp=0.007*analogRead(A2);
    consKi=0.001*analogRead(A1)+1;
    consKd=0.001*analogRead(A0);
}

void boton(){
  buttonState = digitalRead(7);
  // compare the buttonState to its previous state
  if (buttonState != 1) { 
     a=a*-1;    
    if (a==1){
      digitalWrite(13, LOW);
       myPID.SetMode(MANUAL);
       Output=0;
    }else if(a==-1){
      digitalWrite(13, HIGH);
       myPID.SetMode(AUTOMATIC);
       
    }   
  }
}


