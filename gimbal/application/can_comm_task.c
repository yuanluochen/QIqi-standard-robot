/**
 * @file can_comm_task.c
 * @author yuanluochen
 * @brief can�豸ͨ���������ö���ʵ��can����˳����
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
 * @brief canͨ���̳߳�ʼ��, ��Ҫ����Ϊ�����̶߳���
 * 
 * @param can_comm_init canͨ���̳߳�ʼ���ṹ��
 */
static void can_comm_task_init(can_comm_task_t *can_comm_init);

/**
 * @brief canͨ�������ͺ�����ͨ�����ݶ��з��� 
 * 
 * @param can_comm_transmit canͨ��������ƽṹ��
 */
static void can_comm_task_transmit(can_comm_task_t * can_comm_transmit);

/**
 * @brief canͨ�Ŷ�����Ӻ��� 
 * 
 * @param add_comm_queue canͨ��������
 * @param comm_data canͨ������
 */
static void add_can_comm_queue(can_comm_task_t *add_comm_queue, can_comm_data_t *comm_data);

//��̨canͨ������
static can_comm_data_t gimbal_can_comm_data = {
    .can_handle = &GIMBAL_CAN, // ��ʼ����̨ͨ���豸can
};

//˫��canͨ������
static can_comm_data_t board_can_comm_data = {
    .can_handle = &BOARD_CAN, // ��ʼ��˫��ͨ���豸can
};
//ʵ����canͨ���߳̽ṹ��,ȫ�ֱ�������֤����һֱ����
static can_comm_task_t can_comm = { 0 };

void can_comm_task(void)
{ 
    //�ȴ���̨���������������
    vTaskDelay(CAN_COMM_TASK_INIT_TIME);
    //canͨ�������ʼ��
    can_comm_task_init(&can_comm);
    while(1)
    {
        //canͨ�����ݷ���
        can_comm_task_transmit(&can_comm);
        //can�������ݷ��� 
        vTaskDelay(CAN_COMM_TASK_TIME);
    }
}


static void can_comm_task_init(can_comm_task_t *can_comm_init)
{
    if (can_comm_init == NULL)
        return; 
    //��������ʼ��canͨ�Ŷ���
    can_comm_init->can_comm_queue = can_comm_queue_init(CAN_COMM_QUEUE_CAPACITY); 
}

static void can_comm_task_transmit(can_comm_task_t * can_comm_transmit)
{
    if (can_comm_transmit == NULL)
        return;
    //���зǿշ���
    if (!can_comm_queue_is_empty(can_comm_transmit->can_comm_queue))
    {
        can_transmit(can_comm_queue_pop(can_comm_transmit->can_comm_queue));
    }
}


static void add_can_comm_queue(can_comm_task_t *add_comm_queue, can_comm_data_t *comm_data)
{
    if (add_comm_queue == NULL || comm_data == NULL)
        return;
    //������ݵ����Ͷ�����
    can_comm_queue_push(add_comm_queue->can_comm_queue, comm_data);
}


void can_comm_gimbal(int16_t yaw, int16_t pitch)
{
    //����can��������
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
    //������ݵ�ͨ�Ŷ���
    add_can_comm_queue(&can_comm, &gimbal_can_comm_data);
}

void can_comm_board(int16_t relative_angle, int16_t chassis_vx, int16_t chassis_vy, int16_t chassis_behaviour)
{
    //����can��������
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
    //������ݵ�ͨ�Ŷ���
    add_can_comm_queue(&can_comm, &board_can_comm_data);
}