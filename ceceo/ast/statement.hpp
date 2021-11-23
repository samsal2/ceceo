#ifndef CECEO_AST_STATEMENT_HPP_
#define CECEO_AST_STATEMENT_HPP_

#include "ceceo/ast/list.hpp"

namespace ceceo::ast {

// TODO(samuel): behaviour could easly be injected instead of creating
// 23123123 classes
class statement : public list {
public:
  using list::list;

  virtual bool is_statement() const noexcept override { return true; }
  virtual bool is_fn_statment() const noexcept { return false; }
};

class if_statement : public statement {
public:
  using statement::statement;

  atom execute(context &context) override;
};

class while_statement : public statement {
public:
  using statement::statement;

  atom execute(context &context) override;
};

class auto_statement : public statement {
public:
  using statement::statement;

  atom execute(context &context) override;
};

class set_statement : public statement {
public:
  using statement::statement;

  atom execute(context &context) override;
};

class cond_statement : public statement {
public:
  using statement::statement;

  atom execute(context &context) override;
};

class prog_statement : public statement {
public:
  using statement::statement;

  atom execute(context &context) override;
};

// TODO(samuel) mode this outta here
class print_statement : public statement {
public:
  using statement::statement;

  atom execute(context &context) override;
};


} // ceceo::ast

#endif
