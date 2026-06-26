#include <gtest/gtest.h>
#include <YakoEngine.h>

using namespace YakoEngine;

namespace LogTesting
{

TEST(LogSystemTest, Core)
{
    EngineSettings defaultEngineSettings;
    Engine         engine(defaultEngineSettings);

    auto duplicateInitializationResult = Log::CreateInstance();

    EXPECT_FALSE(duplicateInitializationResult.has_value());
    EXPECT_EQ(duplicateInitializationResult.error(), SingletonWarnings::COMMAND_IGNORED);

    EXPECT_NO_FATAL_FAILURE({
        YAKO_TRACE(TestCategory, "Test trace with arg: {}", 42);
        USER_INFO(UserCategory, "Hello from the user side!");
        YAKO_WARN(System, "Testing warning behavior");
    });
}

}  // namespace LogTesting