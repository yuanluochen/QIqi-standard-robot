/**
 * @file serialPort_debug.c
 * @author yuanluochen
 * @brief ���ڵ����ļ�
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
    //��������
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
    if ((sign = n) < 0) // ��¼����
        n = -n;         // ʹn��Ϊ����
    i = 0;
    do
    {
        s[i++] = n % 10 + '0'; // ȡ��һ������
    } while ((n /= 10) > 0);   // ɾ��������
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    int z = 0;
    for (j = i; j >= 0; j--) // ���ɵ�����������ģ�����Ҫ�������
        num[z++] = s[j];
}