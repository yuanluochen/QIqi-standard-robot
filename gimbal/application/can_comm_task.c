/**
 * @file can_comm_task.c
 * @author yuanluochen
 * @brief can�豸ͨ���������ö���ʵ��can���ݶ��з���
 * @version 0.1
 * @date 2023-10-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "can_comm_task.h"
#include "FreeRTOS.h"
#include "task.h"

void can_comm_task(void)
{ 
    //�ȴ���̨���������������
    vTaskDelay(CAN_COMM_TASK_INIT_TIME);

}