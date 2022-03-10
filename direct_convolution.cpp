#include <random>
#include <iostream>

#define MAX_N 8//64
#define MIN_N 8
#define MAX_K 11
#define MIN_K 1

using namespace std;

/** For generating random inputs **/
template <typename T = uniform_int_distribution<mt19937::result_type>>
static inline int randn(int low, int high) {
  random_device dev;
  mt19937 rng(dev());
  T prng(low, high);
  return prng(rng);
}

static inline int* generate_grayscale_image(unsigned int n) {
  int *result = new int[n*n];
  for (int i=0; i<n*n; ++i)
    result[i] = randn(0, 255);
  return result;
}

void print_image(int image[], unsigned int n) {
  for (int i=0; i<n; ++i) {
    for (int j=0; j<n; ++j)
      cout << image[i*n + j] << "\t";
    cout << endl << endl;
  }
}

int main(void) {
  // Main steps:
  // 1. generate random test images
  int n = randn(MIN_N, MAX_N);
  int *input_image = generate_grayscale_image(n);
  // 2. implement direct convolution
  print_image(input_image, n);
  // 3. verify results somehow
  // 4. implement matmul convolution
  // 5. verify and cross-check results
  delete[] input_image;
  return 0;
}
