#include "ceceo/tokenizer.hpp"

#include "ceceo/token.hpp"

#include <iostream>

namespace ceceo {

token tokenizer::next_token() {
  consume_whitespace();

  auto const submit = [this] (source_range range, auto type) {
    return (previous_ = token(range, type));
  };

  if ('(' == peek())
    return submit(consume(), token::type::left_parenthesis);
 
  if (')' == peek())
    return submit(consume(), token::type::right_parenthesis);

  if ('\"' == peek())
    return submit(consume_string(), token::type::atom);

  if (detail::is_atom(peek()))
    return submit(consume_atom(), token::type::atom);

  if ('\0' == peek())
    return submit(consume(), token::type::end);

  std::cout << "peeking: " << (int)peek() << '\n';
  throw std::runtime_error("tokenizer: invalid token");
}

} // ceceo
