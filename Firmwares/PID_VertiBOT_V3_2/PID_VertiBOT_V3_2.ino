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
    
    //#include <PID_v1.h>
    
    #include <SoftwareSerial.h>
    #include <PololuQik.h>    
    #include <FreeSixIMU.h>
    #include <FIMU_ADXL345.h>
    #include <FIMU_ITG3200.h>
    #include <Wire.h>
    
    //Define Variables we'll be connecting to
    double Setpoint, Input, Output;
    //Aggressive
    double aggK=1, aggKp=50, aggKi=1.5, aggKd=-8; 
    //Conservative
    double consK=1, consKp=15, consKi=0.005, consKd=3;
    //Specify the links and initial tuning parameters
    //PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);
    PololuQik2s9v1 qik(2, 3, 4);
    unsigned long serialTime=0; //this will help us know when to talk with processing
    float angles[3]; // yaw pitch roll
    // Set the FreeSixIMU object
    FreeSixIMU sixDOF = FreeSixIMU();
    float error = 0;
    int   STD_LOOP_TIME  =          9;   
    int lastLoopTime = STD_LOOP_TIME;
    int lastLoopUsefulTime = STD_LOOP_TIME;
    unsigned long loopStartTime = 0;
    int a= 1;
    int buttonState = 0;
    
    void setup()
    { Serial.begin(9600);
      Setpoint =88.5;
      qik.init();
      Wire.begin();  
      delay(1000);
      sixDOF.init(); //begin the IMU 
    }
    
    void loop()
    {
      sensor();
     /*Change the tuning parameters: use Conservative Tuning Parameters when we're near
      setpoint and more agressive Tuning Parameters when we're farther away*/ 
       double gap = abs(Setpoint-Input); //distance away from setpoint
        if(gap<10)
        {  //we're close to setpoint, use conservative tuning parameters
          //myPID.SetTunings(consKp, consKi, consKd);
          Output=updatePid(Setpoint, Input, consK, consKp, consKi, consKd);
        }
        else
        {
           //we're far from setpoint, use aggressive tuning parameters
           //myPID.SetTunings(aggKp, aggKi, aggKd);
            Output=updatePid(Setpoint, Input, aggK, aggKp, aggKi, aggKd);
        }
       
        if(Input<15){    
          Output=0; }
      
      
      motores();
         if(millis()>serialTime)
      {
        
        SerialSend();
        serialTime+=500;
      }
      
      //*********************** loop timing control **************************
      lastLoopUsefulTime = millis()-loopStartTime;
      if(lastLoopUsefulTime<STD_LOOP_TIME)         delay(STD_LOOP_TIME-lastLoopUsefulTime);
      lastLoopTime = millis() - loopStartTime;
      loopStartTime = millis();
      
    } //END LOOP
    
    void motores(){
      qik.setSpeeds(Output,Output);
      //delay(5);
    }
    
    double sensor(){
    sixDOF.getEuler(angles);
    Input=abs(angles[2]);
    //Serial.println(Input);
    
    }

