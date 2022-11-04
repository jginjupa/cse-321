/*
 * File:  CSE321_project2_jginjupa_main.cpp
 *
 * Author1:Jya prakash Ginjupalli (jginjupa@buffalo.edu)
 * Date: 2022 October 28
 * Course: CSE 321 Embedded Systems
 * Assignment: Project 2
 *
 * inputs: PE7,PE8,PE9
 * Outputs: Pin PA0,PA1,PA2,PA3,PA4
 *
 * Modules:
 *   - mbed.h
 *
 * Summary of the File:
 *
 *   Explore design and implementation in a bare metal system with a combination lock/security system
 *
 * References:
 *    - RM0432 Reference Manuel
 * :https://www.st.com/resource/en/reference_manual/rm0432-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
 *    - MbedOS documentation:
 * https://os.mbed.com/docs/mbed-os/v6.15/introduction/index.html
 *
 * Constraints:
 *   Intended to be used with a NUCLEO-L4R5ZI
 *///#include "lcd_1602.cpp"
#include "lcd_1602.h"
#include "mbed.h"
#include "PinNames.h"
#include <cstdint>
#include <cstdio>
#include <stdio.h>
#include <string.h>

void Interrupt_1(void);
void Interrupt_2(void);
void Interrupt_3(void);

InterruptIn Pin_1(PE_12, PullDown);
InterruptIn Pin_2(PE_14, PullDown);
InterruptIn Pin_3(PE_15, PullDown);
// global variables
CSE321_LCD lcd(16,2);
int ubit[4] = {8, 3, 5, 1};
//print on lcd 
const char *print[4]; 
//mode for printing
int locl_state;   
//check if its true; o is lock_state and 1 is unlocked        
int check;            
bool lock_state;
//UBIT entry number
int entry = 0; 

// main function
int main() {
  RCC->AHB2ENR |= 0x15; // clock bus for E INPUT to A output

  GPIOE->MODER &= ~(0xF3000000); // input for PE12,PE14,PE15

  GPIOA->MODER &= ~(0xAA); // output for PA0,PA1,PA2,PA3

  GPIOA->MODER |= (0x55); // output for A

  GPIOA->ODR |= 0xF; // make this 1

  // this is for the Green led light
  GPIOB->MODER &= ~(0x8000); // PC7 output
  GPIOB->MODER |= 0x4000;

  // KEYPAD dispaly settings.
  print[1] = "UNLOCKED";
  print[0] = "LOCKED";
  print[2] = "WRONG entry";
  while (true) {
    if (check == 1) {
      lcd.clear();
      lcd.begin();
      lcd.print(print[locl_state]);
      check = 0;
    }
    //calling keyhandler during internupt
    Pin_1.rise(&Interrupt_1);
    Pin_2.rise(&Interrupt_2);
    Pin_3.rise(&Interrupt_3);


    //enabling interrupt
    Pin_1.enable_irq();
    Pin_2.enable_irq();
    Pin_3.enable_irq();
    //make this one
    GPIOA->ODR |= 0xF; 
  }
  return 0;
}


void Lock_check(int input) {
  if (ubit[entry] != input) {
    locl_state = 2;
    check = 1;
    entry = 0;
    GPIOB->ODR |= 0x4000; //  TURNS THE LED ON
    wait_us(250000);       // waiting time
    GPIOB->ODR &= ~(0x4000);
  } else {
    if (entry == 3) {
      if (lock_state == 0) { // unlock
        // printf("UNLOCKED");
        lock_state = 1;
        locl_state = 1;
        check = 1;
        entry = 0;
        return;
      }
      if (lock_state == 1) {
        // printf("LOCKED");
        lock_state = 0;
        locl_state = 0;
        check = 1;
        entry = 0;
        return;
      }
    }
    entry++;
  }
}
// led on or off

void Interrupt_1() {

  GPIOA->ODR &= ~(0x1);
  if (Pin_1.read() == 0) {
    printf("1");
    Lock_check(1);
    //wait time
    wait_us(1000000);        
    // turns on led
    GPIOB->ODR |= 0x80;    
    // wait time
    wait_us(10000);       
    // led fuction call
    GPIOB->ODR &= ~(0x80);
    return;
  }

  GPIOA->ODR &= ~(0x2);
  if (Pin_1.read() == 0) {
    printf("4");
    Lock_check(4);
    // wait time
    wait_us(1000000);    
    //  TURNS THE LED ON
    GPIOB->ODR |= 0x80; 
    // wait time
    wait_us(10000);       
    GPIOB->ODR &= ~(0x80);
    return;
  }

  GPIOA->ODR &= ~(0x4);
  if (Pin_1.read() == 0) {
    printf("7");
    Lock_check(7);
    wait_us(1000000);     // wait time
    GPIOB->ODR |= 0x80; //  TURNS THE LED ON
    wait_us(10000);       // wait time
    GPIOB->ODR &= ~(0x80);
    return;
  }
}

void Interrupt_2() {
  GPIOA->ODR &= ~(0x1);
  if (Pin_2.read() == 0) {
    printf("2");
    Lock_check(2);
   // wait time
    wait_us(1000000); 
    //  TURNS THE LED ON
    GPIOB->ODR |= 0x80;
    // wait time    
    wait_us(10000);       
    GPIOB->ODR &= ~(0x80);
    return;
  }
  GPIOA->ODR &= ~(0x2);
  if (Pin_2.read() == 0) {
    printf("5");
    Lock_check(5);
    //wait time
    wait_us(1000000);     
    //  TURNS THE LED ON
    GPIOB->ODR |= 0x80; 
    // wait time
    wait_us(10000);       
    GPIOB->ODR &= ~(0x80);
    return;
  }
  GPIOA->ODR &= ~(0x4);
  if (Pin_2.read() == 0) {
    printf("8");
    Lock_check(8);
    wait_us(1000000);     // wait time
    GPIOB->ODR |= 0x80; //  TURNS THE LED ON
    wait_us(10000);       // wait time
    GPIOB->ODR &= ~(0x80);
    return;
  }
  GPIOA->ODR &= ~(0x8);
  if (Pin_2.read() == 0) {
    printf("0");
    Lock_check(0);
    wait_us(1000000);     // wait time
    GPIOB->ODR |= 0x80; //  TURNS THE LED ON
    wait_us(10000);       // wait time
    GPIOB->ODR &= ~(0x80);
    return;
  }
}

void Interrupt_3() {
  GPIOA->ODR &= ~(0x1);
  if (Pin_3.read() == 0) {
    printf("3");
    Lock_check(3);
    wait_us(1000000);     // wait time
    GPIOB->ODR |= 0x80; //  TURNS THE LED ON
    wait_us(10000);       // wait time
    GPIOB->ODR &= ~(0x80);
    return;
  }
  GPIOA->ODR &= ~(0x2);
  if (Pin_3.read() == 0) {
    printf("6");
    Lock_check(6);
    wait_us(1000000);     // wait time
    GPIOB->ODR |= 0x80; //  TURNS THE LED ON
    wait_us(10000);       // wait time
    GPIOB->ODR &= ~(0x80);
    return;
  }
  GPIOA->ODR &= ~(0x4);
  if (Pin_3.read() == 0) {
    printf("9");
    Lock_check(9);
    wait_us(1000000);     // wait time
    GPIOB->ODR |= 0x80; //  TURNS THE LED ON
    wait_us(10000);       // wait time
    GPIOB->ODR &= ~(0x80);
    return;
  }
}