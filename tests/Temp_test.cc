#include <memory>
#include "gtest/gtest.h"
#include "src/lib/Temp.h"

TEST(TempShould, ReturnSomething){
	std::unique_ptr<Temp> temp = std::make_unique<Temp>();
	std::string actual = temp->DoSomething();
	std::string expected = Something;
	EXPECT_EQ(expected, actual);
}
