#include "types.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {
	int fd;
	
	//create a new test file
	fd = open("test_file", O_CREATE | O_RDWR);
	
	//write to the file
	printf(fd,"This is a long string and now it ends here.\n");
	
	//set offset to 5 bytes from start
	if (lseek(fd,5) < 0 ) {
		printf(1, "Error changing R/W pointer\n");
	}

	//write a new string at the seeked location
	write(fd,"NEW\n",4);

	close(fd);
	exit();	
}
