#include <stdio.h>
#include <string.h>
#include "uart.c"




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

