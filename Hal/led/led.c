
/*
 * led.c
 */

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h" 
#include "led.h"


//#include "system.h"
//GPIOC0 -GPIOC7�ֱ���8��LED�Ŀ��ƿڣ� 
void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);         //����GPIOC��ʱ������
	
	GPIO_InitStructure.GPIO_Pin=(GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
														 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);  //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(GPIOC,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	
	GPIO_SetBits(GPIOC,(GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
														 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7));   //��LED�˿����ߣ�Ϩ������LED
	//GPIO_ResetBits(GPIOC,GPIO_Pin_1);
}


TaskHandle_t LEDTask_Handler;
void led_task(void *pvParameters)
{
	for( ; ; )
	{
//		LED7 = LED_OFF;
//		LED0 = LED_ON;
//		vTaskDelay(500);
//		LED0 = LED_OFF;
//		LED1 = LED_ON;
//		vTaskDelay(500);
//		LED1 = LED_OFF;
//		LED2 = LED_ON;
//		vTaskDelay(500);
//		LED2 = LED_OFF;
//		LED3 = LED_ON;
//		vTaskDelay(500);
		LED7 = LED_OFF;
		LED4 = LED_ON;
		vTaskDelay(500);
		LED4 = LED_OFF;
		LED5 = LED_ON;
		vTaskDelay(500);
		LED5 = LED_OFF;
		LED6 = LED_ON;
		vTaskDelay(500);
		LED6 = LED_OFF;
		LED7 = LED_ON;
		vTaskDelay(500);
	}
}

TaskHandle_t read_led_task_Handler(void)
{
	return LEDTask_Handler;
}

/*******************************************************************************
* �� �� ��         : set_led
* ��������		     : ����led
* ��    ��         : unsigned char serial_numberΪҪ���õ�LED�����кã���0��LED0����
                     1��LED1�� ��8����ȫ����9����ȫ�� unsigned char value, �����0��Ӧ��LED����1��
* ��    ��         : �м����·���1�� û�����·���0
*******************************************************************************/

void set_led(unsigned char serial_number, unsigned char value)
{
	switch(serial_number)
	{
		case 0:
			LED0 = value;
		break;
		case 1:
			LED1 = value;
		break;
		case 2:
			LED2 = value;
		break;
		case 3:
			LED3 = value;
		break;
		case 4:
			LED4 = value;
		break;
		case 5:
			LED5 = value;
		break;
		case 6:
			LED6 = value;
		break;
		case 7:
			LED7 = value;
		break;
		case 8:  //8ȫ��
			LED0 = LED_ON;
			LED1 = LED_ON;
			LED2 = LED_ON;
			LED3 = LED_ON;
			LED4 = LED_ON;
			LED5 = LED_ON;
			LED6 = LED_ON;
			LED7 = LED_ON;
		break;
		case 9:  //��
			LED0 = LED_OFF;
			LED1 = LED_OFF;
			LED2 = LED_OFF;
			LED3 = LED_OFF;
			LED4 = LED_OFF;
			LED5 = LED_OFF;
			LED6 = LED_OFF;
			LED7 = LED_OFF;
		break;
		default:
		break;
	}
}



