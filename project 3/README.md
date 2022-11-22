About
Author: Jayaprakash Ginjupalli

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Project Description: The objective of this project is to build a system by fusing hardware and software. The DHT11 sensor, which can measure temperature and humidity, will be used by this gadget to keep track of the humidity level in a house. The 16x2 LCD display will show the humidity percentage and safety rating (Ideal, Fair, Harmful). When humidity levels fall below 25% or climb beyond 75%, the buzzer device will constantly emit audio signals until they are safe, or until the user manually mutes it using the on-board user button. The goal of this research is to develop a tool that guards against the negative consequences that could arise from low or high humidity levels that go unnoticed.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Features

Runs Forever
Realtime display.
Detects humidity levels.
Displays current humidity percentage.
Audio warning when harmful humidity levels are detected.
User interactive.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Required Materials

Nucleo L4R5ZI

Solderless Breadboard

USB A to Micro USB B cable

DHT11 temperature humidity sensor

4x4 membrane matrix keypad

1602 LCD screen

ARCELI Passive Low Level Trigger Buzzer

Nucleo L4R5ZI

Jumper wires

    At least 10 Male to Female jumper wires
    At least 20 Male to Male jumper wires

Breadboard.
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Resources and References
UM2179 User Manual: https://www.st.com/resource/en/user_manual/dm00368330-stm32-nucleo-144-boards-mb1312-stmicroelectronics.pdf.
RM0432 Reference Manual: https://www.st.com/resource/en/reference_manual/dm00310109-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
Watchdog: https://os.mbed.com/docs/mbed-os/v6.15/apis/watchdog.html
LCD Manual: https://learn-us-east-1-prod-fleet02-xythos.content.blackboardcdn.com/5e00ea752296c/10911180?X-Blackboard-Expiration=1634364000000&X-Blackboard-Signature=MOnja6ZGfmHtNs46fE12cbxFgsWLDdX4ZfLcV9TC9Es%3D&X-Blackboard-Client-Id=100310&response-cache-control=private%2C%20max-age%3D21600&response-content-disposition=inline%3B%20filename%2A%3DUTF-8%27%27JDH_1804_Datasheet.pdf&response-content-type=application%2Fpdf&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20211016T000000Z&X-Amz-SignedHeaders=host&X-Amz-Expires=21600&X-Amz-Credential=AKIAZH6WM4PL5SJBSTP6%2F20211016%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=6fa8d9a1bdf470eda9395760ffff2ab2ed7a58c10a191064bf3342ddedc1d5ee
Buzzer Reference: http://tinkbox.ph/sites/tinkbox.ph/file/downloads/5V_BUZZER_MODULE.pdf
DHT11 Reference: https://components101.com/sites/default/files/component_datasheet/DHT 11-Temperature-Sensor.pdf
EventQueue: https://os.mbed.com/docs/mbed-os/v6.15/apis/eventqueue.html
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Getting Started
Connect the Nucleo to a computer with a USB A to Micro USB B cable.
Setup a power and ground connection to the breadboard.
Connect the external peripherals to the correct pins on the Nucleo-L4R5ZI with resistors and wires. 
Currently the hardware schematic has not been completed.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Additional Files

1602.cpp
1602.h
DHT11.cpp
DHT11.h

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Declarations

"lcd1602.cpp"
"lcd1602.h"
"DHT.cpp"
"DHT.h"
int sense_interval = 2000;
const uint32_t watchdog_timeout = 2500;
void sense();
void display();
void audio();
void mute();
void initiate_watchdog(int);
DHT11 sensor(PC_8);
CSE321_LCD LCD(16,2,LCD_5x10DOTS,PB_9,PB_8);
bool muted;

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
