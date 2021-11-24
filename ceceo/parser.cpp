#include <ceceo/ast/variable.hpp>
#include <ceceo/context.hpp>
#include <ceceo/parser.hpp>
#include <charconv>
#include <iostream>
#include <stdexcept>

namespace ceceo {

namespace detail {

constexpr auto is_number(std::string_view str) noexcept {
  if ('+' == str[0] || '-' == str[0]) {
    str.remove_prefix(1);

    if (0 == size(str))
      return false;
  }

  for (auto const c : str)
    if (!std::isdigit(c))
      return false;

  return true;
}

constexpr auto is_string(std::string_view str) noexcept {
  return '\"' == str.back() && '\"' == str.front();
}

}; // namespace detail

std::unique_ptr<ast::literal> parser::parse_literal(context const &context) {
  auto const token = tokenizer_.previous();

  if (detail::is_string(token.value()))
    return parse_string(context);

  if (!detail::is_number(token.value())) {
    consume(token::type::atom);
    return std::make_unique<ast::literal>(token.range(),
                                          atom(symbol(token.value())));
  }

  consume(token::type::atom);
  auto const str = std::string(begin(token.value()), size(token.value()));
  auto const value = std::atoi(str.c_str());

  return std::make_unique<ast::literal>(token.range(), atom(value));
}

std::unique_ptr<ast::variable>
parser::parse_variable([[maybe_unused]] context const &context) {
  auto const token = consume(token::type::atom);
  return std::make_unique<ast::variable>(token.range(),
                                         symbol(token.value()));
}

std::unique_ptr<ast::literal> parser::parse_string([[maybe_unused]] context const &context) {
  auto const token = consume(token::type::atom);
  auto value = token.value();

  if (!detail::is_string(token.value()))
    throw std::runtime_error("parser: invalid string");

  value.remove_prefix(1);
  value.remove_suffix(1);

  return std::make_unique<ast::literal>(token.range(), atom(symbol(value)));
}

std::unique_ptr<ast::list> parser::parse_list(context const &context) {
  auto const start = consume(token::type::left_parenthesis);
  auto list = std::vector<std::unique_ptr<ast::node>>();

  while (!tokenizer_.done()) {
    switch (tokenizer_.previous().type()) {
    case token::type::left_parenthesis:
      list.push_back(parse_list(context));
      break;

    case token::type::atom: {
      auto const name = tokenizer_.previous().value();
      auto const &builtins = context.builtins;
      if (end(builtins) != builtins.find(name))
        list.push_back(parse_literal(context));
      else if (detail::is_number(name))
        list.push_back(parse_literal(context));
      else if (detail::is_string(name))
        list.push_back(parse_string(context));
      else
        list.push_back(parse_variable(context));
    } break;

    case token::type::right_parenthesis: {
      auto const end = consume(token::type::right_parenthesis);
      auto const source = source_range::merge(start.range(), end.range());
      return std::make_unique<ast::list>(source, std::move(list));
    }

    case token::type::none:
      consume(token::type::none);
      break;

    case token::type::end:
      throw std::runtime_error("expected )");
    }
  }

  throw std::runtime_error("expected )");
}

std::unique_ptr<ast::node> parser::parse(context const &context) {
  consume(token::type::none);
  return parse_list(context);
}

} // namespace ceceo
