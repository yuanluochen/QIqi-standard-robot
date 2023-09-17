/**
 * @file gimbal_chassis_interface.h
 * @author yuanluochen
 * @brief 该文件是为了统一云台与底盘通信接口而编写的特殊接口通信文件
 * @version 0.1
 * @date 2023-09-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef GIMBAL_CHASSIS_INTERFACE
#define GIMBAL_CHASSIS_INTERFACE


//can 双板通信接口ID
typedef enum
{
    CAN_GIMBAL_CONTROL_CHASSIS_ID = 0x218,  //底盘云台双板通信底盘控制id
} can_msg_device_e;

//底盘行为
#endif // !GIMBAL_CHASSIS_INTERFACE
