#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int min(int a, int b, int c) {
    int m = a;
    if (b < m) m = b;
    if (c < m) m = c;
    return m;
}

int levenshtein_wf(const char *s1, const char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    
    int **matriz = (int **)malloc((len1) * sizeof(int *));
    for (int i = 0; i <= len1; i++) {
        matriz[i] = (int *)malloc((len2) * sizeof(int));
    }

    
    for (int i = 0; i <= len1; i++) {
        matriz[i][0] = i;
    }
    for (int j = 0; j <= len2; j++) {
        matriz[0][j] = j;
    }

    // Preenchimento da matriz
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            // Custo é 0 se os caracteres forem iguais, 1 se forem diferentes (substituição)
            int custo_substituicao = (s1[i - 1] == s2[j - 1]) ? 0 : 1;

            matriz[i][j] = min(
                matriz[i - 1][j] + 1,       // Deleção (custo 1)
                matriz[i][j - 1] + 1,       // Inserção (custo 1)
                matriz[i - 1][j - 1] + custo_substituicao // Substituição
            );
        }
    }

    int distancia = matriz[len1][len2];

    // Liberação de memória
    for (int i = 0; i <= len1; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return distancia;
}

// --- FUNÇÕES AUXILIARES ---

// Gera uma string aleatória de tamanho n
void gerar_string_aleatoria(char *s, int len) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < len; i++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        s[i] = charset[key];
    }
    s[len] = '\0';
}

int main() {
    // Configurações do teste
    int tamanho_inicial = 1000;
    int tamanho_maximo = 45000; 
    int passo = 1000;
    
    // Arquivo de saída
    FILE *fp = fopen("../dados/resultados.csv", "w");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo CSV. Verifique se a pasta '../dados' existe.\n");
        return 1;
    }
    
    // Cabeçalho do CSV
    fprintf(fp, "tamanho,tempo_segundos\n");
    printf("Iniciando benchmark...\n");

    srand(time(NULL));

    for (int n = tamanho_inicial; n <= tamanho_maximo; n += passo) {
        // Aloca strings para o teste
        char *s1 = (char*) malloc((n + 1) * sizeof(char));
        char *s2 = (char*) malloc((n + 1) * sizeof(char));

        gerar_string_aleatoria(s1, n);
        gerar_string_aleatoria(s2, n);

        // Medição do tempo
        clock_t inicio = clock();
        levenshtein_wf(s1, s2);
        clock_t fim = clock();

        double tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

        // Salva no CSV e imprime no console para acompanhamento
        fprintf(fp, "%d,%.6f\n", n, tempo_gasto);
        printf("Tamanho: %d | Tempo: %.6f s\n", n, tempo_gasto);

        free(s1);
        free(s2);
    }

    fclose(fp);
    printf("Benchmark concluído! Dados salvos em '../dados/resultados.csv'.\n");

    return 0;
}