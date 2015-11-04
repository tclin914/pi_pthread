#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/sysinfo.h>
#include <math.h>
#define BILLION  1E9; 

double randNumGen();
void *calc(void *threadid);

long thread_count = 100;
long long number_of_tosses;
long long number_in_circle = 0;

pthread_mutex_t mutex;

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        printf("Please input the number of tosses.\n");
        fflush(stdout);
        exit(1);
    }

    struct timespec requestStart, requestEnd;
    clock_gettime(CLOCK_REALTIME, &requestStart);

    printf("This system has %d processors configured and "
            "%d processors available.\n",
            get_nprocs_conf(), get_nprocs());

    number_of_tosses = strtoll(argv[1], NULL, 10);

    srand((unsigned)time(NULL));

    long thread;
    pthread_t *thread_handles;
    thread_handles = (pthread_t*) malloc(sizeof(pthread_t) * thread_count);
    pthread_mutex_init(&mutex, NULL);

    for (thread = 0; thread < thread_count; thread++) 
        pthread_create(&thread_handles[thread], NULL, 
                calc, (void*)thread);

    for (thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread], NULL);

    clock_gettime(CLOCK_REALTIME, &requestEnd);
    double accum = ( requestEnd.tv_sec - requestStart.tv_sec )
           + ( requestEnd.tv_nsec - requestStart.tv_nsec )
                  / BILLION;
    printf("run time = %lf\n", accum);
    printf("number_of_tosses = %llu number_in_circle = %llu\n", number_of_tosses, number_in_circle);
    printf("Pi = %f\n", 4 * (number_in_circle / (double)number_of_tosses));
    fflush(stdout);

    pthread_mutex_destroy(&mutex);
    free(thread_handles);
    return 0;
}

double randNumGen() {
    int rand_value = rand();
    double unit_random = rand_value / (double) RAND_MAX;
    return unit_random;
}

void *calc(void *threadid) {
    long id = (long)threadid;
    long long i;
    long long n = number_of_tosses / thread_count;
    long long in_circle = 0;

    for (i = 0; i < n; i++) {
        double x = randNumGen();
        double y = randNumGen();
        double result = (x * x) + (y * y);

        fflush(stdout);
        if (result < 1) {
            in_circle += 1;            
        }    
    }
    pthread_mutex_lock(&mutex);
    number_in_circle += in_circle;
    pthread_mutex_unlock(&mutex);

    return NULL;
}
