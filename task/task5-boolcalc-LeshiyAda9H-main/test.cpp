#include "gtest/gtest.h"
#include "boolexpr.h"


TEST(Constr, easy) {
	BooleanExpression exp1("x1 ^ x2");
	BooleanExpression exp2("x50 & 1");
	BooleanExpression exp3("x1 | ~x10");
	
	EXPECT_EQ((std::string)exp1, "(x1 ^ x2)");
	EXPECT_EQ((std::string)exp2, "(x50 & 1)");
	EXPECT_EQ((std::string)exp3, "(x1 | ~x10)");
}

TEST(Constr, middle) {
	BooleanExpression exp1("x1 ^ x2 + x70");
	BooleanExpression exp2("x50 & 1 > x999");
	BooleanExpression exp3("x1 | ~x10 < x121");

	EXPECT_EQ((std::string)exp1, "(x1 ^ (x2 + x70))");
	EXPECT_EQ((std::string)exp2, "((x50 & 1) > x999)");
	EXPECT_EQ((std::string)exp3, "(x1 | (~x10 < x121))");
}


TEST(Constr, hard) {
	BooleanExpression exp1("x1 ^ ((x2 + x70) & (x59 v x88)) ");
	BooleanExpression exp2("x50 & (1 > x999) | x1 | x1");
	BooleanExpression exp3("~(x1 | ~x10) < x121 + ~~x77 & 0");

	EXPECT_EQ((std::string)exp1, "(x1 ^ ((x2 + x70) & (x59 v x88)))");
	EXPECT_EQ((std::string)exp2, "(((x50 & (1 > x999)) | x1) | x1)");
	EXPECT_EQ((std::string)exp3, "(~(x1 | ~x10) < (x121 + (~~x77 & 0)))");
}

TEST(Constr, identity) {
	BooleanExpression exp1("x1 v ~x1");
	BooleanExpression exp2("x50 & ~x50");
	BooleanExpression exp3("0 | 1");

	EXPECT_EQ((std::string)exp1, "(x1 v ~x1)");
	EXPECT_EQ((std::string)exp2, "(x50 & ~x50)");
	EXPECT_EQ((std::string)exp3, "(0 | 1)");
}

///////////////////////////////////////////////////////////////

TEST(zig, easy) {
	BooleanExpression exp1("x1 ^ x2");
	BooleanExpression exp2("x50 & 1");
	BooleanExpression exp3("x1 | ~x10");

	EXPECT_EQ(exp1.zhegalkin(), "1 + x2 + x1 + x1 & x2");
	EXPECT_EQ(exp2.zhegalkin(), "x50");
	EXPECT_EQ(exp3.zhegalkin(), "1 + x1 + x1 & x10");
}

TEST(zig, middle) {
	BooleanExpression exp1("x1 ^ x2 + x3");
	BooleanExpression exp2("x1 & 1 > x2");
	BooleanExpression exp3("x1 | ~x2 < x3");

	EXPECT_EQ(exp1.zhegalkin(), "1 + x3 + x2 + x1 + x1 & x3 + x1 & x2");
	EXPECT_EQ(exp2.zhegalkin(), "1 + x1 + x1 & x2");
	EXPECT_EQ(exp3.zhegalkin(), "1 + x1 + x1 & x2 & x3");
}


TEST(zig, hard) {
	BooleanExpression exp1("x1 ^ ((x2 + x3) & (x1 v x2)) ");
	BooleanExpression exp2("x1 & (1 > x3) | x2 | x2");
	BooleanExpression exp3("~(x1 | ~x2) < x3 + ~~1 & 0");

	EXPECT_EQ(exp1.zhegalkin(), "1 + x2 + x2 & x3 + x1 + x1 & x2 + x1 & x2 & x3");
	EXPECT_EQ(exp2.zhegalkin(), "1 + x2 + x1 & x2 & x3");
	EXPECT_EQ(exp3.zhegalkin(), "1 + x3 + x1 & x3 + x1 & x2 & x3");
}

TEST(zig, identity) {
	BooleanExpression exp1("x1 v ~x1");
	BooleanExpression exp2("x50 & ~x50");
	BooleanExpression exp3("0");
	BooleanExpression exp4("1");

	EXPECT_EQ(exp1.zhegalkin(), "1");
	EXPECT_EQ(exp2.zhegalkin(), "0");
	EXPECT_EQ(exp3.zhegalkin(), "0");
	EXPECT_EQ(exp4.zhegalkin(), "1");
}

///////////////////////////////////////////////////////////////

TEST(cnf, easy) {
	BooleanExpression exp1("x1 ^ x2");
	BooleanExpression exp2("x1 & 1");
	BooleanExpression exp3("x1 | ~x2");

	EXPECT_EQ(exp1.cnf(), "(x1 v ~x2) & (~x1 v x2) & (~x1 v ~x2)");
	EXPECT_EQ(exp2.cnf(), "x1");
	EXPECT_EQ(exp3.cnf(), "(~x1 v x2)");
}

TEST(cnf, middle) {
	BooleanExpression exp1("x1 ^ x2 + x3");
	BooleanExpression exp2("x1 & 1 > x2");
	BooleanExpression exp3("x1 | ~x2 < x3");

	EXPECT_EQ(exp1.cnf(), "(x1 v x2 v ~x3) & (x1 v ~x2 v x3) & (~x1 v x2 v x3) & (~x1 v x2 v ~x3) & (~x1 v ~x2 v x3) & (~x1 v ~x2 v ~x3)");
	EXPECT_EQ(exp2.cnf(), "(~x1 v x2)");
	EXPECT_EQ(exp3.cnf(), "(~x1 v x2 v x3) & (~x1 v x2 v ~x3) & (~x1 v ~x2 v x3)");
}


TEST(cnf, hard) {
	BooleanExpression exp1("x1 ^ ((x2 + x3) & (x1 v x2)) ");
	BooleanExpression exp2("x1 & (1 > x3) | x2 | x2");
	BooleanExpression exp3("~(x1 | ~x2) < x3 + ~~1 & 0");

	EXPECT_EQ(exp1.cnf(), "(x1 v ~x2 v x3) & (~x1 v x2 v x3) & (~x1 v x2 v ~x3) & (~x1 v ~x2 v x3) & (~x1 v ~x2 v ~x3)");
	EXPECT_EQ(exp2.cnf(), "(x1 v ~x2 v x3) & (x1 v ~x2 v ~x3) & (~x1 v ~x2 v x3)");
	EXPECT_EQ(exp3.cnf(), "(x1 v x2 v ~x3) & (x1 v ~x2 v ~x3) & (~x1 v ~x2 v ~x3)");
}

TEST(cnf, identity) {
	BooleanExpression exp1("x1 v ~x1");
	BooleanExpression exp2("x50 & ~x50");
	BooleanExpression exp3("0");
	BooleanExpression exp4("1");

	EXPECT_EQ(exp1.cnf(), "1");
	EXPECT_EQ(exp2.cnf(), "x50 & ~x50");
	EXPECT_EQ(exp3.cnf(), "0");
	EXPECT_EQ(exp4.cnf(), "1");
}

///////////////////////////////////////////////////////////////

TEST(dnf, easy) {
	BooleanExpression exp1("x1 ^ x2");
	BooleanExpression exp2("x1 & 1");
	BooleanExpression exp3("x1 | ~x2");

	EXPECT_EQ(exp1.dnf(), "~x1 & ~x2");
	EXPECT_EQ(exp2.dnf(), "x1");
	EXPECT_EQ(exp3.dnf(), "~x1 & ~x2 v ~x1 & x2 v x1 & x2");
}

TEST(dnf, middle) {
	BooleanExpression exp1("x1 ^ x2 + x3");
	BooleanExpression exp2("x1 & 1 > x2");
	BooleanExpression exp3("x1 | ~x2 < x3");

	EXPECT_EQ(exp1.dnf(), "~x1 & ~x2 & ~x3 v ~x1 & x2 & x3");
	EXPECT_EQ(exp2.dnf(), "~x1 & ~x2 v ~x1 & x2 v x1 & x2");
	EXPECT_EQ(exp3.dnf(), "~x1 & ~x2 & ~x3 v ~x1 & ~x2 & x3 v ~x1 & x2 & ~x3 v ~x1 & x2 & x3 v x1 & x2 & x3");
}

TEST(dnf, identity) {
	BooleanExpression exp1("x1 v ~x1");
	BooleanExpression exp2("x50 & ~x50");
	BooleanExpression exp3("0");
	BooleanExpression exp4("1");

	EXPECT_EQ(exp1.dnf(), "~x1 v x1");
	EXPECT_EQ(exp2.dnf(), "0");
	EXPECT_EQ(exp3.dnf(), "0");
	EXPECT_EQ(exp4.dnf(), "1");
}

///////////////////////////////////////////////////////////////