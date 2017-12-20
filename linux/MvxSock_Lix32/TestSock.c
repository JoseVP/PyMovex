/**
 * This is an example program that show how to use the Movex API Client Interface in
 * the Linux environment.
 * 
 * When you compile/create your own programs and modules use the following commands:
 *
 *  gcc -o TestSock TestSock.c -L. -lMvxSock
 *
 * Note: 
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>

#include "MvxSock.h"

#define LOBYTE(w)           ((unsigned char)(w))
#define HIBYTE(w)           ((unsigned char)(((unsigned short)(w) >> 8) & 0xFF))


SERVER_ID comStruct;
int result;
char sendBuff[200];
char recvBuff[1000];
unsigned long len;
int count;

int main(int argc, char *argv[])
{
short int ver;

   /*
    * If FPW is running remote or locally does not matter if you use
    * the host name by which it is known in your network.
    * If only locally on this server you can as well use 127.0.0.1.
    * It might as well be on another AS/400 in which case we write that IP-address
    * or its host name.
    * We name this test-program "MvxSock C-test"
    * We do NOT want encryption (0) so the last argument (CryptKey) is ignored.
    */
/* "10.20.20.139", 56800 */
   memset(&comStruct, '\0', sizeof(SERVER_ID));
   if((result=MvxSockSetup(&comStruct, "10.20.29.60", 6000, "MvxSock C-test", 0, "NotUsed")))
      printf("MvxSockSetup returned %d\n", result);


   /**
    * Print out version of MvxSock
    */
   ver = MvxSockVersion();
   printf( "MvxSock %d.%d\n", HIBYTE(ver), LOBYTE(ver));

   /*
    * We use the AS400 account MVXWWWC with password WB11028
    * We want to connect to a program called CRS610MI
    */
   if((result=MvxSockInit(&comStruct, "LOCALA", "MVXWWWC", "WB11028", "CRS610MI"))) {
      printf("MvxSockInit returned error %d: %s\n", result, comStruct.Buff);
      exit(0);
      }

   /* Build a command string, list all customer templates */
   strcpy(sendBuff, "LstTemplates   001          ");
   len=sizeof(recvBuff);
   count=0;

   if((result=MvxSockTrans(&comStruct, sendBuff, recvBuff, &len))) {
      printf("MvxSockTrans returned error %d: %s\n", result, comStruct.Buff);
      exit(0);
      }

   printf("Sent %d bytes: %s\n", strlen(sendBuff), sendBuff);
   printf("Got %d bytes: %s\n", strlen(recvBuff), recvBuff);

   while(strncmp(recvBuff, "REP  ", 5)==0) {
      count++;
      len=1000;
      if((result=MvxSockReceive(&comStruct, recvBuff, &len)))
         printf("   MvxSockReceive returned error %d: %s\n", result, comStruct.Buff);

      printf("Got %d bytes: %s\n", strlen(recvBuff), recvBuff);
      }

   if((result=MvxSockClose(&comStruct)))
      printf("   MvxSockClose returned error %d: %s\n", result, comStruct.Buff);
   printf("Got %d REP-lines.\n", count);

   exit(0);
}


