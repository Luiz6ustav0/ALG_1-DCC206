#ifndef QUEUE_H
#define QUEUE_H

struct Node;

// Pilha de números inteiros.
class Stack {
  public:
    // Representa uma exceção que ocorre quando a pilha está vazia.
    class EmptyException {};
  
    // Constrói uma pilha vazia.
    Stack();
    
    // Insere um elemento no topo da pilha.
    void push(unsigned elem);
    
    // Retorna o elemento no topo da pilha.
    // Lança EmptyException caso a pilha esteja vazia.
    unsigned top() const;

    // Remove o elemento no topo da pilha.
    // Lança EmptyException caso a pilha esteja vazia.
    void pop(); 
    
    // Retorna o número de elementos na pilha.
    unsigned count() const;

    ~Stack();
  private:
    Node* _top;
    unsigned _count;
};

#endif