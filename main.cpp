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
    return new BiList< T >{d, nullptr, nullptr};
  }
  BiList< T >* head = new BiList< T >{d, h, nullptr};
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
  BiList< T >* node = new BiList< T >{d, h->next, h};
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
  BiList< T >* node = new BiList< T >{d, h, h->prev};
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
  delete h;
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
    delete current;
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
  clear(node, nullptr);
}

int main()
{}
