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

