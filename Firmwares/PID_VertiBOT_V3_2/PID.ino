// Patrick Olsson.X-firm System Projects. Best, Balancing guide. http://www.x-firm.com/

#define   GUARD_GAIN   100.0

float last_error = 0;
float integrated_error = 0;
float pTerm = 0, iTerm = 0, dTerm = 0;

float updatePid(float targetPosition, float currentPosition, float K, float Kp, float Ki,float Kd)   {
  error = targetPosition - currentPosition; 
  pTerm = Kp * error;
  integrated_error += error;                                       
  iTerm = Ki * constrain(integrated_error, -GUARD_GAIN, GUARD_GAIN);
  dTerm = Kd * (error - last_error);                            
  last_error = error;
  return -constrain(K*(pTerm + iTerm + dTerm), -127, 127);
}
