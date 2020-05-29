
#include <SoftwareSerial.h>
#include <NewPing.h>
 
#define TRIG 9
#define ECHO 8
#define MAX 500
 
NewPing ultra(TRIG, ECHO, MAX);
SoftwareSerial SIM900A(10,11); //5VT,5VR

int door=0;
int led=13;
int flag=0;

void setup() 
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);

  SIM900A.begin(9600);   // Setting the baud rate of GSM Module
  delay(100);
}

void loop() 
{
  door=ultra.ping_cm();
  Serial.println(door);
  if(door>4 && door<6 && flag==0)
  {
    digitalWrite(led,HIGH);
    Serial.println("Door is Closed");
    SendMessageClosed();
    delay(1000);
    flag=1;
    delay(20);
  }
  if(door>7 && flag==1)
  {
    digitalWrite(led,LOW);
    Serial.println("Door is Opened!");
    SendMessage();
    delay(1000);
    flag=0;
    delay(20);
  }
  delay(500);
}

void SendMessage()
{
  Serial.println ("Sending Message");
  SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(500);
  Serial.println ("Set SMS Number");
  SIM900A.println("AT+CMGS=\"+959768001285\"\r"); //Mobile phone number to send message
  delay(500);
  SIM900A.println("The Door is Opened!");// Messsage content
  Serial.println ("Finish");
  SIM900A.println((char)26);// ASCII code of CTRL+Z
}

void SendMessageClosed()
{
  SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(500);
  SIM900A.println("AT+CMGS=\"+959768001285\"\r"); //Mobile phone number to send message
  delay(500);
  SIM900A.println("The Door is Closed!");// Messsage content
  Serial.println ("ClosedFinish");
  SIM900A.println((char)26);// ASCII code of CTRL+Z
}
