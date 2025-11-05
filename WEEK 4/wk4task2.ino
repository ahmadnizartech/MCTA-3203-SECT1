#include <Wire.h>
#include <MPU6050.h>
#include <Servo.h>

MPU6050 mpu;
Servo servo;

int servoPin = 9;
int greenLED = 4;
int redLED = 3;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  servo.attach(servoPin);

  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }

  Serial.println("System Ready");
  servo.write(90); 
  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, LOW);
}

void loop() {
  
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  
  Serial.print(ax); Serial.print(",");
  Serial.print(ay); Serial.print(",");
  Serial.println(az);

  
  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == 'A') {
      servo.write(180);
      digitalWrite(greenLED, HIGH);
      digitalWrite(redLED, LOW);
    } else if (cmd == 'D') {
      servo.write(90);
      digitalWrite(greenLED, LOW);
      digitalWrite(redLED, HIGH);
    }
  }

  delay(100);
}
