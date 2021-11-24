#include <ceceo/ast/statement.hpp>
#include <ceceo/ast/variable.hpp>
#include <ceceo/context.hpp>
#include <stdexcept>

namespace ceceo::ast {

atom if_statement::execute(context &context) {
  auto const test = view().at(1)->execute(context);

  if (atom::type::number != test.type())
    throw std::runtime_error("ast::if_statement: expected number");

  if (test.as_number().value())
    return view().at(2)->execute(context);

  return view().at(3)->execute(context);
}

atom while_statement::execute(context &context) {
  auto result = atom(atom::null);
  auto test = view().at(1)->execute(context);

  if (atom::type::number != test.type())
    throw std::runtime_error("ast::while_statement: expected number");

  for (; test.as_number().value(); test = view().at(1)->execute(context))
    result = view().at(2)->execute(context);

  return result;
}

atom auto_statement::execute(context &context) {
  auto &first = view().at(1);

  if (!first->is_variable())
    throw std::runtime_error("ast::auto_statement: expected literal");

  auto const &var = static_cast<ast::variable const &>(*first);
  auto const name = var.name().value();
  auto const value = view().at(2)->execute(context);

  context.variables.insert({name, value});

  return value;
}

atom set_statement::execute(context &context) {
  auto const &first = view().at(1);

  if (!first->is_variable())
    throw std::runtime_error("ast::set_statement: expected literal");

  auto const &var = static_cast<ast::variable const &>(*first);
  auto &vars = context.variables;
  auto found = vars.find(var.name().value());

  if (end(vars) == found)
    throw std::runtime_error("ast::set_statment: variable not found");

  found->second = view().at(2)->execute(context);

  return found->second;
}

atom cond_statement::execute(context &context) {

  if (1 == size()) // it only contains the keyword (cond)
    throw std::runtime_error("ast::cond_statement: empty cond");

  // test everything that's not the last statement
  for (size_t i = 1; i < size() - 1; ++i) {
    auto const &current = view()[i];

    if (!current->is_list())
      throw std::runtime_error("ast::cond_statment: expected a list");

    auto const &list = static_cast<ast::list const &>(*current);
    auto const test = list.view().at(0)->execute(context);

    if (test.as_number().value())
      return list.view().at(1)->execute(context);
  }

  return view().back()->execute(context);
}

atom prog_statement::execute(context &context) {
  auto result = atom(atom::null);

  for (size_t i = 1; i < size(); ++i)
    result = view()[i]->execute(context);

  return result;
}

atom print_statement::execute(context &context) {
  auto result = atom(atom::null);

  for (size_t i = 1; i < size(); ++i) {
    result = view()[i]->execute(context);
    std::cout << result << ' ';
  }

  std::cout << '\n';

  return result;
}

} // namespace ceceo::ast
