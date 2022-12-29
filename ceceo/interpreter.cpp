#include <ceceo/context.hpp>
#include <ceceo/interpreter.hpp>
#include <iostream>

namespace ceceo {

interpreter::interpreter(std::string_view source) {
  auto p = parser(source);

  load_default_context(context_);
  p.consume(token::type::none);

  while (token::type::left_parenthesis == p.previous().type())
    expressions_.push_back(p.parse_list(context_));

  if (!p.done())
    throw std::runtime_error("parser: unable to interpret");
}

atom interpreter::interpret() {
  auto result = atom(atom::null);

  for (auto const &expr : expressions_)
    result = expr->execute(context_);

  return result;
}

} // namespace ceceo
