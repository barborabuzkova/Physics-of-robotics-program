
#include <IRremote.h>

#include <AFMotor.h>
#include <Servo.h>

AF_DCMotor fanmotor(1);
AF_DCMotor wheelmotor(2);
int speedfan = 0;
const int FAN_INCREMENT = 50;
int speedwheel = 0;
const int WHEEL_INCREMENT = 50;

Servo servomotor; // servo motor (contorls turning of fan and wheels)
int servo_position = 90; // servo starts perpendicular to boat body 
const int SERVO_INCREMENT = 5;

const int RECV_PIN = A14; // IR reciever starting code
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;
int reading = 0;

void setup() {
  Serial.begin(9600); // IR remote setup
  irrecv.enableIRIn();
  irrecv.blink13(true);  
  Serial.println("setuped");
  
  fanmotor.setSpeed(speedfan); // fanmotor setup
  fanmotor.run(RELEASE);
  wheelmotor.setSpeed(speedfan); // wheelmotor setup
  wheelmotor.run(RELEASE);

  servomotor.attach(9); // servomotor setup
}

void loop() {
  
  if (irrecv.decode(&results)){
           

        if (results.value == 0XFFFFFFFF)
          results.value = key_value;

        switch(results.value){
          case 0xFFA25D:
          Serial.println("Power"); // stops dc motors
          fanmotor.setSpeed(0);
          fanmotor.run(FORWARD);
          wheelmotor.setSpeed(0);
          wheelmotor.run(FORWARD);
          break;
          case 0xFF629D:
          Serial.println("+"); // vol + on remote, increases speed of the fan motor
          speedfan += FAN_INCREMENT;
          Serial.println(speedfan);
          if (speedfan >= 0) { // if-else function sets speedfan
            fanmotor.setSpeed(speedfan);
          } else {
            fanmotor.setSpeed(abs(speedfan));
          }
          if (speedfan > 0) { // if-else_if-else function moves fanmotor in desired direction
            fanmotor.run(FORWARD);
          } else if(speedfan = 0) {
            fanmotor.run(RELEASE);
          } else {
            fanmotor.run(BACKWARD);
          }
          break;
//          case 0xFFE21D:
//          Serial.println("F/St");
//          break;
          case 0xFF22DD:
          Serial.println("|<<"); // turns servo motor to the right to propel the boat to the left
          servo_position -= SERVO_INCREMENT;
          Serial.println(servo_position);
          servomotor.write(servo_position);
          break;
//          case 0xFF02FD:
//          Serial.println(">|");
//          break ;  
          case 0xFFC23D:
          Serial.println(">>|"); // turns servo motor to the left to propel the boat to the right
          servo_position += SERVO_INCREMENT;
          Serial.println(servo_position);
          servomotor.write(servo_position);
          break;
                         
          case 0xFFE01F:
          Serial.println("v"); // decreases speed of the wheel motor
          speedwheel -= WHEEL_INCREMENT;
          Serial.println(speedwheel);
           if (speedwheel >= 0) { // if-else function sets speedwheel
            wheelmotor.setSpeed(speedwheel);
          } else {
            wheelmotor.setSpeed(abs(speedwheel));
          }
          if (speedwheel > 0) { //if-else_if-else function moves wheelmotor in desired direction)
            wheelmotor.run(FORWARD);
          } else if(speedwheel = 0) {
            wheelmotor.run(RELEASE);
          } else {
            wheelmotor.run(BACKWARD);
          }
          break;
            
          case 0xFFA857:
          Serial.println("-"); // vol - on remote, decreases speed of the fan motor
          speedfan -= FAN_INCREMENT;
          Serial.println(speedfan);
          if (speedfan >= 0) { // if-else function sets speedfan
            fanmotor.setSpeed(speedfan);
          } else {
            fanmotor.setSpeed(abs(speedfan));
          }
          if (speedfan > 0) { //if-else_if-else function moves fanmotor in desired direction
            fanmotor.run(FORWARD);
          } else if(speedfan = 0) {
            fanmotor.run(RELEASE);
          } else {
            fanmotor.run(BACKWARD);
          }
          break;
            
          case 0xFF906F:
          Serial.println("^"); // increases speed of the wheel motor
          speedwheel += WHEEL_INCREMENT;
          Serial.println(speedwheel);
          if (speedwheel >= 0) { // if-else function sets speedwheel
            wheelmotor.setSpeed(speedwheel);
          } else {
            wheelmotor.setSpeed(abs(speedwheel));
          }
          if (speedwheel > 0) { //if-else_if-else function moves wheelmotor in desired direction
            wheelmotor.run(FORWARD);
          } else if(speedwheel = 0) {
            wheelmotor.run(RELEASE);
          } else {
            wheelmotor.run(BACKWARD);
          }
          break;
//          case 0xFF6897:
//          Serial.println("0");
//          break ;  
//          case 0xFF9867:
//          Serial.println("EQ");
//          break ;
//          case 0xFFB04F:
//          Serial.println("St/Rept");
//          break ;
//          case 0xFF30CF:
//          Serial.println("1");
//          break ;
//          case 0xFF18E7:
//          Serial.println("2");
//          break ;
//          case 0xFF7A85:
//          Serial.println("3");
//          break ;
//          case 0xFF10EF:
//          Serial.println("4");
//          break ;
//          case 0xFF38C7:
//          Serial.println("5");
//          break ;
//          case 0xFF5AA5:
//          Serial.println("6");
//          break ;
//          case 0xFF42BD:
//          Serial.println("7");
//          break ;
//          case 0xFF4AB5:
//          Serial.println("8");
//          break ;
//          case 0xFF52AD:
//          Serial.println("9");
//          break ;    
          default:
          Serial.println(results.value);  
        }
        key_value = results.value;
        irrecv.resume(); 
  }
}
