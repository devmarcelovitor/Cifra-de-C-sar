/*
 * Atividade Avaliativa 02 - Cifra de Cesar + Sequencias Numericas
 * Disciplina: Algoritmo e Pensamento Computacional
 * Camada 1: Cifra de Cesar (SHIFT fixo)
 * Camada 2: deslocamento dinamico por sequencia (PA, PG, Fibonacci, Primos)
 * Deslocamento total da letra i = SHIFT + sequencia[i]  (mod 26)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_LETRAS 15
#define ARQ_RESULTADO "resultado_criptografia.txt"
#define ARQ_LOG "log_execucao.txt"

typedef enum { PA = 1, PG = 2, FIBONACCI = 3, PRIMOS = 4 } Tipo;

static const char *nome_tipo(int t) {
    switch (t) {
        case PA: return "Progressao Aritmetica";
        case PG: return "Progressao Geometrica";
        case FIBONACCI: return "Fibonacci";
        case PRIMOS: return "Numeros Primos";
        default: return "Desconhecido";
    }
}

static void registrar_log(const char *msg) {
    FILE *f = fopen(ARQ_LOG, "a");
    if (!f) return;
    time_t agora = time(NULL);
    char data[32];
    strftime(data, sizeof data, "%Y-%m-%d %H:%M:%S", localtime(&agora));
    fprintf(f, "[%s] %s\n", data, msg);
    fclose(f);
}

static int eh_primo(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

/* Gera n termos da sequencia (valores reduzidos mod 26 para evitar overflow;
 * a1 = primeiro termo, r = razao/constante, usados em PA e PG). */
static void gerar_sequencia(Tipo t, int n, int a1, int r, int seq[]) {
    long long v;
    switch (t) {
        case PA:
            for (int i = 0; i < n; i++) seq[i] = (a1 + i * r) % 26;
            break;
        case PG:
            v = a1 % 26;
            for (int i = 0; i < n; i++) { seq[i] = (int)v; v = (v * r) % 26; }
            break;
        case FIBONACCI: {
            int a = 1, b = 1;
            for (int i = 0; i < n; i++) {
                seq[i] = a % 26;
                int c = (a + b) % 26; a = b; b = c;
            }
            break;
        }
        case PRIMOS: {
            int p = 2, k = 0;
            while (k < n) { if (eh_primo(p)) seq[k++] = p % 26; p++; }
            break;
        }
    }
}

static void processar(const char *entrada, char *saida, int shift, const int seq[], int decifrar) {
    int n = (int)strlen(entrada);
    for (int i = 0; i < n; i++) {
        int total = shift + seq[i];
        int base = toupper((unsigned char)entrada[i]) - 'A';
        int novo = decifrar ? ((base - total) % 26 + 26) % 26 : (base + total) % 26;
        saida[i] = (char)('a' + novo);
    }
    saida[n] = '\0';
}

static int palavra_valida(const char *p) {
    int n = (int)strlen(p);
    if (n < 1 || n > MAX_LETRAS) return 0;
    for (int i = 0; i < n; i++) if (!isalpha((unsigned char)p[i])) return 0;
    return 1;
}

static void ler_linha(char *buf, size_t tam) {
    if (!fgets(buf, (int)tam, stdin)) { buf[0] = '\0'; return; }
    buf[strcspn(buf, "\r\n")] = '\0';
}

static int ler_int(const char *msg) {
    char buf[64];
    printf("%s", msg);
    ler_linha(buf, sizeof buf);
    return atoi(buf);
}

static void executar(int decifrar) {
    char palavra[64], resultado[64], msg[256];
    int a1 = 1, r = 1;

    printf("Palavra (ate %d letras, sem acentos): ", MAX_LETRAS);
    ler_linha(palavra, sizeof palavra);
    if (!palavra_valida(palavra)) {
        printf("Palavra invalida!\n");
        registrar_log("ERRO: palavra invalida");
        return;
    }
    int shift = ler_int("SHIFT (ex.: 3): ");
    printf("Sequencia: 1-PA  2-PG  3-Fibonacci  4-Primos\n");
    int tipo = ler_int("Tipo: ");
    if (tipo < 1 || tipo > 4) {
        printf("Tipo invalido!\n");
        registrar_log("ERRO: tipo de sequencia invalido");
        return;
    }
    if (tipo == PA || tipo == PG) {
        a1 = ler_int("Primeiro termo a1: ");
        r = ler_int(tipo == PA ? "Razao r: " : "Razao q: ");
    }

    int n = (int)strlen(palavra);
    int seq[MAX_LETRAS];
    gerar_sequencia((Tipo)tipo, n, a1, r, seq);
    processar(palavra, resultado, shift, seq, decifrar);

    printf("\nSequencia (mod 26): ");
    for (int i = 0; i < n; i++) printf("%d%s", seq[i], i < n - 1 ? ", " : "\n");
    printf("%s: %s\n", decifrar ? "Palavra decifrada" : "Palavra criptografada", resultado);

    snprintf(msg, sizeof msg, "%s | entrada=%s | SHIFT=%d | tipo=%s | saida=%s",
             decifrar ? "DECIFRAR" : "CIFRAR", palavra, shift, nome_tipo(tipo), resultado);
    registrar_log(msg);

    if (!decifrar) {
        FILE *f = fopen(ARQ_RESULTADO, "a");
        if (f) {
            fprintf(f, "Palavra codificada: %s | SHIFT: %d | Tipo: %d | Letras: %d\n",
                    resultado, shift, tipo, n);
            fclose(f);
            printf("Resultado gravado em %s\n", ARQ_RESULTADO);
        } else {
            printf("Nao foi possivel gravar o arquivo.\n");
            registrar_log("ERRO: falha ao gravar arquivo de resultado");
        }
    }
}

int main(void) {
    int op;
    registrar_log("Programa iniciado");
    do {
        printf("\n=== CIFRA DE CESAR + SEQUENCIAS ===\n");
        printf("1 - Criptografar\n2 - Descriptografar\n0 - Sair\n");
        op = ler_int("Opcao: ");
        if (op == 1) executar(0);
        else if (op == 2) executar(1);
        else if (op != 0) printf("Opcao invalida!\n");
    } while (op != 0);
    registrar_log("Programa encerrado");
    return 0;
}
