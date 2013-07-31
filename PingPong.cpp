#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <sys/time.h>

using namespace std;

//#define ACT_AS_SERVER

#ifdef ACT_AS_SERVER
static inline long GetLongTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec*1000000l+tv.tv_usec;
}
#endif

#include "MPWide.h"

int main(int argc, char** argv)
{
  if(argc!=5) {
    printf("usage: ./MPWPingPong <ip address of other endpoint> <repeat> <channels> <data size [kb]>\n");
    return 1;
  }

  /* Initialize */
  string host = string(argv[1]);
  const int repeat       = atoi(argv[2]);
  const int num_channels = atoi(argv[3]);
  const int msgsize      = atoi(argv[4]);

  const int path_id = MPW_CreatePathWithoutConnect(host, 20003, num_channels);
  if (path_id == -1)
	exit(EXIT_FAILURE);

#ifdef ACT_AS_SERVER
  MPW_ConnectPath(path_id, true);
#else
  MPW_ConnectPath(path_id, false);
#endif

  const size_t len = msgsize*1024; 
  char* msg = new char[len]();

  /* test loop */
  for(int i=0; i<repeat; i++) {
#ifdef ACT_AS_SERVER
    long usec = GetLongTime();
    MPW_SendRecv(msg,len,NULL,0,path_id);
    MPW_SendRecv(NULL,0,msg,len,path_id);
    usec = GetLongTime() - usec;
    printf("%ld\n", usec);
#else
    MPW_SendRecv(NULL,0,msg,len,path_id);
    MPW_SendRecv(msg,len,NULL,0,path_id);
#endif
  }

  delete [] msg;

  MPW_Finalize();

  return 0;
}

