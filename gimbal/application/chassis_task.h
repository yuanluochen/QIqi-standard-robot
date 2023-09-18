/**
  ****************************(C) COPYRIGHT 2019 DJI****************************
  * @file       chassis.c/h
  * @brief      chassis control task,
  *             底盘控制任务
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Dec-26-2018     RM              1. 完成
  *  V1.1.0     Nov-11-2019     RM              1. add chassis power control
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2019 DJI****************************
  */
#ifndef CHASSIS_TASK_H
#define CHASSIS_TASK_H
#include "struct_typedef.h"
#include "CAN_receive.h"
#include "gimbal_task.h"
#include "pid.h"
#include "remote_control.h"
#include "user_lib.h"
#include "referee.h"

//in the beginning of task ,wait a time
//任务开始空闲一段时间
#define CHASSIS_TASK_INIT_TIME 357

//the channel num of controlling vertial speed 
//前后的遥控器通道号码
#define CHASSIS_X_CHANNEL 1
//the channel num of controlling horizontal speed
//左右的遥控器通道号码
#define CHASSIS_Y_CHANNEL 0


//the channel of choosing chassis mode,
//选择底盘状态 开关通道号
#define CHASSIS_MODE_CHANNEL 0
//底盘运行模式通道
#define CHASSIS_RUN_MODE_CHANNEL 1
//选择自动模式
#define CHASSIS_AUTO_MODE 1
//遥控器前进摇杆（max 660）转化成车体前进速度（m/s）的比例
#define CHASSIS_VX_RC_SEN 0.006f
//遥控器左右摇杆（max 660）转化成车体左右速度（m/s）的比例
#define CHASSIS_VY_RC_SEN 0.005f

//rocker value deadline
//摇杆死区
#define CHASSIS_RC_DEADLINE 15



//底盘任务控制间隔 2ms
#define CHASSIS_CONTROL_TIME_MS 2
//底盘任务控制间隔 0.002s
#define CHASSIS_CONTROL_TIME 0.002f

//底盘前后左右控制按键
#define CHASSIS_FRONT_KEY KEY_PRESSED_OFFSET_W
#define CHASSIS_BACK_KEY KEY_PRESSED_OFFSET_S
#define CHASSIS_LEFT_KEY KEY_PRESSED_OFFSET_A
#define CHASSIS_RIGHT_KEY KEY_PRESSED_OFFSET_D

typedef enum
{
    CHASSIS_FOLLOW_GIMBAL_YAW = 10000,        // 底盘跟随云台
    CHASSIS_RUDDER_FOLLOW_GIMBAL_YAW = 20000, // 舵跟随云台
    CHASSIS_SPIN = 30000,                     // 底盘小陀螺
    CHASSIS_NO_MOVE = 40000,                  // 底盘保持不动
    CHASSIS_ZERO_FORCE,               // 底盘无力, 跟没上电那样
} chassis_behaviour_e;


typedef struct
{
    const RC_ctrl_t *chassis_RC;               // 底盘使用的遥控器指针, the point to remote control
    const gimbal_motor_t *chassis_yaw_motor;   // will use the relative angle of yaw gimbal motor to calculate the euler angle.底盘使用到yaw云台电机的相对角度来计算底盘的欧拉角.
    const gimbal_motor_t *chassis_pitch_motor; // will use the relative angle of pitch gimbal motor to calculate the euler angle.底盘使用到pitch云台电机的相对角度来计算底盘的欧拉角
    const INS_t* chassis_INS_point;             // the point to the euler angle of gyro sensor.获取陀螺仪解算出的欧拉角指针
    chassis_behaviour_e chassis_behaviour;
    fp32 vx_set;                     // chassis set vertical speed,positive means forward,unit m/s.底盘设定速度 前进方向 前为正，单位 m/s
    fp32 vy_set;                     // chassis set horizontal speed,positive means left,unit m/s.底盘设定速度 左右方向 左为正，单位 m/s
    fp32 chassis_relative_angle;     // the relative angle between chassis and gimbal.底盘与云台的相对角度，单位 rad

} chassis_move_t;

/**
  * @brief          chassis task, osDelay CHASSIS_CONTROL_TIME_MS (2ms) 
  * @param[in]      pvParameters: null
  * @retval         none
  */
/**
  * @brief          底盘任务，间隔 CHASSIS_CONTROL_TIME_MS 2ms
  * @param[in]      pvParameters: 空
  * @retval         none
  */
extern void chassis_task(void const *pvParameters);

#endif
