#include "ceceo/ast/procedure.hpp"

#include "ceceo/context.hpp"

namespace ceceo::ast {

procedure::procedure(source_range source,
                     std::vector<std::unique_ptr<node>> childs,
                     std::vector<symbol> args) noexcept
    : list(source, std::move(childs)), args_(std::move(args)) {}


} // namespace ceceo::ast
