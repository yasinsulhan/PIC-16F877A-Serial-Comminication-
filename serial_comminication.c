
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#include <xc.h>
#include <stdint.h>
#include <proc/pic16f877a.h>
#include <stdio.h>
#include <string.h>
#include <htc.h>
#define _XTAL_FREQ 4000000

//--[ Control Data ]--
#define Blue_LED_ON    49 //1
#define Blue_LED_OFF   50 //2
#define Yellow_Toggle  51 //3
//--------------------------------

// Functions Declarations
void UART_RX_Init(void);
// Globals
uint8_t UART_Buffer;
uint8_t UART_Buffer2,UART_Buffer3,UART_Buffer4,UART_Buffer5,UART_Buffer6;
//--------------------------------
 
// Main Routine
void main(void)
{
  //--[ Peripherals & IO Configurations ]--
  UART_RX_Init(); // Initialize The UART in Master Mode @ 9600bps
  TRISB0 = 0;     // Blue LED  (Switch)
  TRISB1 = 0;     // Yellow LED (Toggle)
  RB0 = 0;        // Initially OFF
  RB1 = 0;        // Initially OFF
  //---------------------------
  while(1)
  {
 
  }
  return;
}
//--------------------------------
// Functions Definitions
 
void UART_RX_Init()
{
  
  SPBRG = 25; // Set The Baud Rate To Be 9600 bps
  
  // Set The RX-TX Pins to be in UART mode (not io)
  TRISC6 = 1; // As stated in the datasheet
  TRISC7 = 1; // As stated in the datasheet
  
  //--[ Enable UART Receiving Interrupts ]--
  RCIE = 1; // UART Receving Interrupt Enable Bit
  PEIE = 1; // Peripherals Interrupt Enable Bit
  GIE = 1; // Global Interrupt Enable Bit
  //------------------
 
  
  //RCSTA
  RCSTA=0X90;
  /*
  SPEN = 1;
  CREN = 1; // Enable Data Continous Reception
  OERR = 0;
  FERR = 0;
  */
  
/*
  //TXSTA
  TXSTA = 0x24;
  /*
  SYNC = 0;
  BRGH = 1; // Set For High-Speed Baud Rate
  */
/*   
}
 
void __interrupt() ISR (void)
{
  if (RCIF == 1)
  {
    UART_Buffer = RCREG; // Read The Received Data Buffer
    UART_Buffer2 = RCREG;
    UART_Buffer3 = RCREG;
    UART_Buffer4 = RCREG;
    UART_Buffer5 = RCREG;
 
    // This could have been done within the main loop. Since it's not
    // Excessive processing, so it's OK to do it here below
    if(UART_Buffer == 49)
      RB0 = 1; // Blue LED ON
    if(UART_Buffer == Blue_LED_OFF)
      RB0 = 0; // Blue LED OFF
    if(UART_Buffer == Yellow_Toggle)
      RB1 = ~RB1; // Toggle Yellow LED
 
    RCIF = 0; // Clear The Interrupt Flag
  }
}

