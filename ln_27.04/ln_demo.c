#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, const char** argv){
	char* pathname = argv[1];
	int fd = open(pathname, O_RDWR | O_CREAT);
	if(fd < 0){
		printf("Can not open a file!\n");
		exit(-1);
	}
	char* buf = "Hello, world!";
	if(write(fd, buf, 14) != 14){
		printf("Can not write content to file!\n");
		exit(-1);
	}
	if(link(pathname, "hard_link.txt") < 0){
		printf("Can not create hard link!\n");
		exit(-1);
	}
	if(symlink(pathname, "sym_link.txt") < 0){
		printf("Can not create symbolic link!\n");
		exit(-1);
	}
	if(close(fd) < 0){
		printf("Can not close file\n");
		exit(-1);
	}
}
