#ifndef LIST_HPP
#define LIST_HPP
#include <cassert>
#include <initializer_list>
#include "list-node.hpp"
#include "list-iterators.hpp"

namespace savintsev
{
  template< typename T >
  class List
  {
  public:
    using iterator = Iterator< T >;
    using const_iterator = ConstIterator< T >;
    using const_it = ConstIterator< T >;

    List();
    ~List();
    List(const List & rhs);
    List(List && rhs) noexcept;
    List(size_t n, const T & value);
    List(const_iterator first, const_iterator last);
    List(std::initializer_list< T > il);

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    T & front();
    const T & front() const;
    T & back();
    const T & back() const;

    bool empty() const noexcept;
    size_t size() const noexcept;

    List & operator=(std::initializer_list< T > il);

    void push_front(const T & value);
    void push_front(T && value);
    void push_back(const T & value);
    void push_back(T && value);
    void pop_front();
    void pop_back();
    void swap(List & rhs);
    void clear() noexcept;

    void remove(const T & value);
    template< class Predicate >
    void remove_if(Predicate pred);

    void splice(const_iterator pos, List & rhs);
    void splice(const_iterator pos, List && rhs);
    void splice(const_iterator pos, List & rhs, const_iterator i);
    void splice(const_iterator pos, List && rhs, const_iterator i);
    void splice(const_it pos, List & rhs, const_it first, const_it last);
    void splice(const_it pos, List && rhs, const_it first, const_it last);

    void assign(const_iterator first, const_iterator last);
    void assign(size_t n, const T & value);
    void assign(std::initializer_list< T > il);

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);

    iterator insert(const_iterator pos, const T & value);
    iterator insert(const_iterator pos, size_t n, const T & value);
    iterator insert(const_it pos, const_it first, const_it last);
    iterator insert(const_iterator pos, T && value);
    iterator insert(const_iterator pos, std::initializer_list< T > il);

    void reverse() noexcept;

    template< class... Args >
    iterator emplace(const_iterator pos, Args &&... args);

    template< class... Args >
    iterator emplace_back(Args &&... args);

    template< class... Args >
    iterator emplace_front(Args &&... args);

    void sort();
    template< class Compare >
    void sort(Compare comp);

    void merge(List & x);
    void merge(List && x);
    template< class Compare >
    void merge(List & x, Compare comp);
    template< class Compare >
    void merge(List && x, Compare comp);

    void unique();
    template< class BinaryPredicate >
    void unique(BinaryPredicate binary_pred);
  private:
    ListNode< T > * dummy;
    size_t list_size;
  };

  template< typename T >
  bool operator==(const List< T > & lhs, const List< T > & rhs);

  template< typename T >
  bool operator!=(const List< T > & lhs, const List< T > & rhs);

  template< typename T >
  bool operator<(const List< T > & lhs, const List< T > & rhs);
  template< typename T >
  bool operator<=(const List< T > & lhs, const List< T > & rhs);

  template< typename T >
  bool operator>(const List< T > & lhs, const List< T > & rhs);
  template< typename T >
  bool operator>=(const List< T > & lhs, const List< T > & rhs);
}

template< typename T >
bool savintsev::operator==(const List< T > & lhs, const List< T > & rhs)
{
  if (lhs.size() != rhs.size())
  {
    return false;
  }
  auto jt = rhs.cbegin();
  for (auto it = lhs.cbegin(); it != lhs.cend(); ++it)
  {
    if (!(*it == *jt))
    {
      return false;
    }
    ++jt;
  }
  return true;
}

template< typename T >
bool savintsev::operator!=(const List< T > & lhs, const List< T > & rhs)
{
  return (!(lhs == rhs));
}

template< typename T >
bool savintsev::operator<(const List< T > & lhs, const List< T > & rhs)
{
  auto jt = rhs.cbegin();
  for (auto it = lhs.cbegin(); it != lhs.cend(); ++it)
  {
    if (jt == rhs.end() || *jt < *it)
    {
      return false;
    }
    else if (*it < *jt)
    {
      return true;
    }
    ++jt;
  }
  return (jt != rhs.end());
}

template< typename T >
bool savintsev::operator<=(const List< T > & lhs, const List< T > & rhs)
{
  return (!(rhs < lhs));
}

template< typename T >
bool savintsev::operator>(const List< T > & lhs, const List< T > & rhs)
{
  return (rhs < lhs);
}

template< typename T >
bool savintsev::operator>=(const List< T > & lhs, const List< T > & rhs)
{
  return (!(lhs < rhs));
}

template< typename T >
savintsev::List< T >::List():
  dummy(new ListNode< T >()),
  list_size(0)
{}

template< typename T >
savintsev::List< T >::~List()
{
  clear();
  delete dummy;
}

template< typename T >
savintsev::List< T >::List(const List & rhs):
  dummy(new ListNode< T >()),
  list_size(0)
{
  try
  {
    for (auto it = rhs.begin(); it != rhs.end(); ++it)
    {
      push_back(*it);
    }
  }
  catch (const std::bad_alloc & e)
  {
    clear();
    delete dummy;
    throw;
  }
}

template< typename T >
savintsev::List< T >::List(List && rhs) noexcept:
  dummy(rhs.dummy),
  list_size(rhs.list_size)
{
  rhs.dummy = nullptr;
  rhs.list_size = 0;
}

template< typename T >
savintsev::List< T >::List(size_t n, const T & value):
  dummy(new ListNode< T >()),
  list_size(0)
{
  try
  {
    for (size_t i = 0; i < n; ++i)
    {
      push_back(value);
    }
  }
  catch (const std::bad_alloc & e)
  {
    clear();
    delete dummy;
    throw;
  }
}

template< typename T >
savintsev::List< T >::List(std::initializer_list< T > il):
  dummy(new ListNode< T >()),
  list_size(0)
{
  try
  {
    for (auto it = il.begin(); it != il.end(); ++it)
    {
      push_back(*it);
    }
  }
  catch (const std::bad_alloc & e)
  {
    clear();
    delete dummy;
    throw;
  }
}

template< typename T >
savintsev::List< T >::List(const_iterator first, const_iterator last):
  dummy(new ListNode< T >()),
  list_size(0)
{
  try
  {
    for (auto it = first; it != last; ++it)
    {
      push_back(*it);
    }
  }
  catch (const std::bad_alloc & e)
  {
    clear();
    delete dummy;
    throw;
  }
}

template< typename T >
typename savintsev::List< T >::iterator savintsev::List< T >::begin() noexcept
{
  return iterator(dummy->next);
}

template< typename T >
typename savintsev::List< T >::const_iterator savintsev::List< T >::begin() const noexcept
{
  return const_iterator(dummy->next);
}

template< typename T >
typename savintsev::List< T >::iterator savintsev::List< T >::end() noexcept
{
  return iterator(dummy);
}

template< typename T >
typename savintsev::List< T >::const_iterator savintsev::List< T >::end() const noexcept
{
  return const_iterator(dummy);
}

template< typename T >
typename savintsev::List< T >::const_iterator savintsev::List< T >::cbegin() const noexcept
{
  return const_iterator(dummy->next);
}

template< typename T >
typename savintsev::List< T >::const_iterator savintsev::List< T >::cend() const noexcept
{
  return const_iterator(dummy);
}

template< typename T >
T & savintsev::List< T >::front()
{
  return *(dummy->next->data);
}

template< typename T >
const T & savintsev::List< T >::front() const
{
  return *(dummy->next->data);
}

template< typename T >
T & savintsev::List< T >::back()
{
  return *(dummy->prev->data);
}

template< typename T >
const T & savintsev::List< T >::back() const
{
  return *(dummy->prev->data);
}

template< typename T >
bool savintsev::List< T >::empty() const noexcept
{
  return list_size == 0;
}

template< typename T >
size_t savintsev::List< T >::size() const noexcept
{
  return list_size;
}

template< typename T >
savintsev::List< T > & savintsev::List< T >::operator=(std::initializer_list< T > il)
{
  clear();
  for (auto it = il.begin(); it != il.end(); ++it)
  {
    push_back(*it);
  }
}

template< typename T >
void savintsev::List< T >::push_front(const T & value)
{
  ListNode< T > * new_node = new ListNode< T >(value, dummy->next, dummy);
  dummy->next->prev = new_node;
  dummy->next = new_node;
  ++list_size;
}

template< typename T >
void savintsev::List< T >::push_front(T && value)
{
  ListNode< T > * new_node = new ListNode< T >(std::move(value), dummy->next, dummy);
  dummy->next->prev = new_node;
  dummy->next = new_node;
  ++list_size;
}

template< typename T >
void savintsev::List< T >::push_back(const T & value)
{
  ListNode< T > * new_node = new ListNode< T >(value, dummy, dummy->prev);
  dummy->prev->next = new_node;
  dummy->prev = new_node;
  ++list_size;
}

template< typename T >
void savintsev::List< T >::push_back(T && value)
{
  ListNode< T > * new_node = new ListNode< T >(std::move(value), dummy, dummy->prev);
  dummy->prev->next = new_node;
  dummy->prev = new_node;
  ++list_size;
}

template< typename T >
void savintsev::List< T >::pop_front()
{
  assert(!empty());
  ListNode< T > * temp_front = dummy->next;
  dummy->next = temp_front->next;
  dummy->next->prev = dummy;
  delete temp_front;
  --list_size;
}

template< typename T >
void savintsev::List< T >::pop_back()
{
  assert(!empty());
  ListNode< T > * temp_back = dummy->prev;
  dummy->prev = temp_back->prev;
  dummy->prev->next = dummy;
  delete temp_back;
  --list_size;
}

template< typename T >
void savintsev::List< T >::swap(List & rhs)
{
  std::swap(dummy->next->prev, rhs.dummy->next->prev);
  std::swap(dummy->prev->next, rhs.dummy->prev->next);
  std::swap(dummy->next, rhs.dummy->next);
  std::swap(dummy->prev, rhs.dummy->prev);
  std::swap(list_size, rhs.list_size);
}

template< typename T >
void savintsev::List< T >::clear() noexcept
{
  while (!empty())
  {
    pop_front();
  }
}

template< typename T >
void savintsev::List< T >::remove(const T & value)
{
  for (auto it = cbegin(); it != cend(); ++it)
  {
    if (*it == value)
    {
      it.node->prev->next = it.node->next;
      it.node->next->prev = it.node->prev;
      auto temp = it--;
      delete temp.node;
      --list_size;
    }
  }
}

template< typename T >
template< class Predicate >
void savintsev::List< T >::remove_if(Predicate pred)
{
  for (auto it = cbegin(); it != cend(); ++it)
  {
    if (pred(*it))
    {
      it.node->prev->next = it.node->next;
      it.node->next->prev = it.node->prev;
      auto temp = it--;
      delete temp.node;
      --list_size;
    }
  }
}

template< typename T >
template< class... Args >
typename savintsev::List< T >::iterator savintsev::List< T >::emplace(const_iterator pos, Args &&... args)
{
  return insert(pos, T(args...));
}

template< typename T >
template< class... Args >
typename savintsev::List< T >::iterator savintsev::List< T >::emplace_back(Args &&... args)
{
  return insert(const_iterator(end()), T(args...));
}

template< typename T >
template< class... Args >
typename savintsev::List< T >::iterator savintsev::List< T >::emplace_front(Args &&... args)
{
  return insert(const_iterator(begin()), T(args...));
}

template< typename T >
void savintsev::List< T >::splice(const_iterator pos, List & rhs)
{
  list_size += rhs.list_size;
  rhs.list_size = 0;

  pos.node->prev->next = rhs.dummy->next;
  rhs.dummy->next->prev = pos.node->prev;
  rhs.dummy->prev->next = pos.node;
  pos.node->prev = rhs.dummy->prev;

  rhs.dummy->next = rhs.dummy;
  rhs.dummy->prev = rhs.dummy;
}

template< typename T >
void savintsev::List< T >::splice(const_iterator pos, List && rhs)
{
  splice(pos, rhs);
}

template< typename T >
void savintsev::List< T >::splice(const_iterator pos, List & rhs, const_iterator i)
{
  pos.node->prev->next = i.node;
  pos.node->prev = i.node;
  i.node->prev->next = i.node->next;
  i.node->next->prev = i.node->prev;
  i.node->next = pos.node;
  i.node->prev = pos.node->prev->prev;
  list_size++;
  rhs.list_size--;
}

template< typename T >
void savintsev::List< T >::splice(const_iterator pos, List && rhs, const_iterator i)
{
  splice(pos, rhs, i);
}

template< typename T >
void savintsev::List< T >::splice(const_it pos, List & rhs, const_it first, const_it last)
{
  size_t dist = std::distance(first, last);
  list_size += dist;
  rhs.list_size -= dist;

  ListNode< T > * temp_first_prev = first.node->prev;

  last.node->prev->next = pos.node;
  pos.node->prev->next = first.node;
  first.node->prev->next = last.node;
  first.node->prev = pos.node->prev;
  pos.node->prev = last.node->prev;
  last.node->prev = temp_first_prev;

  temp_first_prev = nullptr;
}

template< typename T >
void savintsev::List< T >::splice(const_it pos, List && rhs, const_it first, const_it last)
{
  splice(pos, rhs, first, last);
}

template< typename T >
void savintsev::List< T >::assign(const_iterator first, const_iterator last)
{
  clear();
  for (auto it = first; it != last; ++it)
  {
    push_back(*it);
  }
}

template< typename T >
void savintsev::List< T >::assign(size_t n, const T & value)
{
  clear();
  for (size_t i = 0; i < n; ++i)
  {
    push_back(value);
  }
}

template< typename T >
void savintsev::List< T >::assign(std::initializer_list< T > il)
{
  clear();
  for (auto it = il.begin(); it != il.end(); ++it)
  {
    push_back(*it);
  }
}

template< typename T >
typename savintsev::List< T >::iterator savintsev::List< T >::erase(const_iterator pos)
{
  iterator result(pos.node->next);
  pos.node->prev->next = pos.node->next;
  pos.node->next->prev = pos.node->prev;
  delete pos.node;
  --list_size;
  return result;
}

template< typename T >
typename savintsev::List< T >::iterator savintsev::List< T >::erase(const_iterator first, const_iterator last)
{
  iterator result();
  for (auto it = first; it != last; ++it)
  {
    result = erase(it);
  }
  return result;
}

template< typename T >
typename savintsev::List< T >::iterator savintsev::List< T >::insert(const_iterator pos, const T & value)
{
  ListNode< T > * new_node = new ListNode< T >(value, pos, pos->prev);
  list_size++;
  pos.node->prev->next = new_node;
  pos.node->prev = new_node;
  return iterator(new_node);
}

template< typename T >
typename savintsev::List< T >::iterator savintsev::List< T >::insert(const_iterator pos, size_t n, const T & value)
{
  const_iterator first(pos.node->prev);
  try
  {
    for (size_t i = 0; i < n; ++i)
    {
      insert(pos, value);
    }
  }
  catch (const std::bad_alloc & e)
  {
    erase(++first, pos);
    throw;
  }
  return ++first;
}

template< typename T >
typename savintsev::List< T >::iterator savintsev::List< T >::insert(const_it pos, const_it first, const_it last)
{
  const_iterator current_first(pos.node->prev);
  try
  {
    for (auto it = first; it != last; ++it)
    {
      insert(pos, *it);
    }
  }
  catch (const std::bad_alloc & e)
  {
    erase(++current_first, pos);
    throw;
  }
  return ++current_first;
}

template< typename T >
typename savintsev::List< T >::iterator savintsev::List< T >::insert(const_iterator pos, T && value)
{
  ListNode< T > * new_node = new ListNode< T >(std::move(value), pos, pos->prev);
  list_size++;
  pos.node->prev->next = new_node;
  pos.node->prev = new_node;
  return iterator(new_node);
}

template< typename T >
typename savintsev::List< T >::iterator savintsev::List< T >::insert(const_iterator pos, std::initializer_list< T > il)
{
  return insert(pos, il.begin(), il.end());
}

template< typename T >
void savintsev::List< T >::reverse() noexcept
{
  const_iterator it = cbegin();
  for (size_t i = 0; i < size(); ++i)
  {
    dummy->next = it.node->next;
    dummy->prev->next = it.node;
    it.node->prev = dummy->prev;
    dummy->prev = it.node;
    it.node->next = dummy;
    dummy->next->prev = dummy;
    it = cbegin();
  }
}

#endif
