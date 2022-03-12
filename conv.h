#ifndef CONV_H
#define CONV_H
#include <random>
#include <iostream>

#define MAX_N 5//64
#define MIN_N 5//7
#define MAX_K 3//1
#define MIN_K 3//1

using namespace std;

/** For generating random inputs **/
template <typename S, typename T = uniform_int_distribution<mt19937::result_type>>
static inline S randn(S low, S high) {
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

static inline float* im2float(int image[], unsigned int n) {
  float *result = new float[n*n];
  for (int i=0; i<n*n; ++i)
    result[i] = image[i]/255.0f;
  return result;
}

static inline float* generate_filter(unsigned int k) {
  using unireal=uniform_real_distribution<float>;
  float *result = new float[k*k]();
  for (int i=0; i<k*k; ++i)
    result[i] = randn<float, unireal>(0.0f, 1.0f);
  return result;
}

template <typename T>
static inline void print_image
(
  T image[],
  unsigned int n,
  unsigned int m
) {
  cout << fixed;
  cout.precision(8);
  for (int i=0; i<n; ++i) {
    cout << "[";
    for (int j=0; j<m; ++j)
      cout << image[i*m + j] << ", ";
    cout << "]," << endl;
  }
  cout << endl;
}

template <typename T>
static inline void print_image
(
  T image[],
  unsigned int n
) {
  print_image(image, n, n);
}

static inline float pad_coord
(
  float *image,
  unsigned int n,
  int x,
  int y,
  float def=0.0f
) {
  if (0 <= x && x < n)
    if (0 <= y && y < n)
      return image[y*n + x];
  return def;
}

static inline float flip_kernel
(
  float *filter,
  unsigned int k,
  int x,
  int y
) {
  return filter[(k+~y)*k + (k+~x)];
}

#endif // CONV_H
