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

static void funcd(DP x, DP& fn, DP& df)
{
  fn = bessj0(x);
  df = -bessj1(x);
}

static DP fx1(DP x) {
  return 10 * pow(K_E, -x) * sin(2 * K_PI * x) - 2;
}

static DP fx2(DP x) {
  return pow(x, 2) - 2 * x * pow(K_E, -x) + pow(K_E, -2 * x);
}

static DP fx3(DP x) {
  return cos(x + sqrt(2)) + x * (x / 2 + sqrt(2));
}

static DP fx4(DP x) {
  return sin(pow(K_E,(1 + x)) * x) * cos(3 * K_E);
}

static void one(DP x, DP& fn, DP& df) {
  fn = fx1(x);
  df = 10 * pow(K_E, -x) * (2 * K_PI * cos(2 * K_PI * x) - sin(2 * K_PI * x));
}

static void two(DP x, DP& fn, DP& df) {
  fn = fx2(x);
  df = 2*pow(K_E,(-2*x))*(pow(K_E,x)+1) * (pow(K_E, x) * x - 1);
}

static void three(DP x, DP& fn, DP& df) {
  fn = fx3(x);
  df = sqrt(2) + x - sin(sqrt(2) + x);
}

static void four(DP x, DP& fn, DP& df) {
  fn = fx4(x);
  df = pow(K_E, 1 + x) * (1 + x) * cos(3 * K_E) * cos(pow(K_E, (1 + x))* x);
}

int main() {
  cout << setprecision(49);
  Vec_O_DP xb1(NBMAX), xb2(NBMAX);
  int nb;

  zbrak(fx, X1, X2, N, xb1, xb2, nb);

  printf("\nbrackets for roots of bessj0:\n");
  printf("%21s %10s %16s %10s\n", "lower", "upper", "f(lower)", "f(upper)");
  for (int i = 0; i < nb; i++)
    printf("%s %2d  %10.4f %10.4f %3s %10.4f %10.4f\n",
      "  root ", i, xb1[i], xb2[i], " ",
      fx(xb1[i]), fx(xb2[i]));

  // Bisection method
  printf("\nRoots of bessj0 (Bisection method):\n");
  printf("%7c %24s\n", 'i', "x");
  for (int i = 0; i < nb; i++) {
    double xacc = (1.0e-6)*(xb1[i] + xb2[i]) / 2.0;
    double root = rtbis(fx, xb1[i], xb2[i], xacc);
    cout << "root  " << i << "  " << root << endl;
  }

  // Linear interpolation method
  printf("\nRoots of bessj0 (Linear interpolation method):\n");
  printf("%7c %24s\n", 'i', "x");
  for (int i = 0; i < nb; i++) {
    double xacc = (1.0e-6)*(xb1[i] + xb2[i]) / 2.0;
    double root = rtflsp(fx, xb1[i], xb2[i], xacc);
    cout << "root  " << i << "  " << root << endl;
  }

  // Secant method
  printf("\nRoots of bessj0 (Secant method):\n");
  printf("%7c %24s\n", 'i', "x");
  for (int i = 0; i < nb; i++) {
    double xacc = (1.0e-6)*(xb1[i] + xb2[i]) / 2.0;
    double root = rtsec(fx, xb1[i], xb2[i], xacc);
    cout << "root  " << i << "  " << root << endl;
  }

  // Newton-Raphson method
  printf("\nRoots of bessj0 (Newton-Raphson method):\n");
  printf("%7c %24s\n", 'i', "x");
  for (int i = 0; i < nb; i++) {
    double xacc = (1.0e-6)*(xb1[i] + xb2[i]) / 2.0;
    double root = rtnewt(funcd, xb1[i], xb2[i], xacc);
    cout << "root  " << i << "  " << root << endl;
  }

  // Newton with bracketing method
  printf("\nRoots of bessj0 (Newton with bracketing method):\n");
  printf("%7c %24s\n", 'i', "x");
  for (int i = 0; i < nb; i++) {
    double xacc = (1.0e-6)*(xb1[i] + xb2[i]) / 2.0;
    double root = rtsafe(funcd, xb1[i], xb2[i], xacc);
    cout << "root  " << i << "  " << root << endl;
  }

  // Equation 1
  xb1 = 0;
  xb2 = 0;
  zbrak(fx1, 0.1, 1.0, N, xb1, xb2, nb);
  printf("\nRoots of #1 (Newton with bracketing method):\n");
  printf("%7c %24s\n", 'i', "x");
  for (int i = 0; i < nb; i++) {
    double xacc = (1.0e-6)*(xb1[i] + xb2[i]) / 2.0;
    double root = rtsafe(one, xb1[i], xb2[i], xacc);
    cout << "root  " << i << "  " << root << endl;
  }

  // Equation 2
  xb1 = 0;
  xb2 = 0;
  zbrak(fx2, 0.0, 1.0, N, xb1, xb2, nb);
  printf("\nRoots of #2 (Newton with bracketing method):\n");
  printf("%7c %24s\n", 'i', "x");
  for (int i = 0; i < nb; i++) {
    double xacc = (1.0e-6)*(xb1[i] + xb2[i]) / 2.0;
    double root = rtsafe(two, xb1[i], xb2[i], xacc);
    cout << "root  " << i << "  " << root << endl;
  }

  // Equation 3
  xb1 = 0;
  xb2 = 0;
  zbrak(fx3, -2.0, -1.0, N, xb1, xb2, nb);
  printf("\nRoots of #3 (Newton with bracketing method):\n");
  printf("%7c %24s\n", 'i', "x");
  for (int i = 0; i < nb; i++) {
    double xacc = (1.0e-6)*(xb1[i] + xb2[i]) / 2.0;
    double root = rtsafe(three, xb1[i], xb2[i], xacc);
    cout << "root  " << i << "  " << root << endl;
  }

  // Equation 4 (not interesting)
  xb1 = 0;
  xb2 = 0;
  zbrak(fx4, 0.0, 1.4, N, xb1, xb2, nb);
  printf("\nRoots of #4 (Newton with bracketing method):\n");
  printf("%7c %24s\n", 'i', "x");
  for (int i = 0; i < nb; i++) {
    double xacc = (1.0e-6)*(xb1[i] + xb2[i]) / 2.0;
    double root = rtsafe(four, xb1[i], xb2[i], xacc);
    cout << "root  " << i << "  " << root << endl;
  }

  return 0;
}
