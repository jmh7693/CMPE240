#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "Utilities.h"

#include <string.h>
#include <stdio.h>

char buffer[BufferSize];
char str1[] = "Commands: RON, ROFF, GON, GOFF, RFLASH, GFLASH, FLASHOFF";
char com[1];

int run(void){
	char rxByte;
	int count = 0;
	int rfcount = 0;
	int gfcount = 0;
	int rflashing = 0;
	int gflashing = 0;
	while(1){
		
		rxByte = USART_Read(USART2);
		if(rxByte != 0){ //non-zero
			if(rxByte == 13){ //enter key
				USART_Write(USART2, (uint8_t *)"\n", 1);
				
				if(strcmp(buffer, "RON") == 0){
					Red_LED_On();
					clearBuffer(buffer, 3);
					count = 0;
					rflashing = 0;
					}
				else if(strcmp(buffer, "ROFF") == 0){
					Red_LED_Off();
					clearBuffer(buffer, 4);
					count = 0;
					rflashing = 0;					
					}
				else if(strcmp(buffer, "GON") == 0){
					Green_LED_On();
					clearBuffer(buffer, 3);
					count = 0;
					gflashing = 0;
				}
				else if(strcmp(buffer, "GOFF") == 0){
					Green_LED_Off();
					clearBuffer(buffer, 4);
					count = 0;
					gflashing = 0;
				}
				else if(strcmp(buffer, "RFLASH") == 0){
					rflashing = 1;
					clearBuffer(buffer, 7);
					count = 0;
				}
				else if(strcmp(buffer, "GFLASH") == 0){		
					gflashing = 1;
					clearBuffer(buffer, 7);
					count = 0;
				}
				else if(strcmp(buffer, "FLASHOFF") == 0){
					rflashing = 0;
					gflashing = 0;
					clearBuffer(buffer, 9);
					count = 0;	
				}
				else{
					USART_Write(USART2, (uint8_t *)"Invalid Command\n", 16);
					clearBuffer(buffer, 16);
					count = 0;
					}
					count = 0;
				}
			else if(rxByte == 127){
					if(backspace(buffer, count)){
						count = count -1;
					}
			}
			else{
				buffer[count++] = rxByte;
				com[0] = rxByte;
				USART_Write(USART2, (uint8_t *)com, 1);
				com[0] = '\0';
			}			
		}
		USART_Delay(1000);
		
		if(rflashing == 1){
			rfcount++;
			if(rfcount == 1000){
				Red_LED_Toggle();
				rfcount = 0;
			}
		}
		if(gflashing == 1){
			gfcount++;
			if(gfcount == 1000){
				Green_LED_Toggle();
				gfcount = 0;
			}
		}
	}
}
	
	
