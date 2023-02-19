# IOT-BASED-SOLAR-PANEL-CLEANING-SYSTEM

## Description
  This project is used for automatic/manual cleaning of solar panel whenever it is required. First of all it will measure the level of dust by using LDR sensors. LDR sensor will measure the intensity of sun, as intensity decreases dust will be detected if not there is no dust. When the level of dust is increases up to specific value at that time intensity will be reduced, so user get an alert msg on telegram bot for clean the solar panel. Also with the help of ESP32-cam module user will get photo panel on same telegram bot so that user can know false triggering is done or not. False triggering is due to cloudy weather or monsoon season. Also for turning on motor we have used one manual switch. 

  When any one of the LDR sensor shows less intensity we will clean panel and we will check again intensity, if it shows again less value comapre to our predefine value indicates dust has been freezed on LDR sensor (or on that area of solar panel). If all LDR shows less intensity everytime so the water used for cleaning may be tedious, so user have to clean manually whole solar panel.
  
  Also it can be done automatically with the help of telegram bot. user may give command like motor on, motor off, status (intensity or dust level), photo etc. At night time ESP32 will be in sleep mode, So no false triggering occurs at night, for that we have use timer for 18 hours which is inbuilt in ESP32.

## Challanges
We face a problem in code that some unnessasary delay is produce due to functions. Also major problem faced in interfacing esp32 cam module with esp32 module. The command we give to telegram bot that command telegram bot gives further to esp32 but we want to take photo from esp32 cam module and send it to telegram bot where we have given command, So we have to merge both module(esp32 and esp32 cam).

## LDR VALUES

![photo_2023-02-19_17-21-24](https://user-images.githubusercontent.com/124424323/219948760-fcdbcc3f-a10b-4946-b051-f4c090cd6b64.jpg)

## TELEGRAM BOT

![photo_2023-02-19_17-21-50](https://user-images.githubusercontent.com/124424323/219948796-d4e78e13-d648-49cc-b952-a721a7abd394.jpg)
![photo_2023-02-19_17-22-13](https://user-images.githubusercontent.com/124424323/219951736-8d4647aa-7569-4423-bbf6-25e05becc555.jpg)

## Temprary Setup On Bread Board

![photo_2023-02-19_17-22-22](https://user-images.githubusercontent.com/124424323/219951856-28cee4c7-67b6-467e-a419-c3e396ecb5ea.jpg)

## Prototype View

![photo_2023-02-19_18-03-04](https://user-images.githubusercontent.com/124424323/219951887-4cd73bf2-01ea-45ee-b0b6-9295ea7c7f22.jpg)

## Wholw setup

![photo_2023-02-19_17-21-15](https://user-images.githubusercontent.com/124424323/219952639-9423192d-8c87-441c-b662-2b83ef1d4670.jpg)


## You Tube
<a href=https://youtu.be/SolaR4ohJPU> ![image](https://user-images.githubusercontent.com/124425596/219943044-52ab591f-99d9-42aa-9d2f-920951f22c1d.png)
</a>
