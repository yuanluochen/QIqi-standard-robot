/**
 * @file can_comm_task.c
 * @author yuanluochen
 * @brief can设备通信任务，利用队列实现can数据队列发送
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
    //等待云台底盘任务运行完毕
    vTaskDelay(CAN_COMM_TASK_INIT_TIME);

}