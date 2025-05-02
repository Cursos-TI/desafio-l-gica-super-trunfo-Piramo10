#include <stdio.h>
#include <string.h>

// Definição da estrutura da carta
typedef struct {
    char estado[50];
    char codigo[20];
    char nome[50];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade;       // Calculado: populacao / area
    float pib_per_capita;  // Calculado: pib / populacao
} Carta;

// Função para cadastrar uma carta
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
    
    // Calculando densidade populacional e PIB per capita
    c->densidade = c->populacao / c->area;
    c->pib_per_capita = c->pib / c->populacao;
}

// Função para exibir as informações de uma carta (opcional)
void exibirCarta(Carta c) {
    printf("\n--- %s ---\n", c.nome);
    printf("Estado: %s\n", c.estado);
    printf("Código: %s\n", c.codigo);
    printf("População: %d\n", c.populacao);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: %.2f milhões\n", c.pib);
    printf("Pontos turísticos: %d\n", c.pontos_turisticos);
    printf("Densidade populacional: %.2f\n", c.densidade);
    printf("PIB per capita: %.2f\n", c.pib_per_capita);
}

// Função para obter o valor do atributo a ser comparado
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

// Função para fazer a comparação e exibir o resultado
void compararCartas(Carta c1, Carta c2, int atributo) {
    float val1 = obterValorAtributo(c1, atributo);
    float val2 = obterValorAtributo(c2, atributo);
    
    // Nome do atributo para exibição
    const char *nomeAtributo;
    switch (atributo) {
        case 1: nomeAtributo = "População"; break;
        case 2: nomeAtributo = "Área"; break;
        case 3: nomeAtributo = "PIB"; break;
        case 4: nomeAtributo = "Densidade Populacional"; break;
        case 5: nomeAtributo = "PIB per Capita"; break;
        default: nomeAtributo = "";
    }
    
    printf("\nComparação de cartas (Atributo: %s):\n", nomeAtributo);
    printf("Carta 1 - %s: %.2f\n", c1.nome, val1);
    printf("Carta 2 - %s: %.2f\n", c2.nome, val2);
    
    // Regra de comparação
    if (atributo == 4) { // Densidade - menor vence
        if (val1 < val2)
            printf("Resultado: Carta 1 (%s) venceu!\n", c1.nome);
        else if (val1 > val2)
            printf("Resultado: Carta 2 (%s) venceu!\n", c2.nome);
        else
            printf("Resultado: Empate!\n");
    } else { // Outros atributos - maior vence
        if (val1 > val2)
            printf("Resultado: Carta 1 (%s) venceu!\n", c1.nome);
        else if (val1 < val2)
            printf("Resultado: Carta 2 (%s) venceu!\n", c2.nome);
        else
            printf("Resultado: Empate!\n");
    }
}

int main() {
    Carta carta1, carta2;
    int atributoEscolhido = 1; // 1-População, 2-Área, 3-PIB, 4-Densidade, 5-PIB per Capita

    // Cadastro das cartas
    lerCarta(&carta1, "Carta 1");
    lerCarta(&carta2, "Carta 2");
    
    // Opcional: exibir detalhes das cartas
    exibirCarta(carta1);
    exibirCarta(carta2);

    // Realizar a comparação
    compararCartas(carta1, carta2, atributoEscolhido);

    return 0;
}
