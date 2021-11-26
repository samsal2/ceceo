#ifndef CECEO_BADGE_HPP_
#define CECEO_BADGE_HPP_

namespace ceceo {

template <typename T> class badge {
  friend T;
  consteval badge() noexcept = default;
};

} // namespace ceceo

#endif
