#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

void printStat(struct stat *st)
{
  //print stat info
  char *filetype = "";
  if(st->type == T_EXTENT){
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
    int i=0;
    while(st->addrs[i] && i < NDIRECT+1){
      //first 3 byte is pointer and remaining 1 byte is length
      printf(1, "Pointer: %x\n", ((st->addrs[i] & ~0xff) >> 8));
      printf(1, "Length: %d\n", (st->addrs[i] & 0xff));
      ++i;
    }
  }
}

int main(int argc, char *argv[])
{

  //create a new test file
  int fd1 = open("extent_test1", O_RDWR | O_CREATE | O_EXTENT);
  int fd2 = open("extent_test2", O_RDWR | O_CREATE | O_EXTENT);
  int fd3 = open("extent_test3", O_RDWR | O_CREATE | O_EXTENT);
  int fd4 = open("extent_test4", O_RDWR | O_CREATE | O_EXTENT);
  
  int regularFd1 = open("extent_test_reg1", O_CREATE | O_RDWR);
  int regularFd2 = open("extent_test_reg2", O_CREATE | O_RDWR);
  int regularFd3 = open("extent_test_reg3", O_CREATE | O_RDWR);
  int regularFd4 = open("extent_test_reg4", O_CREATE | O_RDWR);
  struct stat st;

  printf(1, "In this test, we are making extent based file with really big string\n");
  //write something in the file

  printf(1, "Test1: Not that long string\n");
  char *prompt1 = "This is not that long string!\n";

  write(fd1, prompt1, strlen(prompt1));
  write(regularFd1, prompt1, strlen(prompt1));
  
  printf(1, "Stat info of extent-based file using same string\n");
  fstat(fd1, &st);
  printStat(&st);

  printf(1, "Compare to: Stat info of pointer-based file using same string\n");
  fstat(regularFd1, &st);
  printStat(&st);
 
  printf(1, "\n\n\n");
  printf(1, "Test2: Kind of long string\n");
  char *prompt2 = "This is kind of long string! This is kind of long string!This is kind of long string!This is kind of long string!This is kind of long string!This is kind of long string!This is kind of long string!This is kind of long string!This is kind of long string!This is kind of long string!This is kind of long string!\n";

  write(fd2, prompt2, strlen(prompt2));
  write(regularFd2, prompt2, strlen(prompt2));
  
  printf(1, "Stat info of extent-based file using same string\n");
  fstat(fd2, &st);
  printStat(&st);

  printf(1, "Compare to: Stat info of pointer-based file using same string\n");
  fstat(regularFd2, &st);
  printStat(&st);
 
  printf(1, "\n\n\n");
  printf(1, "Test3: long string\n");
  char *prompt3 = "This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! \n This is long string!This is long string!This is long string!This is long string!This is long string! ";

  write(fd3, prompt3, strlen(prompt3));
write(regularFd3, prompt3, strlen(prompt3));
  
  printf(1, "Stat info of extent-based file using same string\n");
  fstat(fd3, &st);
  printStat(&st);

  printf(1, "Compare to: Stat info of pointer-based file using same string\n");
  fstat(regularFd3, &st);
  printStat(&st);


  printf(1, "\n\n\n");
    printf(1, "Test4: super long string\n");

  char *prompt4 = "This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! This is long string! ";
  
  write(fd4, prompt4, strlen(prompt4));
  write(regularFd4, prompt4, strlen(prompt4));
  
  printf(1, "Stat info of extent-based file using same string\n");
  fstat(fd4, &st);
  printStat(&st);

  printf(1, "Compare to: Stat info of pointer-based file using same string\n");
  fstat(regularFd4, &st);
  printStat(&st);
  
  close(fd1);
close(fd2);
close(fd3);
close(fd4);

  close(regularFd1);
close(regularFd2);
close(regularFd3);
close(regularFd4);

exit();
}

