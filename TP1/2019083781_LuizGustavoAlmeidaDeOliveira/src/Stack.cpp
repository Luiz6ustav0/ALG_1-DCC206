#include "Stack.h"

struct Node {
  unsigned elem;
  Node* next;
};

Stack::Stack() {
    this->_top = nullptr;
    this->_count = 0;
}

Stack::~Stack() {
    while (this->_top != nullptr) {
        this->pop();
    }
}

void Stack::push(unsigned elem) {
    Node *newNode = new Node();
    newNode->elem = elem;
    if (this->_top != nullptr) {
        newNode->next = this->_top;
        this->_top = newNode;
    } else {
        this->_top = newNode;
        newNode->next = nullptr;
    }
    this->_count++;
}

void Stack::pop() {
    if (this->_top != nullptr) {
        Node* topElementNext = this->_top->next;
        delete this->_top;
        if (topElementNext != nullptr) this->_top = topElementNext;
        else this->_top = nullptr;
        this->_count--;
    } else throw EmptyException();
}

unsigned Stack::top() const {
    int topElem;
    if (this->_top != nullptr) {
        topElem = this->_top->elem;
        return topElem;
    } else {
        throw EmptyException();
        return -1;
    }
}

unsigned Stack::count() const {
    return this->_count;
}