#include <stdio.h>
#include <string.h>
#include "uart.h"



void Uart_init(UART_t *uart){
    

    uart->rxBuffer.head = 0;
    uart->rxBuffer.tail = 0;
    uart->rxBuffer.count = 0;

    memset( uart->rxBuffer.Buffer, 0, sizeof(uart->rxBuffer.Buffer));

}





void Uart_receive(UART_t *uart, char data){

    if(uart->rxBuffer.count >= SIZE)
    {
        printf("Buffer is full!\n");
        return;
    }

    uart->rxBuffer.Buffer[uart->rxBuffer.head] = data;
    uart->rxBuffer.head = ( uart->rxBuffer.head + 1) % 8;
    uart->rxBuffer.count++;

}

void Uart_read(UART_t *uart, char *data){

    if(uart->rxBuffer.count == 0)
    {
        printf("There is no data to read!\n");
        *data = '\0';
        return;
    }
    *data = uart->rxBuffer.Buffer[uart->rxBuffer.tail];
    uart->rxBuffer.Buffer[uart->rxBuffer.tail] = '\0';
    uart->rxBuffer.tail = (uart->rxBuffer.tail + 1) % 8;
    uart->rxBuffer.count--;


}



void Uart_print(UART_t *uart)
{

    int index = uart->rxBuffer.tail;

    if(uart->rxBuffer.count == 0)
    {
        printf("There is no data to print!\n");
        return;
    }

    for(int i = 0; i < uart->rxBuffer.count; i++)
    {
        printf("Data[%d] is :%c\n", index, uart->rxBuffer.Buffer[index]);
        index = (index + 1) % 8;
    }
}