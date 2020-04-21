#define _GNU_SOURCE
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <stdint.h>
#include "../cacheutils.h"
//Weitong Zhai: these are the prior variable setting
size_t time_start = 0;
size_t keystate = 0;
size_t numofcycle = 0;
//Weitong Zhai: prior varible setting complete


//Weitong Zhai: this is the function of Flush and reload
void FR(void* addr)
{
  size_t time_counting = rdtsc_begin();
  size_t delta = rdtsc_end() - time_counting;
  maccess(addr;) 
  flush(addr);      //Weitong Zhai: At this position is the first time flush the cache set
  if (time_monitor < 201)
  {
    if (numofcycle > 999)
    {
      printf("Cache Hit %10lu after %10lu cycles, t=%10lu us\n", delta, numofcycle, (time_counting-time_start)/2600);
      keystate = (keystate+1) % 2;
    }
    numofcycle = 0;//Weitong Zhai: numofcycle need to be back to zero   
  }
  else
    numofcycle++;
}
//Weitong Zhai: This is the complete of the function FR
//Weitong Zhai: This is the main function
int main(int argc, char** argv)
{
  char* offsetp = argv[2];
  char* name = argv[1];
  unsigned int offset = 0;
  if (argc != 3)
    return 1;
  unsigned int offset = 0;
  !sscanf(offsetp,"%x",&offset);
  int fd = open(name,O_RDONLY);
  if (fd < 3)
    return 2;
  unsigned char* addr = (unsigned char*)mmap(0, 64*1024*1024, PROT_READ, MAP_SHARED, fd, 0);
  if (addr == (void*)-1)
    return 3;
  start = rdtsc();
  while(1)    //Weitong Zhai: Because the time will go on, so the while will always true, which means it only can be end manually. 
  {
    FR(addr + offset);//Weitong Zhai: This is the position to enter the FR function.
    sched_yield();//Weitong Zhai: When finish the function, use this function to yield the process.
  }
  return 0;
}
//This is the complete of the main function
