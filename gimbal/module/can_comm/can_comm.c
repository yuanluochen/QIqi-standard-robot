/**
 * @file can_comm.c
 * @author yuanluochen
 * @brief 多设备通信模块，主要用于控制板之间的通信，使用can总线实现
 * @version 0.1
 * @date 2023-09-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "can_comm.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/**
 * @brief can设备通信函数 
 * 
 * @param can_comm_transmit can设备通信结构体 
 * @param data 发送数据指针
 * @param data_len 数据长度
 */
void can_comm_transmit(can_comm_t *can_comm_transmit, uint8_t* data, uint8_t data_len)
{
    //判断发送数据是否符合要求
    if ((data_len > CAN_COMM_MAX_BUFSIZE) || (can_comm_transmit == NULL) || (data == NULL))
    {
        //不符合要求,直接退出
        return;
    }
    //赋值发送数据参数
    can_comm_transmit->transmit_buf_len = data_len;
    memcpy(can_comm_transmit->transmit_buf, data, data_len);
    //在发送数据末尾添加crc8检验
    
}

int main()
{
}

