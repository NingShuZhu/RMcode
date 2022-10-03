#include<Servo.h>
#define rightGreyA A3    //右边的灰度传感器
#define leftGreyA A2     //左边的灰度传感器
int BorWr = 0;           //black or white (right) 储存右边的灰度传感器的灰度数值，小于100为白，大于100为黑
int BorWl = 0;           //black or white (left) 储存左边的灰度传感器的灰度数值

const int TrigPin = 12;  //超声波测距仪的输出口
const int EchoPin = 11;  //超声波测距仪的输入口
float distance;          //检测到的距离障碍物的距离（cm）

int duojiPin1 = 5;       //右舵机
int duojiPin2 = 9;       //左舵机
Servo mys1;              //右舵机初始化
Servo mys2;              //左舵机初始化

void setup() {
	// put your setup code here, to run once:
	pinMode(rightGreyA, INPUT);
	Serial.begin(9600);
	mys1.attach(duojiPin1);             //舵机操作
	mys2.attach(duojiPin2);
	mys1.writeMicroseconds(1500);
	mys2.writeMicroseconds(1500);       //舵机归位
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}

//直行
void goStraight(){
  mys1.writeMicroseconds(1000);
  mys2.writeMicroseconds(2000);
  delay(500);
}

//掉头
void turnAround(){
  mys1.writeMicroseconds(1000);
  mys2.writeMicroseconds(1000);
  delay(2800);
}

//左转约90度
void turnLeft(){
  mys1.writeMicroseconds(1000);
  mys2.writeMicroseconds(1500);
  delay(1350);
}

//右转约90度
void turnRight(){
  mys1.writeMicroseconds(1500);
  mys2.writeMicroseconds(2000);
  delay(1500);
}

//获取+计算，得到障碍物距离
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
}

void loop() {
	// put your main code here, to run repeatedly:
	BorWr = analogRead(rightGreyA);
	BorWl = analogRead(leftGreyA);

	//print，输出一下灰度传感器检测到的数值看看，可以不用
	Serial.print(BorWr);
	Serial.print("   ");
	Serial.print(BorWl);
	Serial.println("");

	if (BorWr < 100 && BorWl < 100) {        //如果两侧灰度传感器检测到的都是白，直走
  	mys1.writeMicroseconds(1000);
		mys2.writeMicroseconds(2000);
		delay(50);
	}
	else if (BorWr < 100 && BorWl >= 100) {  //如果左边是黑，右边是白，向左拐一点
		mys1.writeMicroseconds(1000);
		mys2.writeMicroseconds(1500);
		delay(50);
	}
	else if (BorWr >= 100 && BorWl < 100) {  //如果右边是黑，左边是白，向右拐一点
		mys1.writeMicroseconds(1500);
		mys2.writeMicroseconds(2000);
		delay(50);
	}
	else if (BorWr >= 100 && BorWl >= 100) { //如果都是黑，直走
		mys1.writeMicroseconds(1000);
		mys2.writeMicroseconds(2000);
		delay(50);
	}

  getDistance();                           //获取距离

  if(distance <= 13){                      //如果障碍物距离<=13cm，开始避障
    turnLeft();                            
    goStraight();                          //左转，走一会，右转，走一会，再右转，走一会，再左转，就绕过去了
    turnRight();
    goStraight();
    goStraight();
    delay(1000);
    turnRight();
    goStraight();
    turnLeft();
    delay(50);
  }
}