#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"
#include "stat.h"

void printStat(struct stat *st)
{
//print stat info
  char *filetype = "";
  if(st->type == T_EXTENT) {
    filetype = "extent-based file";
  }else{
    filetype = "pointer-based file";
  }

  printf(1, "Type: %s\n", filetype);
  printf(1, "Device: %d\n", st->dev);
  printf(1, "Inode #: %d\n", st->ino);
  printf(1, "Number of links: %d\n", st->nlink);
  printf(1, "Size: %d\n", st->size);

  //extent-based file
  if(st->type == T_EXTENT) {
    int i = 0;
    while(st->addrs[i] && i < NDIRECT+1){
      //first 3 byte is pointer and remaining 1 byte is length
      printf(1,"Pointer: %x\n", ((st->addrs[i] & ~0xff) >> 8));
      printf(1, "Length: %d\n", (st->addrs[i] & 0xff));
      ++i;
    }
  }
}


int main(int argc, char *argv[]){

  //create a new test file
  int fd = open("fstat_test", O_CREATE | O_RDWR | O_EXTENT);
  int regularFd = open("fstat_test_reg", O_CREATE | O_RDWR);
  struct stat st;

  printf(1, "In this test, we are comparing pointer-based file and extent-based file!\n\n");
  
  //Initial value
  printf(1, "Initial value when you open a new file!\n");
  printf(1, "When you use pointer-based file\n");
  fstat(regularFd, &st);
  printStat(&st);
  
  printf(1, "\nWhen you use extent-based file\n");
  fstat(fd, &st);
  printStat(&st);
  printf(1, "\n");

  printf(1, "Let's write something!\n");
  //Write something on
  int i;
  for(i = 1; i < 4; i++){
    char *newline = "We are adding new line! This line is long!\n"; 
    write(fd, newline, strlen(newline));
    write(regularFd, newline, strlen(newline));

    printf(1, "\n\nAfter adding %dth line..\n", i);
    printf(1, "pointer-based file\n");
    fstat(regularFd, &st);
    printStat(&st);
    printf(1, "\nextent-based file\n");
    fstat(fd, &st);
    printStat(&st);
    
  }
  
  close(fd);
  close(regularFd);
  exit();
}
  
