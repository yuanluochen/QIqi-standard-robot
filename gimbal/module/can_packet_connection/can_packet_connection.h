/**
 * @file can_packet_connection.h
 * @author yuanluochen
 * @brief can数据包通信
 * @version 0.1
 * @date 2023-09-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef CAN_PACKEET_CONNECTION_H
#define CAN_PACKEET_CONNECTION_H
#include <stdint.h>


//代码测试
#define CAN_PACKET_CONNECTION_DEBUG 1
#define CAN_SINGLE_SEND_DATA_COUNT 8

/**
 * @brief can通信状态
 * 
 */
typedef enum
{
    CAN_PACKET_START = 0,      // 开始通信
    CAN_PACKET_CONNECTING = 1, // 通信中
    CAN_PACKET_END = 2,        // 通信结束
} can_packet_statue;


/**
 * @brief can数据包通信数据位 共八位格式如下
 *                   
 * --------------------
 * |0位     数据通信状态|
 * --------------------
 * |1位     报文数据量  |
 * --------------------
 * |2 ~ 7位 报文数据段  |
 * --------------------
 */
typedef enum
{
    CAN_STATUS_BIT = 0,      // can发送状态位
    CAN_PACKET_SIZE_BIT = 1, // can数据包大小位
    CAN_DATA_BIT = 2,        // can数据段开始位
    CAN_SUM = 8,             // can发送总计数据量
} can_packet_data_bit;



void can_send_packet_msg(const uint8_t *send_data, const uint8_t send_packet_size);

#endif // !CAN_PACKEET_CONNECTION_H
