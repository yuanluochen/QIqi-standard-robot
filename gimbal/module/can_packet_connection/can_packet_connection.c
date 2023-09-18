/**
 * @file can_packet_connection.c
 * @author yuanluochen
 * @brief can���ݰ�ͨ��
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

//can���ݶδ�С
#define CAN_DATA_SUM (CAN_SUM - CAN_DATA_BIT)

/**
 * @brief canͨ�����ݰ�����ʵ�� ���ݸ�ʽ����
 *                   --------------------
 *                   |0λ     ����ͨ��״̬|
 *                   --------------------
 *                   |2λ     ����������  |
 *                   --------------------
 *                   |3 ~ 7λ �������ݶ�  |
 *                   --------------------
 * @param data �������ݰ�������ָ��, ����ʱ��Ҫ������ת��Ϊָ������
 * @param send_packet_size ���ݰ���С ��λbyte
 */
void can_send_packet_msg(const uint8_t* data, const uint8_t send_packet_size)
{
    //��ʱ�������ݶ�
    uint8_t data_temp[CAN_DATA_SUM] = { 0 };
    //������������
    uint8_t send_data[CAN_SUM] = { 0 };
    
    //������ʱ�����ڴ滺����
    uint8_t* send_msg_temp = (uint8_t*)malloc(send_packet_size);
    //������������
    memcpy(send_msg_temp, data, send_packet_size);
    //���㷢�ʹ���
    float temp = (float)send_packet_size / (float)CAN_DATA_SUM;
    int send_count = (int)temp + (temp - (int)temp > 0 ? 1 : 0);
    
    // �������ݴ�С
    uint8_t send_packet_size_temp = send_packet_size;
    //���ݷ���
    for (int i = 0; i < send_count; i++)
    {
        //��շ�������
        memset(send_data, 0, sizeof(CAN_SUM));
        //����ôη������ݸ���
        uint8_t cur_send_data_count = (((send_packet_size_temp - i * CAN_DATA_SUM) / CAN_DATA_SUM) >= 1) ? CAN_DATA_SUM : send_packet_size_temp - i * CAN_DATA_SUM;
        for (int j = 0; j < cur_send_data_count; j++)
        {
            data_temp[j] = send_msg_temp[i * CAN_DATA_SUM + j];
            printf("%d ", data_temp[j]);
        }
        
        //��ֵ��������״̬
        printf("\n");
    }


}

int main()
{
    uint8_t a[19] = {5, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 2, 12, 4, 5, 6};
    can_send_packet_msg(a, 19);
    return 0;
}

