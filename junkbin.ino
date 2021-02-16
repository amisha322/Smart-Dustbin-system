
#include <Servo.h>

unsigned long lastTimeMillis = 0;

Servo servoMain;

const int trigpin = 9;
const int echopin = 8;
const int trigpin2 = 10;
const int echopin2 = 11;

long duration1,duration2;
float distance1,distance2,val;

int height = 35; //Height or depth of dustbin

String msg = "Dustbin status : "; //msg you want to send || output - Dustbin is : <percent> %

//char l = "%"; // only for percent symbol

//String mob = "AT+CMGS=\"+917869994284\"\r"; // Put your mob no. here

int sms25 = 0; // sms will be sent only if value is 0.
int sms50 = 0; 
int sms75 = 0;
int sms100 = 0;

void setup()
{
servoMain.attach(7); //
pinMode(trigpin, OUTPUT);
pinMode(echopin, INPUT);
pinMode(trigpin2, OUTPUT);
pinMode(echopin2, INPUT);
pinMode(13, OUTPUT);

Serial.begin(9600);

Serial.println("Smartbin System online");
}

void sms30() {
  
  String cmd = "GET /apps/thinghttp/send_request?api_key=2JNWZUJIPGP52LNY HTTP/1.1";
    Serial.println("AT+CIPSEND=4," + String(cmd.length() + 4));
    delay(1000);

    Serial.println(cmd);
    delay(1000);
    Serial.println(""); 
    
  }

void sms60() {
  
  String cmd = "GET /apps/thinghttp/send_request?api_key=IQZ6NWXDJ4GNVP1F HTTP/1.1";
    Serial.println("AT+CIPSEND=4," + String(cmd.length() + 4));
    delay(1000);

    Serial.println(cmd);
    delay(1000);
    Serial.println(""); 
  
  
  }

void printResponse() {
  while (Serial.available()) {
    Serial.println(Serial.readStringUntil('\n')); 
  }
}


void sms90() {
  
  String cmd = "GET /apps/thinghttp/send_request?api_key=DA3F1LJS4FH3Q3ER HTTP/1.1";
    Serial.println("AT+CIPSEND=4," + String(cmd.length() + 4));
    delay(1000);

    Serial.println(cmd);
    delay(1000);
    Serial.println(""); 
  }
  void sms0() {
  
  String cmd = "GET /apps/thinghttp/send_request?api_key=7V5KAQH3OMV9X92W HTTP/1.1";
    Serial.println("AT+CIPSEND=4," + String(cmd.length() + 4));
    delay(1000);

    Serial.println(cmd);
    delay(1000);
    Serial.println(""); 
  }

/*int sms(int p){  
    //sms function ... call with " sms(<percentage>) " to use  
     Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     Serial.println(mob); // Replace x with mobile number
     delay(1000);
     Serial.println(msg + p + l);// The SMS text you want to send
     delay(100);
     Serial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
      

}*/

void init() {
  if (millis() - lastTimeMillis > 30000) {
    lastTimeMillis = millis();

    Serial.println("AT+CIPMUX=1");
    delay(1000);
    printResponse();

    Serial.println("AT+CIPSTART=4,\"TCP\",\"192.168.1.19\",80");
    delay(1000);
    printResponse();

    
  }
}

void loop()
{
digitalWrite(trigpin, LOW);
delay(2);
digitalWrite(trigpin, HIGH);
delayMicroseconds(10);
digitalWrite(trigpin, LOW);
duration1 = (echopin, HIGH);
long cm1 = (duration1/58.82);
distance1 = cm1;
    
digitalWrite(trigpin2, LOW);
delay(2);
digitalWrite(trigpin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigpin2, LOW);
duration1 = (echopin2, HIGH);
long cm2 = (duration2/58.82);
distance2 = cm2;
val = map(distance2, 0, height, 0, 100);
int Q = round(val); //final value for dustbin status in % 0- 100

if(distance1<30) { 
  servoMain.write(180);
   delay(3000);
   digitalWrite(13, HIGH);
   }
   else
   { 
    servoMain.write(0); 
    delay(50); 
    digitalWrite(13, LOW);
    } 



if(Q <= 30){
  
  if(sms25 = 0){
    init();
    sms30(); // send sms for 25%

    sms25 = 1; // to stop sending sms again and again
    sms50 = 0; // allow rest sms to be able to send.
    sms75 = 0;
    sms100 = 0;
    } 
  } else if(Q >= 60){
  
  if(sms50 = 0){
    init();
    sms60(); // send sms for 50%

    sms25 = 0; // allow the sms to be sent again
    sms50 = 1; // to stop sending sms again and again
    sms75 = 0; // rest sms can be sent
    sms100 = 0;
    } 
  } else if(Q >= 90){
  
  if(sms75 = 0){
    init();
    sms90(); // send sms for 75%

    sms25 = 0; // allow the sms to be sent again
    sms50 = 0; 
    sms75 = 1; // rest sms can be sent
    sms100 = 0;
    } 
  } else if(Q <= 5) {
    if(sms75 = 1){
      init();
      sms0();
      }
  }   
 }
