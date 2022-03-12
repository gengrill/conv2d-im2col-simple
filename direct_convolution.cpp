#include "conv.h"

static inline void convolve
(
  float *result,
  const float *image,
  const float *filter,
  const int x,
  const int y,
  const unsigned int n,
  const unsigned int k
) {
  for (auto j=0U; j<k; ++j) {
    for (auto i=0U; i<k; ++i) {
      float G = pad_coord(image, n, x+i-k/2, y+j-k/2);
      float F = flip_kernel(filter, k, i, j);
      result[y*n + x] += F * G;
    }
  }
}

/**
 * Scalar direct convolution (2D Linear Discrete Cross-Correlation).
 * Inputs are nxn image and kxk kernel, output is nxn ('same' mode).
 **/
float* direct_convolution
(
  const float *image,
  const float *filter,
  const unsigned int n,
  const unsigned int k
) {
  float *result = new float[n*n]();
  for (auto y=0U; y<n; ++y) {
    for (auto x=0U; x<n; ++x) {
      convolve(result, image, filter, x, y, n, k);
    }
  }
  return result;
}
