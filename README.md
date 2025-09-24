# IoT Based Smart Dustbin

This project presents a novel solution to the critical challenge of waste management in urban environments. The **IoT Based Smart Dustbin** is a system designed to enhance efficiency, hygiene, and user convenience in waste disposal. By integrating various sensors and actuators with an IoT platform, the system provides real-time monitoring and automates waste disposal processes to prevent overflow and promote a cleaner environment.

---

### Key Features

* **Hands-Free Lid Opening:** The system uses a servo motor activated by an **IR sensor** to automatically open the lid when a person is detected, ensuring a hygienic, hands-free experience.
* **Real-time Waste Level Monitoring:** An **ultrasonic sensor** continuously measures the fill level of the dustbin, providing real-time data to prevent overflow.
* **Mobile Alerts & Notifications:** The system sends notifications to a user's smartphone via the **Blynk app** when the dustbin reaches a predefined threshold, alerting stakeholders for timely collection.
* **Intuitive User Interface:** An LED-based interface provides visual feedback on the dustbin's status, ensuring accessibility for users.

---

### Technologies Used

#### Hardware
* **Microcontroller:** ESP8266 NodeMCU
* **Sensors:** Ultrasonic Sensor (HC-SR04), IR Sensor
* **Actuator:** Servo Motor (SG90)
* **Indicators:** LEDs

#### Software
* **IDE:** Arduino IDE
* **IoT Platform:** Blynk App

---

### System Architecture

The system is built on an **ESP8266 microcontroller** platform. **IR sensors** detect the presence of a user, triggering the **servo motor** to open the lid. **Ultrasonic sensors** continuously monitor the waste level, and when a predefined threshold is reached, the microcontroller activates the notification system to alert relevant stakeholders. This seamless integration of hardware and software components aims to revolutionize waste disposal practices.

---

### Project Team

This was a mini-project for the Bachelor of Engineering degree in Computer Engineering at Pillai HOC College of Engineering and Technology.

* **Prajwal Halle**
* Smitesh Gajakosh
* Prathmesh Chaudhari
