
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





void Uart_init(UART_t*);
void Uart_receive(UART_t*, char);
void Uart_read(UART_t*, char*);
void Uart_print(UART_t*);