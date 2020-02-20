#define Peizo D8
#define SoundSensor D10
#define LED 13
#define BLYNK_PRINT Serial

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "";
char ssid[] = "";
char pass[] = "";

unsigned long long FDetect=0,LDetect;
int volume=0;
const int TooLoud=80;
BlynkTimer timer;
WidgetLED led1(V1);

void Main(){
  volume = analogRead(SoundSensor);
  if(volume > TooLoud){
      digitalWrite(LED,HIGH);
      LDetect = millis();
      led1.on();
      if(FDetect == 0){
        FDetect = millis();
      }
      if(LDetect - FDetect > 3000){
        tone(Peizo,1000,500);
      }
  }else{
      if(millis() - LDetect < 1500){
          digitalWrite(LED,LOW);
          led1.off();
          FDetect = 0;
      } 
  }
  if(millis() - LDetect < 20000){
    Blynk.virtualWrite(V2, (millis() - LDetect)/1000);
  }else{
    Blynk.virtualWrite(V2, "Room is quite");
  }
}

void setup(){
  Serial.begin(9600);
  pinMode(SoundSensor, INPUT);
  pinMode(LED, OUTPUT);
  Blynk.begin(auth, ssid ,pass);
  timer.setInterval(500L, Main);
}

void loop(){
  Blynk.run();
  timer.run();
}
