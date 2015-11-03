#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        printf("Please input the number of tosses.\n");
        fflush(stdout);
        exit(1);
    }

    long long int number_of_tosses = atoll(argv[1]);
    printf("number_of_tosses = %llu\n", number_of_tosses);
    fflush(stdout);

    srand((unsigned)time(NULL));

    pthread_t

    int number_in_circle = 0;
    int toss;
    for (toss = 0; toss < number_of_tosses; toss++) {
        
    }

    return 0;
}

double randNumGen() {
    int rand_value = rand();
    double unit_random = rand_value / (double) RAND_MAX;
    return unit_random;
}
