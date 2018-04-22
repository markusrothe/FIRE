#include "tokenize.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>

namespace
{
    std::string const testString = "TEST 123 abc &5ds30vxcv2e sdas12 ''*Ä'D$Q";
    
    class TokenizeTest : public ::testing::Test
    {
    public:
        std::vector<std::string> m_tokens;
    };
} // namespace

TEST_F(TokenizeTest, TokenizeWithWhitespaceDelimiterShouldCorrectlySplitStrings)
{
    Tokenize(testString, m_tokens, " ");

    ASSERT_EQ(m_tokens.size(), 6);
    EXPECT_STREQ(m_tokens[0].c_str(), "TEST");
    EXPECT_STREQ(m_tokens[1].c_str(), "123");
    EXPECT_STREQ(m_tokens[2].c_str(), "abc");
    EXPECT_STREQ(m_tokens[3].c_str(), "&5ds30vxcv2e");
    EXPECT_STREQ(m_tokens[4].c_str(), "sdas12");
    EXPECT_STREQ(m_tokens[5].c_str(), "''*Ä'D$Q");
}
