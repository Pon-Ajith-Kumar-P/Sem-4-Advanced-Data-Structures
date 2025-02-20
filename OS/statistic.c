#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int *numbers;      // Array to store numbers
int count;         // Number of elements
double avg;    // Global variable for average
int min;       // Global variable for minimum
int max;       // Global variable for maximum
void *calculate_average(void *param) {
    double sum = 0;
    for (int i = 0; i < count; i++) {
        sum += numbers[i];
    }
    avg = sum / count;
    pthread_exit(0);
}

void *calculate_minimum(void *param) {
    min = numbers[0];
    for (int i = 1; i < count; i++) {
        if (numbers[i] < min) {
            min = numbers[i];
        }
    }
    pthread_exit(0);
}

void *calculate_maximum(void *param) {
    max = numbers[0];
    for (int i = 1; i < count; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <list of numbers>\n", argv[0]);
        return 1;
    }

    count = argc - 1;
    numbers = malloc(count * sizeof(int));
    for (int i = 0; i < count; i++) {
        numbers[i] = atoi(argv[i + 1]);
    }

    pthread_t tid1, tid2, tid3;

    pthread_create(&tid1, NULL, calculate_average, NULL);
    pthread_create(&tid2, NULL, calculate_minimum, NULL);
    pthread_create(&tid3, NULL, calculate_maximum, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    printf("The average value is %.0f\n", avg);
    printf("The minimum value is %d\n", min);
    printf("The maximum value is %d\n", max);

    free(numbers);
    return 0;
}
