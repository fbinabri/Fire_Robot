#include <Servo.h>
#include <NewPing.h>

#define LeftMotorForward 2
#define LeftMotorBackward 3
#define RightMotorForward 5
#define RightMotorBackward 4
#define USTrigger 8
#define USEcho 9
#define MaxDistance 100
#define FAN 10

Servo servo;
NewPing sonar(USTrigger, USEcho, MaxDistance);

unsigned int duration;
unsigned int distance;
unsigned int FrontDistance;
unsigned int LeftDistance;
unsigned int RightDistance;
unsigned int Time;
unsigned int CollisionCounter;

void setup() 
{
Serial.begin(9600);

pinMode(LeftMotorForward, OUTPUT);
pinMode(LeftMotorBackward, OUTPUT);
pinMode(RightMotorForward, OUTPUT);
pinMode(RightMotorBackward, OUTPUT);
pinMode(FAN, OUTPUT);
servo.attach(6);
}

void loop() 
{
servo.write(90);
scan();
FrontDistance = distance;
Serial.println("Front Distance = ");
Serial.print(distance);
if(FrontDistance > 40 || FrontDistance == 0)
  {
    moveForward();
  }
else
  {
    CollisionCounter = CollisionCounter + 1;
    moveStop();
    navigate();
  }
}

void moveForward()
  {
    Serial.println("");
    Serial.print("Moving Forward");
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(RightMotorForward, HIGH);
  }

 void moveBackward()
  {
    Serial.println("");
    Serial.print("Moving Backward");
    digitalWrite(LeftMotorBackward, HIGH);
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(RightMotorBackward, HIGH);
    digitalWrite(RightMotorForward, LOW);
  }

 void moveLeft()
   {
    Serial.println("");
    Serial.print("Moving Left");
    digitalWrite(LeftMotorBackward, HIGH);
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(RightMotorForward, HIGH);
   }

 void moveRight()
   {
    Serial.println("");
    Serial.print("Moving Right");
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorBackward, HIGH);
    digitalWrite(RightMotorForward, LOW);
   }

  void moveStop()
    {
      Serial.println("");
      Serial.print("Stopping");
      digitalWrite(LeftMotorBackward, LOW);
      digitalWrite(LeftMotorForward, LOW);
      digitalWrite(RightMotorBackward, LOW);
      digitalWrite(RightMotorForward, LOW);
      delay(1000);
      digitalWrite(FAN, HIGH);
      delay(1000);
      digitalWrite(FAN, LOW);
    }

  void scan()
    {
      Serial.println("");
      Serial.print("Scanning");
      Time = sonar.ping();
      distance = Time / US_ROUNDTRIP_CM;
      delay(500);
    }

  void navigate()
    {
      Serial.println("There's an Obstacle!!!");
      servo.write(167);
      delay(1000);
      scan();
      LeftDistance = distance;
      Serial.println("Left Distance =");
      Serial.print("distance");
      servo.write(0);
      delay(1000);
      scan();
      RightDistance = distance;
      Serial.println("Right Distance = ");
      Serial.print("distance");
      
}


