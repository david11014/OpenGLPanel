#include <Windows.h>
#include "MyForm.h"

using namespace Project1;
[STAThreadAttribute]
int main(array<System::String ^> ^args)
{

	// �إߥ��󱱨���e�A���ҥ� Windows XP ��ı�ƮĪG
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// �إߥD�����ð���
	Application::Run(gcnew MyForm());
	return 0;
}

int _stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	return main(System::Environment::GetCommandLineArgs());
}