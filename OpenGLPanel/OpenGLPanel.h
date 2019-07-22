// OpenGLPanel.h

#pragma once
#include "OpenGL.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace OpenGLPanel {
	
	public ref class GLPanel : System::Windows::Forms::Panel
	{
	public:
		OpenGL *gl;

		GLPanel() : Panel()
		{
			

#ifdef _WIN64 
			std::cout << "64 bit.\n";
			gl = new OpenGL(::GetDC((HWND)this->Handle.ToInt64()));
			
#else
			std::cout << "32 bit.\n";
			gl = new OpenGL(::GetDC((HWND)this->Handle.ToInt32()));			
#endif

		}

		void RenderScene()
		{
			gl->render();
			gl->SwapBuffers();
		}

	};
}
