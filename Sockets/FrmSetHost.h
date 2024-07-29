#pragma once

namespace SocketsTeste {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FrmSetHost
	/// </summary>
	public ref class FrmSetHost : public System::Windows::Forms::Form
	{
	public:
		FrmSetHost(Int16 host, String^ user, String^ otheName, ComboBox^%combo)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->ShowIcon = false;
			this->ShowInTaskbar = false;

			txbPort->Text = host.ToString();
			txbUserName->Text = user;
			txbAdressFriend->Text = otheName;
	

			for each (auto var in combo->Items)
			{
				cbMain->Items->Add(var);
			}

		/*	if (cbMain->Items->Count <= 0)
			{
				cbMain->Visible = false;
				txbAdressFriend->Visible = true;
			}*/
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FrmSetHost()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	public: System::Windows::Forms::TextBox^ txbUserName;
	private:


	private: System::Windows::Forms::Button^ btnSet;

	private: System::Windows::Forms::Label^ label2;
	public: System::Windows::Forms::TextBox^ txbPort;
	private:


	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Button^ btnCancel;
	private: System::Windows::Forms::Label^ label4;
	public: System::Windows::Forms::TextBox^ txbAdressFriend;
	private: System::Windows::Forms::ComboBox^ cbMain;
	public:
	private:

	private:
	protected:

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txbUserName = (gcnew System::Windows::Forms::TextBox());
			this->btnSet = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->txbPort = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->txbAdressFriend = (gcnew System::Windows::Forms::TextBox());
			this->cbMain = (gcnew System::Windows::Forms::ComboBox());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(26, 19);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(113, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Configurações de host";
			// 
			// txbUserName
			// 
			this->txbUserName->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->txbUserName->Font = (gcnew System::Drawing::Font(L"Arial", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txbUserName->Location = System::Drawing::Point(29, 68);
			this->txbUserName->Margin = System::Windows::Forms::Padding(4);
			this->txbUserName->Name = L"txbUserName";
			this->txbUserName->Size = System::Drawing::Size(208, 22);
			this->txbUserName->TabIndex = 0;
			// 
			// btnSet
			// 
			this->btnSet->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->btnSet->FlatAppearance->BorderSize = 0;
			this->btnSet->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnSet->Location = System::Drawing::Point(149, 184);
			this->btnSet->Margin = System::Windows::Forms::Padding(4);
			this->btnSet->Name = L"btnSet";
			this->btnSet->Size = System::Drawing::Size(88, 28);
			this->btnSet->TabIndex = 2;
			this->btnSet->Text = L"Aplicar";
			this->btnSet->UseVisualStyleBackColor = false;
			this->btnSet->Click += gcnew System::EventHandler(this, &FrmSetHost::btnSet_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(26, 51);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(61, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"User name:";
			// 
			// txbPort
			// 
			this->txbPort->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->txbPort->Font = (gcnew System::Drawing::Font(L"Arial", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txbPort->Location = System::Drawing::Point(29, 154);
			this->txbPort->Margin = System::Windows::Forms::Padding(4);
			this->txbPort->Name = L"txbPort";
			this->txbPort->Size = System::Drawing::Size(208, 22);
			this->txbPort->TabIndex = 1;
			this->txbPort->Text = L"8080";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(26, 137);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(35, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Porta:";
			// 
			// btnCancel
			// 
			this->btnCancel->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->btnCancel->FlatAppearance->BorderSize = 0;
			this->btnCancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnCancel->Location = System::Drawing::Point(29, 184);
			this->btnCancel->Margin = System::Windows::Forms::Padding(4);
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->Size = System::Drawing::Size(88, 28);
			this->btnCancel->TabIndex = 3;
			this->btnCancel->Text = L"Cancelar";
			this->btnCancel->UseVisualStyleBackColor = false;
			this->btnCancel->Click += gcnew System::EventHandler(this, &FrmSetHost::btnCancel_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(25, 95);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(73, 13);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Friend adress:";
			// 
			// txbAdressFriend
			// 
			this->txbAdressFriend->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->txbAdressFriend->Font = (gcnew System::Drawing::Font(L"Arial", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txbAdressFriend->Location = System::Drawing::Point(28, 112);
			this->txbAdressFriend->Margin = System::Windows::Forms::Padding(4);
			this->txbAdressFriend->Name = L"txbAdressFriend";
			this->txbAdressFriend->Size = System::Drawing::Size(208, 22);
			this->txbAdressFriend->TabIndex = 9;
			this->txbAdressFriend->Text = L"192.168.56.1";
			// 
			// cbMain
			// 
			this->cbMain->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cbMain->Font = (gcnew System::Drawing::Font(L"Arial", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cbMain->ForeColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->cbMain->FormattingEnabled = true;
			this->cbMain->Location = System::Drawing::Point(30, 112);
			this->cbMain->Name = L"cbMain";
			this->cbMain->Size = System::Drawing::Size(207, 25);
			this->cbMain->TabIndex = 11;
			this->cbMain->Visible = false;
			// 
			// FrmSetHost
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(260, 228);
			this->Controls->Add(this->cbMain);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->txbAdressFriend);
			this->Controls->Add(this->btnCancel);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->txbPort);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->btnSet);
			this->Controls->Add(this->txbUserName);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(276, 267);
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(276, 267);
			this->Name = L"FrmSetHost";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Host config";
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
