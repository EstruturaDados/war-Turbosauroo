#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// =========================
// Struct para representar um território
// =========================
typedef struct {
    char nome[50]; // Nome do território
    char cor[10];  // Cor do exército que domina
    int tropas;    // Quantidade de tropas no território
} Territorio;

// =========================
// Função para ler dados de um território
// Recebe o ponteiro de um Territorio
// =========================
void lerTerritorio(Territorio* t) {
    printf("Nome do Territorio: ");
    fgets(t->nome, 50, stdin); // lê string incluindo espaços
    t->nome[strcspn(t->nome, "\n")] = '\0'; // remove o '\n' gerado pelo Enter

    printf("Cor do Territorio (ex: Azul, Verde...): ");
    fgets(t->cor, 10, stdin);
    t->cor[strcspn(t->cor, "\n")] = '\0'; // remove '\n'

    printf("Numero de Tropas: ");
    scanf("%d", &t->tropas); // lê inteiro
    getchar(); // limpa o '\n' do buffer para não interferir no próximo fgets
}

// =========================
// Função para mostrar todos os territórios
// =========================
void mostrarMapa(Territorio* cadastro, int n) {
    printf("\n--- MAPA ATUAL ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n",
               i + 1, cadastro[i].nome, cadastro[i].cor, cadastro[i].tropas);
    }
}

// =========================
// Função para validar escolhas de ataque
// Retorna 1 se válido, 0 se inválido
// =========================
int validarEscolha(int* escolha, int n) {
    // Atacante e defensor não podem ser o mesmo
    if (escolha[0] == escolha[1]) {
        printf("Atacante nao pode ser o mesmo defensor!!!\n");
        return 0;
    }
    // Verifica se escolhas estão dentro do intervalo válido
    if (escolha[0] < 1 || escolha[0] > n || escolha[1] < 1 || escolha[1] > n) {
        printf("Escolha fora do intervalo valido (1 a %d)!!!\n", n);
        return 0;
    }
    printf("Escolhas validas, pode prosseguir com o ataque.\n");
    return 1;
}

// =========================
// Função de ataque entre dois territórios
// =========================
void atacar(Territorio* atacante, Territorio* defensor) {
    srand(time(NULL)); // inicializa a semente para números aleatórios

    // Gera números aleatórios de 1 a 6
    int dado_atacante = (rand() % 6) + 1;
    int dado_defensor = (rand() % 6) + 1;

    printf("\n--- FASE DE ATAQUE ---\n");
    printf("Atacante %s rolou: %d\n", atacante->nome, dado_atacante);
    printf("Defensor %s rolou: %d\n", defensor->nome, dado_defensor);

    // Compara os dados e decrementa tropas do perdedor
    if (dado_atacante > dado_defensor) {
        printf("Atacante vence!\n");
        if (defensor->tropas > 0) defensor->tropas--;
    } else {
        printf("Defensor vence!\n");
        if (atacante->tropas > 1) atacante->tropas--;
    }
}

// =========================
// Função principal
// =========================
int main() {
    int n = 5;          // número de territórios
    int escolha[2];     // vetor com escolhas de ataque (atacante e defensor)
    int opcao;          // opção do menu

    // Aloca dinamicamente vetor de territórios usando calloc
    Territorio* cadastro = calloc(n, sizeof(Territorio));
    if (cadastro == NULL) { // checa se a alocação deu certo
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    printf("Vamos cadastrar os %d territorios iniciais do nosso mundo.\n", n);
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);
        lerTerritorio(&cadastro[i]); // chama função para preencher os dados
    }

    printf("\nCadastro concluido com sucesso!!!\n");

    // Loop principal do menu
    do {
        printf("\n*** MENU ***\n");
        printf("1. Atacar\n2. Mostrar mapa\n3. Sair\n");
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        if (opcao == 2) {
            mostrarMapa(cadastro, n); // mostra mapa atualizado
        } else if (opcao == 3) {
            printf("*** Fechando o jogo ***\n");
            break;
        } else if (opcao == 1) {
            
            // Escolha do território atacante
            printf("\nEscolha o territorio atacante (1 a %d): ", n);
            scanf("%d", &escolha[0]);
            getchar();

            // Escolha do território defensor
            printf("Escolha o territorio defensor (1 a %d): ", n);
            scanf("%d", &escolha[1]);
            getchar();

            // Valida e realiza ataque se válido
            if (validarEscolha(escolha, n)) {
                atacar(&cadastro[escolha[0]-1], &cadastro[escolha[1]-1]);
            }
        } else {
            printf("Escolha uma opcao valida!!!\n");
        }

    } while (opcao != 3);

    free(cadastro); // libera memória alocada dinamicamente
    return 0;
}

