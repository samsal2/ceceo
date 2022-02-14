#ifndef CECEO_BUILTIN_HPP_
#define CECEO_BUILTIN_HPP_

#include <ceceo/atom.hpp>
#include <span>

namespace ceceo {

struct context;

namespace ast {

class list;

} // namespace ast

using builtinfn = atom (*)(context &context, ast::list const &args);

namespace builtin {

atom op_auto(context &context, ast::list const &args);
atom op_if(context &context, ast::list const &args);
atom op_while(context &context, ast::list const &args);
atom op_cond(context &context, ast::list const &args);
atom op_prog(context &context, ast::list const &args);
atom op_print(context &context, ast::list const &args);
atom op_sum(context &context, ast::list const &args);
atom op_sub(context &context, ast::list const &args);
atom op_less(context &context, ast::list const &args);
atom op_more(context &context, ast::list const &args);
atom op_eq(context &context, ast::list const &args);
atom op_set(context &context, ast::list const &args);
atom op_and(context &context, ast::list const &args);
atom op_not(context &context, ast::list const &args);
atom op_mod(context &context, ast::list const &args);
atom op_null(context &context, ast::list const &args);
atom op_or(context &context, ast::list const &args);


} // namespace builtin

} // namespace ceceo

#endif
