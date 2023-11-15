#ifndef PIPELINE_PROJECT_UTILS_HPP
#define PIPELINE_PROJECT_UTILS_HPP
#include <cmath>

// From: https://en.wikipedia.org/wiki/Fast_inverse_square_root
// Thank you Quake III
// Function for calculating the fast inverse square root
inline float q_rsqrt(float number)
{
  long i;
  float x2, y;
  const float threehalfs = 1.5F;

  x2 = number * 0.5F;
  y = number;
  i = *(long *)&y;            // evil floating point bit level hacking
  i = 0x5f3759df - (i >> 1);  // what the fuck?
  y = *(float *)&i;
  y = y * (threehalfs - (x2 * y * y));  // 1st iteration
  // y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

  return y;
}

constexpr auto almostEqual(double first, double second) -> bool
{
  constexpr auto kEpsilon{1e-5};

  return std::abs(first - second) < kEpsilon;
};

#endif  // PIPELINE_PROJECT_UTILS_HPP