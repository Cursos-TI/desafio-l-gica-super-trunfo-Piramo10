#include <stdio.h>
#include <string.h>

// Estrutura da carta
typedef struct {
    char estado[50];
    char codigo[20];
    char nome[50]; // nome da cidade/país
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade;       // calculada: populacao / area
    float pib_per_capita;  // calculada: pib / populacao
} Carta;

// Função para cadastro de uma carta
void lerCarta(Carta *c, const char *nome_carta) {
    printf("=== Cadastro da %s ===\n", nome_carta);
    printf("Estado: ");
    scanf("%49s", c->estado);
    printf("Código da carta: ");
    scanf("%19s", c->codigo);
    printf("Nome da cidade: ");
    scanf("%49s", c->nome);
    printf("População: ");
    scanf("%d", &c->populacao);
    printf("Área (km²): ");
    scanf("%f", &c->area);
    printf("PIB (milhões de dólares): ");
    scanf("%f", &c->pib);
    printf("Número de pontos turísticos: ");
    scanf("%d", &c->pontos_turisticos);

    c->densidade = c->populacao / c->area;
    c->pib_per_capita = c->pib / c->populacao;
}

// Função para exibir os dados da carta
void exibirCarta(Carta c) {
    printf("\n--- %s ---\n", c.nome);
    printf("Estado: %s\n", c.estado);
    printf("Código: %s\n", c.codigo);
    printf("População: %d\n", c.populacao);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: %.2f milhões\n", c.pib);
    printf("Pontos turísticos: %d\n", c.pontos_turisticos);
    printf("Densidade: %.2f\n", c.densidade);
    printf("PIB per Capita: %.2f\n", c.pib_per_capita);
}

// Obter valor do atributo pelo índice
float obterValorAtributo(Carta c, int atributo) {
    switch (atributo) {
        case 1: return (float)c.populacao;
        case 2: return c.area;
        case 3: return c.pib;
        case 4: return c.densidade;
        case 5: return c.pib_per_capita;
        default: return 0;
    }
}

// Função de comparação com as regras
void compararCartas(Carta c1, Carta c2, int atributo) {
    float valor1 = obterValorAtributo(c1, atributo);
    float valor2 = obterValorAtributo(c2, atributo);
    const char *atributoNome;
    switch (atributo) {
        case 1: atributoNome = "População"; break;
        case 2: atributoNome = "Área"; break;
        case 3: atributoNome = "PIB"; break;
        case 4: atributoNome = "Densidade Demográfica"; break;
        case 5: atributoNome = "PIB per Capita"; break;
        default: atributoNome = "";
    }

    printf("\n--- Resultado da Comparação ---\n");
    printf("Atributo utilizado: %s\n", atributoNome);
    printf("%s: %s - %.2f\n", (atributo == 1 ? "País 1" : "Carta 1"), c1.nome, valor1);
    printf("%s: %s - %.2f\n", (atributo == 1 ? "País 2" : "Carta 2"), c2.nome, valor2);

    // Regra de comparação
    if (atributo == 4) { // Densidade, menor vence
        if (valor1 < valor2)
            printf("Resultado: %s vence!\n", c1.nome);
        else if (valor1 > valor2)
            printf("Resultado: %s vence!\n", c2.nome);
        else
            printf("Empate!\n");
    } else { // Outros atributos, maior vence
        if (valor1 > valor2)
            printf("Resultado: %s vence!\n", c1.nome);
        else if (valor1 < valor2)
            printf("Resultado: %s vence!\n", c2.nome);
        else
            printf("Empate!\n");
    }
}

// Função do menu interativo
int menu() {
    int opcao;
    printf("\nEscolha o atributo para comparar:\n");
    printf("1 - Nome da Cidade (não usado para comparação)\n");
    printf("2 - População\n");
    printf("3 - Área\n");
    printf("4 - PIB\n");
    printf("5 - Número de Pontos Turísticos\n");
    printf("6 - Densidade Demográfica\n");
    printf("Escolha (1-6): ");
    scanf("%d", &opcao);
    return opcao;
}

int main() {
    Carta c1, c2;
    int atributoEscolhido;

    // Cadastro das cartas
    lerCarta(&c1, "Carta 1");
    lerCarta(&c2, "Carta 2");

    // Exibir cartas cadastradas
    exibirCarta(c1);
    exibirCarta(c2);

    // Menu interativo
    atributoEscolhido = menu();

    // Validar entrada
    if (atributoEscolhido < 1 || atributoEscolhido > 6) {
        printf("Opção inválida!\n");
        return 1;
    }

    // Caso o usuário escolha "nome da cidade" (opção 1), apenas exibir mensagem
    if (atributoEscolhido == 1) {
        printf("O nome da cidade não é usado para comparação.\n");
        printf("Por favor, escolha um atributo numérico para a comparação.\n");
        return 1;
    }

    // Comparar as cartas com base no atributo escolhido
    compararCartas(c1, c2, atributoEscolhido);

    return 0;
}