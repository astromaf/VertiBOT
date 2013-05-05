/*

 // Codigo para Itg3200 y BMa180.
  
  void getGyroRate() {  
     LeerGyro();
     
     GYRO_rate=((Gyro_Vector[0])/(lastLoopUsefulTime));          
  }
  
  void getAccAngle() {
     LeerAcel();
     
    float r;
     
    //------------Calculate inclination angle------------------------------
     r = sqrt((float) Accel_Vector [1] * (float) Accel_Vector [1] + (float) Accel_Vector [2] * (float) Accel_Vector [2]);
     ACC_angle = (float) Accel_Vector [2] / r*256; //sine approximation *256
     
  }
  
  
  
  //*** CALIBRAR ***
  void calibrarGyro (){
    for (int i =0; i< 3;i++){  
      calibradoGyro[i] =  misfunciones.calibrarI2C (GYRO_ADDR , direcDatosGyro [i]); 
    }
  }
  
  void calibrarAcel (){
    int lecturaTeorica [3] = {0 , 0 , 16384}; // 16384 = 4096 * 4    , 4 equivale a >>  2
  
    for (int i=0; i<3; i++){
      correcOffsetBrutaAcel [i] = misfunciones.calibrarI2C (ACEL_DIR , direcDatosAcel [i]) - lecturaTeorica [i]; 
    }
  }
  
  //*** LEER ***
  void LeerGyro(){
    for (int i =0; i< 3;i++){  
      Gyro_Vector[i] =float ( misfunciones.leerGyroI2C (direcDatosGyro [i])-calibradoGyro[i])* KGYRO ;
      Gyro_Vector[i] = -(Gyro_Vector[i]); 
    }
  }//leerGyro
  
  void LeerAcel(){
    for (int i=0; i<3; i++){
      Accel_Vector [i]= float((misfunciones.leerIntI2C (ACEL_DIR , direcDatosAcel [i]))-correcOffsetBrutaAcel [i])/16384 ; // 16384 = 1024 * 4 * 4
      Accel_Vector [i]=-( Accel_Vector [i]);
  }  
  }//leer Accel   
  
  */
