#include <PID_v2.h>
//Variables
double Setpoint, Input, Output;
//PID parameters
double Kp=1.54, Ki=9, Kd=0.002;

//Start PID instance
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
 double smoothingObject()
{
  float samples[100];
  float average;
  int i;
  // Mengambil sampel
  for (i = 0; i < 50; i++)
  {
    samples[i] = analogRead(A0);
    delay(4);
  }

  // Merata ratakan sampel
  average = 0;
  for (i = 0; i < 50; i++)
  {
    average += samples[i];
  }
  average /= 50.0;

  return average;
}

void setup()
{
  //Start a serial connection to send data by serial connection
  Serial.begin(9600);   
  //Set point : Here is the brightness target
  Setpoint = 100;
  //Turn the PID on
  myPID.SetMode(AUTOMATIC);
  //Adjust PID values
  myPID.SetTunings(Kp, Ki, Kd);
}

void loop()
{
  //Read the value from the light sensor. Analog input : 0 to 1024. We map is to a value from 0 to 255 as it's used for our PWM function.
  Input = map(smoothingObject(), 0, 1023, 0, 255); 
  //PID calculation
  myPID.Compute();
  //Write the output as calculated by the PID function
  analogWrite(3,Output);
  //Send data by serial for plotting 
  Serial.print("Input:");
  Serial.print(Input);
Serial.print("\n");
  Serial.print("Output:");
  Serial.println(Output);
}
