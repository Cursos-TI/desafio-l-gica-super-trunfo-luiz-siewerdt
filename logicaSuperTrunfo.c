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

void compararPopulacao(Carta *c1, Carta *c2, float *soma1, float *soma2) {
  printf("Comparando População:\n");
  printf("Carta 1: %d\n", c1->populacao);
  printf("Carta 2: %d\n", c2->populacao);
  if (c1->populacao > c2->populacao) {
    printf("Carta 1 venceu!!\n");
  } else if (c1->populacao < c2->populacao) {
    printf("Carta 2 venceu!!\n");
  }
  *soma1 += c1->populacao;
  *soma2 += c2->populacao;
}

void compararArea(Carta *c1, Carta *c2, float *soma1, float *soma2) {
  printf("Comparando Área:\n");
  printf("Carta 1: %f\n", c1->area);
  printf("Carta 2: %f\n", c2->area);
  if (c1->area > c2->area) {
    printf("Carta 1 venceu!!\n");
  } else if (c1->area < c2->area) {
    printf("Carta 2 venceu!!\n");
  }
  *soma1 += c1->area;
  *soma2 += c2->area;
}

void compararPIB(Carta *c1, Carta *c2, float *soma1, float *soma2) {
  printf("Comparando PIB:\n");
  printf("Carta 1: %.2f\n", c1->pib);
  printf("Carta 2: %.2f\n", c2->pib);
  if (c1->pib > c2->pib) {
    printf("Carta 1 venceu!!\n");
  } else if (c1->pib < c2->pib) {
    printf("Carta 2 venceu!!\n");
  }
  *soma1 += c1->pib;
  *soma2 += c2->pib;
}

void compararPontosTuristicos(Carta *c1, Carta *c2, float *soma1,
                              float *soma2) {
  printf("Comparando Pontos Turísticos:\n");
  printf("Carta 1: %d\n", c1->pontosTuristicos);
  printf("Carta 2: %d\n", c2->pontosTuristicos);
  if (c1->pontosTuristicos > c2->pontosTuristicos) {
    printf("Carta 1 venceu!!\n");
  } else if (c1->pontosTuristicos < c2->pontosTuristicos) {
    printf("Carta 2 venceu!!\n");
  }
  *soma1 += c1->pontosTuristicos;
  *soma2 += c2->pontosTuristicos;
}

void compararDensidade(Carta *c1, Carta *c2, float *soma1, float *soma2) {
  printf("Comparando Densidade Demográfica:\n");
  printf("Carta 1: %.2f\n", c1->densidade);
  printf("Carta 2: %.2f\n", c2->densidade);
  if (c1->densidade < c2->densidade) {
    printf("Carta 1 venceu!!\n");
  } else if (c1->densidade > c2->densidade) {
    printf("Carta 2 venceu!!\n");
  }
  *soma1 += c1->densidade;
  *soma2 += c2->densidade;
}

void cartaVitoriosa(Carta *c1, Carta *c2) {
  int input, input2;
  printf("\nSelecione dois atributos para comparar:\n");
  printf("1) População\n");
  printf("2) Área\n");
  printf("3) PIB\n");
  printf("4) Número de Pontos Turísticos\n");
  printf("5) Densidade Demográfica\n");

  printf("\nAtributo 1: ");
  scanf("%d", &input);

  printf("Atributo 2: ");
  scanf("%d", &input2);

  // Verificando se a entrada é válida
  if (input < 1 || input > 5 || input2 < 1 || input2 > 5 || input == input2) {
    printf("Opções inválidas! Tente novamente.\n");
    return;
  }

  float soma1 = 0.0, soma2 = 0.0;

  printf("\nComparando Carta 1 (%s) com Carta 2 (%s):\n\n", c1->estado,
         c2->estado);

  // Comparando os atributos escolhidos
  switch (input) {
  case 1:
    compararPopulacao(c1, c2, &soma1, &soma2);
    break;
  case 2:
    compararArea(c1, c2, &soma1, &soma2);
    break;
  case 3:
    compararPIB(c1, c2, &soma1, &soma2);
    break;
  case 4:
    compararPontosTuristicos(c1, c2, &soma1, &soma2);
    break;
  case 5:
    compararDensidade(c1, c2, &soma1, &soma2);
    break;
  }

  printf("\n");

  switch (input2) {
  case 1:
    compararPopulacao(c1, c2, &soma1, &soma2);
    break;
  case 2:
    compararArea(c1, c2, &soma1, &soma2);
    break;
  case 3:
    compararPIB(c1, c2, &soma1, &soma2);
    break;
  case 4:
    compararPontosTuristicos(c1, c2, &soma1, &soma2);
    break;
  case 5:
    compararDensidade(c1, c2, &soma1, &soma2);
    break;
  }

  // Exibindo as somas para cada carta
  printf("\nSoma dos Atributos para a Carta 1: %.2f\n", soma1);
  printf("Soma dos Atributos para a Carta 2: %.2f\n", soma2);

  // Verificando o vencedor
  if (soma1 > soma2) {
    printf("\nCarta 1 venceu!\n");
  } else if (soma2 > soma1) {
    printf("\nCarta 2 venceu!\n");
  } else {
    printf("\nEmpate!\n");
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
