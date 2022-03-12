#include "conv.h"

/**
 * Construct a (kxk)x(nxn) matrix in memory from nxn input image.
 * Each kxk long column contains all pixels for one convolution.
 **/
float *im2col
(
  const float *image,
  const unsigned int n,
  const unsigned int k
) {
  float *matrix = new float[n*n * k*k];
  for (auto x=0U; x<n*n; ++x) {
    for (auto y=0U; y<k*k; ++y) {
      auto _i = y%k; auto _j = y/k; // offset from center point
      auto _x = x%n; auto _y = x/n; // center point of conv window
      matrix[y*n*n + x] = pad_coord(image, n, _x+_i-k/2, _y+_j-k/2);
    }
  }
  return matrix;
}

/**
 * Matrix convolution (2D Linear Discrete Cross-Correlation).
 * Inputs are nxn image and kxk kernel, output is nxn ('same' mode).
 * Temporarily constructs (kxk)x(nxn) matrix in memory to compute
 * cross-correlation as matrix multiplication with flattened filter.
 **/
float* matrix_convolution
(
  const float *image,
  const float *filter,
  const unsigned int n,
  const unsigned int k
) {
  float *matrix = im2col(image, n, k);
  float *result = new float[n*n]();
  auto fcols = k*k;
  auto mcols = n*n;
  for (auto j=0U; j<n; ++j) {
    for (auto i=0U; i<n; ++i) {
      for (auto m=0U; m<fcols; ++m) {
        auto F = flip_kernel(filter, k, m%k, m/k);
        auto G = matrix[m*mcols + j*n + i];
        result[j*n + i] += F * G;
      }
    }
  }
  delete[] matrix;
  return result;
}

