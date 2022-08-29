

#include <Servo.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13,11,10,9,8,7); 
Servo myservo;
#define POWER_PIN  4
#define SIGNAL_PIN A2
int pos = 0; //position of servo motor
int value = 0;//water level value

void setup(){
  
  Serial.begin(9600);
  myservo.attach(3); // configure D3 pin for the servo motor
  pinMode(12, OUTPUT); //led, simulating spraying
  pinMode(POWER_PIN, OUTPUT);   // configure D4 pin as an OUTPUT for water level
  digitalWrite(POWER_PIN, LOW); // turn the water level sensor OFF
  
  }

 void loop(){
  int sensorValue=analogRead(A0); //rain sensor
  int dozvola=analogRead(A1); //auto mode
  int prskanje=analogRead(A3); //spraying

  int x1=analogRead(A4); //manual mode
  int x2=analogRead(A5); //manual mode
  
  Serial.println("KISA: "); //checking value from analog input
  Serial.println(sensorValue);

  Serial.println("PRSKANJE: "); //checking value from analog input
  Serial.println(prskanje);

  Serial.println("x1: "); //checking value from analog input
  Serial.println(x1);

  Serial.println("x2: "); //checking value from analog input
  Serial.println(x2);

  


  
//----------------------------------------------------------------------------------------------- AUTO MODE
  if(dozvola>900 || (prskanje>=1000 || prskanje>=950) ){
  if (sensorValue > 950){
  Serial.println("Nema potrebe za ukljucivanjem senzora");
  }


  if(sensorValue >800 && sensorValue <950){
  Serial.println("Sporo");
  for (pos = 0; pos <= 180; pos += 2) { // goes from 0 degrees to 180 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 2) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(2000);
  }
  
  
  if(sensorValue >450 && sensorValue <800){
  Serial.println("Srednje");
  for (pos = 0; pos <= 180; pos += 2) { // goes from 0 degrees to 180 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 10ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 2) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 10ms for the servo to reach the position
  }
  
  }


  if(sensorValue < 450){
  Serial.println("Brzo");
  for (pos = 0; pos <= 180; pos += 2) { // goes from 0 degrees to 180 degrees // in steps of 2 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(7);                       // waits 7ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 2) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(7);                       // waits 7ms for the servo to reach the position
   
  }
  
  }
  //-----------------------------------------------------------------------------------------------AUTO MODE
}

  //-----------------------------------------------------------------------------------------------MANUAL MODE
    if(dozvola<900 && prskanje<900 && x2<900 && x1<900){
    Serial.println("00");       //analog input A4 and A5 are 0/0 //radi
    }
    

    if(dozvola<900 &&  x2<900 && x1>900 && prskanje<900){
    Serial.println("01 SPORO"); //analog input A4 and A5 are 0/1
    for (pos = 0; pos <= 180; pos += 2) { 
    myservo.write(pos);              
    delay(15);                       
    }
    for (pos = 180; pos >= 0; pos -= 2) { 
    myservo.write(pos);       
    delay(15);                       
    }delay(2000);}

    if(dozvola<900 &&  x1<900 && x2>900 && prskanje<900){
    Serial.println("10 SREDNJE"); //analog input A4 and A5 are 1/0  
    for (pos = 0; pos <= 180; pos += 2) { 
    myservo.write(pos);              
    delay(10);                 
    }
    for (pos = 180; pos >= 0; pos -= 2) { 
    myservo.write(pos);            
    delay(10);                       
    }}

    if(dozvola<900 &&  x1>=1000 && x2>=1000 && prskanje<900){
    Serial.println("11 BRZO"); //analog input A4 and A5 are 1/1  
    for (pos = 0; pos <= 180; pos += 2) { 
    myservo.write(pos);              
    delay(5);                       
    }
    for (pos = 180; pos >= 0; pos -= 2) { 
    myservo.write(pos);             
    delay(5);                       
    }}  
  //-----------------------------------------------------------------------------------------------MANUAL MODE

//-----------------------------------------------------------------------------------------------Spraying simulation
  if(prskanje>=980){
    Serial.println("Svetli"); //checking of led
    digitalWrite(12, HIGH);   
    delay(100);} 
  if(prskanje<980) {
    Serial.println("Ne svetli");//checking of led
    digitalWrite(12, LOW);   
    delay(100);     }
//-----------------------------------------------------------------------------------------------Spraying simulation


//-----------------------------------------------------------------------------------------------LCD showing
  digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF
  lcd.begin(16, 2);


  if (value > 500) {
    lcd.setCursor(0, 0);
    lcd.print("Nivo tecnosti:");
    lcd.setCursor(0, 1);
    lcd.print("VISOK NIVO"); //high level
    
    }
  else if ((value > 390) && (value <= 500)) {
    lcd.setCursor(0, 0);
    lcd.print("Nivo tecnosti:");
    lcd.setCursor(0, 1);
    lcd.print("SREDNJI NIVO"); //medium level
    
    }
  else{
    lcd.setCursor(0, 0);
    lcd.print("Nivo tecnosti:");
    lcd.setCursor(0, 1);
    lcd.print("Dopunite tecnost.");  //low level, need additioning
    
 
    } 
//-----------------------------------------------------------------------------------------------LCD showing

}
