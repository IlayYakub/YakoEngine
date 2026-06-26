#pragma once

#include "Utility/Singleton.h"
#include "Utility/NonCopyableMoveable.h"

#include "Engine.h"
#include "Core/Log/Log.h"
#include "Platform/Window/IWindow.h"
#include "Platform/Window/IWindowManager.h"
#include "Platform/Window/GLFW/GLFWwindowWrapper.h"
#include "Platform/Window/GLFW/GLFWwindowWrapperManager.h"
#include "Core/Event/Event.h"
#include "Core/Event/KeyboardEvents.h"
#include "Core/Event/MouseEvents.h"
#include "Core/Event/WindowEvents.h"
#include "Core/Layer/Layer.h"
#include "Core/Layer/LayerStack.h"