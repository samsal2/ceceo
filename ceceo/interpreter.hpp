#ifndef CECEO_INTERPRETER_HPP_
#define CECEO_INTERPRETER_HPP_

#include <ceceo/parser.hpp>
#include <ceceo/context.hpp>

namespace ceceo {

class interpreter {
public:
  interpreter(std::string_view source);

  atom interpret();

private:
  context context_;
  std::vector<std::unique_ptr<ast::list>> expressions_;
};

}; // namespace ceceo

#endif
