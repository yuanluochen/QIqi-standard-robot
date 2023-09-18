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

//can数据段大小
#define CAN_DATA_SUM (CAN_SUM - CAN_DATA_BIT)

/**
 * @brief can通信数据包发送实现 数据格式如下
 *                   --------------------
 *                   |0位     数据通信状态|
 *                   --------------------
 *                   |2位     报文数据量  |
 *                   --------------------
 *                   |3 ~ 7位 报文数据段  |
 *                   --------------------
 * @param data 发送数据包的数据指针, 输入时需要将参数转化为指针类型
 * @param send_packet_size 数据包大小 单位byte
 */
void can_send_packet_msg(const uint8_t* data, const uint8_t send_packet_size)
{
    //临时发送数据段
    uint8_t data_temp[CAN_DATA_SUM] = { 0 };
    //发送数据整体
    uint8_t send_data[CAN_SUM] = { 0 };
    
    //创建临时发送内存缓冲区
    uint8_t* send_msg_temp = (uint8_t*)malloc(send_packet_size);
    //拷贝发送数据
    memcpy(send_msg_temp, data, send_packet_size);
    //计算发送次数
    float temp = (float)send_packet_size / (float)CAN_DATA_SUM;
    int send_count = (int)temp + (temp - (int)temp > 0 ? 1 : 0);
    
    // 发送数据大小
    uint8_t send_packet_size_temp = send_packet_size;
    //数据发送
    for (int i = 0; i < send_count; i++)
    {
        //清空发送数据
        memset(send_data, 0, sizeof(CAN_SUM));
        //计算该次发送数据个数
        uint8_t cur_send_data_count = (((send_packet_size_temp - i * CAN_DATA_SUM) / CAN_DATA_SUM) >= 1) ? CAN_DATA_SUM : send_packet_size_temp - i * CAN_DATA_SUM;
        for (int j = 0; j < cur_send_data_count; j++)
        {
            data_temp[j] = send_msg_temp[i * CAN_DATA_SUM + j];
            printf("%d ", data_temp[j]);
        }
        
        //赋值发送数据状态
        printf("\n");
    }


}

int main()
{
    uint8_t a[19] = {5, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 2, 12, 4, 5, 6};
    can_send_packet_msg(a, 19);
    return 0;
}

