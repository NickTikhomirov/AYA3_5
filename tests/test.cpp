// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include "SimpleStack.hpp"

TEST(Stack1_base, push_pop) {
	SimpleStack<int> s;
	s.push(1);
	EXPECT_EQ(s.head(), 1);
	s.push(3);
	EXPECT_EQ(s.head(), 3);
	s.pop();
	EXPECT_EQ(s.head(), 1);
}
