#ifndef CECEO_AST_VARIABLE_HPP_
#define CECEO_AST_VARIABLE_HPP_

#include <ceceo/ast/node.hpp>
#include <ceceo/atom.hpp>
#include <ceceo/symbol.hpp>

namespace ceceo::ast {

class variable : public node {
public:
  constexpr variable(source_range range, symbol name) noexcept
      : node(range), name_(name) {}

  atom execute(context &context) override;

  bool is_variable() const noexcept override { return true; }
  constexpr auto name() const noexcept { return name_; }

private:
  symbol name_;
};

} // namespace ceceo::ast

#endif
