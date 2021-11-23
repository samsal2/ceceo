#ifndef CECEO_AST_PROCEDURE_HPP_
#define CECEO_AST_PROCEDURE_HPP_

#include "ceceo/ast/list.hpp"
#include "ceceo/ast/variable.hpp"
#include "ceceo/atom.hpp"

#include <vector>

namespace ceceo::ast {

class procedure : public list {
public:
  procedure(source_range source, std::vector<std::unique_ptr<node>> childs,
            std::vector<symbol> args) noexcept;
 
  atom call(ast::list const &variables);

private:
  std::vector<symbol> args_;
};

} // namespace ceceo::ast

#endif
