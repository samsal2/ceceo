#ifndef CECEO_BEHAVIOUR_HPP_
#define CECEO_BEHAVIOUR_HPP_

#include "ceceo/atom.hpp"

#include <vector>

namespace ceceo {

class context;

namespace ast {

class list;

} // ast

using behaviour = atom (*)(context &context, ast::list const &arguments);

}; // namespace ceceo

#endif
