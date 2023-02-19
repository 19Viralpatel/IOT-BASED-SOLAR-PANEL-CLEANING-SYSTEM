# IOT-BASED-SOLAR-PANEL-CLEANING-SYSTEM

## Description
  This project is used for automatic/manual cleaning of solar panel whenever it is required. First of all it will measure the level of dust by using LDR sensors. LDR sensor will measure the intensity of sun, as intensity decreases dust will be detected if not there is no dust. When the level of dust is increases up to specific value at that time intensity will be reduced, so user get an alert msg on telegram bot for clean the solar panel. Also with the help of ESP32-cam module user will get photo panel on same telegram bot so that user can know false triggering is done or not. False triggering is due to cloudy weather or monsoon season. Also for turning on motor we have used one manual switch. 

  When any one of the LDR sensor shows less intensity we will clean panel and we will check again intensity, if it shows again less value comapre to our predefine value indicates dust has been freezed on LDR sensor (or on that area of solar panel). If all LDR shows less intensity everytime so the water used for cleaning may be tedious, so user have to clean manually whole solar panel.
  
  Also it can be done automatically with the help of telegram bot. user may give command like motor on, motor off, status (intensity or dust level), photo etc. At night time ESP32 will be in sleep mode, So no false triggering occurs at night, for that we have use timer for 18 hours which is inbuilt in ESP32.
