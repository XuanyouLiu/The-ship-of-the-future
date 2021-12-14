#define BLYNK_TEMPLATE_ID "TMPLOaHPeT61"
#define BLYNK_DEVICE_NAME "Final Project"
#define BLYNK_AUTH_TOKEN "_O1F1BLHNwyBBoEHyCWR1a4QXTCwrOWA"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

#include<Wire.h>
#include <Blynk.h>

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
 
int minVal=265;
int maxVal=402;
 
double x;
double y;
double z;

char auth[] = BLYNK_AUTH_TOKEN;


// you should get Auth Token in the Blynk App.
// go to the Project Settings (nut icon).


// your WiFi credentials.
// set password to "" for open networks.
char ssid[] = "AirPennNet-Device";
char pass[] = "penn1740wifi";

char arth[] = BLYNK_AUTH_TOKEN;
const int PowerOut = 14;
const int ManualOut = 12;
const int LeftOut = 13;
const int RightOut = 2;
const int LightOut = 16;
int val;
int manual;
int left;
int right;

BLYNK_WRITE(V1){
  val = param.asInt();
  if (val == 1) {
    digitalWrite(PowerOut, HIGH);
  } else {
     digitalWrite(PowerOut, LOW);
    }
}

BLYNK_WRITE(V0){
  manual = param.asInt();
  if (manual == 1) {
    digitalWrite(ManualOut, HIGH);
  } else {
     digitalWrite(ManualOut, LOW);
    }
}

BLYNK_WRITE(V2){
  left = param.asInt();
  if (left == 1) {
    digitalWrite(LeftOut, HIGH);
  } else {
     digitalWrite(LeftOut, LOW);
    }
  
}

BLYNK_WRITE(V3){
  right = param.asInt();
  if (right == 1) {
    digitalWrite(RightOut, HIGH);
  } else {
     digitalWrite(RightOut, LOW);
    }
  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PowerOut, OUTPUT);
  pinMode(ManualOut, OUTPUT);
  pinMode(LeftOut, OUTPUT);
  pinMode(RightOut, OUTPUT);
  pinMode(LightOut, OUTPUT);

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // starts the connection with Blynk using the data provided at the top (Wi-Fi connection name, password, and auth token)
  Blynk.begin(auth, ssid, pass);

}

void loop() {
  // put your main code here, to run repeatedly:
    Blynk.run();

    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr,14,true);
    AcX=Wire.read()<<8|Wire.read();
    AcY=Wire.read()<<8|Wire.read();
    AcZ=Wire.read()<<8|Wire.read();
    int xAng = map(AcX,minVal,maxVal,-90,90);
    int yAng = map(AcY,minVal,maxVal,-90,90);
    int zAng = map(AcZ,minVal,maxVal,-90,90);
 
    x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
    y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
    z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

    if (y > 20) {
      digitalWrite(LightOut, HIGH);
    } else {
      digitalWrite(LightOut, LOW);
    }
 
    Serial.print("AngleX= ");
    Serial.println(x);
 
    Serial.print("AngleY= ");
    Serial.println(y);
 
    Serial.print("AngleZ= ");
    Serial.println(z);
    Serial.println("-----------------------------------------");
 
    Blynk.virtualWrite(V5, y);
 
    delay(1000);

}
