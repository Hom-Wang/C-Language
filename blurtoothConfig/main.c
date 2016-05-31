#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>

#include "rs232.h"

#define BUF_SIZE 100

int com_port = 6;       /* COM7 */
int baudrate = 38400;  /* 115200 */
char mode[]  = {'8', 'N', '1', 0};

int i = 0, n = 0;
unsigned char sendBuf[BUF_SIZE] = {0};
unsigned char recvBuf[BUF_SIZE] = {0};

#define HC05 5
#define HC06 6
void bt_sendCommand( char type, char* pString )
{
//    printf(pString);
//    printf(" ...\t");
//    printf("\n");
    RS232_SendBuf(com_port, pString, strlen(pString));
    if(type == HC05)
        RS232_SendBuf(com_port, "\r\n", 2);
    Sleep(100);
}

void bt_sendBIND( char type, char* pString )
{
    RS232_SendBuf(com_port, "AT+BIND=", strlen("AT+BIND="));
    RS232_SendBuf(com_port, pString, strlen(pString));
    RS232_SendBuf(com_port, "\r\n", 2);
    Sleep(100);
}

void bt_getReturn( void )
{
    int lens = 0;
    unsigned char pString[128] = {0};

    lens = RS232_PollComport(com_port, pString, 100);
 //   printf("[%i]\n", lens);
    printf(pString);
    printf("\n");
    Sleep(100);
}

void bt_getReturnINQ( void )
{
    int lens = 0;
    unsigned char pString[128] = {0};

    lens = RS232_PollComport(com_port, pString, 100);
    printf("[%i]\n", lens);
    printf(pString);
    printf("\n");
}

void bt_sendATCommand( char type, char* pString )
{
    if(strcmp("AT+INQ", pString) != 0) {
        bt_sendCommand(type, pString);
        bt_getReturn();
    }
    else {
        bt_sendCommand(type, pString);
        Sleep(500);
        bt_getReturnINQ();
    }
}
int main()
{
    char HC0x = HC05;
    char pString[128] = {0};

    printf("DeviceType : ");
    scanf ("%d", &HC0x);
    if(HC0x == HC05) {
        baudrate = 38400;
    }
    else {
        printf("Baudrate : ");
        scanf ("%d", &baudrate);
    }

    /* Open COM Port */
    if(!RS232_OpenComport(com_port, baudrate, mode)) {
        printf("Open COM Port Success\n\n");

        do {
            printf("AT Command : ");
            scanf ("%s",pString);
            bt_sendATCommand(HC0x, pString);
        } while(strcmp("EXTI", pString) != 0);

        bt_sendATCommand(HC0x, "AT");
        bt_sendATCommand(HC0x, "AT+ORGL");        //
        bt_sendATCommand(HC0x, "AT+ROLE=1");      //
        bt_sendATCommand(HC0x, "AT+ROLE?");       //
        bt_sendATCommand(HC0x, "AT+PSWD=0000");   //
        bt_sendATCommand(HC0x, "AT+PSWD?");
        bt_sendATCommand(HC0x, "AT+UART=115200,0,0");
        bt_sendATCommand(HC0x, "AT+UART?");
        bt_sendATCommand(HC0x, "AT+CMODE=0");
        bt_sendATCommand(HC0x, "AT+CMODE?");
        printf("AT+BIND=");
        scanf ("%s",pString);
        bt_sendBIND(HC0x, pString);
        bt_sendATCommand(HC0x, "AT+BIND?");
    }
    else {
        printf("Open COM Port Error\n");
    }

    /* Close COM Port */
    RS232_CloseComport(com_port);
    printf("\n\nClose COM Port\n");

    return(0);
}
