/**
 * @file can_packet_connection.c
 * @author yuanluochen
 * @brief can数据包通信
 * @version 0.1
 * @date 2023-09-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "can_packet_connection.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//计算发送次数

void can_send_packet_msg(const uint8_t* send_data, const uint8_t send_packet_size)
{
    //创建临时发送内存缓冲区
    uint8_t* send_msg_temp = (uint8_t*)malloc(send_packet_size);
    //拷贝发送数据
    memcpy(send_msg_temp, send_data, send_packet_size);
    //计算发送次数
    float temp = (float)send_packet_size / (float)CAN_SINGLE_SEND_DATA_COUNT;
    int send_count = (int)temp + (temp - (int)temp > 0 ? 1 : 0);
    
    #if CAN_PACKET_CONNECTION_DEBUG
    printf("共有%d个字节的数据， 要发送%d次\n", send_packet_size, send_count);  
    #endif
}

int main()
{
    uint8_t a[10];
    can_send_packet_msg(a, 18);
    return 0;
}

