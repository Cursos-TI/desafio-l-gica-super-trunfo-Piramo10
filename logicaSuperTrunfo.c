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

// Carregar carta com dados fixos para simplificação
void carregarCartaExemplo(Carta *c, const char *nome) {
    if (strcmp(nome, "Carta 1") == 0) {
        strcpy(c->nome, "São Paulo");
        strcpy(c->estado, "SP");
        strcpy(c->codigo, "SP");
        c->populacao = 12300000;
        c->area = 1500.0;
        c->pib = 6000.0;
        c->pontos_turisticos = 50;
    } else {
        strcpy(c->nome, "Rio de Janeiro");
        strcpy(c->estado, "RJ");
        strcpy(c->codigo, "RJ");
        c->populacao = 6000000;
        c->area = 1200.0;
        c->pib = 4000.0;
        c->pontos_turisticos = 30;
    }
    c->densidade = c->populacao / c->area;
    c->pib_per_capita = c->pib / c->populacao;
}

// Exibir dados da carta
void exibirCarta(Carta c) {
    printf("\n--- %s ---\n", c.nome);
    printf("Estado: %s\n", c.estado);
    printf("Código: %s\n", c.codigo);
    printf("População: %d\n", c.populacao);
    printf("Área: %.2f\n", c.area);
    printf("PIB: %.2f\n", c.pib);
    printf("Pontos turísticos: %d\n", c.pontos_turisticos);
    printf("Densidade: %.2f\n", c.area);
    printf("PIB per Capita: %.2f\n", c.area);
}

// Obter valor do atributo
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

// Menu de seleção de atributos
int menuAtributo(const char *exclusao) {
    int opcao;
    printf("\nEscolha um atributo:\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Densidade Demográfica\n");
    printf("5 - PIB per Capita\n");
    printf("%s", exclusao);
    printf("Opção (1-5): ");
    scanf("%d", &opcao);
    if (opcao < 1 || opcao > 5) {
        printf("Opção inválida!\n");
        return 0; // inválido
    }
    return opcao;
}

// Comparar atributos com regras
const char* compararAtributos(Carta c1, Carta c2, int atributo) {
    float v1 = obterValorAtributo(c1, atributo);
    float v2 = obterValorAtributo(c2, atributo);
    const char* nomeAtrib;
    switch (atributo) {
        case 1: nomeAtrib = "População"; break;
        case 2: nomeAtrib = "Área"; break;
        case 3: nomeAtrib = "PIB"; break;
        case 4: nomeAtrib = "Densidade Demográfica"; break;
        case 5: nomeAtrib = "PIB per Capita"; break;
        default: nomeAtrib = "";
    }

    printf("\n--- Resultado da comparação ---\n");
    printf("Atributo: %s\n", nomeAtrib);
    printf("%s - %s: %.2f\n", (atributo == 1 ? "Carta 1" : "Carta 2"), c1.nome, v1);
    printf("%s - %s: %.2f\n", (atributo == 1 ? "Carta 2" : "Carta 2"), c2.nome, v2);

    // Regras de vitória
    if (atributo == 4) { // Densidade menor vence
        if (v1 < v2)
            return c1.nome;
        else if (v1 > v2)
            return c2.nome;
    } else { // Maior valor vence
        if (v1 > v2)
            return c1.nome;
        else if (v1 < v2)
            return c2.nome;
    }
    return "Empate";
}

int main() {
    Carta c1, c2;
    int atributos[2] = {0, 0};

    // Carregar cartas
    carregarCartaExemplo(&c1, "Carta 1");
    carregarCartaExemplo(&c2, "Carta 2");

    // Exibir cartas
    exibirCarta(c1);
    exibirCarta(c2);

    // Seleção do primeiro atributo
    printf("\nEscolha o primeiro atributo:");
    atributos[0] = menuAtributo(" (não pode repetir)\n");
    while (atributos[0] == 0) {
        atributos[0] = menuAtributo(" (não pode repetir)\n");
    }

    // Seleção do segundo atributo
    printf("\nEscolha o segundo atributo:");
    atributos[1] = menuAtributo(" (não pode repetir)\n");
    while (atributos[1] == 0 || atributos[1] == atributos[0]) {
        if (atributos[1] == atributos[0]) {
            printf("Atributo já selecionado. Escolha outro.\n");
        }
        atributos[1] = menuAtributo(" (não pode repetir)\n");
    }

    // Comparação individual
    const char* vencedor1 = compararAtributos(c1, c2, atributos[0]);
    const char* vencedor2 = compararAtributos(c1, c2, atributos[1]);

    // Valores dos atributos
    float vA1_1 = obterValorAtributo(c1, atributos[0]);
    float vA2_1 = obterValorAtributo(c2, atributos[0]);

    float vA1_2 = obterValorAtributo(c1, atributos[1]);
    float vA2_2 = obterValorAtributo(c2, atributos[1]);

    // Soma dos atributos
    float soma1 = vA1_1 + vA1_2;
    float soma2 = vA2_1 + vA2_2;

    // Exibir resumo
    printf("\n--- Resumo da rodada ---\n");
    printf("%s vs %s\n", c1.nome, c2.nome);
    printf("Atributos utilizados:\n");
    printf("1 - %s: %.2f (Carta 1), %.2f (Carta 2)\n",
        (atributos[0]==1?"População":atributos[0]==2?"Área":atributos[0]==3?"PIB":"Densidade"),
        vA1_1, vA2_1);
    printf("2 - %s: %.2f (Carta 1), %.2f (Carta 2)\n",
        (atributos[1]==1?"População":atributos[1]==2?"Área":atributos[1]==3?"PIB":"Densidade"),
        vA1_2, vA2_2);

    printf("Soma dos atributos:\n");
    printf("%s: %.2f\n", c1.nome, soma1);
    printf("%s: %.2f\n", c2.nome, soma2);

    // Vencedor geral
    if (soma1 > soma2)
        printf("Vencedor geral: %s\n", c1.nome);
    else if (soma1 < soma2)
        printf("Vencedor geral: %s\n", c2.nome);
    else
        printf("Empate!\n");

    return 0;
}