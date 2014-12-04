
#include <Servo.h> 

#define LED_DELAY 100

char data_read[24];
bool ledState;
bool updateOutputs = false;
Servo pin2, pin3, pin4, pin5, pin6, pin7, pin8, pin9;
long ledTimeout;
void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600); // Set the baud.
  while (!Serial1)
  {
  }
  Serial.begin(9600);
  pin2.attach(2);
  pin3.attach(3);
  pin4.attach(4);
  pin5.attach(5);
  pin6.attach(6);
  pin7.attach(7);
  pin8.attach(8);
  pin9.attach(9);
  
  digitalWrite(13, HIGH);
  ledState = true;
  ledTimeout = millis() + LED_DELAY;
}
int loopCount = 0;
void loop() {
  if(Serial1.available()>17)
  {
   Serial1.readBytes(data_read, 18);
   Serial.print(data_read);
   updateOutputs= true;
  }
  
  if(updateOutputs)
  {
    updateOutputs = false;
    if(data_read[1] = '!')
    {
     pin2.write(map((data_read[3]<<8+data_read[4]),-32768, 32767, 0, 255)); 
     pin3.write(map((data_read[5]<<8+data_read[6]),-32768, 32767, 0, 255));
     pin4.write(map((data_read[7]<<8+data_read[8]),-32768, 32767, 0, 255));
     pin5.write(map((data_read[9]<<8+data_read[10]),-32768, 32767, 0, 255));
     pin6.write(map((data_read[11]<<8+data_read[12]),-32768, 32767, 0, 255));
     pin7.write(map((data_read[13]<<8+data_read[14]),-32768, 32767, 0, 255));
    }
  }
  
  if(ledTimeout < millis())
  {
    ledTimeout =
    millis() + LED_DELAY;
    if(ledState)
    {
      digitalWrite(13, LOW);
      ledState = false;
    }
    else
    {
      digitalWrite(13, HIGH);
      ledState = true;
    }
  } 
}
