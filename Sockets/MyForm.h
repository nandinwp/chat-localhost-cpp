#pragma once
#include "FrmSetHost.h"
#include "SystemNode.h"
#include "StaticData.h"
#include "StaticFunctions.h"

namespace SocketsTeste {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		FrmSetHost^ def;
	private: System::Windows::Forms::Button^ btnSendFile;
	public:

	private: System::Windows::Forms::ToolStripMenuItem^ perfilToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ enviarConviteToolStripMenuItem;
	private: System::Windows::Forms::Label^ lbAmigos;
	public:
		ComboBox^ combo;
	public:
		MyForm(void)
		{
			InitializeComponent();
			StaticFunctions::CreateDataBase();

			this->Text += String::Format(" - IP: {0}", StaticData::GetLocalIPAddress());
			
			combo = gcnew ComboBox();
			StaticData::GetLocalNetworkIPs(combo);

			String^ exeDirectory = Application::StartupPath;
			String^ iconPath = System::IO::Path::Combine(exeDirectory, "app.ico");
			this->Icon = gcnew System::Drawing::Icon(iconPath);
			notification->Icon = gcnew System::Drawing::Icon(iconPath);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete networkManager;
				delete components;
			}
		}

	private:
		static int start = 0;
		SystemNode^ networkManager;

		System::Windows::Forms::Button^ sendButton;
		System::Windows::Forms::TextBox^ messageTextBox;
		System::Windows::Forms::ListBox^ messageListBox;
		private: System::Windows::Forms::Label^ lbUserName;



		private: System::Windows::Forms::MenuStrip^ mStrip;
		private: System::Windows::Forms::ToolStripMenuItem^ definiçõesToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ definirHostToolStripMenuItem;
		private: System::Windows::Forms::Label^ lbConnections;
		private: System::Windows::Forms::ToolStripMenuItem^ ActionToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^ FecharMinimizaToolStripMenuItem;
		private: System::Windows::Forms::NotifyIcon^ notification;
		private: System::ComponentModel::IContainer^ components;





#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->sendButton = (gcnew System::Windows::Forms::Button());
			this->messageTextBox = (gcnew System::Windows::Forms::TextBox());
			this->messageListBox = (gcnew System::Windows::Forms::ListBox());
			this->lbUserName = (gcnew System::Windows::Forms::Label());
			this->mStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->definiçõesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->definirHostToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ActionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FecharMinimizaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->perfilToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->enviarConviteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lbConnections = (gcnew System::Windows::Forms::Label());
			this->notification = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->btnSendFile = (gcnew System::Windows::Forms::Button());
			this->lbAmigos = (gcnew System::Windows::Forms::Label());
			this->mStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// sendButton
			// 
			this->sendButton->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->sendButton->FlatAppearance->BorderSize = 0;
			this->sendButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->sendButton->Location = System::Drawing::Point(585, 383);
			this->sendButton->Margin = System::Windows::Forms::Padding(4);
			this->sendButton->Name = L"sendButton";
			this->sendButton->Size = System::Drawing::Size(67, 83);
			this->sendButton->TabIndex = 0;
			this->sendButton->Text = L"Send";
			this->sendButton->UseVisualStyleBackColor = false;
			this->sendButton->Click += gcnew System::EventHandler(this, &MyForm::sendButton_Click);
			// 
			// messageTextBox
			// 
			this->messageTextBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->messageTextBox->Font = (gcnew System::Drawing::Font(L"Arial", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->messageTextBox->Location = System::Drawing::Point(13, 383);
			this->messageTextBox->Margin = System::Windows::Forms::Padding(4);
			this->messageTextBox->Multiline = true;
			this->messageTextBox->Name = L"messageTextBox";
			this->messageTextBox->Size = System::Drawing::Size(495, 83);
			this->messageTextBox->TabIndex = 1;
			this->messageTextBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::messageTextBox_KeyDown);
			// 
			// messageListBox
			// 
			this->messageListBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->messageListBox->FormattingEnabled = true;
			this->messageListBox->HorizontalScrollbar = true;
			this->messageListBox->ItemHeight = 16;
			this->messageListBox->Location = System::Drawing::Point(13, 82);
			this->messageListBox->Margin = System::Windows::Forms::Padding(4);
			this->messageListBox->Name = L"messageListBox";
			this->messageListBox->Size = System::Drawing::Size(639, 288);
			this->messageListBox->TabIndex = 2;
			// 
			// lbUserName
			// 
			this->lbUserName->AutoSize = true;
			this->lbUserName->Location = System::Drawing::Point(10, 33);
			this->lbUserName->Name = L"lbUserName";
			this->lbUserName->Size = System::Drawing::Size(74, 16);
			this->lbUserName->TabIndex = 5;
			this->lbUserName->Text = L"User name:";
			// 
			// mStrip
			// 
			this->mStrip->BackColor = System::Drawing::SystemColors::Control;
			this->mStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->definiçõesToolStripMenuItem,
					this->perfilToolStripMenuItem
			});
			this->mStrip->Location = System::Drawing::Point(0, 0);
			this->mStrip->Name = L"mStrip";
			this->mStrip->Size = System::Drawing::Size(894, 24);
			this->mStrip->TabIndex = 6;
			this->mStrip->Text = L"Menu";
			// 
			// definiçõesToolStripMenuItem
			// 
			this->definiçõesToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->definirHostToolStripMenuItem,
					this->ActionToolStripMenuItem
			});
			this->definiçõesToolStripMenuItem->Name = L"definiçõesToolStripMenuItem";
			this->definiçõesToolStripMenuItem->Size = System::Drawing::Size(74, 20);
			this->definiçõesToolStripMenuItem->Text = L"Definições";
			// 
			// definirHostToolStripMenuItem
			// 
			this->definirHostToolStripMenuItem->Name = L"definirHostToolStripMenuItem";
			this->definirHostToolStripMenuItem->Size = System::Drawing::Size(135, 22);
			this->definirHostToolStripMenuItem->Text = L"Definir host";
			this->definirHostToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::definirHostToolStripMenuItem_Click);
			// 
			// ActionToolStripMenuItem
			// 
			this->ActionToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->FecharMinimizaToolStripMenuItem });
			this->ActionToolStripMenuItem->Name = L"ActionToolStripMenuItem";
			this->ActionToolStripMenuItem->Size = System::Drawing::Size(135, 22);
			this->ActionToolStripMenuItem->Text = L"Ações";
			// 
			// FecharMinimizaToolStripMenuItem
			// 
			this->FecharMinimizaToolStripMenuItem->Name = L"FecharMinimizaToolStripMenuItem";
			this->FecharMinimizaToolStripMenuItem->Size = System::Drawing::Size(193, 22);
			this->FecharMinimizaToolStripMenuItem->Text = L"Botão fechar minimiza";
			this->FecharMinimizaToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::FecharMinimizaToolStripMenuItem_Click);
			// 
			// perfilToolStripMenuItem
			// 
			this->perfilToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->enviarConviteToolStripMenuItem });
			this->perfilToolStripMenuItem->Name = L"perfilToolStripMenuItem";
			this->perfilToolStripMenuItem->Size = System::Drawing::Size(46, 20);
			this->perfilToolStripMenuItem->Text = L"Perfil";
			// 
			// enviarConviteToolStripMenuItem
			// 
			this->enviarConviteToolStripMenuItem->Name = L"enviarConviteToolStripMenuItem";
			this->enviarConviteToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->enviarConviteToolStripMenuItem->Text = L"Enviar convite";
			// 
			// lbConnections
			// 
			this->lbConnections->AutoSize = true;
			this->lbConnections->Location = System::Drawing::Point(10, 473);
			this->lbConnections->Name = L"lbConnections";
			this->lbConnections->Size = System::Drawing::Size(19, 16);
			this->lbConnections->TabIndex = 7;
			this->lbConnections->Text = L"...";
			// 
			// notification
			// 
			this->notification->BalloonTipIcon = System::Windows::Forms::ToolTipIcon::Info;
			this->notification->Text = L"Hello";
			this->notification->Visible = true;
			this->notification->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::notification_MouseClick);
			// 
			// btnSendFile
			// 
			this->btnSendFile->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->btnSendFile->Enabled = false;
			this->btnSendFile->FlatAppearance->BorderSize = 0;
			this->btnSendFile->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnSendFile->Location = System::Drawing::Point(516, 383);
			this->btnSendFile->Margin = System::Windows::Forms::Padding(4);
			this->btnSendFile->Name = L"btnSendFile";
			this->btnSendFile->Size = System::Drawing::Size(61, 83);
			this->btnSendFile->TabIndex = 8;
			this->btnSendFile->Text = L"File";
			this->btnSendFile->UseVisualStyleBackColor = false;
			// 
			// lbAmigos
			// 
			this->lbAmigos->AutoSize = true;
			this->lbAmigos->Font = (gcnew System::Drawing::Font(L"Arial", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbAmigos->Location = System::Drawing::Point(748, 33);
			this->lbAmigos->Name = L"lbAmigos";
			this->lbAmigos->Size = System::Drawing::Size(80, 22);
			this->lbAmigos->TabIndex = 9;
			this->lbAmigos->Text = L"Amigos";
			// 
			// MyForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::SystemColors::ControlLight;
			this->ClientSize = System::Drawing::Size(894, 498);
			this->Controls->Add(this->lbAmigos);
			this->Controls->Add(this->btnSendFile);
			this->Controls->Add(this->lbConnections);
			this->Controls->Add(this->lbUserName);
			this->Controls->Add(this->messageListBox);
			this->Controls->Add(this->messageTextBox);
			this->Controls->Add(this->sendButton);
			this->Controls->Add(this->mStrip);
			this->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->MainMenuStrip = this->mStrip;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Chat";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			this->mStrip->ResumeLayout(false);
			this->mStrip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		void sendButton_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (start == 0) {
				definirHostToolStripMenuItem_Click(sender, e);
				return;
			}
				
			String^ message = String::Format("{0} : {1}", StaticData::Usuario, messageTextBox->Text);
			//networkManager->BroadcastMessage(message);
			messageListBox->Items->Add(message);
			networkManager->SendMessageTo(message, StaticData::Destinatario, StaticData::Porta);
			messageTextBox->Clear();
		}
		void OnMessageReceived(String^ message)
		{
			if (this->InvokeRequired)
			{
				this->Invoke(gcnew Action<String^>(this, &MyForm::OnMessageReceived), message);
			}
			else
			{
				String^ data = DateTime::Now.ToShortTimeString();
				messageListBox->Items->Add(String::Format("{0}: {1}", data,message));
			}
			
		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		networkManager = gcnew SystemNode(StaticData::Usuario, StaticData::Porta, gcnew Action<String^>(this, &MyForm::OnMessageReceived));
		networkManager->OnNewConnection += gcnew NewConnectionEventHandler(this, &SocketsTeste::MyForm::OnOnNewConnection);
		networkManager->OnNewMessage += gcnew NewMessage(this, &SocketsTeste::MyForm::OnNewMenssage);
		networkManager->Start();

		start = 1;
		lbUserName->Text = String::Format("User name: {0}", StaticData::Usuario);
	}

	private: System::Void messageTextBox_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) 
	{
		if (e->KeyCode == Keys::Enter && e->Modifiers == Keys::None) {
			sendButton_Click(sender, e);
		}


	}
	private: System::Void definirHostToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (def != nullptr)
			delete def;

		def = gcnew FrmSetHost(StaticData::Porta, StaticData::Usuario, StaticData::Destinatario, combo);
		auto result = def->ShowDialog();

		if (result == System::Windows::Forms::DialogResult::OK) {
			StaticData::Porta = Int16::Parse(def->txbPort->Text);
			StaticData::Usuario = def->txbUserName->Text;
			StaticData::Destinatario = def->txbAdressFriend->Text;

			if (StaticFunctions::validation() == 0)
				button1_Click(sender, e);
			else
				definirHostToolStripMenuItem_Click(sender, e);
		}
		delete def;
			
	}
		   void OnOnNewConnection(System::String^ address);
	private: System::Void FecharMinimizaToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		FecharMinimizaToolStripMenuItem->Checked =!FecharMinimizaToolStripMenuItem->Checked;
	}
	private: System::Void MyForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) 
	{
		if (FecharMinimizaToolStripMenuItem->Checked) {
			e->Cancel=true;
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->WindowState = FormWindowState::Minimized;
		}
	}
	private: System::Void notification_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		this->ShowIcon = true;
		this->ShowInTaskbar = true;
		this->WindowState = FormWindowState::Normal;
	}
		   void OnNewMenssage(System::String^ msg);
};
}


void SocketsTeste::MyForm::OnOnNewConnection(System::String^ address)
{
	lbConnections->Text =String::Format("Conexões: {0} - {1}",networkManager->GetConnectedNodeCount().ToString(), address);
}


void SocketsTeste::MyForm::OnNewMenssage(System::String^ msg)
{
	notification->Visible = true;
	notification->BalloonTipTitle = "Nova mensagem";
	notification->BalloonTipText = String::Format("{0}...", msg->Substring(0, 10));
	notification->BalloonTipIcon = ToolTipIcon::Info;
	notification->ShowBalloonTip(1000);
}
