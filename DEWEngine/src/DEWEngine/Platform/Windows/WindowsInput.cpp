#include "dewpch.h"
#include "WindowsInput.h"

#include "DEWEngine/Application.h"
#include <GLFW/glfw3.h>

namespace DEWEngine {

	Input* Input::s_Instance = new WindowsInput(); // Has no Constructor, so we can directly instantiate it here

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		// GLFW uses the GLFWwindow pointer to check key states, so we need to get the current window
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT; // Return true if the key is pressed or held down

	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS; 
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos }; // Return mouse position as a pair of floats
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl(); // Get mouse position using the existing method
		return x; // Return the X coordinate of the mouse position
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl(); 
		return y; 
	}

}