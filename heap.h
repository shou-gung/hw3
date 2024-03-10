#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> data;
  int d;
  PComparator comp;


};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : data(), d(m), comp(c) {}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const{
  return data.empty();
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const {
  return data.size();
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T &item) {

  data.push_back(item);

  size_t index = size() - 1;

  while (index > 0) {
    T& child = data[index];
    size_t parent_index = (index - 1) / d;
    T& parent = data[parent_index];

    if (comp(child, parent)) {
      T temp = child;
      child = parent;
      parent = temp;
      index = parent_index;
    } else {
      break;
    }
  }
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap underflow: cannot return from empty heap");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element

  return data.front();

}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap underflow: cannot pop empty heap");
  }

  data[0] = data.back();
  data.pop_back();

  size_t index = 0;
  size_t heap_size = size();
  size_t child_indexes[d];

  while (index < heap_size) {
    size_t pIndex;
    size_t min_child_index = d * index + 1;
    size_t max_child_index;
    
    if (min_child_index + d < heap_size) {
      max_child_index = min_child_index;
    } else {
      max_child_index = heap_size;
    }

    for (size_t i = min_child_index + 1; i < max_child_index; i++) {
      if (comp(data[i], data[min_child_index])) {
        min_child_index = i;
      }
    }

    if (min_child_index < max_child_index && comp(data[min_child_index], data[index])) {
      T temp = data[min_child_index];
      data[min_child_index] = data[index];
      data[index] = temp;
    } else {
      break;
    }
  }
}


#endif

