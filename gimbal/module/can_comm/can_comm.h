/**
 * @file can_comm.h
 * @author yuanluochen
 * @brief ���豸ͨ��ģ�飬��Ҫ���ڿ��ư�֮���ͨ�ţ�ʹ��can����ʵ��
 * @version 0.1
 * @date 2023-09-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef CAN_PACKEET_CONNECTION_H
#define CAN_PACKEET_CONNECTION_H
#include "struct_typedef.h"

//����������� unit byte
#define CAN_COMM_MAX_BUFSIZE 60
//У�������� unit byte, ����֡ͷ֡β + + ���ݳ���λ + crcУ���
#define CAN_COMM_OFFSET_BUFSIZE 4

//֡ͷ
#define CAN_COMM_HEADER 0X73
//֡β
#define CAN_COMM_TAIL 0x65

//can�豸���η������ֵ
#define CAN_COMM_SINGLE_TRANSMIT_MAX_SIZE 8

/**
 * @brief canͨ��״̬
 * 
 */
typedef enum
{
    CAN_COMM_START = 0,      // ��ʼͨ��
    CAN_COMM_CONNECTING = 1, // ͨ����
    CAN_COMM_END = 2,        // ͨ�Ž���
} can_comm_statue_e;


//canͨ�����ݽṹ��
typedef struct 
{
    //ͨ������
    uint8_t* data;
}can_comm_data_t;

//can�豸ͨ�Ŷ���
typedef struct 
{
    //ͨ�����ݶ��д洢����
    can_comm_data_t* can_comm_data; 
    //��������
    int capacity;
    //ͷָ��
    int head;
    //βָ��
    int tail;
}can_comm_queue_t;

/**
 * @brief can�豸ͨ��ͨ�Žṹ��
 * 
 */
typedef struct
{
    //can�豸 
    // ���Ͳ���
    uint8_t transmit_data_len;                                            // �������ݳ���
    uint8_t transmit_buf_len;                                             // ���ͻ��������ݳ��� �ó��Ȱ����������ݳ��� ֡ͷ֡β ���ݳ���λ У���
    uint8_t transmit_buf[CAN_COMM_MAX_BUFSIZE + CAN_COMM_OFFSET_BUFSIZE]; // ����������, ��СΪ CAN_COMM_MAX_BUFSIZE + CAN_COMM_OFFSET_BUFSIZE

    // ���ղ���
    uint8_t receive_data_len;                                            // �������ݳ���
    uint8_t receive_buf_len;                                             // ���ջ��������ݳ��� �ó��Ȱ����������ݳ��� ֡ͷ֡β ���ݳ���λ У���
    uint8_t receive_buf[CAN_COMM_MAX_BUFSIZE + CAN_COMM_OFFSET_BUFSIZE]; // ����������, ��СΪ CAN_COMM_MAX_BUFSIZE + CAN_COMM_OFFSET_BUFSIZE

} can_comm_t;

/**
 * @brief can�豸ͨ�ź��� 
 * 
 * @param can_comm_transmit can�豸ͨ�Žṹ�� 
 * @param data ��������ָ��
 * @param data_len ���ݳ���
 */
void can_comm_transmit(can_comm_t *can_comm_transmit, uint8_t* data, uint8_t data_len);

/**
 * @brief canͨ�Ŷ��г�ʼ��
 * 
 * @param comm_queue ����ʼ����canͨ�Ŷ���
 * @param queue_capacity canͨ�Ŷ��еĴ�С
 */
void can_comm_queue_init(can_comm_queue_t *comm_queue, int queue_capacity);

/**
 * @brief canͨ�Ŷ������
 * 
 * @param comm_queue canͨ�Ŷ��нṹ��
 * @param can_comm_data canͨ�Ŷ�������
 * @return bool_t ��ӳɹ�����true�����ʧ�ܷ���false
 */
bool can_comm_queue_push(can_comm_queue_t *comm_queue, const can_comm_data_t *can_comm_data);

/**
 * @brief canͨ�Ŷ��г���
 * 
 * @param comm_queue 
 * @return can_comm_data_t* ���س���Ԫ��ָ�룬����ӿ��򷵻ؿ�ָ��
 */
can_comm_data_t *can_comm_queue_pop(can_comm_queue_t *comm_queue);

/**
 * @brief ���ض��д�С 
 * 
 * @param comm_queue ���нṹ��
 * @return ���ض��д�С������Ϊ���� 
 */
int can_comm_queue_size(can_comm_queue_t *comm_queue);

#endif // !CAN_PACKEET_CONNECTION_H
