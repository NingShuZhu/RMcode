#include<Servo.h>
#define rightGreyA A3
#define leftGreyA A2
int BorWr = 0; //black or white (right)
int BorWl = 0;

const int TrigPin = 12;
const int EchoPin = 11;
float distance;

int duojiPin1 = 5; //右舵机
int duojiPin2 = 9;
Servo mys1;
Servo mys2;

void setup() {
	// put your setup code here, to run once:
	pinMode(rightGreyA, INPUT);
	Serial.begin(9600);
	mys1.attach(duojiPin1);                     //舵机操作
	mys2.attach(duojiPin2);
	mys1.writeMicroseconds(1500);
	mys2.writeMicroseconds(1500);       //舵机归位
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}

void goStraight(){
  mys1.writeMicroseconds(1000);
  mys2.writeMicroseconds(2000);
  delay(500);
}

void turnAround(){
  mys1.writeMicroseconds(1000);
  mys2.writeMicroseconds(1000);
  delay(2800);
}

void turnLeft(){
  mys1.writeMicroseconds(1000);
  mys2.writeMicroseconds(1500);
  delay(1350);
}

void turnRight(){
  mys1.writeMicroseconds(1500);
  mys2.writeMicroseconds(2000);
  delay(1500);
}

void getDistance(){
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);

  distance = pulseIn(EchoPin, HIGH)/58.00;
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
  delay(50);
  //return distance;
}

void loop() {
	// put your main code here, to run repeatedly:
	BorWr = analogRead(rightGreyA);
	BorWl = analogRead(leftGreyA);
	//print
	Serial.print(BorWr);
	Serial.print("   ");
	Serial.print(BorWl);
	Serial.println("");

	if (BorWr < 100 && BorWl < 100) {
		mys1.writeMicroseconds(1000);
		mys2.writeMicroseconds(2000);
		delay(50);
	}
	else if (BorWr < 100 && BorWl >= 100) {
		mys1.writeMicroseconds(1000);
		mys2.writeMicroseconds(1500);
		delay(50);
	}
	else if (BorWr >= 100 && BorWl < 100) {
		mys1.writeMicroseconds(1500);
		mys2.writeMicroseconds(2000);
		delay(50);
	}
	else if (BorWr >= 100 && BorWl >= 100) {
		mys1.writeMicroseconds(1000);
		mys2.writeMicroseconds(2000);
		delay(50);
	}

  getDistance();
  //delay(50);

  if(distance <= 13){
    turnLeft();
    goStraight();
    turnRight();
    goStraight();
    goStraight();
    delay(1000);
    turnRight();
    goStraight();
    turnLeft();
    delay(50);
    // for(;;){
    //   BorWr = analogRead(rightGreyA);
	  //   BorWl = analogRead(leftGreyA);
    //   if(BorWr>=100 && BorWl<100 || BorWr<100 && BorWl>=100) {
    //     turnLeft();
    //     mys1.writeMicroseconds(1000);
    //     mys2.writeMicroseconds(1500);
    //     delay(500);
    //     break;
    //   }
    //   else {
    //     mys1.writeMicroseconds(1000);
		//     mys2.writeMicroseconds(2000);
		//     delay(50);
    //     }
    //if(BorWr>=100 || BorWl>=100) turnLeft();    
    // goStraight();
    // BorWr = analogRead(rightGreyA);
	  // BorWl = analogRead(leftGreyA);
    // if(!(BorWr>=100 || BorWl>=100)) turnLeft();
    
  }

}