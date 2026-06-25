#include <YakoEngine.h>

int main()
{
    YakoEngine::EngineSettings settings;
    YakoEngine::Engine         engine(settings);

    YakoEngine::WindowSettings window1Settings{};

    if (auto creation_res = engine.CreateWindow(window1Settings); creation_res.has_value())
    {
        auto windowId   = creation_res.value();
        auto window_res = engine.GetWindowById(windowId);

        if (window_res.has_value())
        {
            auto window = window_res.value();
            window->Hide();
            window->Open();
            window->Close();
        }

        engine.Run();
    }

    return 0;
}