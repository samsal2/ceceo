#ifndef CECEO_SYMBOL_HPP_
#define CECEO_SYMBOL_HPP_

#include <string_view>

namespace ceceo {

class symbol {
public:
  constexpr explicit symbol(std::string_view name) noexcept : name_(name) {}

  constexpr std::string_view value() noexcept { return name_; }

private:
  std::string_view name_;
};

} // namespace ceceo

#endif
