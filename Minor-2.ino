#include <VarSpeedServo.h> // download this libragy from external source "google it "
// Pins initialization
//-------------------------------------------------
#include <LiquidCrystal.h>
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LiquidCrystal lcd(A1, A0, A2, A3, A4, A5);
//-------------------------------------------------
#define trigPin  7
#define echoPin  6
#define trigPin1 2
#define echoPin1 3
#define led1Pin 13
#define led2Pin 12
#define led3Pin  11
#define servoPin 4
VarSpeedServo servo; 

void setup()

{

  
   lcd.setCursor(0, 0);
   lcd.print("    WELCOME");
   delay(1200);
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("   Guided Name:");
   delay(2000);

    lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print(" Neenansha Jain");
   delay(1000);

    lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Meha Shrivastava");
   delay(1000);
   
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Project By:");
  delay(2000);



lcd.clear();
   lcd.setCursor(0,0); 
  lcd.print("  Prachi Dubey");
  delay(700);

  lcd.clear();
   lcd.setCursor(0,0); 
  lcd.print("  Shriya Singh");
  delay(700);

  lcd.clear();
   lcd.setCursor(0,0); 
  lcd.print("    Tanu jha");
  delay(700);

  
  lcd.clear();
   lcd.setCursor(0,1); 
  lcd.print("  Shivam Singh");
  delay(700);
  
 
  //-----------------------------------


  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
 
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);

  servo.attach(servoPin); // initialize servo to output pin
  servo.write(0); // default position of servo

  Serial.begin (9600); // Set 9600 baud rate in serial monitor
}


int detect_garbage() // returns garbage level in centimeter
{
  long duration;
  int garbage;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(echoPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  garbage = (duration / 2) / 29.1;
  return garbage;
}

//__________________________________________
int detect_hand() // returns garbage level in centimeter
{
  long duration;
  int level1;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(echoPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);
  level1 = (duration / 2) / 29.1;
  return level1;
}
//______________________________________________
void loop()
{
  int garbage_level = detect_garbage(); // get hthe sensor data 
  int hand_value = detect_hand();
  // print data in serial monitor
  Serial.println("Hand distance: " + String(hand_value) + String(garbage_level) + "" );

  // opens lid when somethig is closer then 30 cm from the dustbin top
  if ( hand_value < 30 )
  {
servo.write(100, 70);
    delay(50);
   
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Dustbin Opened");
    delay(1000);
    lcd.clear();
    lcd.setCursor(1,1);
    lcd.print("Void Space:");
    lcd.print((garbage_level*100)/25);
    lcd.print("%");
    delay(1000);
  }
  else
  {
    servo.write(0, 50);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Dustbin Closed");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Void Space:");
    lcd.print((garbage_level*100)/25);
    lcd.print("%");
    delay(1000);
  }
}
