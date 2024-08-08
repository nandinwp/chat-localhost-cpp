#pragma once

namespace SocketsTeste {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FrmSetUser
	/// </summary>
	public ref class FrmSetUser : public System::Windows::Forms::Form
	{
	public:
		FrmSetUser(bool cad)
		{
			InitializeComponent();
			Check(cad);
		}
		void Check(bool% cad) 
		{
			if (cad) {
				lbTitle->Text = "Cadastre seu novo usuário:";
				this->Text = "Criar usuário";
				btnCancel->Text = "Encerrar";
				btnSet->Text = "Cadastrar";
			}
			else {
				lbTitle->Text = "Logue com seu usuário:";
				btnSet->Text = "Entrar";
				this->Text = "Login";
				btnCancel->Text = "Cancelar";
			}
		}


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FrmSetUser()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnCancel;
	protected:
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ btnSet;
	public: System::Windows::Forms::TextBox^ txbUserName;
	private: System::Windows::Forms::Label^ lbTitle;
	public:
	private:

	private: System::Windows::Forms::Label^ label3;
	public: System::Windows::Forms::TextBox^ txbPass;
	private:

	private:
	public:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->btnSet = (gcnew System::Windows::Forms::Button());
			this->txbUserName = (gcnew System::Windows::Forms::TextBox());
			this->lbTitle = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->txbPass = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// btnCancel
			// 
			this->btnCancel->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->btnCancel->FlatAppearance->BorderSize = 0;
			this->btnCancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnCancel->Location = System::Drawing::Point(34, 136);
			this->btnCancel->Margin = System::Windows::Forms::Padding(4);
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->Size = System::Drawing::Size(88, 28);
			this->btnCancel->TabIndex = 10;
			this->btnCancel->Text = L"Cancelar";
			this->btnCancel->UseVisualStyleBackColor = false;
			this->btnCancel->Click += gcnew System::EventHandler(this, &FrmSetUser::btnCancel_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(31, 36);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(61, 13);
			this->label2->TabIndex = 11;
			this->label2->Text = L"User name:";
			// 
			// btnSet
			// 
			this->btnSet->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->btnSet->FlatAppearance->BorderSize = 0;
			this->btnSet->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnSet->Location = System::Drawing::Point(154, 136);
			this->btnSet->Margin = System::Windows::Forms::Padding(4);
			this->btnSet->Name = L"btnSet";
			this->btnSet->Size = System::Drawing::Size(88, 28);
			this->btnSet->TabIndex = 9;
			this->btnSet->Text = L"Cadastrar";
			this->btnSet->UseVisualStyleBackColor = false;
			this->btnSet->Click += gcnew System::EventHandler(this, &FrmSetUser::btnSet_Click);
			// 
			// txbUserName
			// 
			this->txbUserName->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->txbUserName->Font = (gcnew System::Drawing::Font(L"Arial", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txbUserName->Location = System::Drawing::Point(34, 53);
			this->txbUserName->Margin = System::Windows::Forms::Padding(4);
			this->txbUserName->Name = L"txbUserName";
			this->txbUserName->Size = System::Drawing::Size(208, 22);
			this->txbUserName->TabIndex = 7;
			// 
			// lbTitle
			// 
			this->lbTitle->AutoSize = true;
			this->lbTitle->Location = System::Drawing::Point(12, 9);
			this->lbTitle->Name = L"lbTitle";
			this->lbTitle->Size = System::Drawing::Size(136, 13);
			this->lbTitle->TabIndex = 8;
			this->lbTitle->Text = L"Cadastre seu novo usuário:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(31, 79);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(56, 13);
			this->label3->TabIndex = 13;
			this->label3->Text = L"Password:";
			// 
			// txbPass
			// 
			this->txbPass->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->txbPass->Font = (gcnew System::Drawing::Font(L"Arial", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txbPass->Location = System::Drawing::Point(34, 96);
			this->txbPass->Margin = System::Windows::Forms::Padding(4);
			this->txbPass->Name = L"txbPass";
			this->txbPass->PasswordChar = '*';
			this->txbPass->Size = System::Drawing::Size(208, 22);
			this->txbPass->TabIndex = 12;
			this->txbPass->UseSystemPasswordChar = true;
			// 
			// FrmSetUser
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(284, 201);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->txbPass);
			this->Controls->Add(this->btnCancel);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->btnSet);
			this->Controls->Add(this->txbUserName);
			this->Controls->Add(this->lbTitle);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"FrmSetUser";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Criar usuário";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnSet_Click(System::Object^ sender, System::EventArgs^ e) {
		this->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->Close();
	}
	private: System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e) {
		this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->Close();
	}
};
}
