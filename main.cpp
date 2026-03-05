/*
Неявный интерфейс:
1. Конструктор копирования
2. Деструктор
3. Конструктор копирования у F
4. Оператор () у F
*/

#include <iostream>

template< class T >
struct BiList
{
  T val;
  BiList< T >* next;
  BiList< T >* prev;
};

template< class T >
BiList< T >* updateHead(BiList< T >* h, const T& d)
{
  if (!h)
  {
    return new BiList< T >{d, nullptr, nullptr}; // T::T(const T &)
  }
  BiList< T >* head = new BiList< T >{d, h, nullptr}; // T::T(const T &)
  h->prev = head;
  return head;
}

template< class T >
BiList< T >* addAfter(BiList< T >* h, const T& d)
{
  if (!h)
  {
    return nullptr;
  }
  BiList< T >* node = new BiList< T >{d, h->next, h}; // T::T(const T &)
  if (h->next)
  {
    h->next->prev = node;
  }
  h->next = node;
  return node;
}

template< class T >
BiList< T >* addBefore(BiList< T >* h, const T& d)
{
  if (!h)
  {
    return nullptr;
  }
  BiList< T >* node = new BiList< T >{d, h, h->prev}; // T::T(const T &)
  if (h->prev)
  {
    h->prev->next = node;
  }
  h->prev = node;
  return node;
}

template< class T >
BiList< T >* remove(BiList< T >* h) noexcept
{
  if (!h)
  {
    return nullptr;
  }
  BiList< T >* next = h->next;
  BiList< T >* prev = h->prev;
  delete h; // T::~T()
  if (next)
  {
    next->prev = prev;
  }
  if (prev)
  {
    prev->next = next;
  }
  return next;
}

template< class T >
BiList< T >* removeAfter(BiList< T >* h) noexcept
{
  if (!h->next)
  {
    return nullptr;
  }
  return remove(h->next); // T::~T()
}

template< class T >
BiList< T >* removeBefore(BiList< T >* h) noexcept
{
  if (!h->prev)
  {
    return nullptr;
  }
  return remove(h->prev); // T::~T()
}

template< class T >
BiList< T >* clear(BiList< T >* start, BiList< T >* end) noexcept
{
  if (!start)
  {
    return nullptr;
  }
  BiList< T >* prev = start->prev;
  BiList< T >* current = start;
  while (current != end)
  {
    BiList< T >* next = current->next;
    delete current; // T::~T()
    current = next;
  }
  if (prev)
  {
    prev->next = end;
  }
  if (end)
  {
    end->prev = prev;
  }
  return end;
}

template< class T >
void clearAll(BiList< T >* node) noexcept
{
  if (!node)
  {
    return;
  }
  while (node->prev)
  {
    node = node->prev;
  }
  clear< T >(node, nullptr); // T::~T()
}

template< class T, class F >
F forwardTraverse(F f, BiList< T >* start, BiList< T >* end) // F::F(const F &)
{
  if (!start)
  {
    return f;
  }
  for (; start != end; start = start->next)
  {
    f(start->val); // T::T(const T &); F::operator()(T)
  }
  return f;
}

template< class T, class F >
F backTraverse(F f, BiList< T >* start, BiList< T >* end) // F::F(const F &)
{
  if (!start)
  {
    return f;
  }
  for (; start != end; start = start->prev)
  {
    f(start->val); // T::T(const T &); F::operator()(T)
  }
  return f;
}

template< class T, class F >
F traverseAll(F f, BiList< T >* node) // F::F(const F &)
{
  while(node->prev)
  {
    node = node->prev;
  }
  return forwardTraverse< T >(f, node, nullptr); // T::T(const T &); F::operator()(T)
}

template< class T >
BiList< T >* convert(const T* arr, size_t s)
{
  if (!arr || !s)
  {
    return nullptr;
  }
  BiList< T >* head = updateHead< T >(nullptr, arr[0]);;
  BiList< T >* current = head;
  try
  {
    for (size_t i = 1; i < s; ++i)
    {
      current = addAfter(current, arr[i]);
    }
  }
  catch (...)
  {
    clearAll(head);
    throw;
  }
  return head;
}

template< class T>
size_t size(BiList< T >* node)
{
  size_t count = 0;
  traverseAll([& count](const T &){count++;}, node);
  return count;
}

int main()
{
  int arr[5] = {1, 2, 3, 4, 5};
  BiList< int >* head = convert(arr, 5);
  for(; head->next; head = head->next)
  {
    std::cout << head->val << " ";
  }
  std::cout << head->val << "\n";
  traverseAll([](const int & x) { std::cout << x << "\n";}, head);
  std::cout << size(head) << "\n";
}
