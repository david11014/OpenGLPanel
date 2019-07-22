#include <Windows.h>
#include "MyForm.h"

using namespace Project1;
[STAThreadAttribute]
int main(array<System::String ^> ^args)
{

	// 建立任何控制項之前，先啟用 Windows XP 視覺化效果
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// 建立主視窗並執行
	Application::Run(gcnew MyForm());
	return 0;
}

int _stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	return main(System::Environment::GetCommandLineArgs());
}