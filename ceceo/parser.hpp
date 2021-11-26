#ifndef CECEO_PARSER_HPP_
#define CECEO_PARSER_HPP_

#include <ceceo/ast/list.hpp>
#include <ceceo/ast/literal.hpp>
#include <ceceo/ast/variable.hpp>
#include <ceceo/tokenizer.hpp>

namespace ceceo {

class parser {
public:
   explicit parser(std::string_view source) noexcept
      : tokenizer_(source) {}

   auto consume(enum token::type type) {
    auto token = tokenizer_.previous();

    if (token.type() != type)
      throw std::runtime_error("invalid token in parser");

    tokenizer_.next_token();

    return token;
  }

  auto previous() const noexcept { return tokenizer_.previous(); }
  auto done() const noexcept { return tokenizer_.done(); }

  std::unique_ptr<ast::node> parse(context const &context);
  std::unique_ptr<ast::literal> parse_literal(context const &context);
  std::unique_ptr<ast::variable> parse_variable(context const &context);
  std::unique_ptr<ast::list> parse_list(context const &context);
  std::unique_ptr<ast::literal> parse_string(context const &context);

private:
  tokenizer tokenizer_;
};

}; // namespace ceceo

#endif
