
/* 
Author: Jayaprakash Ginjupalli
Course: CSE321
Creation Date: 12/13/2022
Program Name: tempurature and humidity alarm
Program Summary: This program is the software required to operate the humidity alarm being designed. 
                 The humidity alarm is a device that detects the humidity levels in a room, and alarms 
                 the user when the humidity percentage becomes too high or low via the buzzer audio module.
                 The buzzer will continue to output noise until levels return to normal or the user button B1
                 on the Nucleo is pressed. Once the buzzer is muted, it cannot be unmuted and will remain as such 
                 until the  state returns to "Fair" or "Ideal" again. This design choice is modelled after 
                 smoke detectors.The humidity percentage and state will be printed onto the LCD and serial monitor. 
Inputs: DHT11 humidity data, User button B1
Outputs: Humidity percentage, and state printed to LCD, Buzzer audio output.
Implementation Requirements: Watchdog timer, Synchronization technique, Bitwise driver configuration,
                             Critical section protection, Use of threads/tasks, 1 Interrupt.
Required Materials: Nucleo-L4R5ZI, DHT11 Sensor, Buzzer audio module, 18x2 LCD Display, Wires, Resistors,
                    Breadboard, USBA to Micro USB B.
Additional Info: The buzzer is activated on an actived on an active low signal. 
                 Sampling period of DHT11 must be > 2 seconds.
                 Watchdog times out if not kicked within 2.2 seconds.
                 Pin Mappings:SCL: PB_8, SDA: PB_9, Buzzer: PB_15, Button 1: PC_14, DHT11: PC_5
*/
#include "mbed.h"
#include "DHT.h"
#include "1802.h"
#include <cstdint>
#include <cstdio>
#include <iterator>
#include <string>
#include <stdio.h>

int sense_interval = 3000;              // DHT11 Senses every 3 seconds.
const uint32_t watchdog_timeout = 3000; // Watchdog times out after 2.2 seconds.        

Thread thread_sense;                         // This thread will sense humidity.
Thread thread_display;                       // This thread will update the LCD
Thread thread_audio;                         // This thread will control the buzzer.
InterruptIn mute_pressed(PC_14);        // User Button is the mute button.
void sense();
void display();
void audio();
void mute();
void initialize_watchdog(int);

Queue<int,1> display_humidityque;
Queue<string,1> state_que;
DHT11 sensor(PC_5);
CSE321_LCD LCD(18,2,LCD_5x10DOTS,PB_9,PB_8);

bool muted;
string state;
int humidity;
int main()
{
    LCD.begin();
    initialize_watchdog(watchdog_timeout);

    RCC->AHB2ENR |= 0x6;            //Enable ports B and C.
    GPIOB->MODER &=~(0x800A0000);   //Configure GPIOB Moder: Output (01) for pins 8(SCL), 9(SDA) & 15(Buzzer).
    GPIOB->MODER |= 0x40050000;
    GPIOC->MODER &=~(0x300C000);    //Configure GPIOC Moder: Input (00) for pins 5(DHT) & 14(User Button).
    GPIOB->ODR |= 0x4000;           //Disable buzzer noise: PB_14
    GPIOC->IDR |= 0x20;             //Configure DHT11 IDR: PC_5

    thread_sense.start(sense);  
    thread_display.start(display);
    thread_audio.start(audio);
    mute_pressed.rise(mute);
    
}
/*
Function Name: sense()
Function Purpose: This function is executed by the thread thread_sense,
                  and will continuouslly read data from the DHT11 
                  sensor, and update variables "state", and "humidity"
                  accordingly. 
                  Saftey Levels: 
                    Ideal: 30% < Humidity% < 60%
                    Fair: 25% <= Humidity% <= 30% OR 60% <= humidity% <=70%.
                    Harmful: 30% > humidity% > 70%, 
Inputs: Data from DHT11 Sensor
Outputs: Sends &humidity to display_humidityque, and &state to stateQue.
Constraints: Sensor can only sense in intervals greater than 2 seconds.
*/
void sense(){
    while(true){
        thread_sleep_for(sense_interval);
        sensor.read();
        int H_data = sensor.getHumidity();
        string state_data;
        if(H_data < 30 || H_data < 60 ){
            state_data = "Ideal";
        }
        else if ((H_data >= 25 && H_data <= 30) || (H_data >= 60 && H_data <= 70)) {
            state_data = "Fair";
        }
        else if(H_data < 30 || H_data > 70){
            state_data = "Harmful";
        }
        state_que.try_put(&state_data);
        display_humidityque.try_put(&H_data);
    }
}
/*
Function Name: display()
Function Purpose: This function will wait for humidity and state 
                  data from the two Queues and display the humidity 
                  and state on the LCD display, and serial monitor 
                  when received. If data isn't received from the 
                  queue within 3 seconds, the watchdog timer will
                  reset the program. 
Inputs: int humidity, string level.
Outputs: Update LCD everytime data is given to the queue changes.
         Activates buzzer if state == "Harmful", and disables it
         otherwise.
Constraints: Can only update as fast as sensor is able to sense.
 */
void display(){ 
        while(true){
            // Wait for data to be sent to both queues.
            osEvent humidityMsg = display_humidityque.get(osWaitForever);
            osEvent stateMsg = state_que.get(osWaitForever);
            
            //Extract the values and update global variables.
            state = *(string*)stateMsg.value.p;
            humidity = *(int*)humidityMsg.value.p;

            //Construct the strings to display
            string humidity_str = "Humidity: "+ std::to_string(*(int*)humidityMsg.value.p) + "%";
            string state_str = "State: " + *(string*)stateMsg.value.p;
            
            //Convert std::strings to c strings so it can be printed.
            const char * humidity_const = humidity_str.c_str();     
            const char * state_const = state_str.c_str();

            //Refresh the LCD and print to the serial monitor and LCD.
            LCD.clear();
            printf("%s\n", humidity_const);
            printf("%s\n\n",state_const);
            LCD.print(humidity_const);
            LCD.setCursor(0, 2);
            LCD.print(state_const);

            //Data has been processed, and updated sucessfully, reset the watchdog timer.
            Watchdog::get_instance().kick();
        }   
}
/*
Function Name: audio()
Function Purpose: This function continuously monitors the variables "state" and "muted". 
                  It will activate the buzzer if the state is "Harmful" and isn't muted, 
                  deactivate it if it is "Fair" or "Ideal", or muted = true. Once muted, 
                  the buzzer will not output until levels return to fair or normal,
                  similar to a smoke detector.
Inputs: bool muted, string state. 
Outputs: Buzzer activation/deactivaton.
Constraints:
*/
void audio(){
    while(true){
            if(state == "Harmful" && muted == false){
                GPIOB->ODR &=~(0x4000);
            }
            else if((state == "Harmful" && muted == true)){
                GPIOB->ODR |= 0x4000;
            }
            else if(state == "Fair" || state == "Ideal" ){
                GPIOB->ODR |= 0x4000;
                muted = false;
            }
    }
}
/*
Function Name: mute()
Function Purpose: This function is the ISR called on the rising edge 
                  of the interrupt "mute_pressed". It will turn off
                  the buzzer if state is "Harmful", and isn't currently
                  muted. 
Inputs: bool muted; 
Outputs: muted = 1;
Constraints: Bounce must be accounted for, as a result there is
             a delay incorporated, and interrupt requests are
             disabled.
*/
void mute(){
        mute_pressed.disable_irq();
        osDelay(300);
        if(state == "Harmful" && muted == false){
            muted = true;
        }
        osDelay(300);
        mute_pressed.enable_irq();
}

/*
Function Name: initialize_watchdog()
Function Purpose: This function is called at the beginning of the program
                  and initializes the watchdog timer. It will print out
                  if the timer has been initialized sucessfully or not.
Inputs: int timeout: Time until watchdog times out
Outputs: Prints if timer has  initialized sucessfully or not.
Constraints: 
*/
void initialize_watchdog(int timeout){
    Watchdog &watchdog = Watchdog::get_instance();  
    if(watchdog.start(timeout) == true && watchdog.is_running() == true){
        printf("Watchdog timer started sucessfully \nTimeout initialized to: %ims\n\n", watchdog.get_timeout());
    }
    else{
        printf("Watchdog timer failed to start.\n");
    }
}
