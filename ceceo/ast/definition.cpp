#include "ceceo/ast/definition.hpp"

#include "ceceo/context.hpp"
#include <iostream>

namespace ceceo::ast {

atom definition::execute(context &context) {
  
  if (!view().at(1)->is_variable())
    throw std::runtime_error("expected variable in definition");

  auto name = static_cast<ast::variable const &>(*view().at(1)).name();
  auto value = view().at(2)->execute(context);

  context.variables.insert({name.value(), value});

  return value;
}

} // ceceo::ast
