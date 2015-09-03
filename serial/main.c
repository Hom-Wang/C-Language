#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

#include "rs232.h"

#define RS232_ERROR   1
#define RS232_SUCCESS 0

#define RECV_BUF_SIZE 5

int main()
{
    int state = RS232_ERROR;

    int com_port = 6;       /* COM7 */
    int baudrate = 115200;  /* 115200 */
    char mode[]  = {'8', 'N', '1', 0};

    int i = 0, n = 0;
    unsigned long count = 2000000;

    unsigned char recv_buf[RECV_BUF_SIZE + 1] = {0};

    /* Open COM Port */
    state = RS232_OpenComport(com_port, baudrate, mode);
    if(!state)
        printf("Open COM Port Success\n\n");

    do {
        n = RS232_PollComport(com_port, recv_buf, RECV_BUF_SIZE);
//        printf("count = %4i, n = %i, recv data = ", count, n);
        if(n == 5) {
            printf("count = %7i, n = %i, recv data = ", count, n);
            recv_buf[n] = '\0';
            printf("%s", (char *)recv_buf);
        }
        else if(n > 0) {
            printf("count = %4i, n = %i, recv data = ", count, n);
            printf("*****\n");
        }
 //      Sleep(1);
    } while(--count);

    /* Close COM Port */
    RS232_CloseComport(com_port);
    printf("\nClose COM Port\n");

    return(0);
}
