//#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "MvxSock.h"

SERVER_ID comStruct;
int result;
char szBuffer[200];
int len;
unsigned long ul;
int count;

int main(int argc, char* argv[])
{

   if((result=MvxSockConnect(&comStruct, "10.20.27.78", 16800, "mvxwwwc", "", "CRS610MI", NULL))) {
      printf("MvxSockConnect returned %d\n%s\n", result, comStruct.Buff);
      return 0;
      }

   MvxSockSetField(&comStruct, "CUNO", "60");
//   MvxSockSetField(&comStruct, "CONO", "330");
   if((result=MvxSockAccess(&comStruct, "GetBasicData"))) {
      printf("MvxSockAccess returned error %d: %s\n", result, comStruct.Buff);
      MvxSockClose(&comStruct);
      exit(0);
      }
   printf("'%s' ", MvxSockGetField(&comStruct, "CUNO"));
   printf("'%s'\n", MvxSockGetField(&comStruct, "CUNM"));
   ul=200;
   MvxSockTrans(&comStruct, "GetUserInfo     ", szBuffer, &ul);

   printf("%s\n", szBuffer);

   MvxSockClose(&comStruct);

   return 0;
}

