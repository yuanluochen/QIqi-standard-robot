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
#include "can_comm.h"
#include "can.h"

//can通信任务初始化时间 单位ms
#define CAN_COMM_TASK_INIT_TIME 100
//can通信任务运行时间间隔 单位ms
#define CAN_COMM_TASK_TIME 1
//can通信队列大小
#define CAN_COMM_QUEUE_CAPACITY 10
//云台can设备
#define GIMBAL_CAN hcan1
//双板can通信设备
#define BOARD_CAN hcan1

typedef enum
{
    CAN_CHASSIS_ALL_ID = 0x200,
    CAN_3508_M1_ID = 0x204,
    CAN_3508_M2_ID = 0x203,
    CAN_3508_M3_ID = 0x202,
    CAN_3508_M4_ID = 0x201,
    CAN_GIMBAL_CONTROL_CHASSIS_ID = 0x218,
    CAN_YAW_MOTOR_ID = 0x205,
    CAN_PIT_MOTOR_ID = 0x206,
    CAN_TRIGGER_MOTOR_ID = 0x207,
    CAN_GIMBAL_ALL_ID = 0x1FF,

    CAN_SHOOT_ALL_ID = 0x1FF,
    CAN_3508_S1_ID = 0x205,
    CAN_3508_S2_ID = 0x206,
} can_msg_id_e;

//can通信任务结构体
typedef struct
{
    //can通信队列结构体
    can_comm_queue_t *can_comm_queue;
    
}can_comm_task_t;


/**
 * @brief  can通信任务
 * 
 */
void can_comm_task(void const* pvParameters);

/**
 * @brief 云台控制数据发送，发送值为电机电流值，发送到can_comm线程的通信队列中
 * 
 * @param yaw (0x205) 6020电机控制电流，范围[-30000, 30000]
 * @param pitch (0x206) 6020电机控制电流， 范围[-30000, 30000]
 */
void can_comm_gimbal(int16_t yaw, int16_t pitch);

/**
 * @brief 双板通信代码，云台控制底盘,发送通信数据
 * 
 * @param relative_angle 云台相对角
 * @param chassis_vx 底盘x轴速度方向分量
 * @param chassis_vy 底盘y轴速度方向分量
 * @param chassis_behaviour 底盘运动模式
 */
void can_comm_board(int16_t relative_angle, int16_t chassis_vx, int16_t chassis_vy, int16_t chassis_behaviour);

#endif // !CAN_COMM_TASK_H
