/**
 * @file serialPort_debug.h
 * @author yuanluochen
 * @brief 串口调试文件
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

//串口调试串口号
#define SERIALPORT_DEBUG_UART huart1

/**
 * @brief 调试变量发送函数
 * 
 * @param name 调试变量名
 * @param name_size 调试变量名长度
 * @param value 调试变量数值
 */
void serialPort_debug_variable_transmit(const char *name, uint8_t name_size, int value);

#endif // !SERIALPORT_DEBUG_H