
#include <cmath>

namespace Easing {
inline float easeInQuad(float x) { return x * x; }

inline float easeOutQuad(float x) { return 1 - (1 - x) * (1 - x); }

inline float easeOutQuart(float x) { return 1 - std::pow(1 - x, 4); }

inline float easeInOutQuad(float x) {
  return x < 0.5 ? 2 * x * x : 1 - std::pow(-2 * x + 2, 2) / 2;
}

inline float easeInBack(float x) {
  float c1 = 1.70158;
  float c3 = c1 + 1;

  return c3 * x * x * x - c1 * x * x;
}

inline float easeOutBounce(float x) {
  float n1 = 7.5625;
  float d1 = 2.75;

  if (x < 1 / d1) {
    return n1 * x * x;
  } else if (x < 2 / d1) {
    return n1 * (x -= 1.5 / d1) * x + 0.75;
  } else if (x < 2.5 / d1) {
    return n1 * (x -= 2.25 / d1) * x + 0.9375;
  } else {
    return n1 * (x -= 2.625 / d1) * x + 0.984375;
  }
}
} // namespace Easing
