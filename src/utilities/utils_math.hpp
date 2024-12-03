//
// Created by maksym on 12/2/24.
//
#include <math.h>

#ifndef CV_TRICKS_UTILS_MATH_HPP

class GaussianOscillation {
 public:
  double gauss_peak_width = 0;
  double period = 0;
  double min_scaled_value = 0;
  double max_scaled_value = 0;
  double min_value = 0;
  double max_value = 0;
  double input_shift = 0;

  GaussianOscillation() = default;

  GaussianOscillation(double gauss_peak_width,
                      double period,
                      double min_scaled_value,
                      double max_scaled_value,
                      double input_shift = 0)
      : gauss_peak_width(gauss_peak_width),
        period(period),
        min_scaled_value(min_scaled_value),
        max_scaled_value(max_scaled_value),
        input_shift(input_shift) {
    auto max_input = period / 2;
    auto min_input = period;

    max_value = compute_envelope(max_input);
    min_value = compute_envelope(min_input);
  }

  [[nodiscard]] double compute_envelope(double input) const {
    auto gaussian_envelope =
        std::exp(gauss_peak_width *
                 std::pow(std::sin(M_PI * (input + input_shift) / period), 2));
    return gaussian_envelope;
  }

  [[nodiscard]] double compute(double input) const {
    auto gaussian_envelope = compute_envelope(input);
    auto scaled = (gaussian_envelope - min_value) / (max_value - min_value) *
                      (max_scaled_value - min_scaled_value) +
                  min_scaled_value;
    return scaled;
  }
};

#define CV_TRICKS_UTILS_MATH_HPP

#endif  // CV_TRICKS_UTILS_MATH_HPP
