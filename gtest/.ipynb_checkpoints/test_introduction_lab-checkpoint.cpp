// Tests for Introduction Lab (C++) mirroring the provided Java autograder

#include <gtest/gtest.h>

// Access Bag::contents for deterministic setup like the Java tests
#define private public
#include "../include/Bag.hpp"
#undef private
#include "../include/Token.hpp"

#include <string>
#include <vector>

namespace {

// Helper to set up a Bag with deterministic contents and compute expectations
struct BagSetupResult {
    int sum{};
    int num_high{};
    int first_green{-1};
};

BagSetupResult setupBagWithKnownContents(Bag& bag) {
    static const int NUM_TOKENS = 16;
    static const std::vector<std::string> colors = {
        "Red", "Yellow", "Green", "Cyan", "Green",
        "Blue", "Violet", "Green"
    };

    BagSetupResult r;
    // The bag was constructed with NUM_TOKENS size; fill deterministically
    for (int i = 0; i < NUM_TOKENS; ++i) {
        int value = i % Token::MAX_VALUE; // MAX_VALUE is 10
        const std::string& color = colors[static_cast<size_t>(i) % colors.size()];

        bag.contents[static_cast<size_t>(i)].setValue(value);
        bag.contents[static_cast<size_t>(i)].setColor(color);

        r.sum += value;
        if (value > Token::MAX_VALUE / 2)
            r.num_high++;
        if (color == "Green" && r.first_green < 0)
            r.first_green = i;
    }
    return r;
}

} // namespace

// --- Token tests ---
TEST(TokenTests, GetValueReturnsAsConstructed) {
    Token t1{"None", 1};
    Token t10{"None", 10};
    EXPECT_EQ(1, t1.getValue());
    EXPECT_EQ(10, t10.getValue());
}

TEST(TokenTests, SetValueChangesValue) {
    Token t{"None", 1};
    t.setValue(6);
    EXPECT_EQ(6, t.getValue());
}

TEST(TokenTests, SetColorChangesColor) {
	Token t{"None", 1};
	t.setColor("Beige");
	EXPECT_EQ(std::string("Beige"), t.getColor());
}

TEST(TokenTests, IsMaxAndHighValue) {
	Token t10{"None", 10};
	EXPECT_EQ(true, t10.isMax());
	EXPECT_EQ(true, t10.isHighValue());

	Token t6{"None", 6};
	EXPECT_EQ(false, t6.isMax());
	EXPECT_EQ(true, t6.isHighValue());

	Token t5{"None", 5};
	EXPECT_EQ(false, t5.isMax());
	EXPECT_EQ(false, t5.isHighValue());

	Token t1{"None", 1};
	EXPECT_EQ(false, t1.isMax());
	EXPECT_EQ(false, t1.isHighValue());
}

TEST(TokenTests, ToStringDescribesToken){
	Token t{"Blue", 4};

	EXPECT_EQ(std::string("Token's color is Blue and has value 4 "), t.toString());
}


// --- Bag tests ---

TEST(BagTests, AddTokensReturnsValueSum) {
	Bag b{16};

	BagSetupResult r = setupBagWithKnownContents(b);

	EXPECT_EQ(r.sum, b.addTokens());
}

TEST(BagTests, highValueTokensReturnsCorrectly) {
	Bag b{16};

	BagSetupResult r = setupBagWithKnownContents(b);

	EXPECT_EQ(r.num_high, b.highValueTokens());
}

TEST(BagTests, firstGreenReturnsCorrectly) {
	Bag b{16};

	BagSetupResult r = setupBagWithKnownContents(b);

	EXPECT_EQ(r.first_green, b.firstGreen());
}
