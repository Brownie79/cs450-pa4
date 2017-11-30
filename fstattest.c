#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"
#include "stat.h"


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
  printf(1, "\nWhen you use extent-based file\n");
  fstat(fd, &st);
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
    printf(1, "\nextent-based file\n");
    fstat(fd, &st);
    
  }
  
  close(fd);
  close(regularFd);
  exit();
}
  
