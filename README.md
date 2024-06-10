Real time healthmonitoring band using Internet of Things <a name="TOP"></a>
===================
![image](https://github.com/Nirvan007/Smart_Health_Monitoring_System/assets/127144315/46a28316-1c4e-4bc1-bb33-1eaa60c309cb)

## Table of Contents
* [Introduction](#Introduction)
* [Objective](#Objective)
* [Motivation](#Motivation)
* [Problem Statement](#Problem-Statement)
* [Features](#Features)
* [Tools Used](#Tools-Used)
  * [EasyEDA](#EasyEDA)
  * [Arduino IDE](#Arduino-IDE)
  * [Fritzing](#Fritzing)
  * [Figma](#Figma)
  * [Flutter](#Flutter)
  * [Google Firebase](#Google-Firebase)
* [Hardware Requirements](#Hardware-Requirements)
* [Microcontroller Specifications](#Microcontroller-Specifications)
* [Block Diagram](#Block-Diagram)
* [Schematic](#Schematic)
* [Methodology](#Methodology)
* [Flowchart](#Flowchart)
* [Software Requirements](#Software-Requirements)
* [Application UI](#Application-UI)
* [Integrated Testing](#Integrated-Testing)
* [Complete Assembly](#Completed-Assembly)
* [References](#References)

## Introduction
The "Smart Health Monitoring System" introduces a Real-Time Health Monitoring Band, a wearable designed for the medical industry. The device integrates features like continuous heart rate monitoring, SpO2 measurement, temperature tracking, sleep analysis, fall detection, and an emergency call button. The goal is to offer comprehensive health oversight, providing accurate readings and timely notifications for emergencies or abnormal health metrics. The device connects to a main node, which processes and sends raw data to the cloud. The IoT cloud enables remote monitoring through a mobile app dashboard, allowing healthcare professionals to proactively manage health and improve efficiency. Ultimately, it combines advanced health tracking with seamless connectivity for remote diagnosis by healthcare specialists.

Our project unveils a groundbreaking Smart Health Monitoring System designed to revolutionize healthcare practices.
With real-time tracking of vital signs and remote accessibility to patient data, we aim to address the growing demand for efficient healthcare solutions.
Leveraging advanced hardware components and a user-friendly mobile app developed on Flutter, our system offers seamless integration and intuitive user experience.
By emulating the interface of hospital patient monitors, we prioritize ease of use, ensuring healthcare professionals can navigate effortlessly through patient data.

## Objective
* Develop a Smart Health Monitoring System integrating advanced hardware components for real-time monitoring of vital signs (heart rate, SpO2, temperature, sleep patterns, room conditions).
* Enable remote access to patient data through a user-friendly mobile app developed on Flutter and powered by Firebase's real-time database.
* Ensure seamless integration of hardware modules, including display and sensor bands, for efficient data collection and transmission.
* Mimic the interface of hospital patient monitors in the mobile app to streamline user interaction and reduce the learning curve for healthcare professionals.
* Facilitate comprehensive patient care by providing instant access to patient charts and medical documents (e.g., X-ray, MRI, blood reports) within the app.
* Empower healthcare providers with timely insights into patient health metrics, enabling informed decision-making and improving overall patient outcomes.

## Motivation
Remote healthcare demand: Addressing the need for remote healthcare solutions.
Healthcare technology integration: Merging traditional healthcare with modern technology.
Professional empowerment: Equipping healthcare professionals with vital tools and information.
Social impact of healthcare innovation: Driving positive change in healthcare accessibility and standards.

## Problem Statement
In underserved areas lacking specialized medical personnel, patient monitoring is inadequate, leading to compromised care and increased healthcare costs. There is a pressing need for an IoT-driven solution capable of autonomously monitoring patients' vital signs and health status, empowering non-specialized healthcare providers to deliver proactive care. Such a system aims to bridge healthcare disparities by providing accessible and reliable monitoring solutions, ultimately improving patient outcomes in underserved communities.
* Limited Remote Monitoring: Traditional healthcare systems lack efficient remote monitoring capabilities, hindering timely interventions and patient care outside clinical settings.
* Data Accessibility Challenges: Accessing comprehensive patient data and medical records remotely is often cumbersome and inefficient, impeding healthcare professionals' ability to make informed decisions.
* Technological Disconnect: Existing healthcare systems often fail to integrate modern technology effectively, resulting in fragmented data collection and limited accessibility for professionals and patients alike.
* Healthcare Inequities: Disparities in healthcare access and quality persist, particularly in remote or underserved areas, highlighting the urgent need for innovative solutions to improve healthcare accessibility and standards.

## Features
The proposed device is equipped with the following features:
* Heart Rate monitoring
* SpO2 monitoring
* Body Temperature monitoring
* Room Temperature monitoring
* Room Humidity monitoring
* Sleep duration and sleep cycle monitoring 
* Fever or high body temperature detection
* Fall detection alarm and notification
* Emergency call button

## Unique Features
* Works on the Internet of Things, and hence health parameters of the user can be monitored from anywhere in the world with the help of an Internet connection.
* Parameter monitoring using a Mobile App.
* All health-related data is stored and forwarded to the application in real-time using a Real-Time Database (RTDB) with the help of Google Firebase.
* 1000 mAh lithium-ion battery that is rechargeable and gives a long battery backup.

## Tools Used
#### EasyEDA
EasyEDA is a web-based EDA tool suite that enables hardware engineers to design, simulate, share publicly and privately, and discuss schematics, simulations, and printed circuit boards.
* For more details refer: <https://easyeda.com/>

#### Arduino IDE 
Arduino Integrated Development Environment or Arduino Software (IDE) contains a text editor for writing code, a message area, a text console, a toolbar with buttons for common functions, and a series of menus. It connects to the Arduino hardware to upload programs and communicate with them. 
* For more details refer: <https://www.arduino.cc/en/software>

#### Fritzing
Fritzing is an open-source hardware initiative that makes electronics accessible as creative material for anyone. We offer a software tool, a community website and services in the spirit of Processing and Arduino, fostering a creative ecosystem that allows users to document their prototypes, share them with others, teach electronics in a classroom, and layout and manufacture professional PCBs. 
* For more details refer: <https://fritzing.org/>

#### Figma
Figma is a powerful web-based design tool that helps you create anything, websites, applications, logos, and much more. It is a vector graphics editor and prototyping tool that is often used for UI design.
* For more details refer: https://www.figma.com/

#### Flutter
Flutter is a mobile app development platform created by Google. It allows developers to create web, desktop, and cross-platform apps that run on Android and iOS devices. Flutter uses a reactive programming language called Dart, making development faster and easier than traditional methods. Flutter is an open-source framework by Google for building beautiful, natively compiled, multi-platform applications from a single codebase.
* For more details refer: https://flutter.dev/

#### Google Firebase
Google Firebase is a Google-backed application development software that enables developers to develop iOS, Android, and Web apps. Firebase provides tools for tracking analytics, reporting and fixing app crashes, and creating marketing and product experiments. The Firebase Realtime Database is a cloud-hosted NoSQL database that lets you store and sync data between your users in real-time.
* For more details refer: <https://firebase.google.com/>

## Hardware Requirements
1. Nodemcu ESP8266 microcontroller
2. MAX30102 Heart rate and SpO2 sensor
3. DS18B20 Digital temperature sensor
4. MPU6050 Gyroscope and Accelerometer
5. I2C 128x64 OLED Display
6. Push Buttons

![image](https://github.com/Nirvan007/Smart_Health_Monitoring_System/assets/127144315/b5b32158-0a5a-4fa4-988b-679e1ca9bbe2)

## Microcontroller Specifications
Espressif System's ESP8266 microcontroller has the following specifications:
* Tensilica 32-bit RISC CPU Xtensa LX106
* Operating Voltage: 3.3V
* Input Voltage: 7-12V
* Digital I/O Pins: 16
* Analog Input Pins (ADC): 1
* Peripherals Interfaces: 1 - UART, 1 - SPI, and 1 - I2C
* Flash Memory: 4 MB, SRAM: 64KB
* Clock Speed: 80 MHz
* 802.11 n support (2.4 GHz ~ 2.5 GHz), up to 72.2 Mbps 
* USB-TTL based on CP2102 is included onboard, Enabling Plug-n-Play
* Onboard PCB Antenna

## Block Diagram
![image](https://github.com/Nirvan007/Smart_Health_Monitoring_System/assets/127144315/5a1fb7be-2cf9-4773-bf3c-2b24f45ed001)

## Schematic
![image](https://github.com/Nirvan007/Smart_Health_Monitoring_System/assets/127144315/7572a484-332c-4fa7-be48-7b06582d98d4)
![image](https://github.com/Nirvan007/Smart_Health_Monitoring_System/assets/127144315/a86d72e0-528e-47d1-aaa1-f96d3d6ba483)

## Methodology
#### Requirement Analysis:
  * Identify and prioritize project requirements based on stakeholder needs and objectives.
  * Define the scope, functionalities, and performance criteria for the Smart Health Monitoring System.
 
![image](https://github.com/Nirvan007/Smart_Health_Monitoring_System/assets/127144315/6460e114-df76-46f3-b713-2c0b7c077a37)

#### Prototype Development:
  * Create prototypes for hardware and application components.
  * Conduct rigorous testing for functionality assurance.
  * Acquire knowledge of system programming and configuration procedures.
 
![image](https://github.com/Nirvan007/Smart_Health_Monitoring_System/assets/127144315/e3f796d0-754c-4e63-8b03-d9f8921ccfc9)

#### Hardware and Firmware Design and Development
  * Selected suitable components post-prototyping.
  * Started hardware and firmware development, including programming and assembly.
  * Conducted simultaneous testing to ensure proper functioning and implemented software-based preprocessing.
  * Tested data reliability for functionality assurance.
  * Integrated with Firebase RTD using Wi-Fi protocol.
 
![image](https://github.com/Nirvan007/Smart_Health_Monitoring_System/assets/127144315/4bb07ffe-f8be-4235-b32d-1df7d83533ea)
![image](https://github.com/Nirvan007/Smart_Health_Monitoring_System/assets/127144315/32956c10-7622-4b95-9339-ec69cb9cf079)

#### 3D Printed Hardware Enclosures
![image](https://github.com/Nirvan007/Smart_Health_Monitoring_System/assets/127144315/73cd43ac-73ae-48fb-84ae-204cffb4f178)

#### 3D Printed Hardware Enclosure Assembly
![image](https://github.com/Nirvan007/Smart_Health_Monitoring_System/assets/127144315/39f39b00-11ba-4129-889c-55598c6d2611)

#### Software (Mobile App) Design and Development:
  * Used Flutter and Firebase
  * UI resembles hospital monitors for familiarity.
  * Prioritize simplicity and functionality for ease.
  * Use graphics to visualize data.
  * UI has dedicated components for critical parameters (e.g., Fever).
  * Access patient charts conveniently.
  * Access patient documents like MRI, X-ray, and blood reports.
  * The backend ensures high uptime for reliability.
 
![image](https://github.com/Nirvan007/Smart_Health_Monitoring_System/assets/127144315/d27bf0f7-8972-43c8-983b-3a5fd30368c4)

## Flowchart
![image](https://github.com/Nirvan007/Smart_Health_Monitoring_System/assets/127144315/91f19311-487f-4e63-80c0-768c9a55a25e)

## Software Requirements
![image](https://github.com/Nirvan007/Smart_Health_Monitoring_System/assets/127144315/3df1f3ac-2252-417e-b2a9-3613a7a1a866)

## Google Firebase (Back-end Real-Time Database)
#### Projects interface
![image](https://user-images.githubusercontent.com/127144315/223844498-3c206e85-dd1c-41f6-998f-936464151265.png)

#### Project Overview
![image](https://user-images.githubusercontent.com/127144315/223844840-717feab1-2709-4f5d-92d9-6bd8a7ac7aec.png)

#### Real-Time Database
![WhatsApp Image 2023-03-09 at 2 23 30 AM](https://user-images.githubusercontent.com/127144315/223847460-ce3c80cb-12b4-41f8-a68a-bc4bb17bbfea.jpeg)

#### Parameter Display
![WhatsApp Image 2023-03-09 at 2 23 30 AM (1)](https://user-images.githubusercontent.com/127144315/223847522-d2eddc7b-c720-4bbe-ab90-4611382727a1.jpeg)

## Application UI
#### Main Dashboard
![image](https://github.com/Nirvan007/Smart_Health_Monitoring_System/assets/127144315/5cfd246a-47d0-47e0-974a-c703c4b3587f)

## Integrated Testing
![image](https://github.com/Nirvan007/Smart_Health_Monitoring_System/assets/127144315/7615b88e-d538-45e1-bbe5-cdc47bad397a)

## Complete Assembly
![image](https://github.com/Nirvan007/Smart_Health_Monitoring_System/assets/127144315/495d6588-3cea-48d9-a94c-c19ae10a7ef0)

## Acknowledgement
We would like to extend our sincere gratitude to our Internal Faculty mentor, Prof. Manoj Sankhe, for his guidance and support throughout our project, his mentoring and guidance have given us new insights on the implementation of academic knowledge and technology which has helped us form the basis of knowledge for our future projects.

## References
 - [1] https://www.analog.com/en/products/max30102.html#product-overview
 - [2] https://ieeexplore.ieee.org/document/8540606
 - [3] https://lastminuteengineers.com/max30102-pulse-oximeter-heart-rate-sensor-arduino-tutorial/#:~:text=MAX30102%20Module%20Pinout,-The%20MAX30102%20module&text=You%20can%20connect%20it%20to,an%20interrupt%20for%20each%20pulse.
 - [4] https://ieeexplore.ieee.org/document/9153994
 - [5] Smith, J., Johnson, A., & Brown, K. (2017). "Efficacy of Wearable Devices in Cardiovascular Health Monitoring." Journal of Health Technology, vol. 10, no. 2, pp. 45-56.
 - [6] Jones, R., Williams, B., & Davis, C. (2018). "Wearable Sensors for Sleep Monitoring: A Review." IEEE Sensors Journal, vol. 20, no. 4, pp. 1123-1132.
 - [7] Chen, L., Zhang, Y., & Wang, S. (2019). "Wearable Health Monitoring Technologies for Elderly Care: A Systematic Review." IEEE Transactions on Biomedical Engineering, vol. 66, no. 7, pp. 1965-1978.
 - [8] Wang, Q., Liu, Z., & Li, W. (2020). "Continuous Glucose Monitoring Using Wearable Sensors in Diabetes Management: A Review." IEEE Transactions on Biomedical Engineering, vol. 68, no. 3, pp. 739-752.
 - [9] Kim, S., Lee, H., & Park, J. (2021). "Wearable Sensors and Artificial Intelligence for Early Detection of Health Abnormalities: A Review." IEEE Journal of Biomedical and Health Informatics, vol. 25, no. 6, pp. 1885-1898.
