#include <YakoEngine.h>

int main()
{
    YakoEngine::EngineSettings settings;
    YakoEngine::Engine         engine(settings);

    USER_FATAL(Log, "Hello");

    engine.Run();
}