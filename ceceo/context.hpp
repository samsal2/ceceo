#ifndef CECEO_CONTEXT_HPP_
#define CECEO_CONTEXT_HPP_

#include <ceceo/atom.hpp>
#include <string_view>
#include <unordered_map>

namespace ceceo {

class context {
public:
  std::unordered_map<std::string_view, atom> variables;
};

} // namespace ceceo

#endif
