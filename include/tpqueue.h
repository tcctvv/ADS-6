// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template <typename T>
class TPQueue {
    struct Node {
        T     data;
        Node* sled;

        explicit Node(const T& d, Node* n = nullptr)
            : data(d), sled(n) {}
    };

    Node* head_ = nullptr;
    Node* tail_ = nullptr;

 public:
    TPQueue()  = default;
    ~TPQueue() {
      clear();
    }
    TPQueue(const TPQueue&)            = delete;
    TPQueue& operator=(const TPQueue&) = delete;
    [[nodiscard]] bool empty() const noexcept { return head_ == nullptr; }

    void clear() noexcept {
        while (head_) {
            Node* temp = head_;
            head_ = head_->sled;
            delete temp;
        }
        tail_ = nullptr;
    }

    void push(const T& value) {
        Node* node = new Node(value);

        if (empty()) {
            head_ = tail_ = node;
            return;
        }

        if (value.prior > head_->data.prior) {
            node->sled = head_;
            head_ = node;
            return;
        }

        Node* cur = head_;
        while (cur->sled && cur->sled->data.prior >= value.prior) {
            cur = cur->sled;
        }

        node->sled = cur->sled;
        cur->sled  = node;
        if (!node->sled) tail_ = node;
    }

    T pop() {
        if (empty()) {
            throw std::out_of_range (
                "TPQueue::front(): queue is empty");
        }

        Node* temp = head_;
        T     val = head_->data;
        head_     = head_->sled;
        if (!head_) tail_ = nullptr;
        delete temp;
        return val;
    }

    const T& front() const {
        if (empty()) {
            throw std::out_of_range (
                "TPQueue::front(): queue is empty");
        }
        return head_->data;
    }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
