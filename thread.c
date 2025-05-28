#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
    int index;
    int sleep_time;
} ThreadData;

void* thread_task(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    printf("Поток %d начал работу (будет работать %d секунд)\n", data->index + 1, data->sleep_time);
    sleep(data->sleep_time);
    printf("Поток %d завершил работу через %d секунд\n", data->index + 1, data->sleep_time);
    free(arg);
    return NULL;
}

int main() {
    char choice;
    do {
        pthread_t threads[5];
        int sleep_times[5];
        
        // Ввод времени для каждого потока
        for (int i = 0; i < 5; i++) {
            printf("Введите время для потока %d: ", i + 1);
            scanf("%d", &sleep_times[i]);
        }
        
        // Создание потоков
        for (int i = 0; i < 5; i++) {
            ThreadData* data = malloc(sizeof(ThreadData));
            data->index = i;
            data->sleep_time = sleep_times[i];
            pthread_create(&threads[i], NULL, thread_task, data);
        }
        
        
        // Ожидание завершения всех потоков
        for (int i = 0; i < 5; i++) {
            pthread_join(threads[i], NULL);
        }
        
        printf("Все потоки завершены!\n\n");
        printf("Нажмите 'r' для повтора или 'x' для выхода: ");
        scanf(" %c", &choice);
        
    } while (choice != 'x');
    
    return 0;
}
