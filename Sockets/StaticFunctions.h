#pragma once
#include "FrmSetUser.h"
#include "FrmListUser.h"
#include "StaticData.h"
#include "Dbfunctions.h"
#include "Secure.h"


using namespace System::Runtime::InteropServices;
using namespace System;
using namespace Microsoft::Win32;
using namespace SocketsTeste;

public ref class StaticFunctions
{
private:
	static String^ RegKey = "SOFTWARE\\CHATUDP";
public:
	static int validation() {
		if (String::IsNullOrEmpty(StaticData::Usuario))
			return-1;

		if (String::IsNullOrEmpty(StaticData::Destinatario))
			return-1;

		String^ aux = StaticData::Porta.ToString();

		if (String::IsNullOrEmpty(aux) || aux->Equals("0") || aux->Length < 4)
			return-1;

		StaticData::Usuario = StaticData::Usuario->Replace(" ", "");
		StaticData::Usuario = StaticData::Usuario->ToLower();
		StaticData::Usuario = StaticData::Usuario->Trim();
		return 0;
	}

	static String^ StringToBase64(String^ base) {
		cli::array<Byte>^ bytes = Encoding::UTF8->GetBytes(base);
		String^ base64String = Convert::ToBase64String(bytes);
		return base64String;
	}
	static String^ Base64ToString(String^ base64) {
		cli::array<Byte>^ bytes = Convert::FromBase64String(base64);
		return Encoding::UTF8->GetString(bytes);
	}

	static int CreateDataBase() 
	{
		int resp = createDatabase();
		/*for (int i = 0; i < 50; i++)
		{
			String^ guid = Guid::NewGuid().ToString();

			insertMessage((char*)(void*)Marshal::StringToHGlobalAnsi(guid), "0", 0, "Oiee", "1234", "900");
		}*/
		return resp;
	}
	static void LoadMenssages(System::Object^ form) {
		getAllMessageFromUser((char*)(void*)Marshal::StringToHGlobalAnsi(StaticData::CurrentUserID), form);
	}
	static void GenerateInvite() {

	}
	static void AcceptInvite() {
		if (StaticData::ParamLink == nullptr)
			return;

		if (StaticData::ParamLink->Length > 0) {
			String^ aux = StaticData::ParamLink;
			StaticData::ParamLink = nullptr;

			aux = aux->Replace("chat://", "");

			aux = Base64ToString(aux);
			String^ requestName = aux->Split('#')[0];
			String^ conectionContex = aux->Split('#')[1];

			String^ userId = aux->Split('#')[2];
			if (userId->Equals(StaticData::CurrentUserID))
				return;
			
			if (!String::IsNullOrEmpty(requestName)) {
				DialogResult result = MessageBox::Show("Aceitar o pedido de amizade de " + requestName + " ?", "Confirmação", MessageBoxButtons::YesNo, MessageBoxIcon::Question);

				if (result == DialogResult::Yes) {
					InsertAmigo("0", 0, requestName, userId, conectionContex);
				}
			}
		}
	}

	static void CreateUser() {
		
		if (findUserInConfig()==EXIT_FAILURE) {
			FrmSetUser^ frCad = gcnew FrmSetUser(true);
			frCad->ShowIcon = false;
			frCad->ShowInTaskbar = false;

			auto result = frCad->ShowDialog();
			
			if (result == System::Windows::Forms::DialogResult::OK) {
				array<Byte>^ cipherTextBytes = Secure::EncryptMessage(frCad->txbPass->Text);
				String^ aux = Convert::ToBase64String(cipherTextBytes);

				std::string pass = (char*)(void*)Marshal::StringToHGlobalAnsi(aux);
				std::string id = (char*)(void*)Marshal::StringToHGlobalAnsi(Guid::NewGuid().ToString());
				std::string userId = (char*)(void*)Marshal::StringToHGlobalAnsi(Guid::NewGuid().ToString());
				std::string date = (char*)(void*)Marshal::StringToHGlobalAnsi(DateTime::Now.ToString("yyyy-MM-dd HH:mm:ss"));
				std::string name = (char*)(void*)Marshal::StringToHGlobalAnsi(frCad->txbUserName->Text);

				insertIntoConfig(id, "0", 0, date, name, userId, pass);

			} else {
				exit(0);
			}
		} else {
			FrmListUser^ user = gcnew FrmListUser();
			user->ShowIcon = false;
			user->ShowInTaskbar = false;
			LoadDataToListView(user->lvUsers);

			auto result = user->ShowDialog();
			if (result == System::Windows::Forms::DialogResult::OK) {
				
				if (Login(user->pass, user->user) != 0) {
					delete user;
					CreateUser();
				}
				StaticData::Usuario = user->user;
				StaticData::CurrentUserID = user->userId;
				delete user;

			}
			else if (result == System::Windows::Forms::DialogResult::Ignore) {
				CreateUser();
			} else {
				exit(1);
			}

		}
		
	}

	static int Login(String^ pass, String^ user) {
		FrmSetUser^ frCad = gcnew FrmSetUser(false);
		frCad->ShowIcon = false;
		frCad->ShowInTaskbar = false;
		frCad->txbUserName->Text = user;
		auto result = frCad->ShowDialog();

		if (result == System::Windows::Forms::DialogResult::OK) {

			array<Byte>^ encryptedBytes = Convert::FromBase64String(pass);
			String^ _pass = Secure::DecryptMessage(encryptedBytes);

			if (_pass->Equals(frCad->txbPass->Text))
				return EXIT_SUCCESS;
			else
				return EXIT_FAILURE;
		}
		else {
			return EXIT_FAILURE;
		}
	}

	static int LoadFriendsFunction(ListView^% friendList) {
		return LoadFriends(friendList);
	}

	static void RegisterProtocol() {
		String^ executablePath = System::Diagnostics::Process::GetCurrentProcess()->MainModule->FileName;
		try
		{
			String^ keyPath = "Software\\Classes\\chat";
			RegistryKey^ existingKey = Registry::CurrentUser->OpenSubKey(keyPath);

			if (existingKey == nullptr)
			{
				RegistryKey^ key = Registry::CurrentUser->CreateSubKey(keyPath);
				if (key != nullptr)
				{
					key->SetValue("", "URL:chat Protocol");
					key->SetValue("URL Protocol", "");

					RegistryKey^ commandKey = key->CreateSubKey("shell\\open\\command");
					if (commandKey != nullptr)
					{
						commandKey->SetValue("", String::Format("\"{0}\" \"%1\"", executablePath));
					}
				}
			}
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(String::Format("Erro ao registrar o protocolo: {0}", ex->Message), "Erro", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	static void SalvarConfiguracao(String^ nomeChave, Object^ valor)
	{
		RegistryKey^ key = Registry::CurrentUser->CreateSubKey(RegKey);
		if (key != nullptr)
		{
			key->SetValue(nomeChave, valor);
		}
	}

	static Object^ LerConfiguracao(String^ nomeChave)
	{
		RegistryKey^ key = Registry::CurrentUser->OpenSubKey(RegKey);
		if (key != nullptr)
		{
			return key->GetValue(nomeChave);
		}

		return nullptr;
	}

	System::Void OnUpdateAmigos(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show("OI");
	}
};
