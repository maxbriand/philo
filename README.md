# philo
9th 42 project

Behavior:
- print status of philosopher for each step

Memset: fill a block memory with a specific byte

Gettimeofday: get lenght of program     
	struct timeval start, end;
    int seconds, useconds;
    int mtime;
    gettimeofday(&start, NULL);
    usleep(2000000); // Simulate a delay of 1 second
    gettimeofday(&end, NULL);
    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    mtime = ((seconds) * 1000 + useconds / 1000);
    printf("Elapsed time: %d milliseconds\n", mtime);

pthread_create: Create a thread + launch thread function
pthread_join: Wait for the specified thread


// ./philo 4 10 10 10
	// minimum 1 philosophers are around the table
	// fork = number of philosophers -> create the number of philosophers
	// need to fork to eat

# Parsing test
scope:
number of philosophers : 1 - 200
time to die: 60 - max int?
time to eat: 60 - max int?
time to sleep: 60 - max int
number of eat time: 1 - max int
// what's the behavior max int

// test int min
// test int max
// test long
// test long long
// test with letter
// test with special char

./philo 


void	ft_write_time(t_philos *philos, struct timeval zero, char *state, int sleep)
{
	struct timeval	current;
	long			total;

	gettimeofday(&current, NULL);
	total = (current.tv_sec - zero.tv_sec) * 1000000;
	total += (current.tv_usec - zero.tv_usec);
	total -= sleep;
	if (philos->i == 1)
		printf("%ld\n", total);
		// printf("%d %ld %s \n", philos->i, total, state);
}

USE A MUTEX EVERYTIME WHEN I CHECK OR MODIFY A CONFIG VARIABLE that can change
