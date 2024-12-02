//
// Created by maksym on 12/2/24.
//
#include <math.h>

#ifndef CV_TRICKS_UTILS_MATH_HPP

class GaussianOscillation {
 public:
  double gauss_alpha;
  double period;
  double min_scaled_value;
  double max_scaled_value;
  double min_value = 0;
  double max_value = 0;

  GaussianOscillation(double gauss_alpha,
                      double period,
                      double min_scaled_value,
                      double max_scaled_value)
      : gauss_alpha(gauss_alpha),
        period(period),
        min_scaled_value(min_scaled_value),
        max_scaled_value(max_scaled_value) {
    auto max_input = period / 2;
    auto min_input = period;

    max_value = compute_envelope(max_input);
    min_value = compute_envelope(min_input);
  }

  [[nodiscard]] double compute_envelope(double input) const {
    auto gaussian_envelope =
        std::exp(gauss_alpha * std::pow(std::sin(M_PI * input / period), 2));
    return gaussian_envelope;
  }

  [[nodiscard]] double compute(double input) const {
    auto gaussian_envelope = compute_envelope(input);
    auto scaled = (gaussian_envelope - min_value) /
                      (min_scaled_value - min_value) *
                      (max_scaled_value - min_scaled_value) +
                  min_scaled_value;
    return scaled;
  }
};

#define CV_TRICKS_UTILS_MATH_HPP

#endif  // CV_TRICKS_UTILS_MATH_HPP
