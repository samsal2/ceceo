#ifndef CECEO_AST_NODE_HPP_
#define CECEO_AST_NODE_HPP_

#include <ceceo/atom.hpp>
#include <ceceo/source_range.hpp>

namespace ceceo {
struct  context;
} // namespace ceceo

namespace ceceo::ast {

class node {
public:
  constexpr explicit node(source_range source) noexcept : source_(source) {}

  node(node const &other) noexcept = default;
  node(node &&other) noexcept = default;

  node &operator=(node const &other) noexcept = default;
  node &operator=(node &&other) noexcept = default;

  virtual ~node() noexcept;

  virtual bool is_list() const noexcept { return false; }
  virtual bool is_literal() const noexcept { return false; }
  virtual bool is_variable() const noexcept { return false; }
  virtual bool is_statement() const noexcept { return false; }
  virtual bool is_op() const noexcept { return false; }

  virtual atom execute([[maybe_unused]] context &context) = 0;

  constexpr auto source() const noexcept { return source_; }

private:
  source_range source_;
};

}; // namespace ceceo::ast

#endif
