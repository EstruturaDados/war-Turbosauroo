#include <stdio.h>
#include <stdlib.h>

// Definindo uma struct para representar um território
// Uso do "typedef" permite declarar variáveis do tipo "territorio" sem escrever "struct" sempre
typedef struct {
    char nome[50];  // Nome do território
    char cor[10];   // Cor do território (indicando quem domina)
    int tropas;     // Quantidade de tropas no território
} territorio;

int main() {
    int i;  // Variável de controle para os laços de repetição
    territorio cadastro[5];  // Array de 5 territórios usando a struct "territorio"
	
	printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n");
	
    // Loop para cadastrar os 5 territórios
    for(i = 0; i < 5; i++){
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);

        printf("Nome do Territorio: \n");
        fgets(cadastro[i].nome, 50, stdin); // Lê uma linha de texto, incluindo espaços, até o Enter ou limite do array

        printf("Cor do Territorio (ex: Azul, Verde...): \n");
        fgets(cadastro[i].cor, 10, stdin); // Lê a cor do território

        printf("Numero de Tropas: \n");
        scanf("%d", &cadastro[i].tropas); // Lê o número de tropas
        getchar(); // Limpa o '\n' deixado pelo scanf para não atrapalhar o próximo fgets
    }

    printf("\nCadastro concluido com sucesso!!!\n\n");

    // Loop para exibir os dados cadastrados
    for(i = 0; i < 5; i++){
        printf("TERRITORIO %d:\n", i + 1);
        printf(" - Nome: %s", cadastro[i].nome);  // fgets já inclui o '\n'
        printf(" - Dominado por: %s", cadastro[i].cor);
        printf(" - Tropas: %d\n\n", cadastro[i].tropas);
    }

    return 0;
}
