#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *thread1(void *arg)
{
	*((int *)arg) = 1;

	pthread_exit(NULL);
}

void *thread2(void *arg)
{
	*((int *)arg) = 2;

	pthread_exit(NULL);
}

void *thread3(void *arg)
{
	*((int *)arg) = 3;

	pthread_exit(NULL);
}

int main()
{
	int array[10] = {0};
	pthread_t pid[3] = {0};

	pthread_create(pid, NULL, thread1, (void *)array);

	pthread_create(pid + 1, NULL, thread2, (void *)(array+1));

	pthread_create(pid + 2, NULL, thread3, (void *)(array+2));

	pthread_join(pid[0], NULL);
	pthread_join(pid[1], NULL);
	pthread_join(pid[2], NULL);

	int sum = 0;

	std::cout << "array0:  " << array[0] << std::endl;

	std::cout << "array1:  " << array[1] << std::endl;

	std::cout << "array2:  " << array[2] << std::endl;

	sum += array[0];
	sum += array[1];
	sum += array[2];

	std::cout << "sum:  " << sum << std::endl;

	return 0;

}
