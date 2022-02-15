#include <ceceo/ast/list.hpp>
#include <ceceo/context.hpp>

namespace ceceo::ast {

list::list(source_range source,
           std::vector<std::unique_ptr<node>> childs) noexcept
    : node(source), list_(std::move(childs)) {}

atom list::execute(context &context) {
  auto const name = view().at(0)->execute(context).as_symbol().value();
  auto const &builtins = context.builtins;

  if (auto f = builtins.find(name); end(builtins) != f)
    return f->second(context, *this);

  throw std::runtime_error("ast::list: customs aren't yet supported");
}

} // namespace ceceo::ast
