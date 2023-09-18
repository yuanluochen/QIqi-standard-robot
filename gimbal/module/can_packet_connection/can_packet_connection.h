/**
 * @file can_packet_connection.h
 * @author yuanluochen
 * @brief can���ݰ�ͨ��
 * @version 0.1
 * @date 2023-09-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef CAN_PACKEET_CONNECTION_H
#define CAN_PACKEET_CONNECTION_H
#include <stdint.h>


//�������
#define CAN_PACKET_CONNECTION_DEBUG 1
#define CAN_SINGLE_SEND_DATA_COUNT 8

/**
 * @brief canͨ��״̬
 * 
 */
typedef enum
{
    CAN_PACKET_START = 0,      // ��ʼͨ��
    CAN_PACKET_CONNECTING = 1, // ͨ����
    CAN_PACKET_END = 2,        // ͨ�Ž���
} can_packet_statue;


/**
 * @brief can���ݰ�ͨ������λ ����λ��ʽ����
 *                   
 * --------------------
 * |0λ     ����ͨ��״̬|
 * --------------------
 * |1λ     ����������  |
 * --------------------
 * |2 ~ 7λ �������ݶ�  |
 * --------------------
 */
typedef enum
{
    CAN_STATUS_BIT = 0,      // can����״̬λ
    CAN_PACKET_SIZE_BIT = 1, // can���ݰ���Сλ
    CAN_DATA_BIT = 2,        // can���ݶο�ʼλ
    CAN_SUM = 8,             // can�����ܼ�������
} can_packet_data_bit;



void can_send_packet_msg(const uint8_t *send_data, const uint8_t send_packet_size);

#endif // !CAN_PACKEET_CONNECTION_H
