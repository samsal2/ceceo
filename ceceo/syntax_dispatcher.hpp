#ifndef CECEO_SYNTAX_DISPATCHER_HPP_
#define CECEO_SYNTAX_DISPATCHER_HPP_

#include "ceceo/ast/list.hpp"

namespace ceceo {

namespace detail {

using dispatcher = std::unique_ptr<ast::list> (*)(
    source_range, std::vector<std::unique_ptr<ast::node>>);

} // namespace detail

struct syntax_dispatcher {
  
};


} // namespace ceceo

#endif
