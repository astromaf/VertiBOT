  // Sending Floating point values to the arduino
  // is a huge pain.  if anyone knows an easier
  // way please let know.  the way I'm doing it:
  // - Take the 6 floats we need to send and
  //   put them in a 6 member float array.
  // - using the java ByteBuffer class, convert
  //   that array to a 24 member byte array
  // - send those bytes to the arduino
  void Send_To_Arduino()
  {
    float[] toSend = new float[6];
  
    toSend[0] = float(SPField.getText());
    toSend[1] = float(InField.getText());
    toSend[2] = float(OutField.getText());
    toSend[3] = float(PField.getText());
    toSend[4] = float(IField.getText());
    toSend[5] = float(DField.getText());
    Byte a = (AMLabel.valueLabel().getText()=="Manual")?(byte)0:(byte)1;
    Byte d = (DRLabel.valueLabel().getText()=="Direct")?(byte)0:(byte)1;
    myPort.write(a);
    myPort.write(d);
    myPort.write(floatArrayToByteArray(toSend));
    justSent=true;
  } 
  
  
  byte[] floatArrayToByteArray(float[] input)
  {
    int len = 4*input.length;
    int index=0;
    byte[] b = new byte[4];
    byte[] out = new byte[len];
    ByteBuffer buf = ByteBuffer.wrap(b);
    for(int i=0;i<input.length;i++) 
    {
      buf.position(0);
      buf.putFloat(input[i]);
      for(int j=0;j<4;j++) out[j+i*4]=b[3-j];
    }
    return out;
  }
  
  
  //take the string the arduino sends us and parse it
  void serialEvent(Serial myPort)
  {
    String read = myPort.readStringUntil(10);
    if(outputFileName!="") output.print(str(millis())+ " "+read);
    String[] s = split(read, " ");
  
    if (s.length ==9)
    {
      Setpoint = float(s[1]);           // * pull the information
      Input = float(s[2]);              //   we need out of the
      Output = float(s[3]);             //   string and put it
      
      SPLabel.setValue(s[1]);           //   where it's needed
      InLabel.setValue(s[2]);           //
      OutLabel.setValue(trim(s[3]));    //
      PLabel.setValue(trim(s[4]));      //
      ILabel.setValue(trim(s[5]));      //
      DLabel.setValue(trim(s[6]));      //
      AMCurrent.setValue(trim(s[7]));   //
      DRCurrent.setValue(trim(s[8]));
      if(justSent)                      // * if this is the first read
      {                                 //   since we sent values to 
        SPField.setText(trim(s[1]));    //   the arduino,  take the
        InField.setText(trim(s[2]));    //   current values and put
        OutField.setText(trim(s[3]));   //   them into the input fields
        PField.setText(trim(s[4]));     //
        IField.setText(trim(s[5]));     //
        DField.setText(trim(s[6]));     //
       // mode = trim(s[7]);              //
        AMLabel.setValue(trim(s[7]));         //
        //dr = trim(s[8]);                //
        DRCurrent.setValue(trim(s[8]));         //
        justSent=false;                 //
      }                                 //
  
      if(!madeContact) madeContact=true;
    }
  }
  
  
  
  
