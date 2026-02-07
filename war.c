// Incluindo as bibliotecas padrão necessárias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Para usar a função rand() para simular ataques aleatórios

// definindo variaveis globais
// OBS: Tanto o numero de territorios, quanto o numero de objetivos foram definidos a mais do que o pedido com a intenção de seguir o jogo real
#define NUM_TERRITORIOS 42
#define NUM_OBJETIVOS 14


// Criando o Struct territorio
struct Territorio{
    char nome[30];
    char cor[10];
    int tropas;
};

// função para limpar o buffer de entrada
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void distribuirTropas(struct Territorio* mapa, int totalTerritorios){
    for (int i = 0; i < totalTerritorios; i++){
        printf("Digite o numero de tropas para o territorio %s (cor do exercito: %s): ", mapa[i].nome, mapa[i].cor);
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();
    }
}

// função para simular ataque entre territorios.
void atacar(struct Territorio* atacante, struct Territorio* defensor){
    if (strcmp(atacante->cor, defensor->cor) == 0){
        printf("Ataque invalido! Voce nao pode atacar um territorio da propria cor.\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1; // Gera um número aleatório entre 1 e 6
    int dadoDefensor = rand() % 6 + 1; // Gera um número aleatório entre 1 e 6

    printf("Dado do atacante (%s): %d\n", atacante->nome, dadoAtacante);
    printf("Dado do defensor (%s): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor){
        printf("Ataque bem-sucedido! %s conquista %s.\n", atacante->nome, defensor->nome);
        int tropasTransferidas = atacante->tropas / 2; // Transfere metade das tropas do atacante para o defensor
        defensor->tropas = tropasTransferidas; // O defensor agora tem as tropas transferidas
        atacante->tropas -= tropasTransferidas; // O atacante perde as tropas transferidas
        strcpy(defensor->cor, atacante->cor); // O defensor agora tem a mesma cor do atacante
    }else{
        printf("Ataque falhou! %s defende com sucesso.\n", defensor->nome);
        atacante->tropas -= 1; // O atacante perde 1 tropa em caso de falha
    }

    // Exibe os dados atualizados dos territórios após o ataque
    printf("Status atualizado:\n");
    printf("Territorio: %s, Cor: %s, Tropas: %d\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Territorio: %s, Cor: %s, Tropas: %d\n", defensor->nome, defensor->cor, defensor->tropas);
}

//crie uma função void liberarMemoria(Territorio* mapa) para liberar o espaço alocado.
void liberarMemoria(struct Territorio* mapa){
    free(mapa);
}

int main(){
    //utilizar calloc ou malloc para alocar memória para um vetor de struct Territorio com tamanho informado pelo usuário.
    struct Territorio* mapa = (struct Territorio*)calloc(NUM_TERRITORIOS, sizeof(struct Territorio));
    int totalTerritorios = 0;
    int opcao;
    int *distropas = (int*)malloc(NUM_TERRITORIOS * sizeof(int));
  
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    // --- Laço Principal do Menu ---
    do
    {
        printf("----------------------------------------------------------------\n");
        printf("               Menu Principal\n");
        printf("----------------------------------------------------------------\n");
        printf("1 Regras do jogo\n");
        printf("2 - Cadastrar novo Territorio e cor do exercito\n");
        printf("3 - Listar todos os Territorios e cor do exercito\n");
        printf("4 - Distribuir tropas entre os territorios\n");
        printf("5 - Atacar um territorio\n");
        printf("0 - Sair\n");
        printf("----------------------------------------------------------------\n");
        printf("Escolha uma opcao: ");

        // Lê a opção do usuário
        scanf("%d", &opcao);
        limparBufferEntrada(); // Limpa o '\n' deixado pelo scanf.

        // função switch para navegar entre as opções do menu
        switch(opcao){
            case 1: // REGRAS DO JOGO
                printf(" --- Regras do jogo ---\n\n");
                printf("O objetivo do jogo e conquistar o mundo dominando todos os territorios ou cumprindo uma missao secreta.\n");
                printf("Cada jogador comeca com um numero de tropas que podem ser distribuídas entre os territorios que possui.\n");
                printf("Em cada turno, o jogador pode atacar territorios vizinhos para conquistar mais areas e ganhar mais tropas.\n");
                printf("O jogo termina quando um jogador conquista todos os territorios ou cumpre sua missao secreta.\n");

                printf("\nPrecione Enter para continuar...");
                getchar(); // Pausa para o usuario ler a mensagem antes de voltar ao menu.
                break;

            case 2: // CADASTRO DE TERRITORIO
                printf(" --- cadastro de novo Territorio ---\n\n");
                
                // uso de fgets para ler o nome do territorio e a cor do exercito, garantindo que o buffer seja limpo corretamente
                // condição para evitar que o usuario cadastre mais territorios do que o permitido pelo jogo, garantindo a integridade do mapa e evitando erros de memoria
                if (totalTerritorios < NUM_TERRITORIOS){
                    printf("Digite o nome do territorio: ");
                    fgets(mapa[totalTerritorios].nome, 30, stdin);

                    printf("Digite a cor do exercito que domina o territorio: ");
                    fgets(mapa[totalTerritorios].cor, 10, stdin);
                    
                    // uso de strcspn para remover o caractere de nova linha ('\n') adicionado pelo fgets, garantindo que a string seja terminada corretamente
                    mapa[totalTerritorios].nome[strcspn(mapa[totalTerritorios].nome, "\n")] = '\0';
                    mapa[totalTerritorios].cor[strcspn(mapa[totalTerritorios].cor, "\n")] = '\0';

                    totalTerritorios++;

                    printf("\nTerritorio cadastrado com sucesso!\n");
                }else{
                    printf("Mapa cheio! nao e possivel cadastrar mais territorios.\n");
                }

                printf("\nPrecione Enter para continuar...");
                getchar(); // Pausa para o usuario ler a mensagem antes de voltar ao menu.
                break;

            case 3: // LISTAGEM DE TERRITORIOS E COR DO EXERCITO
                printf(" ---Lista de Territorios Cadastrados e cor do exercito ---\n\n");

                if (totalTerritorios == 0){
                    printf("Nenhum territorio cadastrado ainda.\n");
                }else{
                    for (int i = 0; i < totalTerritorios; i++) {
                        printf("-----------------------------------\n");
                        printf("TERRITORIO %d\n", i + 1);
                        printf("Nome: %s\n", mapa[i].nome);
                        printf("Cor do exercito: %s\n", mapa[i].cor);
                        printf("-----------------------------------\n");
                    }
                // A pausa é crucial para que o usuário veja a lista antes
                // do próximo loop limpar a tela.
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            
            case 4: // DISTRIBUIR TROPAS ENTRE OS TERRITORIOS
                printf(" --- Distribuir tropas entre os territorios ---\n\n");
                if (totalTerritorios == 0){
                    printf("Nenhum territorio cadastrado para distribuir tropas.\n");
                }else{
                    distribuirTropas(mapa, totalTerritorios);
                }

                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 5: // ATACAR UM TERRITORIO, VALIDANDO AS ESCOLHAS DO USUÁRIO PARA EVITAR ATAQUES INVÁLIDOS
                printf(" --- Atacar um territorio ---\n\n");
                if (totalTerritorios < 2){
                    printf("E necessario ter pelo menos 2 territorios cadastrados para realizar um ataque.\n");
                }else{
                    printf("Digite o numero do territorio atacante: ");
                    int numAtacante;
                    scanf("%d", &numAtacante);
                    limparBufferEntrada();

                    printf("Digite o numero do territorio defensor: ");
                    int numDefensor;
                    scanf("%d", &numDefensor);
                    limparBufferEntrada();

                    // Validação das escolhas do usuário para garantir que os números sejam válidos e que o ataque seja permitido
                    if (numAtacante >= 1 && numAtacante <= totalTerritorios && numDefensor >= 1 && numDefensor <= totalTerritorios){
                        atacar(&mapa[numAtacante - 1], &mapa[numDefensor - 1]);
                    }else{
                        printf("Numero de territorio invalido! Certifique-se de escolher territorios existentes.\n");
                    }
                }

                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 0: // SAIR
                printf("Encerrando o programa. VAMOS JOGAR NOVAMENTE EM BREVE!\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
                }
        }
    }while (opcao != 0);
    
    // Libera a memória alocada para o mapa
    liberarMemoria(mapa);

    return 0;
}
