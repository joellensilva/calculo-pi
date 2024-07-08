#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>

#define NUM_THREADS 32 // Número máximo de threads a serem testadas
#define ITERACOES 1000000000 // 1 bilhão de termos

double resultados_parciais[NUM_THREADS]; // Vetor para armazenar resultados parciais
pthread_t threads[NUM_THREADS];
pthread_mutex_t lock;

// Função para calcular π usando a série de Leibniz-Gregory
void *calcular_pi(void *thread_id) {
    int tid = *((int *) thread_id);
    double resultado_parcial = 0.0;
    int inicio = tid * (ITERACOES / NUM_THREADS);
    int fim = inicio + (ITERACOES / NUM_THREADS);

    for (int i = inicio; i < fim; ++i) {
        resultado_parcial += 4.0 * (i % 2 == 0 ? 1 : -1) / (2 * i + 1);
    }

    resultados_parciais[tid] = resultado_parcial;

    pthread_exit(NULL);
}

// Função para somar todos os resultados parciais
double somar_resultados(int num_threads) {
    double pi = 0.0;
    for (int i = 0; i < num_threads; ++i) {
        pi += resultados_parciais[i];
    }
    return pi;
}

int main() {
    struct timeval start, end;
    double tempo_execucao;
    int num_threads[] = {1, 2, 4, 8, 16, 32};
    int num_experimentos = 5;
    double tempos_execucao[num_experimentos];

    pthread_mutex_init(&lock, NULL);

    for (int k = 0; k < sizeof(num_threads) / sizeof(num_threads[0]); ++k) {
        for (int exp = 0; exp < num_experimentos; ++exp) {
            gettimeofday(&start, NULL);

            for (int i = 0; i < num_threads[k]; ++i) {
                int *tid = malloc(sizeof(int));
                *tid = i;
                pthread_create(&threads[i], NULL, calcular_pi, (void *) tid);
            }
            for (int i = 0; i < num_threads[k]; ++i) {
                pthread_join(threads[i], NULL);
            }

            double pi = somar_resultados(num_threads[k]);

            gettimeofday(&end, NULL);
            tempo_execucao = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000;

            tempos_execucao[exp] = tempo_execucao;

            printf("Número de threads: %d\n", num_threads[k]);
            printf("Valor aproximado de pi: %.12f\n", pi);
            printf("Tempo médio de execução: %.6f segundos\n", tempo_execucao);
            printf("---------------------------------------------\n");
        }

        // Calcular média e coeficiente de variação dos tempos de execução
        double media = 0.0;
        for (int i = 0; i < num_experimentos; ++i) {
            media += tempos_execucao[i];
        }
        media /= num_experimentos;

        double desvio_padrao = 0.0;
        for (int i = 0; i < num_experimentos; ++i) {
            desvio_padrao += pow(tempos_execucao[i] - media, 2);
        }
        desvio_padrao = sqrt(desvio_padrao / num_experimentos);

        double coeficiente_variacao = (desvio_padrao / media) * 100;

        printf("Número de threads: %d\n", num_threads[k]);
        printf("Tempo médio de execução: %.6f segundos\n", media);
        printf("Desvio padrão: %.6f segundos\n", desvio_padrao);
        printf("Coeficiente de variação: %.2f%%\n", coeficiente_variacao);
        printf("---------------------------------------------\n");
    }

    pthread_mutex_destroy(&lock);
    return 0;
}

// 1. As threads implementadas são preemptivas ou cooperativas? Explique sua resposta.
// As threads implementadas são preemptivas, pois elas são executadas em um contexto de execução separado, permitindo que elas possam executar em paralelo com outras tarefas do sistema.

// 2. Que modelo de threads o sistema operacional que você usou implementa (N:1, 1:1 ou N:M)?
// Como isso pode ser deduzido a partir dos experimentos?
// A biblioteca pthread em sistemas Linux é geralmente implementada usando o modelo 1:1, podendo variar dependendo do SO e sua versão. Assim, acreditamos que o sistema operacional implementa o modelo N:1, pois ele executa as threads em um contexto de execução separado, permitindo que elas possam executar em paralelo com ou sem outras tarefas do sistema.
// SO: Linux adfa82e98968 6.5.0-1023-gcp #25~22.04.1-Ubuntu SMP Thu Jun 13 19:41:39 UTC 2024 x86_64 GNU/Linux
