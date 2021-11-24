#include <ceceo/context.hpp>
#include <ceceo/interpreter.hpp>
#include <iostream>

namespace ceceo {

interpreter::interpreter(std::string_view source) {
  auto p = parser(source);

  p.consume(token::type::none);

  while (token::type::left_parenthesis == p.previous().type())
    expressions_.push_back(p.parse_list());
}

atom interpreter::interpret() {
  auto c = context();
  auto result = atom(atom::null);

  for (auto const &expr : expressions_)
    result = expr->execute(c);

  return result;
}

} // namespace ceceo
