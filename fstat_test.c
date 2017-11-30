#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"
#include "stat.h"

#define assert(x) if (x) {/* pass */} else { \
  printf(1, "assert failed %s %s %d\n", #x , __FILE__, __LINE__); \
  exit(); \
  }

char * testname = "fstat";
char buf[512];
struct stat st;

int main(int argc, char *argv[]){

  int fd, status;

  memset(buf, 0, 512);

  unlink("fstat_test_file");
  //create a new test file
  fd = open("fstat_test_file", O_CREATE | O_WRONLY | O_EXTENT);
  assert(fd != -1);

  int i;
  for (i = 0; i< 10; i++){
    buf[0] = i;
    status = write(fd, buf, 512);
    assert(status != -1);
    fstat(fd, &st);
  }

  status = close(fd);
  assert(status != -1);
  fstat(fd, &st);

  int pid = fork();
  if (pid == 0){
    printf(1, "Output from stat: \n");
    char * args[] = {"stat", "fstat_test_file", NULL};
    exec(args[0], args);
    exit();
  } else {
    wait();
    printf(1, "\n");
  }

  fd = open("fstat_test_file", O_RDONLY);
  assert(fd != -1);
  fstat(fd, &st);
  exit();

}
