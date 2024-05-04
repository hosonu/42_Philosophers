#include "philosophers.h"

typedef struct routine_arg
{
	int	cnt;
	pthread_mutex_t	mutex;
}	t_routine_arg;

void	*routine(void *arg)
{
	t_routine_arg	*r_arg;

	r_arg = (t_routine_arg *)arg;
	pthread_mutex_lock(&r_arg->mutex);
	r_arg->cnt++;
	pthread_mutex_unlock(&r_arg->mutex);
	return (NULL);
}

int main()
{
	pthread_t	thread[10];
	t_routine_arg	arg;

	arg.cnt = 0;
	pthread_mutex_init(&arg.mutex, NULL);
	for(int i = 0; i < 11; i++)
	{
		pthread_create(&thread[i], NULL, routine, &arg);
	}
	for(int i = 0; i < 11; i++)
	{
		pthread_join(thread[i], NULL);
	}
	printf("Hello %d\n", arg.cnt);

	pthread_mutex_destroy(&arg.mutex);
	return (0);
}
