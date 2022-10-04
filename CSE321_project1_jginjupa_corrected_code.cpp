
// Included Files:
#include "mbed.h"
// Creating a thread to drive an LED to have an on time of 2000ms and off time 500ms

//resourse: https://www.st.com/resource/en/user_manual/dm00368330-stm32-nucleo-144-boards-mb1312-stmicroelectronics.pdf 
Thread yarn;
DigitalOut fire(LED2); //this sets into blue light

void handler(); //this is the thread handler

//declaring varibles variables
int frodo = 0; //frodo set to 0
int samwise = 1; // samwise set to 1
float newval = 6; // newval set to 5
char merry[] = "christmas";

InterruptIn defiance(PB_12); 

int dumbledoore = 23;
int superman = 42;
int ironman = 42;

void flipflop(); 
//flipflop replaces start/stop

int parade = 0; // get asked if I want the LED to blink or not

void unicorn(); // replaces confirm when being obnoxious
int main() { // public static void main(String[] args)
  // start the allowed execution of the thread
  printf("----------------START----------------\n");
  printf("Starting state of thread: %d\n", yarn.get_state());
  yarn.start(handler);
  printf("State of thread right after start: %d\n", yarn.get_state());
  defiance.rise(flipflop);
  defiance.fall(unicorn);
  // while(true){}

  return 0;
}

// make the handler for the football
void handler() {
  while (true) {

    if (frodo == 0) {
      fire = !fire;
      printf("toggled LED\n");
      thread_sleep_for(2000);
      fire = !fire;
      fire = fire;

      printf("toggled LED\n");
      thread_sleep_for(500);
    }
    if (frodo == 5) {
      printf("Time for to save the world!");
    }
  }
}

void flipflop()

{ //I get to flip floppy a variable when whatever is plugged int port b in 12 goes from 0V to the high voltage
  
  parade = 1;
}


void unicorn() {
  if (parade==1){
    frodo++; // frodo increase by one
    frodo %= 2; // frodo mod 2 
    //duality in technology is binary, 0 is on and 1 is off
    parade=0;
}}