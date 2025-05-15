#include "AFMotor.h"
#include <Servo.h>

#define echopin A1// echo pin
#define trigpin A0// Trigger pin

//#include "I2Cdev.h"

//#include "MPU6050_6Axis_MotionApps20.h"

#include <SPI.h>

#include <RF24.h>

//#include <Servo.h>



//#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE

//#include "Wire.h"

//#endif


RF24 radio(9, 8);

const byte address[6] = "00001";



struct ControlData {

  int sensorValue;

  int rollValue;

  int pitchValue;

};





Servo myservo;

const int MOTOR_1 = 1; 
const int MOTOR_2 = 2; 
const int MOTOR_3 = 3; 
const int MOTOR_4 = 4; 

AF_DCMotor motor1(MOTOR_1, MOTOR12_64KHZ); // create motor object, 64KHz pwm
AF_DCMotor motor2(MOTOR_2, MOTOR12_64KHZ); // create motor object, 64KHz pwm
AF_DCMotor motor3(MOTOR_3, MOTOR12_64KHZ); // create motor object, 64KHz pwm
AF_DCMotor motor4(MOTOR_4, MOTOR12_64KHZ); // create motor object, 64KHz pwm
//===============================================================================
//  Initialization
//===============================================================================

int distance_L, distance_F, distance_R;
long distance;

int set = 50;
 
      int sensorValue ;

      int rollValue = 500;

      int pitchValue = 500;
 
 
void setup() {
  Serial.begin(9600);           // Initialize serial port
  Serial.println("Start");

  myservo.attach(10);
  myservo.write(90);

  pinMode (trigpin, OUTPUT);
  pinMode (echopin, INPUT );
  
  motor1.setSpeed(180);          // set the motor speed to 0-255
  motor2.setSpeed(180);
  motor3.setSpeed(180);
  motor4.setSpeed(180);
  
  radio.begin();

  radio.openReadingPipe(1, address);

  radio.startListening();
  
  
}
//===============================================================================
//  Main
//=============================================================================== 
void loop() {
    
    
    
    if (radio.available()) {

      ControlData receivedData;

      radio.read(&receivedData, sizeof(receivedData));



       sensorValue = receivedData.sensorValue;

       rollValue = receivedData.rollValue;

      pitchValue = receivedData.pitchValue;


//int motorSpeed = map(sensorValue, 0, 1023, 1000, 2000);
    
}

    
 distance_F = data();
 Serial.print("S=");
 Serial.println(distance_F);
 
 Serial.print("p=");
 Serial.println(pitchValue);
 Serial.print("r=");
 Serial.println(rollValue);
 //delay(400);
  if (distance_F > set &pitchValue>800 & pitchValue<1024){
   Serial.println("Forward");
  motor1.run(FORWARD);         // turn it on going forward
  motor2.run(FORWARD); 
  motor3.run(FORWARD); 
  motor4.run(FORWARD);
    }
    else if ( pitchValue < 400  ){
  motor1.run(BACKWARD);  // back
  motor2.run(BACKWARD); 
  motor3.run(BACKWARD); 
  motor4.run(BACKWARD);
    delay(10);}
    
    
    else if (   rollValue < 400 ){
  
    motor1.run(FORWARD);  // the other right
  motor2.run(FORWARD); 
  motor3.run(BACKWARD); 
  motor4.run(BACKWARD);
    delay(10);}
    else if (rollValue > 800 & rollValue < 1024){
        
      motor1.run(BACKWARD);   // turn it on  left
  motor2.run(BACKWARD);
  motor3.run(FORWARD); 
  motor4.run(FORWARD); 
    delay(10);} 
        
  
      else {
         motor1.run(RELEASE);         // stopped
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
      }
   // else{hc_sr4();}
}


long data(){
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  distance = pulseIn (echopin, HIGH);
  return distance / 29 / 2;
}

/*
void compareDistance(){
  if (distance_L > distance_R){
  motor1.run(BACKWARD);   // turn it on going left
  motor2.run(BACKWARD);
  motor3.run(FORWARD); 
  motor4.run(FORWARD); 
    delay(10);
  }
  else if (distance_R > distance_L){
  motor1.run(FORWARD);  // the other right
  motor2.run(FORWARD); 
  motor3.run(BACKWARD); 
  motor4.run(BACKWARD);
    delay(10);
  }
  else{
  motor1.run(BACKWARD);  // the other way
  motor2.run(BACKWARD);
  motor3.run(BACKWARD); 
  motor4.run(BACKWARD); 
   delay(10);
  motor1.run(BACKWARD);   // turn it on going left
  motor2.run(BACKWARD);
  motor3.run(FORWARD); 
  motor4.run(FORWARD); 
    delay(10);
  }
}

void hc_sr4(){
    Serial.println("Stop");
    motor1.run(RELEASE);         // stopped
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
   
    myservo.write(0);
    delay(300);
    distance_R = data();
    delay(100);
    myservo.write(170);
    delay(500);
    distance_L = data();
    delay(100);
    myservo.write(90);
    delay(300);
    compareDistance();
}

*/



