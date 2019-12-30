#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_OF_THREAD 3
//const int NUM_OF_THREAD = 3;
const int NUM_OF_BREAD = 100;
const int NUM_OF_BREAD_IN_A_BOX = 10;
const int NUM_OF_BOX = 10;
const int USEC_HALF_SEC = 500000;

pid_t pid;
int bread_count;
int box_count;
pthread_mutex_t bread_mutex;
sem_t box_sem;

void *thread_maker(void *arg)
{
	int usec, count = 0;
	int id = *(int *)arg;

	/* Implement code */
	printf("[T%d] bread maker started with arg \"%d\"\n", id, id);
	for(;;) {
		usec = random() % USEC_HALF_SEC + USEC_HALF_SEC;
		usleep(usec);

		pthread_mutex_lock(&bread_mutex);{

			if(bread_count == NUM_OF_BREAD) {
				pthread_mutex_unlock(&bread_mutex);
				printf("[T%d] bread maker made %d loafs of bread.\n", id, count);
				pthread_exit(NULL);
			}
			bread_count++;
			count++;
			if(bread_count % NUM_OF_BREAD_IN_A_BOX == 0) {
				printf("[T%d] bread maker have made %d-th bread.\n", id, bread_count);
				sem_post(&box_sem);
			}

		} pthread_mutex_unlock(&bread_mutex);
	}

}

void *thread_boxer(void *arg)
{
	int id = *(int *)arg;

	/* Implement code */
	printf("[T%d] bread boxer started with arg \"%d\"\n", id, id);

	for(;;) {
		sem_wait(&box_sem);
		usleep(USEC_HALF_SEC*10);

		box_count++;
		printf("[T%d] bread boxer have made %d-th box.\n", id, box_count);
		if(box_count >= NUM_OF_BOX) {
			printf("[T%d] bread boxer terminated after making %d boxes.\n", id, box_count);
			pthread_exit(NULL);
		}
	}
}

void *(*thread_func[NUM_OF_THREAD])(void *arg) = {
	thread_maker,
	thread_maker,
	thread_boxer
};

int thread_arg[NUM_OF_THREAD] = {1, 2, 3};

int main(int argc, char **argv)
{
	pthread_t thread_id[NUM_OF_THREAD];
	int ret;
	int i;

        if(argc != 1) {
                printf("usage: %s\n", argv[0]);
                return EXIT_FAILURE;
        }
	printf("[%d] running %s\n", pid = getpid(), argv[0]);

	ret = pthread_mutex_init(&bread_mutex, NULL);
	if(ret != 0) {
		printf("[%d] error: %d (%d)\n", pid, ret, __LINE__);
		return EXIT_FAILURE;
	}

	ret = sem_init(&box_sem, 0, 0);
	if(ret == -1) {
		printf("[%d] error: %d (%d)\n", pid, ret, __LINE__);
		return EXIT_FAILURE;
	}

	printf("[%d] creating threads\n", pid);
	for(i=0; i<NUM_OF_THREAD; i++) {
		ret = pthread_create(&thread_id[i], NULL, thread_func[i], &thread_arg[i]);
		if(ret != 0) {
			printf("[%d] error: %d (%d)\n", pid, ret, __LINE__);
			return EXIT_FAILURE;
		}
	}

	printf("[%d] waiting to join with a terminated thread\n", pid);
	for(i=0; i<NUM_OF_THREAD; i++) {
		ret = pthread_join(thread_id[i], NULL);
		if(ret != 0) {
			printf("[%d] error: %d (%d)\n", pid, ret, __LINE__);
			return EXIT_FAILURE;
		}
	}
	printf("[%d] all threads terminated\n", pid);

	sem_destroy(&box_sem);
	pthread_mutex_destroy(&bread_mutex);
	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}
