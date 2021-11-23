#ifndef CECEO_SOURCE_RANGE_HPP_
#define CECEO_SOURCE_RANGE_HPP_

#include <string_view>

namespace ceceo {

namespace detail {

template <typename T>
concept integral = std::is_integral_v<T>;

template <typename T> using difference = typename T::difference_type;

template <typename T> constexpr auto as_difference(integral auto v) noexcept {
  return static_cast<difference<T>>(v);
}

} // namespace detail

class source_range {
public:
  constexpr source_range() noexcept = default;

  constexpr explicit source_range(std::string_view source) noexcept
      : from_(0), to_(size(source)), source_(source) {}

  constexpr source_range(std::string_view source, std::size_t from,
                         std::size_t to) noexcept
      : from_(from), to_(to), source_(source) {}

  constexpr auto value() const noexcept {
    auto const at = detail::as_difference<std::string_view>(from_);
    return std::string_view(std::next(begin(source_), at), to_ - from_);
  }

  constexpr auto from() const noexcept { return from_; }

  constexpr auto to() const noexcept { return to_; }

  constexpr auto source() const noexcept { return source_; }

  static constexpr auto merge(source_range lhs, source_range rhs) noexcept {
    return source_range{lhs.source(), lhs.from(), rhs.to()};
  }

private:
  std::size_t from_ = 0;
  std::size_t to_ = 0;
  std::string_view source_ = {};
};


} // namespace ceceo

#endif
