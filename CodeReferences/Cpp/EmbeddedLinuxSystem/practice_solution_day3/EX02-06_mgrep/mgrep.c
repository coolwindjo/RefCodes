#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

pid_t pid;

int main(int argc, char **argv)
{
	pid_t pid_temp;	
	int i;
	int num_of_child;

	printf("[%d] running %s", pid = getpid(), argv[0]);
	for(i=1; i<argc; i++) {
		printf(" %s", argv[i]);
	}
	printf("\n");

	num_of_child = argc - 2;

	for(i=0; i<num_of_child; i++) {
		pid_temp = fork();

		if(pid_temp == -1) {
			printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
			return EXIT_FAILURE;
		}
		else if(pid_temp == 0) {
			int ret;
			pid = getpid();
			printf("[%d] about to run [grep -rn %s %s]\n", pid, argv[i+2], argv[1]);
			ret = execlp("grep", "grep", "-rn", argv[i+2], argv[1], NULL);
			printf("[%d] ret = %#x (%#x)\n", pid, ret, WEXITSTATUS(ret));
			return EXIT_FAILURE;
		}
	}

	for(i=0; i<num_of_child; i++) {
		pid_t pid_wait;
		int status;

		printf("[%d] waiting child's termination\n", pid);
		pid_wait = wait(&status);
		printf("[%d] pid %d has been terminated with status %#x\n", pid, pid_wait, status);
	}

	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}

