#include "MyForm.h"
#include "StaticData.h"
#include "StaticFunctions.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void WinCore(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	SocketsTeste::MyForm core;
    
    checkUser();
    CheckArgs(args);

	Application::Run(% core);
}

void CheckArgs(array<String^>^% args) {
    if (args->Length > 0) {
        String^ parameter = args[0];
        StaticData::ParamLink = parameter;
    }
}
void checkUser() {
    StaticFunctions::CreateUser();
}