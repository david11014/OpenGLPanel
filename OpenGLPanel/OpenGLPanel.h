// OpenGLPanel.h
#pragma once

#ifdef OPENGLPANEL_EXPORTS //�P�M�צW�١A�u�O�᭱�T�w��_EXPORTS
#define  OPENGLPANEL_API __declspec(dllexport) //�Ъ`�N�I���T���OExport�n�G�_
#else
#define  OPENGLPANEL_API __declspec(dllimport)
#endif

#include "OpenGL.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace OpenGLPanel {
	
	public ref class GLApp
	{
	public:
		OpenGLCore *gl;

		GLApp(System::IntPtr handle)
		{
			

#ifdef _WIN64 
			std::cout << "64 bit.\n";
			gl = new OpenGL(::GetDC((HWND)handle.ToInt64()));
			
#else
			std::cout << "32 bit.\n";
			gl = new OpenGLCore(::GetDC((HWND)handle.ToInt32()));
#endif

		}

		void RenderScene()
		{
			gl->render();
			gl->SwapBuffers();
		}

	};
}
