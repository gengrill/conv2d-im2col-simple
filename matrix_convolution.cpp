/** g++ matrix_convolution.cpp -o matrix_convolution **/
#include "conv.h"

float *im2col
(
  float *image,
  unsigned int n,
  unsigned int k
) {
  float *matrix = new float[n*n * k*k];
  for (auto x=0U; x<n*n; ++x) {
    for (auto y=0U; y<k*k; ++y) {
      auto _i = y%k; auto _j = y/k;
      auto _x = x%n; auto _y = x/n;
      matrix[y*n*n + x] = pad_coord(image, n, _x+_i-k/2, _y+_j-k/2);
    }
  }
  return matrix;
}

float* matrix_convolution
(
  float *image,
  float *filter,
  unsigned int n,
  unsigned int k
) {
  float *matrix = im2col(image, n, k);
  //  print_image(matrix, k*k, n*n);
  float *result = new float[n*n]();
  auto frows = 1;
  auto fcols = k*k;
  //auto mrows = k*k;
  auto mcols = n*n;
  for (auto j=0U; j<n; ++j) {
    for (auto i=0U; i<n; ++i) {
      for (auto m=0U; m<fcols; ++m) {
        //auto F = filter[m];
        auto F = flip_kernel(filter, k, m%k, m/k);
        auto G = matrix[m*mcols + j*n + i];
        result[j*n + i] += F * G;
      }
    }
  }
  delete[] matrix;
  return result;
}

int main(void) {
  int n = randn(MIN_N, MAX_N);
  int k = (k=randn(MIN_K, MAX_K)) & 1 ? k : k+1; // odd k
  //int *input_image = generate_grayscale_image(n);
  //float *float_image = im2float(input_image, n);
  float float_image[] = {
    1, 2, 3, 4, 5,
    6, 7, 8, 9, 1,
    2, 3, 4, 5, 6,
    7, 8, 9, 1, 2,
    3, 4, 5, 6, 7,
  };
  print_image(float_image, n);
  //float *filter = generate_filter(k);
  float filter[] = {
    1, 0, 1,
    0, 1, 0,
    1, 0, 0,
  };
  print_image(filter, k);
  float *filtered = matrix_convolution(float_image, filter, n, k);
  print_image(filtered, n);
  //delete[] input_image;
  //delete[] float_image;
  //delete[] filter;
  delete[] filtered;
  return 0;
}
