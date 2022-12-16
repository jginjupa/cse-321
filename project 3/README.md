About
Author: Jayaprakash Ginjupalli

---------------------------------------------------------------------------------------------------------------------------------------------------------

This is Project 3 of CSE 321

A temperature and humidity alarm is  designed in this project. The user can input a temperature range between 0 and 50 degree Celsius. 
If the measured temperature is not in the set range, the buzzer outputs sound will alert people that the temperature is out of range.

Features:


Easy to setup.

0 ℃ to 50 ℃. Temperature range

Low power consumption

Watchdog is set up to reset the system in the case of system failures or malfunctions.

EventQueue is used for critical section protection

Mutex is used for synchronization

Multiple threads are used to allow the different peripherals to run at the same time.

----------------------------------------------------------------------------------------------------------------------------------------------------------------
Required Materials
DHT11 temperature humidity sensor

1802 LCD screen

ARCELI Passive Low Level Trigger Buzzer

Nucleo L4R5ZI

Jumper wires

At least 10 Male to Female jumper wires
At least 20 Male to Male jumper wires
Breadboard.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------
Resources and References
IntteruptIn: https://os.mbed.com/docs/mbed-os/v6.14/apis/interruptin.html

Thread_sleep_for: https://os.mbed.com/docs/mbed-os/v6.12/mbed-os-api-doxy/group__mbed__thread.html#gaaa7efb95f13c2f6055a930fd8ae06942

STMicroelectronics, UM2179 User Manual: https://www.st.com/resource/en/user_manual/dm00368330-stm32-nucleo-144-boards-mb1312-stmicroelectronics.pdf

STM32L4 Reference manual: https://www.st.com/resource/en/reference_manual/dm00310109-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf

DigitalOut: https://os.mbed.com/docs/mbed-os/v6.8/apis/digitalout.html

Watchdog: https://os.mbed.com/docs/mbed-os/v6.15/apis/watchdog.html

Mutex: https://os.mbed.com/docs/mbed-os/v6.15/apis/mutex.html

Thread: https://os.mbed.com/docs/mbed-os/v6.15/apis/thread.html

EventQueue: https://os.mbed.com/docs/mbed-os/v6.15/apis/eventqueue.html

------------------------------------------------------------------------------------------------------------------------------------------------------------

Getting Started
Mbed Studio is needed to compile the codes into Nucleo L4R5ZI.
Create an empty Mbed OS program.
Download the files listed below into the program folder, and delete the original main.cpp
CSE321_project3_jginjupa_main.cpp
DHT.cpp
DHT.h
1802.cpp
1802.h
Connect Nucleo L4R5ZI to the computer.
Click “Run program” to compile the code into Nucleo L4R5ZI.
Once the device is connected to a power source the LCD should display “Humidity Level:  %”
on the 1st row and “State: 	“on the 2nd row.
The device will automatically detect and update the display with the current humidity and state every 2.5 seconds.
The state indicates the quality of the current humidity. The alarm will sound if state becomes
“Harmful” and will automatically mute once levels become “Ideal” or “Fair”.
Ideal: This indicates optimal humidity %
Fair: Humidity % isn’t optimal, but not harmful.
Harmful: Humidity is too low or too high, consider addressing this to avoid negative effects.
If the alarm becomes activated, the user button B1 may be pressed to mute it.
Once muted, it cannot be unmuted unless state changes to “Fair” or “Ideal” and back to “Harmful” again.

The main program that implement the logic. Multiple threads are created for parallel tasks. Watchdog is set up to reset the system in the case of system failures or malfunctions. Mutex is set up for synchronization. EventQueue is set up for critical section protection. Four interrupts are set up for four columns of the matrix keypad. Bitwise driver control is used to control the output of rows of the keypad.

-------------------------------------------------------------------------------------------------------------------------------------------------------------
Things Declared

"1802.cpp"
"1802.h"
"DHT.cpp"
"DHT.h"
InterruptIn mute_pressed(PC_13);        // User Button is the mute button.
void sense();
void display();
void audio();
void mute();
void initialize_watchdog(int);

=------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
API and Built In Elements Used
lcd1802.cpp and lcd1802.h is provided by Dr. Winikus. The two files contains API that utilized the 1602 LCD to perform different functions like print, setCursor.

DHT.cpp and DHT.h is provided by Dr. Winikus. The two files contains API that utilized the DHT11 temperature humidity sensor to perform different functions like read, getCelsius.

IntteruptIn: https://os.mbed.com/docs/mbed-os/v6.14/apis/interruptin.html

Thread_sleep_for: https://os.mbed.com/docs/mbed-os/v6.12/mbed-os-api-doxy/group__mbed__thread.html#gaaa7efb95f13c2f6055a930fd8ae06942

STMicroelectronics, UM2179 User Manual: https://www.st.com/resource/en/user_manual/dm00368330-stm32-nucleo-144-boards-mb1312-stmicroelectronics.pdf

STM32L4 Reference manual: https://www.st.com/resource/en/reference_manual/dm00310109-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf

DigitalOut: https://os.mbed.com/docs/mbed-os/v6.8/apis/digitalout.html

Watchdog: https://os.mbed.com/docs/mbed-os/v6.15/apis/watchdog.html

Mutex: https://os.mbed.com/docs/mbed-os/v6.15/apis/mutex.html

Thread: https://os.mbed.com/docs/mbed-os/v6.15/apis/thread.html

EventQueue: https://os.mbed.com/docs/mbed-os/v6.15/apis/eventqueue.html

