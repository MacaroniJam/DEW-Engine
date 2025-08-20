#pragma once

#include "DEWEngine/Window.h"

#include <GLFW/glfw3.h>

namespace DEWEngine {

	class WindowsWindow : public Window
	{
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		
		//Variables for GLFW
		GLFWwindow* m_Window;

		//We need a struct to pass into GLFW instead of the entire class
		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

	public:
		WindowsWindow(const WindowProps& props = WindowProps());
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const override { return m_Window; }
	};

}


