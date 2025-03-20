#include <stdio.h>
#include <string.h>

typedef struct {
  char estado[30];
  char codigoCarta[4];
  char cidade[256];
  int populacao;
  float area;
  float pib;
  int pontosTuristicos;
  float densidade;
  float pibPerCapita;
  float superPoder;
} Carta;

void getInput(char *input, size_t inputSize) {
  if (fgets(input, inputSize, stdin)) {
    size_t strSize = strlen(input);
    if (input[strSize - 1] == '\n' && strSize <= inputSize) {
      input[strSize - 1] = '\0';
    } else {
      int ch;
      while ((ch = getchar()) != '\n' && ch != EOF)
        ;
    }
  }
}

int isCharValid(char *ch, int min, int max, int haveUpercase) {
  int chASCII = (int)*ch;
  if (haveUpercase) {
    return chASCII >= min && chASCII <= max ||
           chASCII >= min + 32 && chASCII <= max + 32;
  } else {
    return chASCII >= min && chASCII <= max;
  }
}

Carta novaCarta(int numero) {
  printf("\n Formulário Carta %i:", numero);
  Carta c;
  int isValidCodigo = 0;

  printf("\n Digite o Estado: ");
  getInput(c.estado, sizeof(c.estado));

  do {
    printf("\n Digite o código: ");
    getInput(c.codigoCarta, sizeof(c.codigoCarta));
    if (isCharValid(&c.codigoCarta[0], 65, 72, 1) && c.codigoCarta[1] == '0' &&
        isCharValid(&c.codigoCarta[2], 49, 52, 0)) {
      isValidCodigo = 1;
    }
  } while (!isValidCodigo);

  printf("\n Digite o nome da cidade: ");
  getInput(c.cidade, sizeof(c.cidade));

  printf("\n Digite o número de população: ");
  scanf("%i", &c.populacao);

  printf("\n Digite a área da cidade (em km²): ");
  scanf("%f", &c.area);

  printf("\n Digite o PIB ");
  scanf("%f", &c.pib);

  printf("\n Digite o número de pontos turísticos: ");
  scanf("%i", &c.pontosTuristicos);

  getchar();

  return c;
}

void calcularDensidade(Carta *c) {
  c->densidade = (float)c->populacao / c->area;
}

void calcularPipPerCapita(Carta *c) {
  c->pibPerCapita = c->pib / (float)c->populacao;
}

void compararPopulacao(Carta *c1, Carta *c2) {
  if (c1->populacao > c2->populacao)

    printf("Carta 1 venceu na comparação de População!\n");
  else if (c1->populacao < c2->populacao)
    printf("Carta 2 venceu na comparação de População!\n");
  else

    printf("Empate na comparação de População!\n");
}

void compararArea(Carta *c1, Carta *c2) {
  if (c1->area > c2->area)
    printf("Carta 1 venceu na comparação de Área!\n");
  else if (c1->area < c2->area)
    printf("Carta 2 venceu na comparação de Área!\n");

  else
    printf("Empate na comparação de Área!\n");
}

void compararPIB(Carta *c1, Carta *c2) {
  if (c1->pib > c2->pib)
    printf("Carta 1 venceu na comparação de PIB!\n");
  else if (c1->pib < c2->pib)
    printf("Carta 2 venceu na comparação de PIB!\n");
  else
    printf("Empate na comparação de PIB!\n");
}

void compararPontosTuristicos(Carta *c1, Carta *c2) {
  if (c1->pontosTuristicos > c2->pontosTuristicos)
    printf("Carta 1 venceu na comparação de Pontos Turísticos!\n");
  else if (c1->pontosTuristicos < c2->pontosTuristicos)
    printf("Carta 2 venceu na comparação de Pontos Turísticos!\n");
  else
    printf("Empate na comparação de Pontos Turísticos!\n");
}

void compararDensidade(Carta *c1, Carta *c2) {
  if (c1->densidade < c2->densidade)

    printf("Carta 1 venceu na comparação de Densidade Demográfica!\n");
  else if (c1->densidade > c2->densidade)
    printf("Carta 2 venceu na comparação de Densidade Demográfica!\n");
  else
    printf("Empate na comparação de Densidade Demográfica!\n");
}

void cartaVitoriosa(Carta *c1, Carta *c2) {
  int input;
  printf("\nSelecione qual atributo comparar:\n");
  printf("1) Nome do país (Apenas para Exibir)\n");
  printf("2) População\n");
  printf("3) Área\n");
  printf("4) PIB\n");
  printf("5) Número de Pontos Turísticos\n");
  printf("6) Densidade Demográfica\n");

  scanf("%i", &input);

  if (input < 1 || input > 6) {
    printf("Opção inválida! Tente novamente.\n");

    return;
  }

  printf("\nComparando Carta 1 com Carta 2:\n");

  switch (input) {
  case 1:
    printf("Nome do país:\n");
    printf("Carta 1: %s\n", c1->estado);
    printf("Carta 2: %s\n", c2->estado);
    break;

  case 2:
    compararPopulacao(c1, c2);
    break;

  case 3:
    compararArea(c1, c2);
    break;

  case 4:
    compararPIB(c1, c2);
    break;

  case 5:
    compararPontosTuristicos(c1, c2);
    break;

  case 6:
    compararDensidade(c1, c2);
    break;
  }
}

void exibirCarta(Carta *c, int numeroCarta) {
  printf("\n --- Carta %i --- \n", numeroCarta);
  printf("Estado: %s\n", c->estado);
  printf("Codigo da Carta: %s\n", c->codigoCarta);
  printf("Cidade: %s\n", c->cidade);
  printf("População: %d\n", c->populacao);
  printf("Área: %.2f km²\n", c->area);
  printf("PIB: %.2f bilhões\n", c->pib);
  printf("Pontos Turísticos: %d\n", c->pontosTuristicos);
  printf("Densidade: %.2f habitantes por km²\n", c->densidade);
  printf("PIB per Capita: %.2f\n\n", c->pibPerCapita);
}

int main() {
  Carta carta = novaCarta(1);
  Carta carta2 = novaCarta(2);

  calcularDensidade(&carta);
  calcularDensidade(&carta2);

  calcularPipPerCapita(&carta);
  calcularPipPerCapita(&carta2);

  exibirCarta(&carta, 1);
  exibirCarta(&carta2, 2);

  cartaVitoriosa(&carta, &carta2);

  return 0;
}
