#ifndef CECEO_CONTEXT_HPP_
#define CECEO_CONTEXT_HPP_

#include <unordered_map>
#include <string_view>

#include "ceceo/atom.hpp"

namespace ceceo {

class context {
public:
  std::unordered_map<std::string_view, atom> variables;
};

} // ceceo

#endif
