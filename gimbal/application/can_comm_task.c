/**
 * @file can_comm_task.c
 * @author yuanluochen
 * @brief can设备通信任务，利用队列实现can数据顺序发送
 * @version 0.1
 * @date 2023-10-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "can_comm_task.h"
#include "FreeRTOS.h"
#include "task.h"

/**
 * @brief can通信线程初始化, 主要任务为开辟线程队列
 * 
 * @param can_comm_init can通信线程初始化结构体
 */
static void can_comm_task_init(can_comm_task_t *can_comm_init);

/**
 * @brief can通信任务发送函数，通信数据队列发送 
 * 
 * @param can_comm_transmit can通信任务控制结构体
 */
static void can_comm_task_transmit(can_comm_task_t * can_comm_transmit);

/**
 * @brief can通信队列添加函数 
 * 
 * @param add_comm_queue can通信任务函数
 * @param comm_data can通信数据
 */
static void add_can_comm_queue(can_comm_task_t *add_comm_queue, can_comm_data_t *comm_data);

//云台can通信数据
static can_comm_data_t gimbal_can_comm_data = {
    .can_handle = &GIMBAL_CAN, // 初始化云台通信设备can
};

//双板can通信数据
static can_comm_data_t board_can_comm_data = {
    .can_handle = &BOARD_CAN, // 初始化双板通信设备can
};
//实例化can通信线程结构体,全局变量，保证数据一直存在
static can_comm_task_t can_comm = { 0 };

void can_comm_task(void)
{ 
    //等待云台底盘任务运行完毕
    vTaskDelay(CAN_COMM_TASK_INIT_TIME);
    //can通信任务初始化
    can_comm_task_init(&can_comm);
    while(1)
    {
        //can通信数据发送
        can_comm_task_transmit(&can_comm);
        //can数据数据发送 
        vTaskDelay(CAN_COMM_TASK_TIME);
    }
}


static void can_comm_task_init(can_comm_task_t *can_comm_init)
{
    if (can_comm_init == NULL)
        return; 
    //创建并初始化can通信队列
    can_comm_init->can_comm_queue = can_comm_queue_init(CAN_COMM_QUEUE_CAPACITY); 
}

static void can_comm_task_transmit(can_comm_task_t * can_comm_transmit)
{
    if (can_comm_transmit == NULL)
        return;
    //队列非空发送
    if (!can_comm_queue_is_empty(can_comm_transmit->can_comm_queue))
    {
        can_transmit(can_comm_queue_pop(can_comm_transmit->can_comm_queue));
    }
}


static void add_can_comm_queue(can_comm_task_t *add_comm_queue, can_comm_data_t *comm_data)
{
    if (add_comm_queue == NULL || comm_data == NULL)
        return;
    //添加数据到发送队列中
    can_comm_queue_push(add_comm_queue->can_comm_queue, comm_data);
}


void can_comm_gimbal(int16_t yaw, int16_t pitch)
{
    //配置can发送数据
    gimbal_can_comm_data.transmit_message.StdId = CAN_GIMBAL_ALL_ID;
    gimbal_can_comm_data.transmit_message.IDE = CAN_ID_STD;
    gimbal_can_comm_data.transmit_message.RTR = CAN_RTR_DATA;
    gimbal_can_comm_data.transmit_message.DLC = 0x08;
    gimbal_can_comm_data.data[0] = (yaw >> 8);
    gimbal_can_comm_data.data[1] = yaw;
    gimbal_can_comm_data.data[2] = (pitch >> 8);
    gimbal_can_comm_data.data[3] = pitch;
    gimbal_can_comm_data.data[4] = 0;
    gimbal_can_comm_data.data[5] = 0;
    gimbal_can_comm_data.data[6] = 0;
    gimbal_can_comm_data.data[7] = 0;
    //添加数据到通信队列
    add_can_comm_queue(&can_comm, &gimbal_can_comm_data);
}

void can_comm_board(int16_t relative_angle, int16_t chassis_vx, int16_t chassis_vy, int16_t chassis_behaviour)
{
    //配置can发送数据
    board_can_comm_data.transmit_message.StdId = CAN_GIMBAL_CONTROL_CHASSIS_ID;
    board_can_comm_data.transmit_message.IDE = CAN_ID_STD;
    board_can_comm_data.transmit_message.RTR = CAN_RTR_DATA;
    board_can_comm_data.transmit_message.DLC = 0x08;
    board_can_comm_data.data[0] = (relative_angle >> 8);
    board_can_comm_data.data[1] = relative_angle;
    board_can_comm_data.data[2] = (chassis_vx >> 8);
    board_can_comm_data.data[3] = chassis_vx;
    board_can_comm_data.data[4] = (chassis_vy >> 8);
    board_can_comm_data.data[5] = chassis_vy;
    board_can_comm_data.data[6] = (chassis_behaviour >> 8);
    board_can_comm_data.data[7] = chassis_behaviour;
    //添加数据到通信队列
    add_can_comm_queue(&can_comm, &board_can_comm_data);
}