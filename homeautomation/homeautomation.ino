#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define FIREBASE_HOST "blink-e1c88-defaultrtdb.firebaseio.com" // the project name address from firebase id
#define FIREBASE_AUTH "****************************" // thesecret key generated from firebase
#define WIFI_SSID "realmw 7"
#define WIFI_PASSWORD "12340765"
String fireStatus1 = "";
String fireStatus2 = "";
String fireStatus3 = ""; //
led status received from firebase
int LIGHT_1 = 16;
int LIGHT_2 = 5;
int LIGHT_3 = 4;
int sens = 0;
int sensor;
int count=0;
int switch1=2;
String c="";
void setup()
{
Serial.begin(9600);
delay(1000);
pinMode(LIGHT_1, OUTPUT);
pinMode(LIGHT_2, OUTPUT);
pinMode(LIGHT_3, OUTPUT);
pinMode(sens, INPUT);
pinMode(switch1, INPUT);
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("Connecting to ");
Serial.print(WIFI_SSID);
while (WiFi.status() != WL_CONNECTED)
{
Serial.print(".");
delay(500);
}
Serial.println();
Serial.print("Connected to ");
Serial.println(WIFI_SSID);
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // connect tofirebase
Firebase.setString("LIGHT_2", "0"); //send initialstring of led status
Firebase.setString("LIGHT_3", "0"); //send initialstring of led status
}
void loop()
{
sensor = digitalRead(sens);
if (sensor==0)
{
count++;
Serial.println(sensor);
Serial.println(count);
}
if (count%2==0)
{
caseLIGHT_2();
}
else
{
caseLIGHT_1();
}
fireStatus2 = Firebase.getString("LIGHT_2"); // get ld status input from firebase
if (fireStatus2 == "1")
{ // compare the input of led status received from firebase
Serial.println("LIGHT_2 Turned ON");
digitalWrite(LIGHT_2,HIGH); // makeexternal led ON
}
else if (fireStatus2 == "0")
{ // compare the input of led status received from firebase
Serial.println("LIGHT_2 Turned OFF");
digitalWrite(LIGHT_2,LOW); // make externalled OFF
}
else
{
Serial.println("Command Error! Please send ON/OFF LIGHT_2");
}
fireStatus3 = Firebase.getString("LIGHT_3"); // get ld status input from firebas
if (fireStatus3 == "1")
{ // compare the input of led status received from firebase
Serial.println("LIGHT_3 Turned
ON");
digitalWrite(LIGHT_3,HIGH); // make external led ON
}
else if (fireStatus3 == "0")
{ 
  // compare the input of led status received from firebase
Serial.println("LIGHT_3 Turned OFF");
digitalWrite(LIGHT_3,LOW); // make external led OFF
}
int s=digitalRead(switch1);
if (s==1)
{
String st="OFF";
Firebase.setString("Manual switch3 for light3 is", st);
Serial.println("Manual switch3 is OFF");
 delay(1000);
}
else if (s==0)
{
String st="ON";
Firebase.setString("Manual switch3 for light3 is", st);
Serial.println("Manual switch3 is ON");
 delay(1000);
}
}
void caseLIGHT_1()
{
digitalWrite(LIGHT_1, HIGH); // make external led ON
String st="ON";
Firebase.setString("IR detected !LIGHT_1 turned ", st);
Serial.println("LIGHT_1 Turned ON");
}
void caseLIGHT_2()
{
digitalWrite(LIGHT_1, LOW);
String st="OFF"
Firebase.setString("IR detected !LIGHT_1 turned ",st); // make external led ON
Serial.println("LIGHT_1 Turned OFF");
}
