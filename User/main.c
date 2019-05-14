
#include "usart.h"
#include "stdio.h"
#include "system.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "stm32f10x_it.h"
#include "delay.h"
#include "led.h"
#include "key.h"

//#include "system_stm32f10x.h"
TaskHandle_t PrintTask_Handler;
void print_task(void *pvParameters)
{
	while (1)
	{
		printf("Hello STM32!\n");
		vTaskDelay(500);		
	}
}

TaskHandle_t StartTask_Handler;
void start_task(void *pvParameters)
{
	while(1)
	{
		vTaskDelay(500);
		LED0 = ~LED0;
	}
}
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //����ϵͳ�ж����ȼ�����4
	//SystemInit();
	delay_init();
	USART1_init(115200);
//	printf("Hello FreeRTOS!\n");
	led_init();
	key_init();
	xTaskCreate((TaskFunction_t )print_task,     //������
							 (const char*   )"print_task",    //��������
							 (uint16_t      )128,                  //START_STK_SIZE, //�����ջ��С
							 (void *        )NULL,           //���ݸ��������Ĳ���
							 (UBaseType_t   )1,            //START_TASK_PRIO,//�������ȼ�
							 (TaskHandle_t* )&PrintTask_Handler); //������
	
	xTaskCreate((TaskFunction_t )start_task,     //������
							 (const char*   )"start_task",    //��������
							 (uint16_t      )128,                  //START_STK_SIZE, //�����ջ��С
							 (void *        )NULL,           //���ݸ��������Ĳ���
							 (UBaseType_t   )1,            //START_TASK_PRIO,//�������ȼ�
							 (TaskHandle_t* )&StartTask_Handler); //������
							 
	xTaskCreate((TaskFunction_t)led_task, (const char*)"led_task", (uint16_t)128, 
							(void*)NULL, (UBaseType_t)1, (TaskHandle_t*)read_led_task_Handler());		
	
	xTaskCreate((TaskFunction_t)key_task, (const char*)"key_task", (uint16_t)128, 
							(void*)NULL, (UBaseType_t)1, (TaskHandle_t*)NULL);
  						 
  vTaskStartScheduler();						//�����������							

}

