#include <Wire.h>;
#include <Servo.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

Servo myservo1; 
Servo myservo2;
Servo myservo3; 
Servo myservo4;
Servo myservo5;

#define servo_4 3
#define servo_3 5
#define servo_5 6
#define servo_2 9
#define servo_1 10
//#define servo_ 11

#define BUTTON_2 8
#define BUTTON_3 12
#define BUTTON_1 13

#define Sensor_1 2
#define Sensor_2 4
#define Sensor_3 7

#define Motor A0

int money=0, mode, up, down;
uint8_t slot_a=2, slot_b=2, slot_c=2;

void Slot_A()
{

  if(slot_a==2)
  {
   myservo2.write(90);
  }
  else if(slot_a==1)
  {
    myservo1.write(90);
  }
  slot_a--;
}

void Slot_B()
{
  if(slot_b==2)
  {
   myservo3.write(90);
  }
  else if(slot_b==1)
  {
    myservo4.write(90);
  }
  slot_b--;
}

void Slot_C()
{
  if(slot_c>0)
  {
   myservo5.write(180);
   delay(500);
   myservo5.write(50);
  }

  slot_c--;
}


void checkButton()
{

  if(digitalRead(BUTTON_1) == 0)
  {
   while(digitalRead(BUTTON_1) == 0);
   money=money-5;
   if(money>-1) Slot_A();
  }
  if(digitalRead(BUTTON_2) == 0)
  {
    while(digitalRead(BUTTON_2) == 0);
    money=money-5;
    if(money>-1) Slot_B();
    
  }
  if(digitalRead(BUTTON_3) == 0)
  {
    while(digitalRead(BUTTON_3) == 0);
    if(money<10)
    {
    lcd.setCursor(0,0);
    lcd.print("Khong du tien");
    delay(1000);
    }
    else
    {
      money=money-10;
      if(money>-1) Slot_C();
    }
  }

}

int Detec_Money()
{
  int check=0;
  int scan_10k=0;
  
  digitalWrite(Motor,HIGH);
  while(digitalRead(Sensor_3) == 1)
  {
    while((digitalRead(Sensor_1) == 1)&&(digitalRead(Sensor_2) == 1))
    {
      check=1;
    }
    if(((digitalRead(Sensor_1) == 0)||(digitalRead(Sensor_2) == 0))&&(check==1)&&(digitalRead(Sensor_3) == 1))
    {
      scan_10k=1;
      break;
    }

  }
  
  
  if(scan_10k==1)
  {
    delay(5000);
    digitalWrite(Motor,LOW);
    return 10;
  }
  else 
  {
    delay(1000);
    digitalWrite(Motor,LOW);
    return 5;
  }
}

void setup() {
  // put your setup code here, to run once:
 lcd.begin();       //Khởi động màn hình. Bắt đầu cho phép Arduino sử dụng màn hình
 lcd.backlight();   //Bật đèn nền
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Xin Chao");
 delay(1000);
 pinMode(Sensor_1,INPUT);
 pinMode(Sensor_2,INPUT);
 pinMode(Sensor_3,INPUT);

 pinMode(BUTTON_1,INPUT);
 pinMode(BUTTON_2,INPUT);
 pinMode(BUTTON_3,INPUT);

 pinMode(Motor,   OUTPUT);
 
 pinMode(Sensor_2,INPUT);
 pinMode(Sensor_3,INPUT);

 myservo1.attach(servo_1); 
 myservo2.attach(servo_2); 
 myservo3.attach(servo_3); 
 myservo4.attach(servo_4); 
 myservo5.attach(servo_5); 
 //myservo.attach(servo_6); 
 myservo1.write(180);
 myservo2.write(180);
 myservo3.write(180);
 myservo4.write(180);
 myservo5.write(50);

}

void loop() {
  // put your main code here, to run repeatedly:
   if(digitalRead(Sensor_3) == 1)
   {
    // check money
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Dang doc ...");
    money = Detec_Money(); // phan biet loai tien
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("So tien la: ");
    lcd.print(money);
    lcd.print("k");
    delay(1000);
    lcd.clear();
   }
   else if(money==0)
   {
    lcd.setCursor(0,0);
    lcd.print("Moi Nap Tien");
   }
   
   while(money>0)
   {
    lcd.setCursor(0,0);
    lcd.print("Da nap ");
    lcd.print(money);
    lcd.print("k     ");
    checkButton();
   }
   
  
}
