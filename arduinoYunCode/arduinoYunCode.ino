#include <Servo.h>
#include <string.h>

//uncomment to enable hardware serial debug messages
//#define DEBUG 1 

#define LED_DELAY 100
#define MOTOR_WATCHDOG_DELAY 200
#define MOTOR_IDLE 93
#define MOTOR_MAX 190
#define MOTOR_MIN 0
#define L_STICK_DEADZONE 5
#define R_STICK_DEADZONE 10
#define MIN_STRING 22

#define MTR1_SIG 5  
#define MTR1_POS 6
#define MTR1_GND 7

#define MTR2_SIG 2
#define MTR2_POS 3
#define MTR2_GND 4

//uncomment next line to invert left axis
//#define INVERT_LEFT_AXIS 1

//uncomment next line to inver right axis
#define INVERT_RIGHT_AXIS 1

char data_read[40];
bool ledState;
bool updateOutputs = false;
Servo mtr1, mtr2;
long ledTimeout, motorWatchdog;

byte oneVal;
byte twoVal;
byte threeVal;
byte fourVal;
byte fiveVal;
byte sixVal;

void setup() {
  Serial1.begin(115200); // Set the baud.
  while (!Serial1)
  {
  }
  Serial.begin(115200);
  pinMode(MTR1_SIG, OUTPUT);
  pinMode(MTR1_POS, OUTPUT);
  pinMode(MTR1_GND, OUTPUT);

  pinMode(MTR2_SIG, OUTPUT);
  pinMode(MTR2_POS, OUTPUT);
  pinMode(MTR2_GND, OUTPUT);

  digitalWrite(MTR1_POS, HIGH);
  digitalWrite(MTR1_GND, LOW);
  digitalWrite(MTR2_POS, HIGH);
  digitalWrite(MTR2_GND, LOW);

  mtr1.attach(MTR1_SIG);
  mtr2.attach(MTR2_SIG);


  digitalWrite(13, HIGH);
  ledState = true;
  ledTimeout = millis() + LED_DELAY;
  motorWatchdog = millis();
}

void loop() {
  if (Serial1.available() > MIN_STRING)
  {
    Serial.print("rdy:");
    int i;
    for (i = 0; i < MIN_STRING && Serial1.read() != '!'; i++);

    Serial1.readBytesUntil('?', data_read, 40);
	
	//check to weed out garbage data on start-up, if reasonable data size between delimiters then accept packet 
	char *gCheckStart, *gCheckEnd;
	if(gCheckStart=strchr(data_read, ','))
	{
		if(gCheckEnd = strchr(gCheckStart+1, ','))
		{
			if(gCheckEnd - gCheckStart < 7)
			{
				updateOutputs = true;
			}
		}
				
	}
	
	#ifdef DEBUG
    Serial.println(data_read);
	#endif
  }

  if (updateOutputs)
  {
    updateOutputs = false;
    data_read[0] = '0';
    oneVal = map(atoi(strtok(data_read, ",")), 0, 255, MOTOR_MIN, MOTOR_MAX);
    twoVal = map(atoi(strtok(NULL, ",")), 0, 255, MOTOR_MIN, MOTOR_MAX);
    threeVal = map(atoi(strtok(NULL, ",")), 0, 255, MOTOR_MIN, MOTOR_MAX);
    fourVal = map(atoi(strtok(NULL, ",")), 0, 255, MOTOR_MIN, MOTOR_MAX);
    fiveVal = map(atoi(strtok(NULL, ",")), 0, 255, MOTOR_MIN, MOTOR_MAX);
    sixVal = map(atoi(strtok(NULL, ",")), 0, 255, MOTOR_MIN, MOTOR_MAX);

	#ifdef DEBUG
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
	#endif


    int lftMtr = MOTOR_IDLE;
    int rghtMtr = MOTOR_IDLE;
    if(twoVal > MOTOR_IDLE + L_STICK_DEADZONE || twoVal < MOTOR_IDLE - L_STICK_DEADZONE)
    {
	#ifdef INVERT_LEFT_AXIS
      rghtMtr = map(twoVal,0,190,190,0); //right motor is inverted
      lftMtr = twoVal;		
	#else
      rghtMtr = map(twoVal,0,190,190,0); //left motor is inverted
      lftMtr = twoVal;
	#endif
    }
    if(threeVal > MOTOR_IDLE + R_STICK_DEADZONE || threeVal < MOTOR_IDLE - R_STICK_DEADZONE)
    {
	#ifdef INVERT_RIGHT_AXIS
	  rghtMtr -= threeVal - MOTOR_IDLE;
      lftMtr -= threeVal - MOTOR_IDLE;
	#else
      lftMtr += threeVal - MOTOR_IDLE;
      rghtMtr += threeVal - MOTOR_IDLE;
	#endif
    }
    
    mtr1.write(lftMtr);
    mtr2.write(rghtMtr);
    motorWatchdog = millis();
  }

  if (motorWatchdog + MOTOR_WATCHDOG_DELAY < millis())
  {
    mtr1.write(MOTOR_IDLE);
    mtr2.write(MOTOR_IDLE);
    motorWatchdog = millis();
	
	#ifdef DEBUG
    Serial.println("watchdog not feed");
	#endif
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
