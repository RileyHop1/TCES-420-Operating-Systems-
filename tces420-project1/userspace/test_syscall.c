#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>








int main(void) {
	long res = syscall(470);
	if (res == -1) {
		perror("syscall");
		return 1;
	}
	
	printf("Syscall returned: %ld\n", res);
	return 0;
}
