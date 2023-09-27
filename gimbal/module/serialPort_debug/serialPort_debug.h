/**
 * @file serialPort_debug.h
 * @author yuanluochen
 * @brief ���ڵ����ļ�
 * @version 0.1
 * @date 2023-09-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef SERIALPORT_DEBUG_H
#define SERIALPORT_DEBUG_H
#include "stdint.h"
#include "usart.h"

//���ڵ��Դ��ں�
#define SERIALPORT_DEBUG_UART huart1

/**
 * @brief ���Ա������ͺ���
 * 
 * @param name ���Ա�����
 * @param name_size ���Ա���������
 * @param value ���Ա�����ֵ
 */
void serialPort_debug_variable_transmit(const char *name, uint8_t name_size, int value);

#endif // !SERIALPORT_DEBUG_H