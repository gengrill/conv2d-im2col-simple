/** g++ direct_convolution.cpp -o direct_convolution **/
#include "conv.h"

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
      float G = pad_coord(image, n, x+i-k/2, y+j-k/2);
      float F = flip_kernel(filter, k, i, j);
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
  float *result = new float[n*n]();
  for (int y=0; y<n; ++y) {
    for (int x=0; x<n; ++x) {
      convolve(result, image, filter, x, y, n, k);
    }
  }
  return result;
}

int main(void) {
  int n = randn(MIN_N, MAX_N);
  int k = (k=randn(MIN_K, MAX_K)) & 1 ? k : k+1; // odd k
  int *input_image = generate_grayscale_image(n);
  float *float_image = im2float(input_image, n);
  print_image(float_image, n);
  float *filter = generate_filter(k);
  print_image(filter, k);
  float *filtered = direct_convolution(float_image, filter, n, k);
  print_image(filtered, n);
  delete[] input_image;
  delete[] float_image;
  delete[] filter;
  delete[] filtered;
  return 0;
}
