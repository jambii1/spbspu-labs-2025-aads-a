#include "postfix_token.hpp"

maslevtsov::PostfixToken maslevtsov::PostfixToken::operator+(const PostfixToken& other) const
{
  PostfixToken result(*this);
  return result.math_operator_impl(other, "+");
}

maslevtsov::PostfixToken maslevtsov::PostfixToken::operator-(const PostfixToken& other) const
{
  PostfixToken result(*this);
  return result.math_operator_impl(other, "-");
}

maslevtsov::PostfixToken maslevtsov::PostfixToken::operator*(const PostfixToken& other) const
{
  PostfixToken result(*this);
  return result.math_operator_impl(other, "*");
}

maslevtsov::PostfixToken maslevtsov::PostfixToken::operator/(const PostfixToken& other) const
{
  PostfixToken result(*this);
  return result.math_operator_impl(other, "/");
}

maslevtsov::PostfixToken maslevtsov::PostfixToken::operator%(const PostfixToken& other) const
{
  PostfixToken result(*this);
  return result.math_operator_impl(other, "%");
}

maslevtsov::PostfixToken& maslevtsov::PostfixToken::math_operator_impl(const PostfixToken& other,
  const std::string& operation)
{
  PostfixToken copy(other);
  while (!copy.token_.empty()) {
    this->token_.push(copy.token_.front());
    copy.token_.pop();
  }
  this->token_.push(operation);
  return *this;
}
