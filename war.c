// Incluindo as bibliotecas padrão necessárias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(){
    struct Territorio mapa[NUM_TERRITORIOS];
    int totalTerritorios = 0;
    int opcao;

    // --- Laço Principal do Menu ---
    do
    {
        printf("----------------------------------------------------------------\n");
        printf("               Menu Principal\n");
        printf("----------------------------------------------------------------\n");
        printf("1 Regras do jogo\n");
        printf("2 - Cadastrar novo Territorio e cor do exercito\n");
        printf("3 - Listar todos os Territorios e cor do exercito\n");
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
                
            case 0: // SAIR
                printf("Encerrando o programa. VAMOS JOGAR NOVAMENTE EM BREVE!\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
                }
        }
    }while (opcao != 0);
    



    return 0;
}
