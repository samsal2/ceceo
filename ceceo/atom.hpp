#ifndef CECEO_ATOM_HPP_
#define CECEO_ATOM_HPP_

#include <ceceo/number.hpp>
#include <ceceo/symbol.hpp>
#include <iostream>

namespace ceceo {

class atom {
  struct null_type {};

public:
  enum class type { symbol, number, null };

  static constexpr auto null = null_type{};

  constexpr atom([[maybe_unused]] null_type type) noexcept
      : type_(type::null), storage_(0) {}

  constexpr explicit atom(symbol symbol) noexcept
      : type_(type::symbol), storage_(symbol) {}

  constexpr explicit atom(number number) noexcept
      : type_(type::number), storage_(number) {}

  constexpr auto as_symbol() const {
    if (type::symbol != type_)
      throw std::runtime_error("atom::type::symbol");

    return storage_.as_symbol;
  }

  constexpr auto as_number() const {
    if (type::number != type_)
      throw std::runtime_error("atom::type::number");

    return storage_.as_number;
  }

  constexpr auto is_null() const { return type::null == type_; }

  constexpr auto type() const { return type_; }

private:
  // TODO compare compile time perf against variant
  enum type type_;

  union storage {
    constexpr storage(symbol symbol) noexcept : as_symbol(symbol) {}
    constexpr storage(number number) noexcept : as_number(number) {}

    symbol as_symbol;
    number as_number;
  };

  storage storage_;
};

inline std::ostream &operator<<(std::ostream &os, atom atom) {
  switch (atom.type()) {
  case atom::type::null:
    os << "null";
    break;
  case atom::type::number:
    os << atom.as_number().value();
    break;
  case atom::type::symbol:
    os << atom.as_symbol().value();
    break;
  }

  return os;
}

} // namespace ceceo

#endif
