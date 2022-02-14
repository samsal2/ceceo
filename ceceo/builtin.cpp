#include <ceceo/ast/list.hpp>
#include <ceceo/ast/variable.hpp>
#include <ceceo/builtin.hpp>
#include <ceceo/context.hpp>

namespace ceceo::builtin {

namespace detail {

static atom op_auto_variable(context &context, ast::list const &args) {
  auto const &first = args.view().at(1);

  if (!first->is_variable())
    throw std::runtime_error("builtin::op_auto: expected literal");

  auto const &var = static_cast<ast::variable const &>(*first);
  auto const name = var.name().value();
  auto const value = args.view().at(2)->execute(context);

  context.variables.insert({name, value});

  return value;
}

} // namespace detail

atom op_auto(context &context, ast::list const &args) {
  if (args.view().at(1)->is_variable())
    return detail::op_auto_variable(context, args);

  return atom::null;
}

atom op_if(context &context, ast::list const &args) {
  auto const test = args.view().at(1)->execute(context);

  if (atom::type::number != test.type())
    throw std::runtime_error("bultin::op_auto: expected number");

  if (test.as_number().value())
    return args.view().at(2)->execute(context);

  return args.view().at(3)->execute(context);
}

atom op_while(context &context, ast::list const &args) {
  auto result = atom(atom::null);
  auto test = args.view().at(1)->execute(context);

  if (atom::type::number != test.type())
    throw std::runtime_error("builtin::op_while: expected number");

  for (; test.as_number().value(); test = args.view().at(1)->execute(context))
    result = args.view().at(2)->execute(context);

  return result;
}

atom op_cond(context &context, ast::list const &args) {
  if (1 == std::size(args)) // it only contains the keyword (cond)
    throw std::runtime_error("builtin::op_cond: empty cond");

  // test everything that's not the last statement
  for (size_t i = 1; i < std::size(args) - 1; ++i) {
    auto const &current = args.view()[i];

    if (!current->is_list())
      throw std::runtime_error("builtin::op_cond: expected a list");

    auto const &list = static_cast<ast::list const &>(*current);
    auto const test = list.view().at(0)->execute(context);

    if (test.as_number().value())
      return list.view().at(1)->execute(context);
  }

  return args.view().back()->execute(context);
}

atom op_prog(context &context, ast::list const &args) {
  auto result = atom(atom::null);

  for (size_t i = 1; i < std::size(args); ++i)
    result = args.view()[i]->execute(context);

  return result;
}

atom op_print(context &context, ast::list const &args) {
  auto result = atom(atom::null);

  for (size_t i = 1; i < std::size(args); ++i) {
    result = args.view()[i]->execute(context);
    std::cout << result << ' ';
  }

  std::cout << '\n';

  return result;
}

atom op_sum(context &context, ast::list const &args) {
  auto const lhs = args.view().at(1)->execute(context);
  auto const rhs = args.view().at(2)->execute(context);

  return atom(lhs.as_number().value() + rhs.as_number().value());
}

atom op_sub(context &context, ast::list const &args) {
  auto const lhs = args.view().at(1)->execute(context);
  auto const rhs = args.view().at(2)->execute(context);

  return atom(lhs.as_number().value() - rhs.as_number().value());
}

atom op_less(context &context, ast::list const &args) {
  auto const lhs = args.view().at(1)->execute(context);
  auto const rhs = args.view().at(2)->execute(context);

  return atom(lhs.as_number().value() < rhs.as_number().value());
}

atom op_more(context &context, ast::list const &args) {
  auto const lhs = args.view().at(1)->execute(context);
  auto const rhs = args.view().at(2)->execute(context);

  return atom(lhs.as_number().value() > rhs.as_number().value());
}

atom op_not(context &context, ast::list const &args) {
  return atom(!args.view().at(1)->execute(context).as_number().value());
}

atom op_eq(context &context, ast::list const &args) {
  auto const lhs = args.view().at(1)->execute(context);
  auto const rhs = args.view().at(2)->execute(context);

  if (atom::type::number == lhs.type() && atom::type::number == rhs.type())
    return atom(lhs.as_number().value() == rhs.as_number().value());

  if (atom::type::symbol == lhs.type() && atom::type::symbol == rhs.type())
    return atom(lhs.as_symbol().value() == rhs.as_symbol().value());

  throw std::runtime_error("builtin::eq_op: comparing symbol with number");
}

atom op_set(context &context, ast::list const &args) {
  auto const &first = args.view().at(1);

  if (!first->is_variable())
    throw std::runtime_error("builtin::op_set: expected variable");

  auto const &var = static_cast<ast::variable const &>(*first);
  auto &vars = context.variables;
  auto found = vars.find(var.name().value());

  if (end(vars) == found)
    throw std::runtime_error("builtin::op_set: variable not found");

  found->second = args.view().at(2)->execute(context);

  return found->second;
}

atom op_and(context &context, ast::list const &args) {
  auto state = true;

  for (std::size_t i = 1; i < args.view().size(); ++i)
    state = state && args.view().at(i)->execute(context).as_number().value();

  return atom(state);
}

atom op_mod(context &context, ast::list const &args) {
  auto const lhs = args.view().at(1)->execute(context);
  auto const rhs = args.view().at(2)->execute(context);

  return atom(lhs.as_number().value() % rhs.as_number().value());
}

atom op_null([[maybe_unused]] context &context,
             [[maybe_unused]] ast::list const &args) {
  return atom::null;
}

atom op_or(context &context, ast::list const &args) {
  auto state = false;

  for (std::size_t i = 1; i < args.view().size(); ++i)
    state = state || args.view().at(i)->execute(context).as_number().value();

  return atom(state);
}

} // namespace ceceo::builtin
