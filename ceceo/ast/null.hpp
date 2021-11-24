#ifndef CECEO_AST_NULL_HPP_
#define CECEO_AST_NULL_HPP_

#include <ceceo/ast/node.hpp>

namespace ceceo::ast {

class null : public node {
public:
  using node::node;

  atom execute([[maybe_unused]] context &context) override {
    return atom::null;
  }
};

} // namespace ceceo::ast

#endif
