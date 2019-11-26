// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER1_HPP_
#define INCLUDE_HEADER1_HPP_

#include <utility>
#include <stdexcept>


template <typename T>
class Stack
{
	struct Node {
		T data;
		Node* next = nullptr;
		Node(T&& arg) {	data = std::forward<T>(arg); }
		static Node* create(T&& arg, Node* pointer) {
			Node* n = new Node(std::forward<T>(arg));
			n->next = pointer;
			return n;
		}
		~Node() {
			if (next != nullptr) {
				delete next;
				next = nullptr;
			}
		}
	};
	Stack(const Stack& a) {}
	void operator=(const Stack& a) {}
	Node* top = nullptr;

public:
	Stack() {}
	Stack(T&& value) {
		push(std::forward<T>(value));
	}
	Stack(Stack&& r) {
		top = r.top;
		r.top = nullptr;
	}
	void operator=(Stack&& r) {
		if (this == &r) return;
		~Stack();
		top = r.top;
		r.top = nullptr;
	}
	void push(T&& value) { top = Node::create(std::forward<T>(value), top);}
	template<typename ... Args>
	void push_emplace(Args&& ...value) {
		T object_brrrrr{ std::forward<Args>(value)... };
		top = Node::create(std::move(object_brrrrr),top);
	}
	T pop() {
		if (top == nullptr) throw std::logic_error{ "The stack is empty!" };
		T t(std::move(top->data));
		Node* temp = top;
		top = temp->next;
		temp->next = nullptr;
		delete temp;
		return t;
	}
	const T& head() const {	
		if (top == nullptr) throw std::logic_error{ "The stack is empty!" };
		return top->data;
	}
	~Stack() {
		if (top != nullptr) {
			delete top;
			top = nullptr;
		}
	}
	operator bool() const{
		return top != nullptr;
	}
};


#endif // INCLUDE_HEADER1_HPP_
