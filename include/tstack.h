// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template <typename T, int N>
class TStack {
 private:
  T data[N];
  int topIndex;

 public:
  TStack() : data{}, topIndex(-1) {}

  void push(const T& value) {
    if (topIndex < N - 1) {
      data[++topIndex] = value;
    }
  }

  T pop() {
    if (topIndex >= 0) {
      return data[topIndex--];
    }
    return T{};
  }

  T top() const {
    if (topIndex >= 0) {
      return data[topIndex];
    }
    return T{};
  }

  bool isEmpty() const {
    return topIndex == -1;
  }

  int size() const {
    return topIndex + 1;
  }
};

#endif  // INCLUDE_TSTACK_H_
