/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo servoTwo;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int val;
int valMan;
int left;
int right;
const int FAN = 4;
const int Node = 7;
const int Manual = 8;
const int LeftIn = 6;
const int RightIn = 5;
#define trigPin 13
#define echoPin 12

void setup() {
  // attaches the servo on pin 9 to the servo object
  // the latter two arguments will give us a full 180-degree servo range
  myservo.attach(9, 544, 2400);
  servoTwo.attach(10, 544, 2400);
  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
  pinMode (Node, INPUT);
  pinMode (Manual, INPUT);
  pinMode (LeftIn, INPUT);
  pinMode (RightIn, INPUT);
  pinMode(FAN, OUTPUT);
  Serial.begin (9600);
}

void loop() {
  digitalWrite(FAN,LOW);
  val = digitalRead(Node);
  valMan = digitalRead(Manual);
  if (val == HIGH) {
    digitalWrite(FAN,HIGH);
    if (valMan == LOW){
    
    long duration, distance45, distance90, distance135;
    servoTwo.write(90);
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15); // waits 15ms for the servo to reach the position
      val = digitalRead(Node);
      if (pos == 45 || pos == 90 || pos == 135) {
        delay(1500); 
        digitalWrite (trigPin, LOW);
        delayMicroseconds (2);
        digitalWrite (trigPin, HIGH);
        delayMicroseconds (10);
        digitalWrite (trigPin, LOW);
        duration = pulseIn (echoPin, HIGH);

        val = digitalRead(Node);
        if (val == LOW){
          return;
        }

        valMan = digitalRead(Manual);
        if (valMan == HIGH) {
          return;
          }
          
        if (pos == 45){
        distance45 = (duration / 2) / 29.1;
        Serial.print("distance45: ");
        Serial.println(distance45);              
        }

       if (pos == 90) {
       distance90 = (duration / 2) / 29.1;
       Serial.print("distance90: ");
       Serial.println(distance90); 
       }

       if (pos == 135) {
       distance135 = (duration / 2) / 29.1;
       Serial.print("distance135: ");
       Serial.println(distance135); 
       }
     }
  }
  myservo.write(90);

      if (distance45 <= distance90 && distance45 <= distance135) {
        servoTwo.write(135);
        delay(5000);
      } else if (distance135 <= distance90) {
        servoTwo.write(45);
        delay(5000);
      } else {
        servoTwo.write(90);
        delay(5000);        
   } 
  } else {
    left = digitalRead(LeftIn);
    right = digitalRead(RightIn);
    if (left == HIGH) {
      servoTwo.write(45);
    } else if (right == HIGH) {
      servoTwo.write(135);
    } else {
      servoTwo.write(90);
    }
  }
 }
} 
