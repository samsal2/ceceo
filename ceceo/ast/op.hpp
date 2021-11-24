#ifndef CECEO_AST_OP_HPP_
#define CECEO_AST_OP_HPP_

#include <ceceo/ast/list.hpp>

namespace ceceo::ast {

class op : public list {
public:
  using list::list;

  virtual bool is_op() const noexcept override { return true; }
};

class sum_op : public op {
public:
  using op::op;

  atom execute(context &context) override;
};

class sub_op : public op {
public:
  using op::op;

  atom execute(context &context) override;
};

class mul_op : public op {
public:
  using op::op;

  atom execute(context &context) override;
};

class div_op : public op {
public:
  using op::op;

  atom execute(context &context) override;
};

class mod_op : public op {
public:
  using op::op;

  atom execute(context &context) override;
};

class less_op : public op {
public:
  using op::op;

  atom execute(context &context) override;
};

class more_op : public op {
public:
  using op::op;

  atom execute(context &context) override;
};

class and_op : public op {
public:
  using op::op;

  atom execute(context &context) override;
};

class not_op : public op {
public:
  using op::op;

  atom execute(context &context) override;
};

class eq_op : public op {
public:
  using op::op;

  atom execute(context &context) override;
};

} // namespace ceceo::ast

#endif
