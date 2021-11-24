#include <ceceo/ast/variable.hpp>
#include <ceceo/context.hpp>

namespace ceceo::ast {

atom variable::execute(context &context) {
  auto const &variables = context.variables;

  if (auto v = variables.find(name_.value()); end(variables) == v) {
    std::cout<< "culprit: " << name_.value() << '\n';
    throw std::runtime_error("ast::variable: variable not found");
  } else
    return v->second;
}

} // namespace ceceo::ast
