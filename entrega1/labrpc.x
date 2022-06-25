#define MAXVET 500000

struct vetor {
  float v[MAXVET];
};

program ENTREGA1 {
  version VERSAO {
    float max(vetor *) = 1;
    float min(vetor *) = 2;
  } = 100;
} = 88888;