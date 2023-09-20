/**
 * @file can_comm.c
 * @author yuanluochen
 * @brief ���豸ͨ��ģ�飬��Ҫ���ڿ��ư�֮���ͨ�ţ�ʹ��can����ʵ��
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
 * @brief can�豸ͨ�ź��� 
 * 
 * @param can_comm_transmit can�豸ͨ�Žṹ�� 
 * @param data ��������ָ��
 * @param data_len ���ݳ���
 */
void can_comm_transmit(can_comm_t *can_comm_transmit, uint8_t* data, uint8_t data_len)
{
    //�жϷ��������Ƿ����Ҫ��
    if ((data_len > CAN_COMM_MAX_BUFSIZE) || (can_comm_transmit == NULL) || (data == NULL))
    {
        //������Ҫ��,ֱ���˳�
        return;
    }
    //��ֵ�������ݲ���
    can_comm_transmit->transmit_buf_len = data_len;
    memcpy(can_comm_transmit->transmit_buf, data, data_len);
    //�ڷ�������ĩβ���crc8����
    
}

int main()
{
}

