#include "ceceo/ast/variable.hpp"

#include "ceceo/context.hpp"

namespace ceceo::ast {

atom variable::execute(context &context) {
  auto &variables = context.variables;

  if (auto v = variables.find(name_.value()); end(variables) == v)
    throw std::runtime_error("ast::variable: variable not found");
  else
    return v->second;
}

} // ceceo::ast
