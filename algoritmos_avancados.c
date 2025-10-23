#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Definição da Estrutura do Nó (Sala)
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

/**
 * @brief Cria e retorna um novo nó (Sala) para a árvore binária.
 * @param nome O nome do cômodo.
 * @return Um ponteiro para a nova Sala criada.
 */
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        perror("Erro ao alocar memória para a sala.");
        exit(EXIT_FAILURE);
    }
    // Copia o nome para a estrutura
    strncpy(novaSala->nome, nome, sizeof(novaSala->nome) - 1);
    novaSala->nome[sizeof(novaSala->nome) - 1] = '\0'; // Garantir terminação
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

/**
 * @brief Libera a memória de todos os nós da árvore (pós-ordem).
 * @param raiz O nó raiz da subárvore a ser liberada.
 */
void liberarArvore(Sala* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

/**
 * @brief Permite ao jogador explorar a mansão interativamente.
 * @param salaAtual O nó (cômodo) onde o jogador está atualmente.
 */
void explorarSalas(Sala* salaAtual) {
    char acao;

    if (salaAtual == NULL) {
        printf("\n[ERRO DE NAVEGAÇÃO]: Fim inesperado do caminho.\n");
        return;
    }

    // Loop de exploração
    while (salaAtual != NULL) {
        printf("\n-------------------------------------------------\n");
        printf("Você está em: \033[1;33m%s\033[0m\n", salaAtual->nome); // Amarelo para destaque

        // Verifica se é um nó-folha (fim do caminho)
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("\n\033[1;32m[FIM DO CAMINHO]\033[0m: Você alcançou o final desta ala da mansão.\n");
            break;
        }

        // Oferece opções de navegação
        printf("Para onde deseja ir?\n");
        if (salaAtual->esquerda != NULL) {
            printf("  (e) Esquerda\n");
        }
        if (salaAtual->direita != NULL) {
            printf("  (d) Direita\n");
        }
        printf("  (s) Sair da exploração\n");
        printf("Sua escolha: ");

        // Lendo a ação do usuário
        if (scanf(" %c", &acao) != 1) {
             // Tratamento de erro de leitura
             printf("\n[ERRO]: Entrada inválida.\n");
             // Limpa o buffer de entrada
             while (getchar() != '\n'); 
             continue;
        }

        // Lógica de navegação
        switch (acao) {
            case 'e':
            case 'E':
                if (salaAtual->esquerda != NULL) {
                    salaAtual = salaAtual->esquerda;
                } else {
                    printf("\n[AVISO]: Não há caminho à esquerda a partir desta sala.\n");
                }
                break;
            case 'd':
            case 'D':
                if (salaAtual->direita != NULL) {
                    salaAtual = salaAtual->direita;
                } else {
                    printf("\n[AVISO]: Não há caminho à direita a partir desta sala.\n");
                }
                break;
            case 's':
            case 'S':
                printf("\nSaindo da exploração da mansão. Até breve!\n");
                return; // Sai da função
            default:
                printf("\n[ERRO]: Opção inválida. Use 'e', 'd' ou 's'.\n");
                break;
        }
    } // Fim do while (exploração)

    printf("\n-------------------------------------------------\n");
}

/**
 * @brief Função principal para montar a árvore e iniciar o jogo.
 */
int main() {
    printf("==================================================\n");
    printf("        DETETIVE QUEST - MAPA DA MANSÃO\n");
    printf("             NÍVEL NOVATO - ÁRVORE BINÁRIA\n");
    printf("==================================================\n");

    // 2. Construção Estática da Árvore Binária
    // (A árvore é montada manualmente, conforme a regra do Nível Novato)

    Sala* hall = criarSala("Hall de Entrada");

    // Nível 1
    hall->esquerda = criarSala("Cozinha");
    hall->direita = criarSala("Biblioteca");

    // Nível 2
    hall->esquerda->esquerda = criarSala("Despensa"); // Despensa (Folha)
    hall->esquerda->direita = criarSala("Sala de Jantar");
    
    hall->direita->esquerda = criarSala("Escritório");
    hall->direita->direita = criarSala("Quarto Principal");

    // Nível 3
    hall->esquerda->direita->esquerda = criarSala("Jardim de Inverno"); // Jardim (Folha)
    hall->esquerda->direita->direita = criarSala("Copa"); // Copa (Folha)
    
    hall->direita->esquerda->esquerda = criarSala("Arquivo Secreto"); // Arquivo (Folha)
    hall->direita->esquerda->direita = criarSala("Corredor Oeste"); // Corredor
    
    hall->direita->direita->esquerda = criarSala("Banheiro Suíte"); // Banheiro (Folha)
    hall->direita->direita->direita = criarSala("Varanda"); // Varanda (Folha)

    // Nível 4 (Final de um caminho)
    hall->direita->esquerda->direita->direita = criarSala("Quarto de Hóspedes"); // Quarto Hóspedes (Folha)

    // 3. Início do Jogo
    explorarSalas(hall);

    // 4. Liberação da Memória ao Final
    liberarArvore(hall);
    printf("\nMemória da mansão liberada. Fim do programa.\n");

    return 0;
}