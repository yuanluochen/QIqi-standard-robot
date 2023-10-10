/**
 * @file can_comm_task.h
 * @author yuanluochen
 * @brief can�豸ͨ���������ö���ʵ��can���ݶ��з���
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

//canͨ�������ʼ��ʱ�� ��λms
#define CAN_COMM_TASK_INIT_TIME 400
//canͨ����������ʱ���� ��λms
#define CAN_COMM_TASK_TIME 1
//canͨ�Ŷ��д�С
#define CAN_COMM_QUEUE_CAPACITY 10
//��̨can�豸
#define GIMBAL_CAN hcan1
//˫��canͨ���豸
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

//canͨ������ṹ��
typedef struct
{
    //canͨ�Ŷ��нṹ��
    can_comm_queue_t *can_comm_queue;
    
}can_comm_task_t;


/**
 * @brief  canͨ������
 * 
 */
void can_comm_task(void);

/**
 * @brief ��̨�������ݷ��ͣ�����ֵΪ�������ֵ�����͵�can_comm�̵߳�ͨ�Ŷ�����
 * 
 * @param yaw (0x205) 6020������Ƶ�������Χ[-30000, 30000]
 * @param pitch (0x206) 6020������Ƶ����� ��Χ[-30000, 30000]
 */
void can_comm_gimbal(int16_t yaw, int16_t pitch);

/**
 * @brief ˫��ͨ�Ŵ��룬��̨���Ƶ���,����ͨ������
 * 
 * @param relative_angle ��̨��Խ�
 * @param chassis_vx ����x���ٶȷ������
 * @param chassis_vy ����y���ٶȷ������
 * @param chassis_behaviour �����˶�ģʽ
 */
void can_comm_board(int16_t relative_angle, int16_t chassis_vx, int16_t chassis_vy, int16_t chassis_behaviour);

#endif // !CAN_COMM_TASK_H
