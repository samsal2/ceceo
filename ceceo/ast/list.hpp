#ifndef CECEO_AST_LIST_HPP_
#define CECEO_AST_LIST_HPP_

#include <ceceo/ast/node.hpp>
#include <span>
#include <vector>

namespace ceceo::ast {

class list : public node {
public:
  list(source_range source, std::vector<std::unique_ptr<node>> childs) noexcept;

  auto &view() noexcept { return list_; }

  auto const &view() const noexcept { return list_; }

  bool is_list() const noexcept override { return true; }

  atom execute(context &context) override;

  constexpr auto size() const noexcept { return std::size(list_); }

private:
  std::vector<std::unique_ptr<node>> list_;
};

}; // namespace ceceo::ast

#endif
