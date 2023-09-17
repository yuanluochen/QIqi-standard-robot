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
//can���η��͵�������
#define CAN_SINGLE_SEND_DATA_COUNT 8

void can_send_packet_msg(const uint8_t* send_data, const uint8_t send_packet_size);

#endif // !CAN_PACKEET_CONNECTION_H
