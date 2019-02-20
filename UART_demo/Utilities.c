#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"

#include <string.h>
#include <stdio.h>


char clearBuffer(char buffer[], int len){
	for(int i = 0; i < len; i++){
		buffer[i] = '\0';
	}
	return *buffer;
}

char backspace(char buffer[], int count){
	if(buffer[0] != '\0'){
		buffer[count - 1] = '\0';
		USART_Write(USART2, (uint8_t *)"\n", 1);
		USART_Write(USART2, (uint8_t *)buffer, 16);
		count = count -1;
	}
	return *buffer;
}
