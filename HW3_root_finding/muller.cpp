// Numerical Analysis HW3: Root Finding

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#include <cmath>

#include "NRs\nr.h"
#include "NRs\nrutil.h"

using namespace std;
using namespace NR;

const double X1 = 1.0;
const double X2 = 10.0;
const int N = 10000;
const int NBMAX = 100;
const double K_E = 2.71828182845904523536;
const double K_PI = 3.14159265358979323846;

static DP fx(DP x)
{
  return bessj0(x);
}

double muller(DP func(const DP), const DP x1_, const DP x2_, const DP acc) {
  double result = 0.0;
  const int MAXIT = 30;

  DP h0, h1, d0, d1, a, b, c, sqrt_disc;
  DP x0 = x1_;
  DP x2 = (x1_ + x2_) / 2;
  DP x1 = x2_;
  DP x3 = 0;

  for (int i = 0; i < MAXIT; ++i) {
    h0 = x1 - x0;
    h1 = x2 - x1;
    d0 = (func(x1) - func(x0)) / h0;
    d1 = (func(x2) - func(x1)) / h1;
    a = (d1 - d0) / (h1 + h0);
    b = a * h1 + d1;
    c = func(x2);
    if (isnan(a) || isnan(b) || isnan(c))
      break;
    sqrt_disc = sqrt(b*b - 4 * a*c);
    if (abs(b + sqrt_disc) > abs(b - sqrt_disc))
      x3 = x2 + (-2 * c) / (b + sqrt_disc);
    else
      x3 = x2 + (-2 * c) / (b - sqrt_disc);

    result = x3;

    if (abs(x3) < acc*x3)
      break;

    x0 = x1;
    x1 = x2;
    x2 = x3;
  }

  return result;
}

int main() {
  cout << setprecision(49);
  Vec_O_DP xb1(NBMAX), xb2(NBMAX);
  int nb;

  zbrak(fx, X1, X2, N, xb1, xb2, nb);

  // Muller method
  printf("\nRoots of bessj0 (Muller method):\n");
  printf("%7c %24s\n", 'i', "x");
  for (int i = 0; i < nb; i++) {
    double root = muller(fx, xb1[i], xb2[i], 1.0e-6);
    cout << "root  " << i << "  " << root << endl;
  }

  return 0;
}
