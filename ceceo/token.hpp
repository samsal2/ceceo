#ifndef CECEO_TOKEN_HPP_
#define CECEO_TOKEN_HPP_

#include "ceceo/source_range.hpp"

namespace ceceo {

class token {
public:
  enum class type {
    none,
    left_parenthesis,
    right_parenthesis,
    atom,
    end
  };

  constexpr token() noexcept = default;

  constexpr token(source_range range, type type) noexcept
    : type_(type), range_(range) {}

  constexpr auto value() const noexcept { return range_.value(); }

  constexpr auto range() const noexcept { return range_; }

  constexpr auto type() const noexcept { return type_; }
  
  
private:
  enum type type_ = type::none;
  source_range range_ = {};
};

} // ceceo


#endif /* CECEO_TOKEN_HPP_ */



