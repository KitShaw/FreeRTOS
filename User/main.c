
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //设置系统中断优先级分组4
	//SystemInit();
	delay_init();
	USART1_init(115200);
//	printf("Hello FreeRTOS!\n");
	led_init();
	key_init();
	xTaskCreate((TaskFunction_t )print_task,     //任务函数
							 (const char*   )"print_task",    //任务名称
							 (uint16_t      )128,                  //START_STK_SIZE, //任务堆栈大小
							 (void *        )NULL,           //传递给任务函数的参数
							 (UBaseType_t   )1,            //START_TASK_PRIO,//任务优先级
							 (TaskHandle_t* )&PrintTask_Handler); //任务句柄
	
	xTaskCreate((TaskFunction_t )start_task,     //任务函数
							 (const char*   )"start_task",    //任务名称
							 (uint16_t      )128,                  //START_STK_SIZE, //任务堆栈大小
							 (void *        )NULL,           //传递给任务函数的参数
							 (UBaseType_t   )1,            //START_TASK_PRIO,//任务优先级
							 (TaskHandle_t* )&StartTask_Handler); //任务句柄
							 
	xTaskCreate((TaskFunction_t)led_task, (const char*)"led_task", (uint16_t)128, 
							(void*)NULL, (UBaseType_t)1, (TaskHandle_t*)read_led_task_Handler());		
	
	xTaskCreate((TaskFunction_t)key_task, (const char*)"key_task", (uint16_t)128, 
							(void*)NULL, (UBaseType_t)1, (TaskHandle_t*)NULL);
  						 
  vTaskStartScheduler();						//开启任务调度							

}

