#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

//#define ACT_AS_SERVER

#include "MPWide.h"

int main(int argc, char** argv)
{
  int num_channels = 1;
  int msgsize = 8;

  if(argc<=2) {
    printf("usage: ./MPWTest <ip address of other endpoint> <repeat> [<channels> [<data size [kb]> [<pacing [MB/s]> [<tcpwin [bytes>]]]]]\n All parameters after the first are optional.\n");
    return 1;
  }

  /* Initialize */
  string host = string(argv[1]);
  int repeat = atoi(argv[2]);

  if(argc>3)
    num_channels = atoi(argv[3]);

  if(argc>4)
    msgsize = atoi(argv[4]);

  if(argc>5)
    MPW_setPacingRate(atoi(argv[5])*1024*1024);
  
  int path_id = MPW_CreatePathWithoutConnect(host, 20506, num_channels);
#ifdef ACT_AS_SERVER
  MPW_ConnectPath(path_id, true); ///path version
#else
  MPW_ConnectPath(path_id, false); ///path version
#endif

  if (argc > 6)
    MPW_setPathWin(path_id, atoi(argv[6]));

  {
    size_t len = msgsize*1024; 
    char msg2 = 0;
    char* msg = new char[len]();
  
    /* test loop */
    for(int i=0; i<repeat; i++) {
#ifdef ACT_AS_SERVER
      MPW_SendRecv(msg,len,&msg2,1,path_id); ///path version
      MPW_SendRecv(&msg2,1,msg,len,path_id); ///path version
#else
      MPW_SendRecv(&msg2,1,msg,len,path_id); ///path version
      MPW_SendRecv(msg,len,&msg2,1,path_id); ///path version
#endif
      cout << "End of iteration " << i << "." << endl;
    }

    delete [] msg;
  }

  MPW_Finalize();

  return 0;
}
