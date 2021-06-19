#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Stack.h"

TEST_CASE("Testing the stack implementation") {
  Stack stack;
  REQUIRE(stack.count() == 0);
  stack.push(0);
  CHECK(stack.count() == 1);
  stack.push(1);
  CHECK(stack.count() == 2);
  stack.push(2);
  CHECK(stack.count() == 3);
  stack.pop();
  CHECK(stack.count() == 2);
  stack.pop();
  CHECK(stack.count() == 1);
  stack.pop();
  CHECK(stack.count() == 0);
}

TEST_CASE("The last element in is the first element out") {
  Stack stack;
  stack.push(0);
  CHECK(stack.top() == 0);
  stack.push(1);
  CHECK(stack.top() == 1);
  stack.pop();
  CHECK(stack.top() == 0);
}

TEST_CASE("Check if top/pop throw the EmptyException") {
  Stack stack;
  CHECK_THROWS_AS(stack.top(), Stack::EmptyException&);
  CHECK_THROWS_AS(stack.pop(), Stack::EmptyException&);
}