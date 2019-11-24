// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include "SimpleStack.hpp"
#include <string>

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

