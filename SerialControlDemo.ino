#include <Adafruit_PWMServoDriver.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_LSM6DSOX.h>
#include <math.h>
#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11); // SRX | STX
#define rxPin 10
#define txPin 11
#define SERVOMIN 150   // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600   // This is the 'maximum' pulse length count (out of 4096)
#define USMIN 1000      // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX 2000     // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50  // Analog servos run at ~50 Hz updates
// For SPI mode, we need a CS pin
#define LSM_CS 10
// For software-SPI mode we need SCK/MOSI/MISO pins
#define LSM_SCK 13
#define LSM_MISO 12
#define LSM_MOSI 11
const float pi = 3.14159267;
Adafruit_LSM6DSOX sox;

LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int echoPin1 = 22, trigPin1 = 23;
int echoPin2 = 24, trigPin2 = 25;
int echoPin3 = 26, trigPin3 = 27;
int echoPin4 = 28, trigPin4 = 29;
int limPin1 = 30, limPin2 = 31, limPin3 = 32, limPin4 = 33;
int serFL = 15, serFR = 14, serBL = 13, serBR = 12;
int leftFwd = 1800, rightFwd = 900, leftBwd = 900, rightBwd = 1800;
struct data {
  float roll;
  float pitch;
};
void setup() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  Serial.begin(9600);
  BTserial.begin(9600);
  //  pinMode(LED_BUILTIN, OUTPUT);
  //  pinMode(trigPin1, OUTPUT);
  //  pinMode(echoPin1, INPUT);
  //  pinMode(trigPin2, OUTPUT);
  //  pinMode(echoPin2, INPUT);
  //  pinMode(trigPin3, OUTPUT);
  //  pinMode(echoPin3, INPUT);
  //  pinMode(trigPin4, OUTPUT);
  //  pinMode(echoPin4, INPUT);
  //  pinMode(limPin1, INPUT_PULLUP);
  //  pinMode(limPin2, INPUT_PULLUP);
  //  pinMode(limPin3, INPUT_PULLUP);
  //  pinMode(limPin4, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);
    while (!Serial)
      delay(10);  // will pause Zero, Leonardo, etc until serial console opens
  
      Serial.println("Adafruit LSM6DSOX test!");
  
      if (!sox.begin_I2C()) {
        // if (!sox.begin_SPI(LSM_CS)) {
        // if (!sox.begin_SPI(LSM_CS, LSM_SCK, LSM_MISO, LSM_MOSI)) {
         Serial.println("Failed to find LSM6DSOX chip");
        while (1) {
          delay(10);
        }
      }
      Serial.println("LSM6DSOX Found!");
}

void loop() {
  //  lcd.clear();
  //  float pitchDeg = getPitch();
  //  lcd.setCursor(0, 0);
  //  lcd.print("Pitch: ");
  //  lcd.print(pitchDeg);
  //  Serial.print("\t\tPitch: ");
  //  Serial.println(pitchDeg);
  //  BTserial.print("Pitch: ");
  //  BTserial.println(pitchDeg);
  //  goForward(300, 1000);
  //  delay(1000);
  //  goBackward(100, 1000);
  //  delay(1000);
  //  turnRight(50, 500);
  //  delay(1000);
  //  turnLeft(50, 500);
  //  delay(1000);
  if (Serial.available())
  {
    int x = Serial.parseInt();
    Serial.print("x = ");
    Serial.println(x);


    if (x != 0) {
      if (x == 5) {
        for (int i = 0; i < 5; i++) {
          //          pwm.writeMicroseconds(serFL, 1800);
          //          pwm.writeMicroseconds(serFR, 900);
          //          pwm.writeMicroseconds(serBL, 1800);
          pwm.writeMicroseconds(serBR, 900);
          delay(250);
          //          pwm.writeMicroseconds(serFL, 900);
          //          pwm.writeMicroseconds(serFR, 1800);
          //          pwm.writeMicroseconds(serBL, 900);
          pwm.writeMicroseconds(serBR, 1800);
          delay(250);
        }
      }
      else if (x == 1) {
        Serial.println("Forward");
        goForwardMax(1000);
        //        pwm.writeMicroseconds(serFL, 1800);
        //        pwm.writeMicroseconds(serFR, 900);
        //        pwm.writeMicroseconds(serBL, 1800);
        //        pwm.writeMicroseconds(serBR, 900);
        //        delay(500);

      }
      else if (x == 2) {
        Serial.println("Backward");
        goBackwardMax(1000);
        //        pwm.writeMicroseconds(serFL, 900);
        //
        //        pwm.writeMicroseconds(serFR, 1800);
        //        pwm.writeMicroseconds(serBL, 900);
        //        pwm.writeMicroseconds(serBR, 1800);
        //        delay(500);
      }
      else if (x == 3) {
        Serial.println("Right");
        //        FL Fwd, BL Fwd FR bwd BR bwd
        //        pwm.writeMicroseconds(serFL, leftFwd);
        //        pwm.writeMicroseconds(serFR, rightBwd);
        //        pwm.writeMicroseconds(serBL, leftFwd);
        //        pwm.writeMicroseconds(serBR, rightBwd);
        //        delay(500);
        goRightMax(1000);
      }
      else if (x == 4) {
        Serial.println("Left");
        //        pwm.writeMicroseconds(serFL, leftBwd);
        //        pwm.writeMicroseconds(serFR, rightFwd);
        //        pwm.writeMicroseconds(serBL, leftBwd);
        //        pwm.writeMicroseconds(serBR, rightFwd);
        //        delay(500);
        goLeftMax(1000);
      }

    }

    //    if (x == '1')
    //    {
    //      digitalWrite(LED_BUILTIN, HIGH);
    //      Serial.println("LED_BUILTIN On");
    //    }
    //    else if (x == '0')
    //    {
    //      digitalWrite(LED_BUILTIN, LOW);
    //      Serial.println("LED_BUILTIN Off");
    //    }
  }

  //  if (Serial.available())
  //  {
  //    byte y = Serial.read();
  //    BTserial.write(y);
  //  }
  stopMoving();
//  data inf = getData();
//  Serial.print(inf.roll);
//  Serial.print("\t");
//  Serial.println(inf.pitch);
//  delay(150);



    printData();
  //Serial.println(getPitch());
    delay(150);


}
int getDistance(int tPin, int ePin) {
  long duration;
  int distance;
  digitalWrite(tPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(tPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(tPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ePin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;  // Speed of sound wave divided by 2 (go and back)
  return distance;
}
struct data getData() {
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  sox.getEvent(&accel, &gyro, &temp);
  //  Serial.print("\t\tAccel X: ");
  //  Serial.print(accel.acceleration.x);
  //  Serial.print(" \tY: ");
  //  Serial.print(accel.acceleration.y);
  //  Serial.print(" \tZ: ");
  //  Serial.print(accel.acceleration.z);
  //  Serial.println(" m/s^2 ");
  float x = accel.acceleration.x, y = accel.acceleration.y, z = accel.acceleration.z;
  float g = 9.81f;

  // float roll = atan2(accel.acceleration.y, accel.acceleration.y);
  float roll = atan2(y, z);
  float pitch = asin(x / g);
  float rollDeg = roll * 180 / pi;
  float pitchDeg = pitch * 180 / pi;
  if ( x / g > 1) {
    pitchDeg = 90.0;
  }
  else if ( x / g < -1) {
    pitchDeg = -90;
  }
  data imuData = {rollDeg, pitchDeg};
  return imuData;
}
void printData() {
  data imuData = getData();
  float pitch = imuData.pitch;
  float roll = imuData.roll;
  Serial.print("Pitch: ");
  Serial.print(pitch);
  Serial.print("\tRoll: ");
  Serial.println(roll);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pitch: ");
  lcd.print(pitch);
  lcd.setCursor(0, 1);
  lcd.print("Roll: ");
  lcd.print(roll);

}
float getPitch() {
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  sox.getEvent(&accel, &gyro, &temp);
  //  Serial.print("\t\tAccel X: ");
  //  Serial.print(accel.acceleration.x);
  //  Serial.print(" \tY: ");
  //  Serial.print(accel.acceleration.y);
  //  Serial.print(" \tZ: ");
  //  Serial.print(accel.acceleration.z);
  //  Serial.println(" m/s^2 ");
  float x = accel.acceleration.x, y = accel.acceleration.y, z = accel.acceleration.z;
  float g = 9.81f;

  // float roll = atan2(accel.acceleration.y, accel.acceleration.y);
  float roll = atan2(y, z);
  float pitch = asin(x / g);
  float rollDeg = roll * 180 / pi;
  float pitchDeg = pitch * 180 / pi;
  if ( x / g > 1) {
    pitchDeg = 90.0;
  }
  else if ( x / g < -1) {
    pitchDeg = -90;
  }

  return pitchDeg;

}
float getMedPitch() {
  long t = millis();
  double pitchBucket = 0;
  int count = 0;
  while (millis() - t < 30) {
    pitchBucket += getPitch();
    count++;
  }
  double pitch = pitchBucket / count;
  return pitch;
}
void forward() {
  pwm.writeMicroseconds(serFL, leftFwd);
  pwm.writeMicroseconds(serFR, rightFwd);
  pwm.writeMicroseconds(serBL, leftFwd);
  pwm.writeMicroseconds(serBR, rightFwd);
}

void goForwardMax(int dly) {
  long t = millis();
  lcd.clear();
  pwm.writeMicroseconds(serFL, leftFwd);
  pwm.writeMicroseconds(serFR, rightFwd);
  pwm.writeMicroseconds(serBL, leftFwd);
  pwm.writeMicroseconds(serBR, rightFwd);
  while (millis() - t < dly) {
    long tim = millis() - t;
    BTserial.print("Going Forward");
    BTserial.println(tim);
    Serial.print("Going Forward ");
    Serial.println(tim);
    printData();
    //    Serial.println(getPitch());
    delay(150);
  }

}
void goBackwardMax(int dly) {
  long t = millis();
  lcd.clear();
  pwm.writeMicroseconds(serFL, leftBwd);
  pwm.writeMicroseconds(serFR, rightBwd);
  pwm.writeMicroseconds(serBL, leftBwd);
  pwm.writeMicroseconds(serBR, rightBwd);
  while (millis() - t < dly) {
    long tim = millis() - t;
    BTserial.print("Going Backward");
    BTserial.println(tim);
    Serial.print("Going Backward ");
    Serial.println(tim);
    printData();
    //    Serial.println(getPitch());
    delay(150);
  }

}
void goRightMax(int dly) {
  long t = millis();
  lcd.clear();
  pwm.writeMicroseconds(serFL, leftFwd);
  pwm.writeMicroseconds(serFR, rightBwd);
  pwm.writeMicroseconds(serBL, leftFwd);
  pwm.writeMicroseconds(serBR, rightBwd);
  while (millis() - t < dly) {
    long tim = millis() - t;
    BTserial.print("Going Right");
    BTserial.println(tim);
    Serial.print("Going Right ");
    Serial.println(tim);
    printData();
    //    Serial.println(getPitch());
    delay(150);
  }

}

void goLeftMax(int dly) {
  long t = millis();
  lcd.clear();
  pwm.writeMicroseconds(serFL, leftBwd);
  pwm.writeMicroseconds(serFR, rightFwd);
  pwm.writeMicroseconds(serBL, leftBwd);
  pwm.writeMicroseconds(serBR, rightFwd);
  while (millis() - t < dly) {
    long tim = millis() - t;
    BTserial.print("Going Left");
    BTserial.println(tim);
    Serial.print("Going Left ");
    Serial.println(tim);
    printData();
    //    Serial.println(getPitch());
    delay(150);
  }

}

void setHeading(int head) {
  //  double currHeading = getPitch();
  //  if(head >=0 && head <= 90{
  //    if(getPitch() < 0
  //  }
  //while (getPitch()
}




void goForward(long x, int dly) {
  long t = millis();
  lcd.clear();
  int rightSec = map(x, 200, 300, 1300, 900);
  int leftSec = map(x, 200, 300, 1300, 2000);
  pwm.writeMicroseconds(serFL, 2000);
  pwm.writeMicroseconds(serFR, 900);
  pwm.writeMicroseconds(serBL, 900);
  pwm.writeMicroseconds(serBR, 2000);
  while (millis() - t < dly) {
    long tim = millis() - t;
    BTserial.print("Going Forward");
    BTserial.println(tim);
    Serial.print("Going Forward ");
    Serial.println(tim);
    delay(100);
  }
}
void goBackward(long x, int dly) {
  long t = millis();
  lcd.clear();
  int leftSec = map(x, 100, 200, 900, 1300);
  int rightSec = map(x, 100, 200, 2000, 1300);
  pwm.writeMicroseconds(serFL, leftSec);
  pwm.writeMicroseconds(serFR, rightSec);
  pwm.writeMicroseconds(serBL, leftSec);
  pwm.writeMicroseconds(serBR, rightSec);
  long tim = millis() - t;
  BTserial.print("Going Backward");
  BTserial.println(tim);
  Serial.print("Going Backward ");
  Serial.println(tim);
  while (millis() - t < dly) {
    tim = millis() - t;
    BTserial.print("Going Backward");
    BTserial.println(tim);
    Serial.print("Going Backward ");
    Serial.println(tim);
    delay(100);
  }
}
void turnRight(long x, int dly) {
  long t = millis();
  lcd.clear();
  int leftSec = map(x, 0, 100, 1300, 2000);
  int rightSec = map(x, 0, 100, 1300, 2000);
  pwm.writeMicroseconds(serFL, leftSec);
  pwm.writeMicroseconds(serFR, rightSec);
  pwm.writeMicroseconds(serBL, leftSec);
  pwm.writeMicroseconds(serBR, rightSec);
  while (millis() - t < dly) {
    long tim = millis() - t;
    BTserial.print("Turning Right");
    BTserial.println(tim);
    Serial.print("Turning Right");
    Serial.println(tim);
    delay(100);
  }

}
void turnLeft(long x, int dly) {
  long t = millis();
  lcd.clear();
  int leftSec = map(x, 0, 100, 1300, 900);
  int rightSec = map(x, 0, 100, 1300, 900);
  pwm.writeMicroseconds(serFL, leftSec);
  pwm.writeMicroseconds(serFR, rightSec);
  pwm.writeMicroseconds(serBL, leftSec);
  pwm.writeMicroseconds(serBR, rightSec);
  while (millis() - t < dly) {
    long tim = millis() - t;
    BTserial.print("Turning Left");
    BTserial.println(tim);
    Serial.print("Turning Left");
    Serial.println(tim);
    delay(100);
  }
}
void stopMoving() {
  int leftSec = 1300;
  int rightSec = 1300;
  pwm.writeMicroseconds(serFL, leftSec);
  pwm.writeMicroseconds(serFR, rightSec);
  pwm.writeMicroseconds(serBL, leftSec);
  pwm.writeMicroseconds(serBR, rightSec);
}


//  Serial.print("\t\tTemperature ");
//  Serial.print(temp.temperature);
//  Serial.println(" deg C");

//  /* Get a new normalized sensor event */
//  sensors_event_t accel;
//  sensors_event_t gyro;
//  sensors_event_t temp;
//  sox.getEvent(&accel, &gyro, &temp);
//
//
//  /* Display the results (acceleration is measured in m/s^2) */
//  Serial.print("\t\tAccel X: ");
//  Serial.print(accel.acceleration.x);
//  Serial.print(" \tY: ");
//  Serial.print(accel.acceleration.y);
//  Serial.print(" \tZ: ");
//  Serial.print(accel.acceleration.z);
//  Serial.println(" m/s^2 ");
//
//  float x = accel.acceleration.x, y = accel.acceleration.y, z = accel.acceleration.z;
//  float g = 9.81f;
//
//  // float roll = atan2(accel.acceleration.y, accel.acceleration.y);
//  float roll = atan2(y, z);
//  float pitch = asin(x / g);
//  float rollDeg = roll * 180 / pi;
//  float pitchDeg = pitch * 180 / pi;
//  Serial.print("Pitch: ");
//  Serial.print(pitch);
//  Serial.print("\tRoll: ");
//  Serial.print(roll);
//  Serial.print("\tPitch Degrees: ");
//  Serial.print(pitchDeg);
//  Serial.print("\tRoll Degrees: ");
//  Serial.println(rollDeg);







//  for (uint16_t microsec = USMIN; microsec < USMAX; microsec += 100) {
//    pwm.writeMicroseconds(11, microsec);
//    pwm.writeMicroseconds(12, microsec);
//    pwm.writeMicroseconds(13, microsec);
//    pwm.writeMicroseconds(14, microsec);
//    pwm.writeMicroseconds(15, microsec);
//    Serial.println(microsec);
//    delay(500);
//
//  }
//
//
//  for (uint16_t microsec = USMAX; microsec > USMIN; microsec -= 100) {
//    pwm.writeMicroseconds(11, microsec);
//    pwm.writeMicroseconds(12, microsec);
//    pwm.writeMicroseconds(13, microsec);
//    pwm.writeMicroseconds(14, microsec);
//    pwm.writeMicroseconds(15, microsec);
//    Serial.println(microsec);
//    delay(500);
//  }

//  lcd.setCursor(0, 0);
//  lcd.print("Pitch: ");
//  lcd.print(pitchDeg);
//  lcd.setCursor(0, 1);
//  lcd.print("Roll: ");
//  lcd.print(rollDeg);



//  Serial.print("I = ");
//  Serial.println(i);
//  Serial.print("J = ");
//  Serial.println(j);
//  Serial.println("\n\n");

/*int dist = getDistance(trigPin1, echoPin1);
  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.println(" cm");
  int dist2 = getDistance(trigPin2, echoPin2);
  Serial.print("Distance 2: ");
  Serial.print(dist2);
  Serial.println(" cm");
  int dist3 = getDistance(trigPin3, echoPin3);
  Serial.print("Distance 3: ");
  Serial.print(dist3);
  Serial.println(" cm");
  int dist4 = getDistance(trigPin4, echoPin4);
  Serial.print("Distance 4: ");
  Serial.print(dist4);
  Serial.println(" cm");
  lcd.setCursor(0, 1);
  lcd.print(dist);
  lcd.print(" ");
  lcd.print(dist2);
  lcd.print(" ");
  lcd.print(dist3);
  lcd.print(" ");
  lcd.print(dist4);


  int state1 = digitalRead(limPin1);
  int state2 = digitalRead(limPin2);
  int state3 = digitalRead(limPin3);
  int state4 = digitalRead(limPin4);
  Serial.print(state1);
  Serial.print(" ");
  Serial.print(state2);
  Serial.print(" ");
  Serial.print(state3);
  Serial.print(" ");
  Serial.println(state4);
  lcd.setCursor(0, 2);
  lcd.print(state1);
  lcd.print(" ");
  lcd.print(state2);
  lcd.print(" ");
  lcd.print(state3);
  lcd.print(" ");
  lcd.print(state4);
*/



//  delay(1000);
