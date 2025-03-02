#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "stdio.h"

int Left;
int Right;
int16_t Count_L;
int16_t Count_R;

void Encoder_Init(){
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim4);
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
}


int Encoder_GetL(){
	uint16_t encoder;
	int16_t temp;
	encoder=__HAL_TIM_GET_COUNTER(&htim3);
	temp=Count_L;
	Count_L=0;
	__HAL_TIM_SET_COUNTER(&htim3,0);
	return encoder+temp*65536;
}

int Encoder_GetR(){
	uint16_t encoder;
	int16_t temp;
	encoder=__HAL_TIM_GET_COUNTER(&htim4);
	temp=Count_R;
	Count_R=0;
	__HAL_TIM_SET_COUNTER(&htim4,0);
	return encoder+temp*65536;
}




void Encoder_Print(int Byte){
	printf("%d\n",Byte);
}





void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim==&htim3){
		if((TIM3->CR1&0x10)==0x00){
			Count_L++;
		}
		else{
			Count_L--;
		}
	}
	
	else if(htim==&htim4){
		if((TIM4->CR1&0x10)==0x00){
			Count_R++;
		}
		else{
			Count_R--;
		}
	}
}




