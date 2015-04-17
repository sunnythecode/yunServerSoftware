
#include <Servo.h>
#include <string.h>
#define LED_DELAY 100
#define MOTOR_WATCHDOG_DELAY 200
#define MOTOR_IDLE 95
#define MIN_STRING 22
char data_read[40];
bool ledState;
bool updateOutputs = false;
Servo pin2, pin3, pin6, pin7, pin8, pin9,pin10;
long ledTimeout, motorWatchdog;
void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200); // Set the baud.
  while (!Serial1)
  {
  }
  Serial.begin(115200);
  pin2.attach(2);
  pin3.attach(3);
  pin6.attach(6);
  pin7.attach(7);
  pin10.attach(10);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  
  digitalWrite(13, HIGH);
  ledState = true;
  ledTimeout = millis() + LED_DELAY;
  motorWatchdog = millis();
}
int loopCount = 0;
    byte oneVal;
    byte twoVal;
    byte threeVal;
    byte fourVal;
    byte fiveVal;
    byte sixVal;
void loop() {
  if (Serial1.available() > MIN_STRING)
  {
    Serial.print("rdy:");
    int i;
    for (i = 0; i < MIN_STRING && Serial1.read() != '!'; i++);

    Serial1.readBytesUntil('?', data_read, 40);
    Serial.println(data_read);
    updateOutputs = true;

  }

  if (updateOutputs)
  {
    updateOutputs = false;
    data_read[0] = '0';
    oneVal = map(atoi(strtok(data_read, ",")), 0, 255, 0, 190);
    twoVal = map(atoi(strtok(NULL, ",")), 0, 255, 0, 190);
    threeVal = map(atoi(strtok(NULL, ",")), 0, 255, 0, 190);
    fourVal = map(atoi(strtok(NULL, ",")), 0, 255, 0, 190);
    fiveVal = map(atoi(strtok(NULL, ",")), 0, 255, 0, 190);
    sixVal = map(atoi(strtok(NULL, ",")), 0, 255, 0, 190);
    
    Serial.print(oneVal);
    Serial.print(" ");
    Serial.print(twoVal);
    Serial.print(" ");
    Serial.print(threeVal);
    Serial.print(" ");
    Serial.print(fourVal);
    Serial.print(" ");
    Serial.print(fiveVal);
    Serial.print(" ");
    Serial.println(sixVal);
    

    pin3.write(twoVal);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(9,HIGH);
    digitalWrite(8,LOW);
    pin10.write(fourVal);
    motorWatchdog = millis();
  }

  if (motorWatchdog + MOTOR_WATCHDOG_DELAY <millis())
  {
    pin3.write(MOTOR_IDLE);
    pin10.write(MOTOR_IDLE);
    motorWatchdog = millis();
    Serial.println("watchdog not feed");
  }


  if (ledTimeout < millis())
  {
    ledTimeout = millis() + LED_DELAY;
    if (ledState)
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
