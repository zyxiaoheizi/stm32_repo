#include "string.h"
#include "gpio.h"
#include "stdio.h"
#include "usart.h"


uint8_t Rx_String[100];    
uint8_t Rx_Flag=0;         
uint8_t Rx_buff;           
uint8_t Receive_Data[100];

void Serial_Init(){
	HAL_UART_Receive_IT(&huart3,(uint8_t*)&Rx_buff,1);
}


void Serial_SendByte(uint8_t Byte){
	HAL_UART_Transmit(&huart3,(uint8_t*)&Byte,1,0xFFFF);
	while(HAL_UART_GetState(&huart3)==HAL_UART_STATE_BUSY);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart3)
	{
		Rx_String[Rx_Flag++] = Rx_buff;  
		if(Rx_String[Rx_Flag-1] == 0x0A) //遇到回车停止接收
		{
			HAL_UART_Transmit(&huart3, (uint8_t *)&Rx_String, Rx_Flag,0xFFFF); 
			while(HAL_UART_GetState(&huart3) == HAL_UART_STATE_BUSY_TX);
			for(int i=0;i<100;i++){Receive_Data[i]=Rx_String[i];}		
			memset(Rx_String,0x00,sizeof(Rx_buff)); 
			Rx_Flag = 0; 
		}
		HAL_UART_Receive_IT(&huart3, (uint8_t *)&Rx_buff, 1);  
	}
}



int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}