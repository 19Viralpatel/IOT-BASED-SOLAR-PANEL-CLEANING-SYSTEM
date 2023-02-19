#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>

// Replace with your network credentials

#define WIFI_NAME "Divyesh's Redmi Note 10T 5G"                    // WiFi Name
#define WIFI_PASS "divyesh2505"                                    // WiFi Password

#define BOTtoken "5831948850:AAEdMpJvW7jeRhM7UX4IuhbHyWB1fCZa-q4"  // your Bot Token (Get from Botfather)
#define CHAT_ID "1715160096"

#define LDR1  34                                                    // Output Of LDR1 + Resistance Pin
#define LDR2  35                                                    // Output Of LDR2 + Resistance Pin
#define LDR3  32                                                    // Output Of LDR2 + Resistance Pin
#define Switch 27
#define Photo_Switch 26

float Level_Percentage = 50.0;

float LDR_Vol1=0.0;
float LDR_Vol2=0.0;
float LDR_Vol3=0.0;

float Intensity1=0.0;
float Intensity2=0.0;
float Intensity3=0.0;
float Intensity_avg=0.0;
bool ledstatus=false;                                                   // Variable For LED Status
bool previous_read=false;
bool SendPhoto=true;

String Intensity_status="0";

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Checks for new messages every 1 second.
int botRequestDelay = 1000;
int Motor_On_Count=0;
unsigned long lastTimeBotRan;

const int wifiled = LED_BUILTIN;
bool ledState = LOW;

void setupWiFi()
 {
   int count=0;
   Serial.println("Connecting..");
   WiFi.begin(WIFI_NAME, WIFI_PASS);
   while (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("Still Connecting....!");
      delay(100);
      count=count+1;
      if(count==15)
        {
          Serial.println(count);
          break;
        }
    }
    if(WiFi.status() == WL_CONNECTED)
      {
        int i=0;
        while(i<5)
          {
            digitalWrite(wifiled, HIGH);
            delay(200);
            digitalWrite(wifiled, LOW);
            delay(200);
            i++;                                                    // 5 Times LED Blink When Connected Successfully With WiFi
          }
        Serial.println("Connected with wifi Successfully..!");
      }
    else
      {
        Serial.println("RESET ESP32..!!");                          // If Esp32 Not Connected in 15 Cycle Of While Loop Then Reset Again
        ESP.restart();
      } 
  }

 void Check_Wifi()
{
  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("RESET ESP32..!!");                          // If Esp32 Not Connected in 15 Cycle Of While Loop Then Reset Again
    ESP.restart();
  }
}

void Check_switch_changes()
{
  if(digitalRead(Switch) != previous_read)
  {
    ledstatus = !ledstatus;
    if(ledstatus)
    {
      Motor_On_Count=Motor_On_Count+1;
    }
    digitalWrite(wifiled,ledstatus);
    previous_read = !previous_read;
  }
}

void LDR_Reading()
{
  LDR_Vol1=analogRead(LDR1);
  delay(100);
  LDR_Vol2=analogRead(LDR2);
  delay(100);
  LDR_Vol3=analogRead(LDR3);
  delay(100);
  
  Intensity1=(LDR_Vol1*100)/4095.0;
  Intensity2=(LDR_Vol2*100)/4095.0;
  Intensity3=(LDR_Vol3*100)/4095.0;

  Intensity_avg = (Intensity1 + Intensity2 + Intensity3)/3;
  Serial.println("\nLDR1 : ");
  Serial.println(Intensity1);
  Serial.println("\nLDR2 : ");
  Serial.println(Intensity2);
  Serial.println("\nLDR3 : ");
  Serial.println(Intensity3);
  
}

void Check_Intensity()
{
  if(Intensity1 <= Level_Percentage && Intensity2 <= Level_Percentage && Intensity3 <= Level_Percentage)
  {
    if (SendPhoto)
    {
      digitalWrite(Photo_Switch,LOW);
      delay(1000);
      digitalWrite(Photo_Switch,HIGH);
      Serial.println("Dust detected..!!\nPlease clean the solar panel."); 
      bot.sendMessage(CHAT_ID, "Dust detected..!!\nPlease clean the solar panel.", "");
      SendPhoto=false;
    }
  }
  else if(Intensity1 <= Level_Percentage && Intensity2 >= Level_Percentage && Intensity3 >= Level_Percentage)
  {
    bot.sendMessage(CHAT_ID, "Intensity of sensor 1 has been reduce due to dust.\nPlease clean sensor 1 area.", "");
    bot.sendMessage(CHAT_ID,"Want to know condition of panel ?\nSend command /PHOTO", "");
  }
  else if(Intensity1 >= Level_Percentage && Intensity2 <= Level_Percentage && Intensity3 >= Level_Percentage)
  {
    bot.sendMessage(CHAT_ID, "Intensity of sensor 2 has been reduce due to dust.\nPlease clean sensor 2 area.", "");
    bot.sendMessage(CHAT_ID,"Want to know condition of panel ?\nSend command /PHOTO", "");
  }
  else if(Intensity1 >= Level_Percentage && Intensity2 >= Level_Percentage && Intensity3 <= Level_Percentage)
  {
    bot.sendMessage(CHAT_ID, "Intensity of sensor 3 has been reduce due to dust.\nPlease clean sensor 3 area.", "");
    bot.sendMessage(CHAT_ID,"Want to know condition of panel ?\nSend command /PHOTO", "");
  }
}

void Check_Intensity_Not_Dust()
{
  if(Intensity1 <= Level_Percentage && Intensity2 <= Level_Percentage && Intensity3 <= Level_Percentage)
  {
    if (SendPhoto)
    {
      digitalWrite(Photo_Switch,LOW);
      delay(1000);
      digitalWrite(Photo_Switch,HIGH);
      Serial.println("Again Dust Detected..!!\nYou Have To Clean Whole Solar Panel Manually..!!"); 
      bot.sendMessage(CHAT_ID, "Dust detected..!!\nPlease clean the solar panel.", "");
      SendPhoto=false;
    }
  }
  else if(Intensity1 <= Level_Percentage && Intensity2 >= Level_Percentage && Intensity3 >= Level_Percentage)
  {
    bot.sendMessage(CHAT_ID, "Intensity of sensor 1 still less.\nPlease clean sensor 1 area manually.", "");
    bot.sendMessage(CHAT_ID,"Want to know condition of panel ?\nSend command /PHOTO", "");
  }
  else if(Intensity1 >= Level_Percentage && Intensity2 <= Level_Percentage && Intensity3 >= Level_Percentage)
  {
    bot.sendMessage(CHAT_ID, "Intensity of sensor 2 still less.\nPlease clean sensor 2 area manually.", "");
    bot.sendMessage(CHAT_ID,"Want to know condition of panel ?\nSend command /PHOTO", "");
  }
  else if(Intensity1 >= Level_Percentage && Intensity2 >= Level_Percentage && Intensity3 <= Level_Percentage)
  {
    bot.sendMessage(CHAT_ID, "Intensity of sensor 3 still less.\nPlease clean sensor 3 area manually.", "");
    bot.sendMessage(CHAT_ID,"Want to know condition of panel ?\nSend command /PHOTO", "");
  }
}

void Telegram_bot()
{
  if (millis() > lastTimeBotRan + botRequestDelay)  
    {
      int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
      while(numNewMessages) 
        {
          Serial.println("got response");
          handleNewMessages(numNewMessages);
          numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        }
      lastTimeBotRan = millis();
    }
}
void handleNewMessages(int numNewMessages) 
{
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;
    
    if (text == "/MOTOR_ON") 
    {
      digitalWrite(wifiled, HIGH);
      bot.sendMessage(chat_id, "MOTOR is ON", "");  
      Serial.println("MOTOR is ON");
      ledstatus=true;
      Motor_On_Count=Motor_On_Count+1;
    }
    
    else if (text == "/MOTOR_OFF") 
    {
      digitalWrite(wifiled, LOW);
      bot.sendMessage(chat_id, "MOTOR is OFF", "");  
      Serial.println("MOTOR is OFF");
      ledstatus=true;
    }
    else if (text == "/PHOTO") 
    {
      digitalWrite(Photo_Switch,LOW);
      delay(1000);
      digitalWrite(Photo_Switch,HIGH);
      bot.sendMessage(chat_id, "Sending Photo....", "");
      Serial.println("Sending Photo....");
    }
    else if (text == "/STATUS") 
    {
      Intensity_status= "\nSUN intensity is : ";
          Intensity_status += Intensity_avg;
          Intensity_status += "%\n";
          Intensity_status += "\nLDR1 intensity is : ";
          Intensity_status += Intensity1;
          Intensity_status += "%\n";
          Intensity_status += "\nLDR2 intensity is : ";
          Intensity_status += Intensity2;
          Intensity_status += "%\n";
          Intensity_status += "\nLDR3 intensity is : ";
          Intensity_status += Intensity3;
          Intensity_status += "%\n";
      if(ledstatus)
      {
        Intensity_status += "\nMOTOR is ON";
        bot.sendMessage(chat_id, Intensity_status);
        Serial.println(Intensity_status);
      }
      else
      {
        Intensity_status += "\nMOTOR is OFF";
        bot.sendMessage(chat_id, Intensity_status);
        Serial.println(Intensity_status);
      }
    }
   else 
   {
    String welcome = "Welcome, " + from_name + ".\n";
          welcome += "Send your command.\n";
          welcome += "/MOTOR_ON : to switch the Motor ON\n";
          welcome += "/MOTOR_OFF : to switch the Motor OFF\n";
          welcome += "/PHOTO : to know condition of panel\n";
          welcome += "/STATUS : to know status of Motor and Sun intensity\n";
          bot.sendMessage(chat_id, welcome, "");
          Serial.println(welcome);
   }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(Photo_Switch, OUTPUT);
  digitalWrite(Photo_Switch,HIGH);
  pinMode(wifiled, OUTPUT);
  digitalWrite(wifiled, ledState);  
  setupWiFi();                                                    // WiFi Setup Function Call
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
}

void loop() {
  Check_Wifi();
  Telegram_bot();
  Check_switch_changes();
  LDR_Reading();
  
  if(Motor_On_Count>0)
  {
    Check_Intensity_Not_Dust();
  }
  else
  {
    Check_Intensity();
  }       
}
