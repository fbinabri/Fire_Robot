#include <Servo.h>
#include <NewPing.h>

#define LeftMotorForward 2
#define LeftMotorBackward 3
#define RightMotorForward 5
#define RightMotorBackward 4
#define TrigPin 8
#define EchoPin 9
#define MaxDistance 200
#define FAN 10

Servo servo;
NewPing sonar(TrigPin, EchoPin, MaxDistance);

unsigned int duration;
unsigned int distance;
unsigned int FrontDistance;
unsigned int LeftDistance;
unsigned int RightDistance;
unsigned int Time;
unsigned int CollisionCounter;
const int analogPin = A0; //Flame sensor connected to Arduino A0 change depending on your connection
const int threshold = 400; // test this value you may need to modify it

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

// read the value of the Flame Sensor:
  int analogValue = analogRead(analogPin);
   Serial.println(analogValue); //serial print the FLAME sensor value
  
  if (analogValue > threshold) {
    digitalWrite(BuzzerPin, HIGH);
    Serial.print("High FLAME");
    moveStop();
  } 
  else if (analogValue = threshold){
    Serial.print("Low FLAME");
    digitalWrite(FAN, HIGH);
    delay(400);
    digitalWrite(FAN, LOW);
    //move to direction of scan giving the higher threshold if its left move left if its right move right
  }
  else {
    digitalWrite(FAN, LOW);
    Serial.print("No flame");
    moveForward();
  }

  delay(1);         
  
  
  
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
      if(abs(RightDistance - LeftDistance) < 5)
      {
        moveBackward();
        delay(200);
        moveRight();
        delay(100);
      }
      else if(RightDistance < LeftDistance)
      {
        moveLeft();
        delay(100);
      }
      else if(LeftDistance < RightDistance)
      {
        moveRight();
        delay(100);
      }
    }
      



