#include <ceceo/builtin.hpp>
#include <ceceo/context.hpp>

namespace ceceo {

void load_default_context(context &context) {
  context.builtins.insert({"auto", builtin::op_auto});
  context.builtins.insert({"if", builtin::op_if});
  context.builtins.insert({"while", builtin::op_while});
  context.builtins.insert({"cond", builtin::op_cond});
  context.builtins.insert({"prog", builtin::op_prog});
  context.builtins.insert({"print", builtin::op_print});
  context.builtins.insert({"set", builtin::op_set});
  context.builtins.insert({"+", builtin::op_sum});
  context.builtins.insert({"-", builtin::op_sub});
  context.builtins.insert({"<", builtin::op_less});
  context.builtins.insert({"<=", builtin::op_less_eq});
  context.builtins.insert({">", builtin::op_more});
  context.builtins.insert({"==", builtin::op_eq});
  context.builtins.insert({"&&", builtin::op_and});
  context.builtins.insert({"!", builtin::op_not});
  context.builtins.insert({"%", builtin::op_mod});
  context.builtins.insert({"null", builtin::op_null});
  context.builtins.insert({"||", builtin::op_or});
}

} // namespace ceceo
