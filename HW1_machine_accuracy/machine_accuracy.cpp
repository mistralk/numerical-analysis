// Numerical Analysis HW1: Machine Accuracy
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Find minimum n that satisfies 1 + 2^(-n) = 1
// Then, 2^(-n) is the machine accuracy(machine epsilon)
// which is the smallest floating-point number.
template <typename T>
T get_eps() {
  int n;
  T base = static_cast<T>(2);
  int bits_num = sizeof(T) * 8;
  for (n = 0; n < bits_num; ++n) {
    if (1 + pow(base, -n) == 1) {
      n--;
      break;
    }
  }
  return pow(base, -n);
}

/*
template <typename T>
T get_eps_NR() {
  removed for copyright (from NR in C)
}*/

int main() {
  cout << setprecision(53);

  cout << "Machine accuracy with my get_eps()" << endl;
  cout << "float: " << get_eps<float>() << endl;
  cout << "double: " << get_eps<double>() << endl;

  return 0;
}