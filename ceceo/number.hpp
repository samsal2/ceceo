#ifndef CECEO_NUMBER_HPP_
#define CECEO_NUMBER_HPP_

namespace ceceo {

namespace detail {

// TODO (samuel) floating point and bigint
using integer = int;

} // namespace detail

class number {
public:
  constexpr number(detail::integer value) noexcept : value_(value) {}

  constexpr auto value() const noexcept { return value_; }

private:
  detail::integer value_;
};

} // namespace ceceo

#endif
