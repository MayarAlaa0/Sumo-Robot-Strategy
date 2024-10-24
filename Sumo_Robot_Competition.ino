/*this documentation to explain sumo robot code and steps to excute it :
MOTOR 1 ==> LEFT MOTOR (LOW , HIGH) ==> FORWARD
MOTOR 2 ==> RIGHT MOTOR (HIGH , LOW) ==> FORWARD

*/

//motor driver L298N
#define ENA 11
#define IN1 10
#define IN2 9
#define IN3 8
#define IN4 7
#define ENB 6
//ultrasonic
#define trigPin01 15
#define echoPin01 14
#define trigPin02 5
#define echoPin02 4
//ir
#define irPin01 16
#define irPin02 3
//line follower
#define lineFollower01 17
#define lineFollower02 18
//Global Vars
const int scoutSpeed = 150;//initial speed here for scouting field
const int attackSpeed = 220; // direct attack robot
const int turnSpeed = 120;//turn around to attack robot
const int ultrasonicThreshold = 10; 
const int linefollowerThreshold = 500;
const int forwardDuration = 1000;
int time=0;
// Timing Variables for motor turning direction
unsigned long previousMillis = 0;
const long interval = 444.4444444444444;  // Change direction every 3 seconds

// Variable to track turning direction (0 = turning right, 1 = turning left)
int turnState = 0;


void initMotors()
{
  pinMode(IN1 , OUTPUT);
  pinMode(IN2 , OUTPUT);
  pinMode(IN3 , OUTPUT);
  pinMode(IN4 , OUTPUT);
  pinMode(ENA , OUTPUT);
  pinMode(ENB , OUTPUT);
  initSpeed(scoutSpeed);
}
void initSensors()
{
  pinMode(trigPin01 , OUTPUT);
  pinMode(echoPin01 , INPUT);
  pinMode(trigPin02 , OUTPUT);
  pinMode(echoPin02 , INPUT);

  pinMode(irPin01 , INPUT);
  pinMode(irPin02 , INPUT);

  pinMode(lineFollower01 , INPUT);
  pinMode(lineFollower02 , INPUT);
}
void initSpeed(int speed)
{
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  initMotors();
  initSensors();




}

void catchIR(){
  if(readIR01() == 1){
    initSpeed(scoutSpeed);
    backward();
    delay(500);
    right();
    delay(500);
    initSpeed(attackSpeed);
    forward();
  }else if(readIR02() == 1){
    initSpeed(scoutSpeed);
    backward();
    delay(500);
    left();
    delay(500);
    initSpeed(attackSpeed);
    forward();
  }
}
void Catch(){
  if(readUltrasonic01() <=50 && readUltrasonic02() >50){
    turnRight(40);
    delay(80);
  }else if(readUltrasonic02() <=50 && readUltrasonic02() >50){
    turnleft(40);
    delay(80);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //scout 
//initSpeed(scoutSpeed);
//catchIR();

initSpeed(scoutSpeed);
search();
//defenseWlineFollower();
//Catch();

/*
while(readUltrasonic01() <= 30 || readUltrasonic02() <= 30)
{
  defenseWlineFollower();
  initSpeed(attackSpeed);
  forward();
  //Catch();
}
*/
//end of loop
}


void search(){
  turnleft(10);
  delay(10);
  while(readUltrasonic01() <= 30 || readUltrasonic02() <= 30)
{
  defenseWlineFollower();
  initSpeed(attackSpeed);
  forward();
  //Catch();
}
  turnleft(10);
  delay(10);
  while(readUltrasonic01() <= 30 || readUltrasonic02() <= 30)
{
  defenseWlineFollower();
  initSpeed(attackSpeed);
  forward();
  //Catch();
}
  turnleft(10);
  delay(10);
  while(readUltrasonic01() <= 30 || readUltrasonic02() <= 30)
{
  defenseWlineFollower();
  initSpeed(attackSpeed);
  forward();
  //Catch();
}
  turnleft(10);
  delay(10);
  while(readUltrasonic01() <= 30 || readUltrasonic02() <= 30)
{
  defenseWlineFollower();
  initSpeed(attackSpeed);
  forward();
  //Catch();
}
  turnRight(10);
  delay(10);
  while(readUltrasonic01() <= 30 || readUltrasonic02() <= 30)
{
  defenseWlineFollower();
  initSpeed(attackSpeed);
  forward();
  //Catch();
}
  turnRight(10);
  delay(10);
  while(readUltrasonic01() <= 30 || readUltrasonic02() <= 30)
{
  defenseWlineFollower();
  initSpeed(attackSpeed);
  forward();
  //Catch();
}
  turnRight(10);
  delay(10);
  while(readUltrasonic01() <= 30 || readUltrasonic02() <= 30)
{
  defenseWlineFollower();
  initSpeed(attackSpeed);
  forward();
  //Catch();
}
  turnRight(10);
  delay(10);

}

void forward()
{
  //MOTOR 1
  digitalWrite(IN1 , LOW);
  digitalWrite(IN2 , HIGH);
  //MOTOR 2
  digitalWrite(IN3 , HIGH);
  digitalWrite(IN4 , LOW);
}
void right()
{
  //MOTOR 1
  digitalWrite(IN1 , LOW);
  digitalWrite(IN2 , HIGH);
  //MOTOR 2
  digitalWrite(IN3 , LOW);
  digitalWrite(IN4 , LOW);
}
void left()
{
  //MOTOR 1
  digitalWrite(IN1 , LOW);
  digitalWrite(IN2 , LOW);
  //MOTOR 2
  digitalWrite(IN3 , HIGH);
  digitalWrite(IN4 , LOW);
}
void backward()
{
  //MOTOR 1
  digitalWrite(IN1 , HIGH);
  digitalWrite(IN2 , LOW);
  //MOTOR 2
  digitalWrite(IN3 , LOW);
  digitalWrite(IN4 , HIGH);
}
void full_rotate()
{
  //MOTOR 1
  digitalWrite(IN1 , HIGH);
  digitalWrite(IN2 , LOW);
  //MOTOR 2
  digitalWrite(IN3 , HIGH);
  digitalWrite(IN4 , LOW);
}
void rotateWdegree(float degree) {
  float rotationTime = degree / 90.0; // Assume 90° takes 1 second
  digitalWrite(IN1 , HIGH);
  digitalWrite(IN2 , LOW);
  digitalWrite(IN3 , HIGH);
  digitalWrite(IN4 , LOW);
  //time = millis();
  delay(rotationTime * 1000);      // Wait for the rotation to complete
  forward();
  if(irPin02 == 0){
    turnRight(90);
    //delay(1000); // 90 degree
  }
}

void turnleft(float degree){
    float rotationTime = degree / 90.0; // Assume 90 takes 1 second
    digitalWrite(IN1 , HIGH);
    digitalWrite(IN2 , LOW);
    digitalWrite(IN3 , HIGH);
    digitalWrite(IN4 , LOW);
  //time = millis();
  delay(rotationTime * 1000);   
}
void turnRight(float degree){
    float rotationTime = degree / 90.0; // Assume 90 takes 1 second
    digitalWrite(IN1 , LOW);
    digitalWrite(IN2 , HIGH);
    digitalWrite(IN3 , LOW);
    digitalWrite(IN4 , HIGH);
  //time = millis();
  delay(rotationTime * 1000);   
}
/*
int startLine = 0;
int endLine = 0;
int intervalLine = 500;
bool isBackingUp = false;  // Keeps track of whether the robot is backing up


void defenseWlineFollower() {
  if (readLineFollower01() == 1 || readLineFollower02() == 1) {
    if (!isBackingUp) {
      backward();                   // Start moving backward
      startLine = millis();         // Store the time when the robot starts moving backward
      isBackingUp = true;           // Set the flag to indicate the robot is backing up
    }
  }

  // Check if enough time has passed since the robot started backing up
  if (isBackingUp) {
    endLine = millis();
    if (endLine - startLine >= intervalLine) {
      // Stop or reset the flag after 500 ms
      isBackingUp = false;          // Reset the backing up flag to allow future movements
      // You can add a stop function here if needed: stop();
    }
  }
}

*/
void defenseWlineFollower(){
  if (readLineFollower01() == 1 || readLineFollower02() == 1) {
    backward();
    delay(500);}

}

void stop()
{
    //MOTOR 1
  digitalWrite(IN1 , HIGH);
  digitalWrite(IN2 , HIGH);
  //MOTOR 2
  digitalWrite(IN3 , HIGH);
  digitalWrite(IN4 , HIGH);
}
bool readIR01()
{
  bool val = !digitalRead(irPin01); //1 for white , 0 for black
  return val;
}
bool readIR02()
{
  bool val = !digitalRead(irPin02);// 1 for white , 0 for black
  return val;
}
float readLineFollower01()
{
  float val = digitalRead(lineFollower01);
  return val;
}
float readLineFollower02()
{
  float val = digitalRead(lineFollower02);
  return val;
}
float readUltrasonic01()
{
  digitalWrite(trigPin01 , LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin01 , HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin01 , LOW);
  float duration = pulseIn(echoPin01, HIGH);
  float distance = (duration * 0.0343) / 2;
  Serial.println(distance);
  return distance;
}
float readUltrasonic02()
{
  digitalWrite(trigPin02 , LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin02 , HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin02 , LOW);
  float duration = pulseIn(echoPin02, HIGH);
  float distance = (duration * 0.0343) / 2;
    Serial.println(distance); 
  return distance;
}