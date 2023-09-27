/**
 * @file serialPort_debug.c
 * @author yuanluochen
 * @brief 串口调试文件
 * @version 0.1
 * @date 2023-09-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "serialPort_debug.h"
#include "string.h"
#include "stdlib.h"

static void itoa(int n, char s[]);

void serialPort_debug_variable_transmit(const char *name, uint8_t name_size, int value)
{
    char data[20] = { 0 };
    //拷贝数据
    memcpy(data, name, name_size);
    strcat(data, "=");
    char num[20] = { 0 };
    itoa(value, num);
    strcat(data, num);
    HAL_UART_Transmit_DMA(&SERIALPORT_DEBUG_UART, (uint8_t*)data, strlen(data));
}

static void itoa(int n,  char* num)
{
    char s[100] = { 0 };
    int i, j, sign;
    if ((sign = n) < 0) // 记录符号
        n = -n;         // 使n成为正数
    i = 0;
    do
    {
        s[i++] = n % 10 + '0'; // 取下一个数字
    } while ((n /= 10) > 0);   // 删除该数字
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    int z = 0;
    for (j = i; j >= 0; j--) // 生成的数字是逆序的，所以要逆序输出
        num[z++] = s[j];
}