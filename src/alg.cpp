// Copyright 2021 NNTU-CS
// include/tpqueue.h
#ifndef TPQUEUE_H
#define TPQUEUE_H

template <typename T>
struct Node {
  T data;
  Node<T>* next;
  explicit Node(const T& data)
      : data(data), next(nullptr) {}  // ← explicit добавлен
};

template <typename T>
class TPQueue {
 private:
  Node<T>* head;
  int size;

 public:
  TPQueue() : head(nullptr), size(0) {}
  ~TPQueue();

  void push(const T& value);
  T pop();
  bool isEmpty() const { return head == nullptr; }
  int getSize() const { return size; }
};

template <typename T>
TPQueue<T>::~TPQueue() {
  while (!isEmpty()) {
    pop();
  }
}

template <typename T>
void TPQueue<T>::push(const T& value) {
  Node<T>* newNode = new Node<T>(value);

  if (isEmpty() || head->data.prior < value.prior) {
    newNode->next = head;
    head = newNode;
  } else {
    Node<T>* current = head;
    while (current->next != nullptr &&
           current->next->data.prior >= value.prior) {
      current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
  }
  size++;
}

template <typename T>
T TPQueue<T>::pop() {
  if (isEmpty()) {
    throw "Queue is empty";
  }

  Node<T>* temp = head;
  T value = temp->data;
  head = head->next;
  delete temp;
  size--;
  return value;
}

#endif  // TPQUEUE_H
