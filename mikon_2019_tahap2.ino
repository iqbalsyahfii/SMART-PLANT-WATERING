 #include <EEPROM.h>
 #include <LiquidCrystal.h>
 #include <OneWire.h>
 #include <Wire.h>
 #include <DallasTemperature.h>
 #include "RTClib.h"
 #include "SIM900.h"
 #include <SoftwareSerial.h>;
 #include "sms.h"

 #define pinyes A0
 #define pinup A1
 #define pindown A2
 #define buzzer 4
 #define ONE_WIRE_BUS A3          //////pH meter Analog output to Arduino Analog Input 0
 #define Offset 0            //deviation compensate
 #define hijau 13
 #define merah 5
 #define pompa 6
 #define samplingInterval 20
 #define printInterval 800
 #define ArrayLenth  40    //times of collection
 #define jumlahnomor 1
 #define pinLevel A6
 #define pinTanah A7

SMSGSM sms;
char* myphone[jumlahnomor]={"088211411294"};
RTC_Millis rtc;
const int DS1307 = 0x68; // Alamat pin RTC pada arduino
byte durasi;
byte second = 0;
byte minute = 0;
byte hour = 0;
byte weekday = 0;
byte monthday = 0;
byte month = 0;
int year = 0;
bool yes,down,up;
int suhu;
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
String data_masuk;
char sms_position;
char phone_number[20];
char sms_text1[200];
String sms_text;
boolean started=false;
int durasi_sekarang=0;
int last_minute=0;
int sensorValue = 0; 
int level = 0;  
int data, tanah ;

void setup() {
Serial.begin(9600);
lcd.begin(16, 2);
sensors.begin();
Wire.begin();
pinMode(pinyes,INPUT);
pinMode(pinup,INPUT);
pinMode(pindown,INPUT);
pinMode(buzzer,OUTPUT);
pinMode(hijau,OUTPUT);
pinMode(merah,OUTPUT);
pinMode(pompa,OUTPUT);

digitalWrite(pinyes,HIGH);
digitalWrite(pinup,HIGH);
digitalWrite(pindown,HIGH);
digitalWrite(buzzer,LOW);

 lcd.setCursor(3,0);
  lcd.print("MONITORING");
  lcd.setCursor(1,1);
  lcd.print("TANAMAN PINTAR");
  beep(3,100);
  delay(2000);
  lcd.clear();
int c=0;
while(c<4){
  bacatombol();
  c++;
  lcd.setCursor(0,0);
  lcd.print("LAKUKAN SETTING?");
  lcd.setCursor(0,1);
  lcd.print("WAIT "+String(c)+" ");
  if(yes){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("MODE SETTING");
    tunggu();
    setTime();
    set_par();
    c=5;
  }
   delay(1000);
}
lcd.clear();
lcd.setCursor(0,0);lcd.print ("GSM CHACKING....");
if (gsm.begin(9600)) 
{
        lcd.clear();
        Serial.println("\nstatus=READY");
        started=true;
        lcd.setCursor(0,0);lcd.print ("GSM OK");
        beep(1,200);
        delay(3000);
       
} 
else
{
        lcd.clear();
        lcd.setCursor(0,0);lcd.print ("GSM ERROR ");
        started=false;
        delay(3000);
        Serial.println("\nstatus=IDLE");
    
}

durasi=EEPROM.read(1);
}

void loop() {
bacatombol();
suhu=get_suhu();
level=get_level();
tanah=get_tanah();
time_read();
if (last_minute!=minute){last_minute=minute;durasi_sekarang++;}
if (durasi_sekarang >= durasi){
String protokol = "SUHU: "+String(suhu)+"'C LEVEL AIR: "+String(level)+" KELEMBAPAN: "+String(tanah)+"%";
durasi_sekarang=0;
sendsms(protokol);

}
if (level<=1){
  digitalWrite(merah,HIGH);
  digitalWrite(hijau,LOW);
}
else if (level>=3){
  digitalWrite(hijau,HIGH);
  digitalWrite(merah,LOW);
}
else if (level>1&&level<3){
  digitalWrite(hijau,LOW);
  digitalWrite(merah,LOW);
}

if (tanah<30){
  digitalWrite(pompa,HIGH);
}
else if (tanah>30){
  digitalWrite(pompa,LOW);
}

tampilan();

}

void tunggu(){
 int ss=0;
  while(ss<50){
    bacatombol();
  if (yes){ 
    ss=0;  
  }
  else{
    ss++;
    delay(3);
  }
  }
}
