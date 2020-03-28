#include <memory>
#include "gtest/gtest.h"
#include "src/lib/Term.h"

TEST(TermShould, ReturnSomething){
	std::unique_ptr<Term> term = std::make_unique<Term>();
	std::string actual = term->DoSomething();
	std::string expected = Something;
	EXPECT_EQ(expected, actual);
}
