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
#include "main.h"
#include "CRC8_CRC16.h"
#include <string.h>
#include <stdlib.h>


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
    //�������ݳ���
    uint8_t transmit_len = 0;
    //��ֵ�������ݲ���
    can_comm_transmit->transmit_buf_len = data_len;
    //��ֵͷ֡
    can_comm_transmit->transmit_buf[0] = CAN_COMM_HEADER;
    //��ֵ����
    can_comm_transmit->transmit_buf[1] = can_comm_transmit->transmit_buf_len;
    //��ֵ���ݶ�
    memcpy(can_comm_transmit->transmit_buf + 2, data, can_comm_transmit->transmit_buf_len);
    //��ֵ֡β
    can_comm_transmit->transmit_buf[2 + can_comm_transmit->transmit_buf_len] = CAN_COMM_TAIL;
    //�ڷ�������ĩβ���crc8����
    append_CRC8_check_sum(can_comm_transmit->transmit_buf, can_comm_transmit->transmit_buf_len);

    //���ݷ��ͣ��������ݴ�Сȷ�����ʹ���
    for (int i = 0; i < can_comm_transmit->transmit_buf_len; i += 8)
    {
        //����ôη������ݳ���
        transmit_len = can_comm_transmit->transmit_buf_len - i >= 8 ? 8 : can_comm_transmit->transmit_buf_len - i;
        //���øôη������ݳ���

        //������������
        // memcpy(can_comm_transmit->)
        
    }
    
}

void can_comm_queue_init(can_comm_queue_t *comm_queue, int queue_capacity)
{
    //�����ÿ�
    memset(comm_queue, 0, sizeof(can_comm_queue_t));
    //��ֵ��������
    comm_queue->capacity = queue_capacity + 1;
    //���ٶ��пռ�
    comm_queue->can_comm_data = malloc(sizeof(can_comm_queue_t) * (comm_queue->capacity));
    //��ʼ����ͷβָ��
    comm_queue->head = comm_queue->tail = 0;
}

bool can_comm_queue_push(can_comm_queue_t *comm_queue, const can_comm_data_t *can_comm_data)
{
    //�ж϶����Ƿ�����
    if ((comm_queue->tail + 1) % comm_queue->capacity == comm_queue->head)
    {
        //���ʧ�ܲ����
        return false;     
    }
    //βָ������������
    memcpy(comm_queue->can_comm_data + (++comm_queue->head), can_comm_data, sizeof(can_comm_data_t));
    //�����������
    return true;

}

can_comm_data_t *can_comm_queue_pop(can_comm_queue_t *comm_queue)
{
    //�ж��Ƿ�ӿ�
    if (comm_queue->head == comm_queue->tail)
    {
        //�ӿշ��ؿ�ָ��
        return NULL;
    }
    //����ͷָ�룬����ͷָ�����
    return comm_queue->can_comm_data + (++comm_queue->head);
}

int can_comm_queue_size(can_comm_queue_t *comm_queue)
{
    return (comm_queue->tail - comm_queue->head + comm_queue->capacity) % comm_queue->capacity;
}