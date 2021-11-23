#include "ceceo/ast/list.hpp"

namespace ceceo::ast {

list::list(source_range source,
           std::vector<std::unique_ptr<node>> childs) noexcept
    : node(source), list_(std::move(childs)) {}

} // namespace ceceo::ast
