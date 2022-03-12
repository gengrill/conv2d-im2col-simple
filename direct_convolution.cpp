/** g++ direct_convolution.cpp -o direct_convolution **/
#include <random>
#include <iostream>

#define MAX_N 3//64
#define MIN_N 3//7
#define MAX_K 2//11
#define MIN_K 2//1

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
  float *result = new float[k];
  for (int i=0; i<k*k; ++i)
    result[i] = randn<float, unireal>(0.0f, 1.0f);
  return result;
}

template <typename T>
static inline void print_image(T image[], unsigned int n) {
  cout << fixed;
  cout.precision(6);
  for (int i=0; i<n; ++i) {
    for (int j=0; j<n; ++j)
      cout << image[i*n + j] << ", ";
    cout << endl << endl;
  }
}

static inline float get_coord
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

static inline void convolve
(
  float *result,
  float *image,
  float *filter,
  int x,
  int y,
  unsigned int n,
  unsigned int k
) {
  for (int j=0; j<k; ++j) {
    for (int i=0; i<k; ++i) {
      int _x = x+i-k/2; int _y = y+j-k/2;
      float G = get_coord(image, n, _x, _y);
      float F = filter[j*k + i]; // TODO: flip and rotate F
      result[y*n + x] += F * G;
    }
  }
}

float* direct_convolution
(
  float *image,
  float *filter,
  unsigned int n,
  unsigned int k
) {
  float *result = new float[n]();
  for (int y=0; y<n; ++y) {
    for (int x=0; x<n; ++x) {
      convolve(result, image, filter, x, y, n, k);
    }
  }
  return result;
}

int main(void) {
  // Main steps:
  // 1. generate random test images
  int n = randn(MIN_N, MAX_N);
  int *input_image = generate_grayscale_image(n);
  print_image(input_image, n);
  float *float_image = im2float(input_image, n);
  print_image(float_image, n);
  // 2. implement direct convolution
  int k = randn(MIN_K, MAX_K);
  float *filter = generate_filter(k);  
  print_image(filter, k);
  float *filtered = direct_convolution(float_image, filter, n, k);
  print_image(filtered, n);
  // 3. verify results somehow
  // 4. implement matmul convolution
  // 5. verify and cross-check results
  delete[] input_image;
  delete[] float_image;
  delete[] filter;
  delete[] filtered;
  return 0;
}
