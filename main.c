#include <stdio.h>
#include <string.h>



/*Structures and Global variables*/
#define SIZE 8

typedef struct CircularBuffer{
    char Buffer[SIZE];
    int head;
    int tail;
    int count;
}CircularBuffer;

typedef struct UART_t{

    CircularBuffer rxBuffer;
    CircularBuffer txBuffer;

}UART_t;



/*Function Prototypes*/

void Uart_init(UART_t*);
void Uart_receive(UART_t*, char);
void Uart_read(UART_t*, char*);
void Uart_print(UART_t*);




int main(){

    UART_t uart;
    int choice = 0;
    

    Uart_init(&uart);

    while(choice != 4)
    {
        printf("Enter:\n1=Uart_recieve\n2=Uart_read\n3=print\n4=exit\n");
        scanf(" %d", &choice);

        switch(choice)
        {
            case 1:
            {
                char data;
                printf("Enter data:\n");
                scanf(" %c", &data);
                Uart_receive(&uart, data);


                break;
            }

            case 2:
            {
                char read_data;
                Uart_read(&uart, &read_data);
                if(read_data != '\0')
                {
                    printf("[%c] has been readed !\n", read_data);
                }
                

                break;
            }

            case 3:
            {
                
                Uart_print(&uart);
                break;
            }

        }
    }

    return 1;
}

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