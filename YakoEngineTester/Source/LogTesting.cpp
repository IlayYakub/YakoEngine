#include <gtest/gtest.h>
#include <YakoEngine.h>

using namespace YakoEngine;

namespace LogTesting
{

TEST(LogTest, DuplicateCreationReturnsError)
{
    EngineSettings settings;
    Engine         engine(settings);

    auto duplicate_result = Log::CreateInstance();

    EXPECT_EQ(duplicate_result.error(), SingletonWarnings::COMMAND_IGNORED);
}

TEST(LogTest, LoggingMacrosExecuteWithoutCrashing)
{
    EngineSettings settings;
    Engine         engine(settings);

    EXPECT_NO_FATAL_FAILURE({
        YAKO_TRACE(TestCategory, "Test trace with arg: {}", 42);
        USER_INFO(UserCategory, "Hello from the user side!");
        YAKO_WARN(System, "Testing warning behavior");
    });
}

}  // namespace LogTesting