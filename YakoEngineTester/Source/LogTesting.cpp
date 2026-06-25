#include <gtest/gtest.h>
#include <YakoEngine.h>

TEST(LogTest, DuplicateCreationReturnsError)
{
    YakoEngine::EngineSettings settings;
    YakoEngine::Engine         engine(settings);

    auto duplicate_result = YakoEngine::Log::CreateInstance();

    EXPECT_EQ(duplicate_result.error(), YakoEngine::SingletonWarnings::COMMAND_IGNORED);
}

TEST(LogTest, LoggingMacrosExecuteWithoutCrashing)
{
    YakoEngine::EngineSettings settings;
    YakoEngine::Engine         engine(settings);

    EXPECT_NO_FATAL_FAILURE({
        YAKO_TRACE(TestCategory, "Test trace with arg: {}", 42);
        USER_INFO(UserCategory, "Hello from the user side!");
        YAKO_WARN(System, "Testing warning behavior");
    });
}