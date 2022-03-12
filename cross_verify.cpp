#include <random>
#include <iostream>

#define EPSILON 1e-7
#define MAX_N 64
#define MIN_N 7
#define MAX_K 11
#define MIN_K 1

using namespace std;

template <typename S, typename T = uniform_int_distribution<mt19937::result_type>>
static inline S randn(S low, S high) {
  random_device dev;
  mt19937 rng(dev());
  T prng(low, high);
  return prng(rng);
}

static inline int* generate_grayscale_image(const unsigned int n) {
  int *result = new int[n*n];
  for (auto i=0U; i<n*n; ++i)
    result[i] = randn(0, 255);
  return result;
}

static inline float* im2float(int image[], const unsigned int n) {
  float *result = new float[n*n];
  for (auto i=0U; i<n*n; ++i)
    result[i] = image[i]/255.0f;
  return result;
}

static inline float* generate_filter(unsigned int k) {
  using unireal=uniform_real_distribution<float>;
  float *result = new float[k*k]();
  for (auto i=0U; i<k*k; ++i)
    result[i] = randn<float, unireal>(0.0f, 1.0f);
  return result;
}

template <typename T>
static inline void print_image
(
  T const image[],
  const unsigned int n,
  const unsigned int m
) {
  cout << fixed;
  cout.precision(8);
  for (auto i=0U; i<n; ++i) {
    cout << "[";
    for (auto j=0U; j<m; ++j)
      cout << image[i*m + j] << ", ";
    cout << "]," << endl;
  }
  cout << endl;
}

template <typename T>
static inline void print_image
(
  T image[],
  const unsigned int n
) {
  print_image(image, n, n);
}
extern float* matrix_convolution
(
  const float *image,
  const float *filter,
  const unsigned int n,
  const unsigned int k
);

extern float *im2col
(
  const float *image,
  const unsigned int n,
  const unsigned int k
);

float* direct_convolution
(
  const float *image,
  const float *filter,
  const unsigned int n,
  const unsigned int k
);

/** Returns true if abs(one-two) <= epsilon else false **/
static inline bool float_equal(float one, float two, float eps=EPSILON) {
  return abs(one-two) <= eps;
}

/**
 * Element-wise comparison of two nxn single-precision matrices.
 **/
bool cross_verify
(
  float *first,
  float *second,
  const unsigned int n
) {
  for (auto i=0U; i<n; ++i)
    for (auto j=0U; j<n; ++j)
      if (!float_equal(first[i*n + j], second[i*n + j]))
        return false;
  return true;
}

int main(void) {
  int result = 0;
  int n = randn(MIN_N, MAX_N);
  int k = (k=randn(MIN_K, MAX_K))&1 ? k : k+1; // odd k
  int *input_image = generate_grayscale_image(n);
  float *float_image = im2float(input_image, n);
  float *filter = generate_filter(k);
  float *direct_filtered = direct_convolution(float_image, filter, n, k);
  float *matrix_filtered = matrix_convolution(float_image, filter, n, k);
  if (cross_verify(direct_filtered, matrix_filtered, n)) {
    print_image(float_image, n);  
    print_image(filter, k);
    print_image(matrix_filtered, n);
  } else {
    result = 1;
    cerr << "Results don't match!" << endl;
  }
  delete[] input_image;
  delete[] float_image;
  delete[] filter;
  delete[] direct_filtered;
  delete[] matrix_filtered;
  return result;
}
