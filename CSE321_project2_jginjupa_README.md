About
Project Description:

Project 2 for CSE 321 at the University at Buffalo. The project main purpouse is to Explore design and implementation in a bare metal system with a combination lock/security
system.
Contribitor List: Jayaprakash Ginjupalli
Features
1.Running  CSE321_project2_jginjupa_main.cpp will run a program in which a code is set to a specific number chosen by the user.
2.User can lock by entering the set code
3.User can unlock by entering the same set code again
Required Materials
 LCD (1602 or 1802)
● Nucleo
● Keypad
● Solderless Breadboard
● Jumper wires
● LEDs
● Resistors
Resources and References
- RM0432 Reference Manuel :https://www.st.com/resource/en/reference_manual/rm0432-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
- MbedOS documentation: https://os.mbed.com/docs/mbed-os/v6.15/introduction/index.html
Getting Started
This section will describe the general setup


1. Attach your laptop to the NUCLEO-L4R5ZI via the USB A to Micro USB B cable
2. Attach a keypad and lcd to the nucleo
3. attach the keypad and nucleo by conecting the jumper wires from keypad and nucleo to specific ports as listed in CSE321_project2_jginjupa_main.cpp.
4. Open Mbed Studio
5. Open Project2/CSE321_project2_jginjupa_main.cpp
6. Set the target to your connect NUCLEO-L4R5ZI
8. Press the Run button on the left hand side of the screen
Files
CSE321_project2_jginjupa_main.cpp: Date Created: 2022 September 29

File Summary: This file contains the code lock and unlock from a keypad

API and Built In Elements Used
API's: - mbed: allows for streamlined interaction between C plus plus and the NUCLEO-L4R5ZI hardware.
