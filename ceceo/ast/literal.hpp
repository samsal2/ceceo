#ifndef CECEO_LITERAL_HPP_
#define CECEO_LITERAL_HPP_

#include "ceceo/badge.hpp"
#include "ceceo/ast/node.hpp"


namespace ceceo {
class parser;
} // ceceo

namespace ceceo::ast {


class literal : public node {
public:
  constexpr explicit literal(source_range source, atom value) noexcept 
    : node(source), value_(value) {}

  virtual bool is_literal() const noexcept override { return true; }

  constexpr auto peek(badge<parser>) const noexcept { return value_; }

  atom execute([[maybe_unused]] context &context) override { return value_; }

private:
  atom value_;
};

}; // namespace ceceo::ast

#endif
