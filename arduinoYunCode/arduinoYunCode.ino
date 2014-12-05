
#include <Servo.h> 

#define LED_DELAY 100
#define MOTOR_WATCHDOG_DELAY 100
#define MOTOR_IDLE 95
char data_read[24];
bool ledState;
bool updateOutputs = false;
Servo pin2, pin3, pin4, pin5, pin6, pin7, pin8, pin9;
long ledTimeout, motorWatchdog;
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
  motorWatchdog = millis();
}
int loopCount = 0;
void loop() {
  if(Serial1.available()>10)
  {
   int i;
   for(i =0; i<11 && Serial1.read() != '!'; i++);
   if(Serial1.available() > 7 && i < 11)
   {
     Serial1.readBytes(data_read, 8);
     Serial.print((int)data_read[0] + ',' + (int)data_read[1] + ',' + (int)data_read[2]);
     updateOutputs= true;
   }
  }
  
  if(updateOutputs)
  {
    updateOutputs = false;

     pin2.write(map(data_read[0],0, 255, 0, 190)); 
     pin3.write(map(data_read[1],0, 255, 0, 190));
     pin4.write(map(data_read[2],0, 255, 0, 190));
     pin5.write(map(data_read[3],0, 255, 0, 190));
     pin6.write(map(data_read[4],0, 255, 0, 190));
     pin7.write(map(data_read[5],0, 255, 0, 190));
     pin8.write(map(data_read[6],0, 255, 0, 190));
     pin9.write(map(data_read[7],0, 255, 0, 190));
     motorWatchdog = millis();
  }
  
  if(motorWatchdog - millis() > MOTOR_WATCHDOG_DELAY)
  {
     pin2.write(MOTOR_IDLE); 
     pin3.write(MOTOR_IDLE);
     pin4.write(MOTOR_IDLE);
     pin5.write(MOTOR_IDLE);
     pin6.write(MOTOR_IDLE);
     pin7.write(MOTOR_IDLE);
     pin8.write(MOTOR_IDLE);
     pin9.write(MOTOR_IDLE);
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
