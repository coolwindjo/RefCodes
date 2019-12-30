#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

pid_t pid;
int g_count;
pthread_mutex_t g_mutex;
#if 0
sem_t g_sem;
#else
sem_t* g_sem;
#endif

void *thread_func1(void *arg)
{
	int temp, count = 0, max = *(int *)arg;

	printf("[%d] thread1 started with arg \"%d\"\n", pid, max);
	for(;;) {
		pthread_mutex_lock(&g_mutex);
		if(g_count == max) {
			pthread_mutex_unlock(&g_mutex);
			printf("[%d] thread1 counted %d\n", pid, count);
			pthread_exit(NULL);
		}
		temp = g_count;
		usleep(1);
		g_count = ++temp;
		count++;
		if(g_count == 100) {
#if 0
			sem_post(&g_sem);
#else
			sem_post(g_sem);
#endif
		}

		pthread_mutex_unlock(&g_mutex);
		usleep(2);
	}
}

void *thread_func2(void *arg)
{
	int temp, count = 0, max = *(int *)arg;

	printf("[%d] thread2 started with arg \"%d\"\n", pid, *(int *)arg);

#if 0
	sem_wait(&g_sem);
#else
	sem_wait(g_sem);
#endif
	for(;;) {
		pthread_mutex_lock(&g_mutex);
		if(g_count == max) {
			pthread_mutex_unlock(&g_mutex);
			printf("[%d] thread2 counted %d\n", pid, count);
			pthread_exit(NULL);
		}
		temp = g_count;
		usleep(1);
		g_count = ++temp;
		count++;
		pthread_mutex_unlock(&g_mutex);
		usleep(2);
	}
}

int main(int argc, char **argv)
{
	pthread_t thread_id1, thread_id2;
	int ret;
	int n = 20000;

        if(argc != 1) {
                printf("usage: %s\n", argv[0]);
                return EXIT_FAILURE;
        }
	printf("[%d] running %s\n", pid = getpid(), argv[0]);

	ret = pthread_mutex_init(&g_mutex, NULL);
	if(ret != 0) {
		printf("[%d] error: %d (%d)\n", pid, ret, __LINE__);
		return EXIT_FAILURE;
	}

#if 0
	ret = sem_init(&g_sem, 0, 0);
	if(ret == -1) {
		printf("[%d] error: %d (%d)\n", pid, ret, __LINE__);
		return EXIT_FAILURE;
	}
#else
	sem_unlink("/g_sem");
	g_sem = sem_open("/g_sem", O_CREAT /*| O_RDWR*/, 0777, 0);
	if(g_sem == SEM_FAILED) {
		printf("[%d] ret: %d error: %d %s (%d)\n", pid, ret, errno, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}
#endif

	printf("[%d] creating thread (g_count = %d)\n", pid, g_count);
	ret = pthread_create(&thread_id1, NULL, thread_func1, &n);
	if(ret != 0) {
		printf("[%d] error: %d (%d)\n", pid, ret, __LINE__);
		return EXIT_FAILURE;
	}
	ret = pthread_create(&thread_id2, NULL, thread_func2, &n);
	if(ret != 0) {
		printf("[%d] error: %d (%d)\n", pid, ret, __LINE__);
		return EXIT_FAILURE;
	}

	printf("[%d] waiting to join with a terminated thread\n", pid);
	ret = pthread_join(thread_id1, NULL);
	if(ret != 0) {
		printf("[%d] error: %d (%d)\n", pid, ret, __LINE__);
		return EXIT_FAILURE;
	}
	ret = pthread_join(thread_id2, NULL);
	if(ret != 0) {
		printf("[%d] error: %d (%d)\n", pid, ret, __LINE__);
		return EXIT_FAILURE;
	}
	printf("[%d] all threads terminated (g_count = %d)\n", pid, g_count);

#if 0
	sem_destroy(&g_sem);
#else
	sem_close(g_sem);
	sem_unlink("/g_sem");
#endif
	pthread_mutex_destroy(&g_mutex); printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}
