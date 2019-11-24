// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <utility>
#include <stdexcept>


template <typename T>
class SimpleStack
{
	struct Node {
		T data;
		Node* next = nullptr;
		Node(T& arg) { data = arg; }
		Node(T&& arg) {	data = std::move(arg); }
		static Node* create(const T& arg, Node* pointer) {
			Node* n = new Node(arg);
			n->next = pointer;
			return n;
		}
		static Node* create(T&& arg, Node* pointer) {
			Node* n = new Node(std::move(arg));
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
	SimpleStack(const SimpleStack& a) {}
	void operator=(const SimpleStack& a) {}
	Node* top = nullptr;

public:
	SimpleStack() {}
	SimpleStack(T&& value) {
		push(std::move(value));
	}
	SimpleStack(const T& value) {
		push(value);
	}
	SimpleStack(SimpleStack&& r) {
		top = r.top;
		r.top = nullptr;
	}
	void operator=(SimpleStack&& r) {
		if (this == &r) return;
		~SimpleStack();
		top = r.top;
		r.top = nullptr;
	}
	void push(T&& value) { top = Node::create(std::move(value), top);}
	void push(const T& value) {	top = Node::create(value, top);}
	void pop() {
		if (top == nullptr) return;
		Node* temp = top;
		top = temp->next;
		temp->next = nullptr;
		delete temp;
	}
	const T& head() const {	
		if (top == nullptr) throw std::logic_error{ "The stack is empty!" };
		return top->data;
	}
	~SimpleStack() {
		if (top != nullptr) {
			delete top;
			top = nullptr;
		}
	}
	operator bool() const{
		return top != nullptr;
	}
};


#endif // INCLUDE_HEADER_HPP_
