#include <ceceo/ast/op.hpp>
#include <ceceo/ast/statement.hpp>
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

std::unique_ptr<ast::literal> parser::parse_literal() {
  auto const token = tokenizer_.previous();

  if (detail::is_string(token.value()))
    return parse_string();

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

std::unique_ptr<ast::variable> parser::parse_variable() {
  auto const token = consume(token::type::atom);
  return std::make_unique<ast::variable>(token.range(),
                                         symbol(token.value()));
}

std::unique_ptr<ast::literal> parser::parse_string() {
  auto const token = consume(token::type::atom);
  auto value = token.value();

  if (!detail::is_string(token.value()))
    throw std::runtime_error("parser: invalid string");

  value.remove_prefix(1);
  value.remove_suffix(1);

  return std::make_unique<ast::literal>(token.range(), atom(symbol(value)));
}

std::unique_ptr<ast::list> parser::parse_list() {
  auto const start = consume(token::type::left_parenthesis);
  auto list = std::vector<std::unique_ptr<ast::node>>();

  while (!tokenizer_.done()) {
    switch (tokenizer_.previous().type()) {
    case token::type::left_parenthesis:
      list.push_back(parse_list());
      break;

    case token::type::atom: {
      auto name = tokenizer_.previous().value();

      // TODO(samuel): move this to the env
      if ("auto" == name)
        list.push_back(parse_literal());
      else if ("if" == name)
        list.push_back(parse_literal());
      else if ("while" == name)
        list.push_back(parse_literal());
      else if ("set" == name)
        list.push_back(parse_literal());
      else if ("cond" == name)
        list.push_back(parse_literal());
      else if ("prog" == name)
        list.push_back(parse_literal());
      else if ("print" == name)
        list.push_back(parse_literal());
      else if ("+" == name)
        list.push_back(parse_literal());
      else if ("-" == name)
        list.push_back(parse_literal());
      else if ("*" == name)
        list.push_back(parse_literal());
      else if ("/" == name)
        list.push_back(parse_literal());
      else if ("<" == name)
        list.push_back(parse_literal());
      else if (">" == name)
        list.push_back(parse_literal());
      else if ("%" == name)
        list.push_back(parse_literal());
      else if ("and" == name)
        list.push_back(parse_literal());
      else if ("not" == name)
        list.push_back(parse_literal());
      else if ("eq" == name)
        list.push_back(parse_literal());
      else if (detail::is_number(name))
        list.push_back(parse_literal());
      else if (detail::is_string(name))
        list.push_back(parse_literal());
      else
        list.push_back(parse_variable());
    } break;

    case token::type::right_parenthesis: {
      auto const end = consume(token::type::right_parenthesis);
      auto const source = source_range::merge(start.range(), end.range());

      if (0 == size(list))
        return std::make_unique<ast::list>(source, std::move(list));

      auto const &first = list[0];

      if (!first->is_literal())
        return std::make_unique<ast::list>(source, std::move(list));

      auto const &literal = static_cast<ast::literal const &>(*first);
      auto const symbol = literal.peek({});

      if (atom::type::symbol != symbol.type())
        throw std::runtime_error("parser: expected symbol");

      auto const name = symbol.as_symbol().value();

      if ("auto" == name)
        return std::make_unique<ast::auto_statement>(source, std::move(list));

      if ("if" == name)
        return std::make_unique<ast::if_statement>(source, std::move(list));

      if ("while" == name)
        return std::make_unique<ast::while_statement>(source,
                                                      std::move(list));

      if ("set" == name)
        return std::make_unique<ast::set_statement>(source, std::move(list));

      if ("cond" == name)
        return std::make_unique<ast::cond_statement>(source, std::move(list));

      if ("prog" == name)
        return std::make_unique<ast::prog_statement>(source, std::move(list));

      if ("print" == name)
        return std::make_unique<ast::print_statement>(source,
                                                      std::move(list));

      if ("+" == name)
        return std::make_unique<ast::sum_op>(source, std::move(list));

      if ("-" == name)
        return std::make_unique<ast::sub_op>(source, std::move(list));

      if ("*" == name)
        return std::make_unique<ast::mul_op>(source, std::move(list));

      if ("/" == name)
        return std::make_unique<ast::div_op>(source, std::move(list));

      if ("%" == name)
        return std::make_unique<ast::mod_op>(source, std::move(list));

      if ("<" == name)
        return std::make_unique<ast::less_op>(source, std::move(list));

      if (">" == name)
        return std::make_unique<ast::more_op>(source, std::move(list));

      if ("and" == name)
        return std::make_unique<ast::and_op>(source, std::move(list));

      if ("not" == name)
        return std::make_unique<ast::not_op>(source, std::move(list));

      if ("eq" == name)
        return std::make_unique<ast::eq_op>(source, std::move(list));

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

std::unique_ptr<ast::node> parser::parse() {
  consume(token::type::none);
  return parse_list();
}

} // namespace ceceo
