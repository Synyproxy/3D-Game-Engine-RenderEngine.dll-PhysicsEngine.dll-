#pragma once

#include <math/Vec2.h>

namespace CoreEngineNS
{
	class Input
	{
	private:

		//Window
		static GLfloat m_windowWidth;
		static GLfloat m_windowHeight;
		static bool m_shouldClose;

		//Mouse
		static bool m_updateMouse;	//If mouse was updated during frame
		static bool m_firstMouse;
		static GLfloat m_lastX;
		static GLfloat m_lastY;
		static GLfloat m_xOffset;
		static GLfloat m_yOffset;

		//Keyboard
		static Vec2 m_movementDirection;
		static Vec2 m_vertical;
		static Vec2 m_horizontal;

	public:
		Input();
		~Input();

		//OpenGL
		static void KeyCallBack(GLFWwindow* p_window, int p_key, int p_scanCode, int p_action, int p_mods);
		static void MouseCallBack(GLFWwindow* p_window, double p_xPos, double p_yPos);


		static void SetWindowSize(const GLfloat& p_windowWidth, const GLfloat& p_windowHeight);
		static bool ShouldClose();
		static bool ShouldUpdateMouse();
		static float GetXOffset();
		static float GetYOffset();
		static float MouseX();
		static float MouseY();
		static Vec2 GetMovementDirection();

		static void Reset();

	};
}