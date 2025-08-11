#include "dewpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "DEWEngine/Platform/OpenGL/ImGuiOpenGLRenderer.h"

#include "DEWEngine/Application.h"

//Temporary
#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace DEWEngine {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	//Keyboard Configs 
	//**TEMPORARY**: should use DEWEngine KeyCodes
	ImGuiKey KeyMap(int keycode) {
		switch (keycode) {
		case GLFW_KEY_TAB: return ImGuiKey_Tab;
		case GLFW_KEY_LEFT: return ImGuiKey_LeftArrow;
		case GLFW_KEY_RIGHT: return ImGuiKey_RightArrow;
		case GLFW_KEY_UP: return ImGuiKey_UpArrow;
		case GLFW_KEY_DOWN: return ImGuiKey_DownArrow;
		case GLFW_KEY_PAGE_UP: return ImGuiKey_PageUp;
		case GLFW_KEY_PAGE_DOWN: return ImGuiKey_PageDown;
		case GLFW_KEY_HOME: return ImGuiKey_Home;
		case GLFW_KEY_END: return ImGuiKey_End;
		case GLFW_KEY_INSERT: return ImGuiKey_Insert;
		case GLFW_KEY_DELETE: return ImGuiKey_Delete;
		case GLFW_KEY_BACKSPACE: return ImGuiKey_Backspace;
		case GLFW_KEY_SPACE: return ImGuiKey_Space;
		case GLFW_KEY_ENTER: return ImGuiKey_Enter;
		case GLFW_KEY_ESCAPE: return ImGuiKey_Escape;
		case GLFW_KEY_A: return ImGuiKey_A;
		case GLFW_KEY_C: return ImGuiKey_C;
		case GLFW_KEY_V: return ImGuiKey_V;
		case GLFW_KEY_X: return ImGuiKey_X;
		case GLFW_KEY_Y: return ImGuiKey_Y;
		case GLFW_KEY_Z: return ImGuiKey_Z;
		default: return ImGuiKey_None; // Return None for unmapped keys
		}
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext(); // Create ImGui context
		ImGui::StyleColorsDark(); // Set dark theme

		ImGuiIO& io = ImGui::GetIO();

		// Mouse Configs
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors; // Enable mouse cursors
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos; // Enable setting mouse position

		

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		// Cleanup ImGui context here
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();

		// Setup Display
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		//Setup delta time
		float time = (float)glfwGetTime(); // Get current time in seconds

		// m_Time: previous frame, time: current frame
		// If m_Time is 0.0f, it means this is the first frame
		// So we set delta time to a default value of 1/60 seconds to get the frame duration
		// Otherwise, we calculate the frame duration as the difference between current and previous frame times
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f); 
		m_Time = time; // Update m_Time to current time for next frame
		
		
		
		ImGui_ImplOpenGL3_NewFrame();//Sets up ImGui for a new frame
		ImGui::NewFrame(); // Start a new ImGui frame
		
		
		static bool show = true;
		ImGui::ShowDemoWindow(&show); // Show the ImGui demo window
		
		ImGui::Render(); //compile frame descriptions into draw data
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Send draw data to OpenGL renderer

	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		// If the event matches the event type of a specific handler, call that handler
		EventDispatcher dispatcher(event);

		// Dispatch mouse events
		dispatcher.Dispatch<MouseButtonPressedEvent>(DEW_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(DEW_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(DEW_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(DEW_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));

		// Dispatch keyboard events
		dispatcher.Dispatch<KeyPressedEvent>(DEW_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(DEW_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(DEW_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));

		// Dispatch window events
		dispatcher.Dispatch<WindowResizeEvent>(DEW_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));

	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(e.GetMouseButton(), true); // true for pressed

		return false; // Return false to allow other layers to process the event
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(e.GetMouseButton(), false); // false for released

		return false; 

	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent(e.GetXOffset(), e.GetYOffset());

		return false;

	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey key = KeyMap(e.GetKeyCode()); // Map GLFW key to ImGui key
		io.AddKeyEvent(key, true); // true for pressed
		GLFWwindow* window = glfwGetCurrentContext();

		//Modifier keys
		io.AddKeyEvent(ImGuiMod_Ctrl, (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) 
			|| (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS));

		io.AddKeyEvent(ImGuiMod_Shift, (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) 
			|| (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS));

		io.AddKeyEvent(ImGuiMod_Alt, (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) 
			|| (glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS));

		// Super key (Windows key on Windows, Command key on macOS)
		io.AddKeyEvent(ImGuiMod_Super, (glfwGetKey(window, GLFW_KEY_LEFT_SUPER) == GLFW_PRESS) 
			|| (glfwGetKey(window, GLFW_KEY_RIGHT_SUPER) == GLFW_PRESS)); 


		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey key = KeyMap(e.GetKeyCode());
		io.AddKeyEvent(key, false); // false for released

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter((unsigned int)e.GetKeyCode());
		
		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f); // temporary configuration
		glViewport(0, 0, e.GetWidth(), e.GetHeight());


		return false;
	}

}