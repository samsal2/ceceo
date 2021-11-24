#ifndef CECEO_BADGE_HPP_
#define CECEO_BADGE_HPP_

namespace ceceo {

template <typename T> class badge {
  friend T;
  badge() = default;
};

} // namespace ceceo

#endif
