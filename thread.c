#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

#define MAX_THREADS 5
#define MIN_SLEEP_TIME 1
#define MAX_SLEEP_TIME 10

typedef struct {
    int id;
    int duration;
} ThreadParams;

void* thread_function(void* arg) {
    ThreadParams* params = (ThreadParams*)arg;
    printf("[Поток %d] Запущен, выполнение %d сек...\n", params->id, params->duration);
    
    sleep(params->duration);
    
    printf("[Поток %d] Завершен через %d сек\n", params->id, params->duration);
    free(params);
    return NULL;
}

bool validate_input(int time) {
    return time >= MIN_SLEEP_TIME && time <= MAX_SLEEP_TIME;
}

void run_threads() {
    pthread_t threads[MAX_THREADS];
    int sleep_times[MAX_THREADS];
    
    for (int i = 0; i < MAX_THREADS; i++) {
        do {
            printf("Введите время выполнения для потока %d (%d-%d сек): ", 
                  i+1, MIN_SLEEP_TIME, MAX_SLEEP_TIME);
            scanf("%d", &sleep_times[i]);
            
            if (!validate_input(sleep_times[i])) {
                printf("Ошибка! Введите значение от %d до %d\n", 
                      MIN_SLEEP_TIME, MAX_SLEEP_TIME);
            }
        } while (!validate_input(sleep_times[i]));
    }
    
    for (int i = 0; i < MAX_THREADS; i++) {
        ThreadParams* params = malloc(sizeof(ThreadParams));
        params->id = i+1;
        params->duration = sleep_times[i];
        
        if (pthread_create(&threads[i], NULL, thread_function, params) != 0) {
            perror("Ошибка создания потока");
            free(params);
        }
    }
    
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("\nВсе потоки успешно завершили работу!\n\n");
}

int main() {
    char command;
    
    do {
        run_threads();
        
        printf("Введите 'r' для повторного запуска или 'q' для выхода: ");
        scanf(" %c", &command);
        
    } while (command == 'r' || command == 'R');
    
    printf("Программа завершена.\n");
    return 0;
}
