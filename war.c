#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_TERRITORIOS 42

// Struct que representa cada território do jogo
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// ---------------- PROTÓTIPOS ----------------
void limparBufferEntrada(); // limpa o buffer de entrada
void RegrasdoJogo(); // exibe as regras do jogo
void listaObjetivos(); // lista os objetivos possíveis
void sortearObjetivo(); // sorteia um objetivo aleatório
void cadastrarTerritorio(struct Territorio *mapa, int *totalTerritorios); // cadastra novo território
void listarTerritorios(struct Territorio *mapa, int totalTerritorios); // lista territórios cadastrados
void distribuirTropas(struct Territorio* mapa, int totalTerritorios); // distribui tropas nos territórios
void executarAtaque(struct Territorio* mapa, int totalTerritorios); // executa ataque entre territórios
void verificarMissaoJogador(char* missaoJogador, struct Territorio* mapa, int totalTerritorios, int* opcao); // verifica se missão foi cumprida
void sairJogo(); // mensagem de saída
void liberarMemoria(struct Territorio* mapa, char* missaoJogador); // libera memória alocada
void atacar(struct Territorio* atacante, struct Territorio* defensor); // lógica de ataque

// ---------------- PROGRAMA PRINCIPAL ----------------
int main() {
    struct Territorio* mapa = (struct Territorio*)calloc(NUM_TERRITORIOS, sizeof(struct Territorio));
    int totalTerritorios = 0;
    int opcao;

    // Missão do jogador (exemplo inicial)
    char* missaoJogador = (char*)malloc(100 * sizeof(char));
    strcpy(missaoJogador, "Eliminar todas as tropas da cor vermelha");

    srand(time(NULL));

    // Loop principal do menu
    do {
        printf("\n----------------------------------------------------------------\n");
        printf("               Menu Principal\n");
        printf("----------------------------------------------------------------\n");
        printf("1 - Regras do jogo\n");              // Case 1: exibe regras
        printf("2 - Lista de missões\n");           // Case 2: lista objetivos
        printf("3 - Sortear Objetivo\n");           // Case 3: sorteia objetivo
        printf("4 - Cadastrar Território\n");       // Case 4: cadastra território
        printf("5 - Listar Territórios\n");         // Case 5: lista territórios
        printf("6 - Distribuir Tropas\n");          // Case 6: distribui tropas
        printf("7 - Atacar\n");                     // Case 7: executa ataque
        printf("8 - Verificar Missão\n");           // Case 8: verifica missão
        printf("0 - Sair\n");                       // Case 0: encerra jogo
        printf("----------------------------------------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch(opcao) {
            case 1: 
                RegrasdoJogo(); // chama função que mostra regras
                break; 
            case 2: 
                listaObjetivos(); // chama função que lista objetivos
                break; 
            case 3: 
                sortearObjetivo(missaoJogador); //chama a função de sortear objetivo
                break;

            case 4: 
                cadastrarTerritorio(mapa, &totalTerritorios); // chama função que cadastra território
                break; 
            case 5:     
                listarTerritorios(mapa, totalTerritorios); // chama função que lista territórios
                break; 
            case 6: 
                distribuirTropas(mapa, totalTerritorios); // chama função que distribui tropas
                break; 
            case 7: 
                executarAtaque(mapa, totalTerritorios); // chama função que executa ataque
                break; 
            case 8:     
                verificarMissaoJogador(missaoJogador, mapa, totalTerritorios, &opcao); // chama função que verifica missão
                break; 
            case 0: 
                sairJogo();  // chama funções de saída e liberar memória
                break; 
            default: printf("Opção inválida! Tente novamente.\n"); // mensagem para opção inválida
        }
    } while(opcao != 0);
    
    liberarMemoria(mapa, missaoJogador);

    return 0;
}

// ---------------- FUNÇÕES AUXILIARES ----------------

// limpa o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// exibe as regras básicas do jogo
void RegrasdoJogo() {
    printf(" --- Regras do jogo ---\n\n");
    printf("O objetivo do jogo é conquistar o mundo dominando todos os territórios ou cumprindo uma missão secreta.\n");
    printf("Cada jogador começa com tropas que podem ser distribuídas.\n");
    printf("Em cada turno, o jogador pode atacar territórios vizinhos.\n");
    printf("O jogo termina quando um jogador conquista todos os territórios ou cumpre sua missão secreta.\n");
}

// lista os objetivos disponíveis
void listaObjetivos() {
    printf(" --- Objetivos ---\n");
    printf("1. Conquistar 3 territórios seguidos\n");
    printf("2. Eliminar todas as tropas da cor vermelha\n");
    printf("3. Dominar todos os territórios da Europa\n");
    printf("4. Eliminar o exército azul\n");
    printf("5. Controlar 10 territórios ao mesmo tempo\n");
    printf("6. Eliminar o exército amarelo\n");
}

// sorteia um objetivo aleatório
void sortearObjetivo(char* missaoJogador) {
    const char* objetivos[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Dominar todos os territórios da Europa",
        "Eliminar o exército azul",
        "Controlar 10 territórios ao mesmo tempo",
        "Eliminar o exército amarelo"
    };
    int objetivo = rand() % 6;
    strcpy(missaoJogador, objetivos[objetivo]);
    printf("Objetivo sorteado: %s\n", missaoJogador);
}


// cadastra um novo território
void cadastrarTerritorio(struct Territorio *mapa, int *totalTerritorios) {
    int t = *totalTerritorios;
    if (t < NUM_TERRITORIOS) {
        printf("Digite o nome do território: ");
        fgets(mapa[t].nome, 30, stdin);
        printf("Digite a cor do exército: ");
        fgets(mapa[t].cor, 10, stdin);
        mapa[t].nome[strcspn(mapa[t].nome, "\n")] = '\0';
        mapa[t].cor[strcspn(mapa[t].cor, "\n")] = '\0';
        (*totalTerritorios)++;
        printf("\nTerritório cadastrado com sucesso!\n");
    } else {
        printf("Mapa cheio!\n");
    }
}

// lista todos os territórios cadastrados
void listarTerritorios(struct Territorio *mapa, int totalTerritorios) {
    if (totalTerritorios == 0) {
        printf("Nenhum território cadastrado.\n");
    } else {
        for (int i = 0; i < totalTerritorios; i++) {
            printf("Território %d: %s - Cor: %s\n", i+1, mapa[i].nome, mapa[i].cor);
        }
    }
}

// distribui tropas entre os territórios
void distribuirTropas(struct Territorio* mapa, int totalTerritorios) {
    if (totalTerritorios == 0) {
        printf("Nenhum território cadastrado para distribuir tropas.\n");
        return;
    }
    for (int i = 0; i < totalTerritorios; i++) {
        printf("Digite o número de tropas para o território %s (cor: %s): ", mapa[i].nome, mapa[i].cor);
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();
    }
}

// executa ataque entre dois territórios
void executarAtaque(struct Territorio* mapa, int totalTerritorios) {
    if (totalTerritorios < 2) {
        printf("É necessário ter pelo menos 2 territórios cadastrados para realizar um ataque.\n");
        return;
    }
    int numAtacante, numDefensor;
    printf("Digite o número do território atacante: ");
    scanf("%d", &numAtacante);
    limparBufferEntrada();
    printf("Digite o número do território defensor: ");
    scanf("%d", &numDefensor);
    limparBufferEntrada();
    if (numAtacante >= 1 && numAtacante <= totalTerritorios &&
        numDefensor >= 1 && numDefensor <= totalTerritorios) {
        atacar(&mapa[numAtacante - 1], &mapa[numDefensor - 1]);
    } else {
        printf("Número de território inválido!\n");
    }
}

void verificarMissaoJogador(char* missaoJogador, struct Territorio* mapa, int totalTerritorios, int* opcao) {
    // Missão: eliminar tropas azuis
    if (strcmp(missaoJogador, "Eliminar o exército azul") == 0) {
        int existeAzul = 0;
        for (int i = 0; i < totalTerritorios; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0 && mapa[i].tropas > 0) {
                existeAzul = 1;
                break;
            }
        }
        if (!existeAzul) {
            printf("Missão cumprida! Você eliminou todas as tropas azuis.\n");
            *opcao = 0;
            return;
        } else {
            printf("Missão ainda não cumprida.\n");
        }
    }

    // Missão: eliminar tropas pretas
    if (strcmp(missaoJogador, "Eliminar o exército preto") == 0) {
        int existePreto = 0;
        for (int i = 0; i < totalTerritorios; i++) {
            if (strcmp(mapa[i].cor, "preto") == 0 && mapa[i].tropas > 0) {
                existePreto = 1;
                break;
            }
        }
        if (!existePreto) {
            printf("Missão cumprida! Você eliminou todas as tropas pretas.\n");
            *opcao = 0;
            return;
        } else {
            printf("Missão ainda não cumprida.\n");
        }
    }

    // Missão: eliminar tropas vermelhas
    if (strcmp(missaoJogador, "Eliminar todas as tropas da cor vermelha") == 0) {
        int existeVermelho = 0;
        for (int i = 0; i < totalTerritorios; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0 && mapa[i].tropas > 0) {
                existeVermelho = 1;
                break;
            }
        }
        if (!existeVermelho) {
            printf("Missão cumprida! Você eliminou todas as tropas vermelhas.\n");
            *opcao = 0;
            return;
        } else {
            printf("Missão ainda não cumprida.\n");
        }
    }

    // Missão: eliminar tropas verdes
    if (strcmp(missaoJogador, "Eliminar o exército verde") == 0) {
        int existeVerde = 0;
        for (int i = 0; i < totalTerritorios; i++) {
            if (strcmp(mapa[i].cor, "verde") == 0 && mapa[i].tropas > 0) {
                existeVerde = 1;
                break;
            }
        }
        if (!existeVerde) {
            printf("Missão cumprida! Você eliminou todas as tropas verdes.\n");
            *opcao = 0;
            return;
        } else {
            printf("Missão ainda não cumprida.\n");
        }
    }

    // Missão: eliminar tropas amarelas
    if (strcmp(missaoJogador, "Eliminar o exército amarelo") == 0) {
        int existeAmarelo = 0;
        for (int i = 0; i < totalTerritorios; i++) {
            if (strcmp(mapa[i].cor, "amarelo") == 0 && mapa[i].tropas > 0) {
                existeAmarelo = 1;
                break;
            }
        }
        if (!existeAmarelo) {
            printf("Missão cumprida! Você eliminou todas as tropas amarelas.\n");
            *opcao = 0;
            return;
        } else {
            printf("Missão ainda não cumprida.\n");
        }
    }

    // Missão: eliminar tropas brancas
    if (strcmp(missaoJogador, "Eliminar o exército branco") == 0) {
        int existeBranco = 0;
        for (int i = 0; i < totalTerritorios; i++) {
            if (strcmp(mapa[i].cor, "branco") == 0 && mapa[i].tropas > 0) {
                existeBranco = 1;
                break;
            }
        }
        if (!existeBranco) {
            printf("Missão cumprida! Você eliminou todas as tropas brancas.\n");
            *opcao = 0;
            return;
        } else {
            printf("Missão ainda não cumprida.\n");
        }
    }

    // Caso a missão não seja uma dessas
    printf("Verificação de missão ainda não implementada para: %s\n", missaoJogador);
}


// lógica de ataque (dados e resultado)
// Função que executa a lógica de ataque entre dois territórios
// Recebe ponteiros para o território atacante e defensor
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    // Verifica se o atacante e o defensor são da mesma cor
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Ataque inválido! Você não pode atacar um território da própria cor.\n");
        return;
    }

    // Verificação de tropas mínimas do atacante
    if (atacante->tropas <= 1) {
        printf("O atacante precisa ter mais de 1 tropa para atacar.\n");
        return;
    }

    // Verificação de tropas mínimas do defensor
    if (defensor->tropas <= 0) {
        printf("O defensor não tem tropas para resistir.\n");
        return;
    }

    // Sorteia os dados (valores de 1 a 6)
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    // Exibe os resultados dos dados
    printf("Dado do atacante (%s): %d\n", atacante->nome, dadoAtacante);
    printf("Dado do defensor (%s): %d\n", defensor->nome, dadoDefensor);

    // Verifica quem venceu a rolagem
    if (dadoAtacante > dadoDefensor) {
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
        strcpy(defensor->cor, atacante->cor);
        printf("Ataque bem-sucedido! %s conquista %s.\n", atacante->nome, defensor->nome);
    } else {
        atacante->tropas -= 1;
        printf("Ataque falhou! %s defende com sucesso.\n", defensor->nome);
    }

    // Exibe o status atualizado dos territórios
    printf("Status atualizado:\n");
    printf("Território: %s | Cor: %s | Tropas: %d\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Território: %s | Cor: %s | Tropas: %d\n", defensor->nome, defensor->cor, defensor->tropas);
}



//função para liberar memória
void liberarMemoria(struct Territorio* mapa, char* missaoJogador) {
    free(mapa);
    free(missaoJogador);
}

//função para sair do jogo
void sairJogo() {
    printf("\nEncerrando o jogo... Obrigado por jogar!\n");
}
