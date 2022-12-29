#ifndef CECEO_TOKENIZER_HPP_
#define CECEO_TOKENIZER_HPP_

#include <ceceo/token.hpp>
#include <iostream>

namespace ceceo {

namespace detail {

template <typename Lhs, typename Rhs>
concept same_as = requires {
  requires std::is_same_v<Lhs, Rhs>;
  requires std::is_same_v<Rhs, Lhs>;
};

// TODO convertible_to
template <typename F>
concept consume_condition = requires(F &&fun, char c) {
  { std::forward<F>(fun)(c) } -> same_as<bool>;
};

// FIXME(samuel): this
static auto is_atom(char c) noexcept {
  return std::isalpha(c) || std::isdigit(c) || '+' == c || '-' == c ||
         '*' == c || '/' == c || '<' == c || '>' == c || '%' == c ||
         '\"' == c || '=' == c || '!' == c || '&' == c;
}

static auto is_whitespace(char c) noexcept {
  return ' ' == c || '\n' == c || '\t' == c;
}

} // namespace detail

class tokenizer {
public:
  explicit tokenizer(std::string_view source) noexcept : source_(source) {}

  token next_token();

  token previous() const noexcept { return previous_; }

  auto done() const noexcept { 
    return size(source_) + 1 == position_; 
  }

private:
  auto peek(size_t offset = 0) noexcept { return source_[position_ + offset]; }

  auto consume() noexcept {
    auto const start = std::exchange(position_, position_ + 1);
    return source_range(source_, start, position_);
  }

  template <typename Condition>
  requires detail::consume_condition<Condition>
  auto consume_while(Condition &&condition) noexcept {
    auto const start = position_;

    while (std::forward<Condition>(condition)(peek())) {
      consume();

      if (size(source_) == position_)
        break;
    }

    return source_range(source_, start, position_);
  }

  auto consume_whitespace() { 
    return consume_while(detail::is_whitespace); 
  }

  auto consume_atom() { 
    return consume_while(detail::is_atom); 
  }

  auto consume_string() {
    auto start = position_;
    consume(); // consume leading "
    consume_while([](auto c) { return '\"' != c; });
    consume(); // consume leading "

    return source_range(source_, start, position_);
  }

  token previous_ = {};
  std::size_t position_ = 0;
  std::string_view source_ = {};
};

} // namespace ceceo

#endif
