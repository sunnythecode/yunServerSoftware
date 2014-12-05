
#include <Servo.h>
#include <string.h>

#define LED_DELAY 100
#define MOTOR_WATCHDOG_DELAY 200
#define MOTOR_IDLE 95
#define MIN_STRING 22
char data_read[40];
bool ledState;
bool updateOutputs = false;
Servo pin2, pin3, pin4, pin5, pin6, pin7, pin8, pin9;
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
    pin2.write(map(atoi(strtok(data_read, ",")), 0, 255, 0, 190));
    pin3.write(map(atoi(strtok(NULL, ",")), 0, 255, 0, 190));
    pin4.write(map(atoi(strtok(NULL, ",")), 0, 255, 0, 190));
    pin5.write(map(atoi(strtok(NULL, ",")), 0, 255, 0, 190));
    pin6.write(map(atoi(strtok(NULL, ",")), 0, 255, 0, 190));
    pin7.write(map(atoi(strtok(NULL, ",")), 0, 255, 0, 190));
    pin8.write(map(atoi(strtok(NULL, ",")), 0, 255, 0, 190));
    pin9.write(map(atoi(strtok(NULL, ",")), 0, 255, 0, 190));
    motorWatchdog = millis();
  }

  if (motorWatchdog + MOTOR_WATCHDOG_DELAY <millis())
  {
    pin2.write(MOTOR_IDLE);
    pin3.write(MOTOR_IDLE);
    pin4.write(MOTOR_IDLE);
    pin5.write(MOTOR_IDLE);
    pin6.write(MOTOR_IDLE);
    pin7.write(MOTOR_IDLE);
    pin8.write(MOTOR_IDLE);
    pin9.write(MOTOR_IDLE);
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
