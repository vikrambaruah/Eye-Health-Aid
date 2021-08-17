#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

char auth[]="rbcHc5YG74C49cdJrYc9XBhrVuE_MH7g";
char ssid[] = "Sandeep";
char wifiPassword[] = "manu2k123";
int flag=0;
uint32_t startTime=millis();
uint32_t endTime;
float blinks=0.00;
uint32_t last_alarm=0;
int flag2=0;
#define IR 13
#define LED_PIN 12
void setup() {
  // put your setup code here, to run once:
  Blynk.begin(auth, ssid, wifiPassword);
  //pinMode(LED_PIN, OUTPUT);
  pinMode(IR, INPUT);
  Serial.begin(9600);
}

void loop(){
  Blynk.run();
  endTime = millis();
  
  if (digitalRead(IR)==LOW){
    flag=0;
    
  }
  else if (digitalRead(IR)==HIGH){
    if (flag==0){
      blinks+=1;
    }
    flag=1;
  }
  /*if((endTime - startTime) <=60000) 
  {  
    Serial.println(startTime);
    Serial.println(endTime);
    if (digitalRead(IR)==HIGH)
      blinks+=1;
      endTime = millis();
      Serial.print(blinks);
  }*/
  
  if (blinks/((endTime-startTime)/1000)<=(15.00/60.00)){
    flag2=0;
    alarm();
  }
  else{
    flag2=1;
    alarm();
  }
  Serial.print("Time: ");
  Serial.println((endTime-startTime)/1000);
  Serial.print("No. of blinks: ");
  Serial.println(blinks);
}
void alarm(){
  
  if ((endTime-last_alarm)/1000>60||last_alarm==0){
    if (flag2==0){
      Serial.println("No. of blinks less than threshold");
      Blynk.email("vikram.baruah2018@vitstudent.ac.in","No of blinks less than threshold. Blink more ");
      Blynk.notify("No. of blinks less than threshold ");
      digitalWrite(LED_PIN,HIGH);
    }
    else if (flag2==1){
      Serial.println("You are blinking well ");
      Blynk.notify("You are blinking well ");
      digitalWrite(LED_PIN,HIGH);
    }
    last_alarm=endTime;
  }
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
}
