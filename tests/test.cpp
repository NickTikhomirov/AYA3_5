// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include "SimpleStack.hpp"
#include "Stack.hpp"
#include <string>

struct for_emplace {
	int a = 0;
	std::string s;
	for_emplace() {}
	for_emplace(std::string p, int r) {
		a = r;
		s = p;
	}
	for_emplace(for_emplace&& r) {
		a = r.a;
		s = std::move(r.s);
	}
	void operator=(for_emplace&& r) {
		a = r.a;
		s = std::move(r.s);
	}
private:
	for_emplace(const for_emplace&);
	void operator=(const for_emplace&);
};

TEST(Stack1_base, push_pop_head) {
	SimpleStack<int> s;
	s.push(1);
	EXPECT_EQ(s.head(), 1);
	s.push(3);
	EXPECT_EQ(s.head(), 3);
	s.pop();
	EXPECT_EQ(s.head(), 1);
}

TEST(Stack1_base, Constructors) {
	SimpleStack<int> s(1234);
	EXPECT_EQ(s.head(), 1234);
	s.push(std::move(5678));
	EXPECT_EQ(s.head(), 5678);
	SimpleStack<int> z(std::move(9876));
	EXPECT_EQ(z.head(),9876);
}

TEST(Stack1_advanced, Move) {
	SimpleStack<int> s(1234);
	SimpleStack<int> z(std::move(s));
	EXPECT_EQ(z.head(), 1234);
	EXPECT_TRUE(!s);
	s = std::move(z);
	EXPECT_EQ(s.head(), 1234);
	EXPECT_TRUE(!z);
}

TEST(Stack1_advanced, Self) {
	SimpleStack<int> s(1234);
	s = std::move(s);
	EXPECT_EQ(s.head(), 1234);
}

TEST(Stack1_advanced, Except) {
	bool flag = false;
	SimpleStack<int> s;
	try {
		s.head();
	}
	catch (std::exception &e) {
		EXPECT_EQ(std::string(e.what()), "The stack is empty!");
		flag = true;
	}
	EXPECT_TRUE(flag);
}

TEST(Stack2_base, push_pop_head) {
	SimpleStack<int> s;
	SimpleStack<int> s1;
	s.push(1234);
	s1.push(3456);
	Stack<SimpleStack<int>> r;
	EXPECT_TRUE(!r);
	r.push(std::move(s));
	EXPECT_EQ(r.head().head(), 1234);
	r.push(std::move(s1));
	EXPECT_EQ(r.head().head(), 3456);
	EXPECT_TRUE(!s);
	s = std::move(r.pop());
	EXPECT_EQ(r.head().head(), 1234);
	EXPECT_EQ(s.head(), 3456);
}

TEST(Stack2_base, emplace) {
	Stack<for_emplace> tester;
	tester.push_emplace("hello",90);
	EXPECT_EQ(tester.head().a, 90);
	EXPECT_EQ(tester.head().s, std::string("hello"));
}

TEST(Stack2_base, Constructors) {
	SimpleStack<int> s;
	SimpleStack<int> s1;
	s.push(1234);
	s1.push(3456);
	Stack<SimpleStack<int>> r(std::move(s));
	EXPECT_EQ(r.head().head(), 1234);
	r.push(std::move(s1));
	EXPECT_EQ(r.head().head(), 3456);
}

TEST(Stack2_advanced, Move) {
	SimpleStack<int> s;
	s.push(1234);
	Stack<SimpleStack<int>> r(std::move(s));
	Stack<SimpleStack<int>> p(std::move(r));
	EXPECT_TRUE(!r);
	EXPECT_EQ(p.head().head(),1234);
	r = std::move(p);
	EXPECT_TRUE(!p);
	EXPECT_EQ(r.head().head(), 1234);
}

TEST(Stack2_advanced, Self) {
	SimpleStack<int> s;
	s.push(1234);
	Stack<SimpleStack<int>> r(std::move(s));
	r = std::move(r);
	EXPECT_EQ(r.head().head(), 1234);
}

TEST(Stack2_advanced, Except) {
	bool flag = false;
	Stack<Stack<int>> r;
	try {
		r.head();
	}
	catch (std::exception & e) {
		EXPECT_EQ(std::string(e.what()), "The stack is empty!");
		flag = true;
	}
	EXPECT_TRUE(flag);
}

