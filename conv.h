#ifndef CONV_H
#define CONV_H
static inline float pad_coord
(
  const float *image,
  int n,
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
  const float *filter,
  unsigned int k,
  int x,
  int y
) {
  return filter[(k+~y)*k + (k+~x)];
}
#endif // CONV_H
