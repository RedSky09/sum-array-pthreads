#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 32

typedef struct {
    int thread_id;
    int *array;
    long start;
    long end;
    long long partial_sum;
} ThreadData;

void *sum_array(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    data->partial_sum = 0;
    for (long i = data->start; i < data->end; i++) {
        data->partial_sum += data->array[i];
    }
    printf("[Thread %2d] Range: %8ld - %8ld | Total: %lld\n",
           data->thread_id, data->start, data->end - 1, data->partial_sum);
    pthread_exit(NULL);
}

int main() {
    long array_size;
    int num_threads, init_method;

    printf("=== PROGRAM PENJUMLAHAN ARRAY MENGGUNAKAN PTHREADS ===\n");
    printf("Masukkan ukuran array (max 100000000): ");
    scanf("%ld", &array_size);
    if (array_size > 100000000 || array_size <= 0) {
        printf("Ukuran array tidak valid.\n");
        return 1;
    }

    printf("Masukkan jumlah thread (max 32): ");
    scanf("%d", &num_threads);
    if (num_threads <= 0 || num_threads > MAX_THREADS) {
        printf("Jumlah thread tidak valid.\n");
        return 1;
    }

    printf("Pilih metode inisialisasi array:\n");
    printf("  [0] Semua elemen bernilai 1\n");
    printf("  [1] Acak (rand %% 10)\n");
    printf("Pilihan Anda: ");
    scanf("%d", &init_method);

    int *array = malloc(sizeof(int) * array_size);
    if (!array) {
        printf("Gagal mengalokasikan memori.\n");
        return 1;
    }

    srand(time(NULL));
    for (long i = 0; i < array_size; i++) {
        array[i] = (init_method == 0) ? 1 : rand() % 10;
    }

    pthread_t threads[MAX_THREADS];
    ThreadData thread_data[MAX_THREADS];

    long chunk = array_size / num_threads;
    long start_time = clock();

    for (int i = 0; i < num_threads; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].array = array;
        thread_data[i].start = i * chunk;
        thread_data[i].end = (i == num_threads - 1) ? array_size : (i + 1) * chunk;

        pthread_create(&threads[i], NULL, sum_array, &thread_data[i]);
    }

    long long total_sum = 0;
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].partial_sum;
    }

    long end_time = clock();
    double elapsed = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("=======================================================\n");
    printf("Total penjumlahan seluruh elemen: %lld\n", total_sum);
    printf("Waktu eksekusi: %.5f detik\n", elapsed);

    free(array);
    return 0;
}
