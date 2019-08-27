#include "geometry.h"
#include <math.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define diferenca 0.000001

int verify(point p, point a, point b) {

  double deltaY = (b.y - a.y);
  double deltaX = (b.x - a.x);
  if (fabs(deltaX) <= diferenca) {
    deltaX = diferenca;               // vertical
    if ((p.x >= a.x) && (p.x <= b.x)) // tem o ponto
    {
      if (((p.y > a.y) && (p.y <= b.y)) || ((p.y > b.y) && (p.y <= a.y))) // Bem a ponta da reta/  
        return 2;
    }
  }
  double m = deltaY / deltaX; // coeficiente angular da reta
  
  if ((p.x >= MIN(a.x, b.x)) && (p.x <= MAX(a.x, b.x))) // limitando x
  {

    if (fabs(p.x - a.x) <= diferenca && fabs(p.y - a.y) <= diferenca) // reta no ponto comparar o ponto A 336 testes
      return 2;
    if (fabs(p.x - b.x) <= diferenca && fabs(p.y - b.y) <= diferenca) // reta no ponto comparar o ponto B 336 testes                               
      return 2;
    if (fabs(p.y - (a.y + m * (p.x - a.x))) <= diferenca) // Reta abaixo do ponto, 336 testes 
      return 2;
  }
  // Limitando o y
  if ((p.y > MIN(a.y, b.y)) && (p.y <= MAX(a.y, b.y))) {
    if (p.x < MIN(a.x, b.x)) // reta atras do ponto, nao cruzando 124 testes
      return 1;
    if ((p.y - a.y < m * (p.x - a.x)) && (m <= 0)) 
      return 1; // m negativo reta descrescente 
    if ((p.y - a.y > m * (p.x - a.x)) && (m >= 0))
      return 1; // m positivo
  }
  return 0;
}

int inside(point p, point poly[], int n) {

  int a = 0;
  int b = verify(p, poly[0], poly[n - 1]);

  if (b == 2) {
    return 1;
  }
  a += b;
  for (int i = 0; i <= n - 2; i++) {
    int r = verify(p, poly[i], poly[i + 1]);
    if (r == 2) {
      return 1;
    } else if (r == 1) {
      a += 1;
    }
  }
  if ((a % 2 == 1)) {
    return 1;
  }
  return 0;
}
