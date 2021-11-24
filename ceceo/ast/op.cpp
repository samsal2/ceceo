#include <ceceo/ast/op.hpp>

namespace ceceo::ast {

atom sum_op::execute(context &context) {
  auto const lhs = view().at(1)->execute(context);
  auto const rhs = view().at(2)->execute(context);

  return atom(lhs.as_number().value() + rhs.as_number().value());
}

atom sub_op::execute(context &context) {
  auto const lhs = view().at(1)->execute(context);
  auto const rhs = view().at(2)->execute(context);

  return atom(lhs.as_number().value() - rhs.as_number().value());
}

atom mul_op::execute(context &context) {
  auto const lhs = view().at(1)->execute(context);
  auto const rhs = view().at(2)->execute(context);

  return atom(lhs.as_number().value() * rhs.as_number().value());
}

atom div_op::execute(context &context) {
  auto const lhs = view().at(1)->execute(context);
  auto const rhs = view().at(2)->execute(context);

  return atom(lhs.as_number().value() / rhs.as_number().value());
}

atom mod_op::execute(context &context) {
  auto const lhs = view().at(1)->execute(context);
  auto const rhs = view().at(2)->execute(context);

  return atom(lhs.as_number().value() % rhs.as_number().value());
}

atom less_op::execute(context &context) {
  auto const lhs = view().at(1)->execute(context);
  auto const rhs = view().at(2)->execute(context);

  return atom(lhs.as_number().value() < rhs.as_number().value());
}

atom more_op::execute(context &context) {
  auto const lhs = view().at(1)->execute(context);
  auto const rhs = view().at(2)->execute(context);

  return atom(lhs.as_number().value() > rhs.as_number().value());
}

atom and_op::execute(context &context) {
  auto const lhs = view().at(1)->execute(context);
  auto const rhs = view().at(2)->execute(context);

  return atom(lhs.as_number().value() && rhs.as_number().value());
}

atom not_op::execute(context &context) {
  return atom(!view().at(1)->execute(context).as_number().value());
}

atom eq_op::execute(context &context) {
  auto const lhs = view().at(1)->execute(context);
  auto const rhs = view().at(2)->execute(context);

  if (atom::type::number == lhs.type() && atom::type::number == rhs.type())
    return atom(lhs.as_number().value() == rhs.as_number().value());

  if (atom::type::symbol == lhs.type() && atom::type::symbol == rhs.type())
    return atom(lhs.as_symbol().value() == rhs.as_symbol().value());

  throw std::runtime_error("ast::eq_op: comparing symbol with number");
}

} // namespace ceceo::ast
