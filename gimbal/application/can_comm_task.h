/**
 * @file can_comm_task.h
 * @author yuanluochen
 * @brief can设备通信任务，利用队列实现can数据队列发送
 * @version 0.1
 * @date 2023-10-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef CAN_COMM_TASK_H
#define CAN_COMM_TASK_H 

//can通信任务初始化时间
#define CAN_COMM_TASK_INIT_TIME 400



/**
 * @brief  can通信任务
 * 
 */
void can_comm_task(void);

#endif // !CAN_COMM_TASK_H
