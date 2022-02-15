#ifndef CECEO_LITERAL_HPP_
#define CECEO_LITERAL_HPP_

#include <ceceo/ast/node.hpp>
#include <ceceo/badge.hpp>

namespace ceceo {
class parser;
} // namespace ceceo

namespace ceceo::ast {

class literal : public node {
public:
  explicit literal(source_range source, atom value) noexcept
      : node(source), value_(value) {}

  virtual bool is_literal() const noexcept override { return true; }

  auto peek(badge<parser>) const noexcept { return value_; }

  atom execute([[maybe_unused]] context &context) override { return value_; }

private:
  atom value_;
};

}; // namespace ceceo::ast

#endif
