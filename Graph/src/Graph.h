#include <memory>

class Vertex<typename T> {
public:
  explicit void Vertex(std::shared_ptr<T> v = std::shared_ptr<T>(new T())) :
    m_value(v) { }
  void ~Vertex() {
    m_value.reset();
  }
  bool link(std::shared_ptr);
  bool unlink();
private:
  std::shared_ptr<T> m_value;
};

struct Edge<typename U, typename V, typename E> {
  std::weak_ptr<Vertex<U>> u;
  std::weak_ptr<Vertex<V>> v;
  std::unique_ptr<E> w;
  void ~Edge() {
    u.unlink(v);
    v.unlink(u);
  }
};

class Graph<typename VertexDescriptor, typename EdgeDescriptor> {
public:
  explicit Graph(std::initializer_list<VertexDescriptor> list);
}


