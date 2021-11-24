#ifndef CECEO_CONTEXT_HPP_
#define CECEO_CONTEXT_HPP_

#include <ceceo/atom.hpp>
#include <ceceo/builtin.hpp>
#include <string_view>
#include <unordered_map>

namespace ceceo {

struct context {
  std::unordered_map<std::string_view, atom> variables;
  std::unordered_map<std::string_view, builtinfn> builtins;
};

void load_default_context(context &context);

} // namespace ceceo

#endif
