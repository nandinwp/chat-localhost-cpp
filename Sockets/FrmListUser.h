#pragma once

namespace SocketsTeste {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FrmListUser
	/// </summary>
	public ref class FrmListUser : public System::Windows::Forms::Form
	{
	public:
		static String^ pass;
		static String^ user;
		static String^ userId;
	public:
		FrmListUser(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FrmListUser()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::ListView^ lvUsers;
	protected:

	protected:
	private: System::Windows::Forms::ColumnHeader^ chName;

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
			System::Windows::Forms::ListViewItem^ listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(L"AAAAAAAAAAAA"));
			this->lvUsers = (gcnew System::Windows::Forms::ListView());
			this->chName = (gcnew System::Windows::Forms::ColumnHeader());
			this->SuspendLayout();
			// 
			// lvUsers
			// 
			this->lvUsers->Activation = System::Windows::Forms::ItemActivation::OneClick;
			this->lvUsers->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->lvUsers->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) { this->chName });
			this->lvUsers->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lvUsers->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lvUsers->FullRowSelect = true;
			this->lvUsers->GridLines = true;
			this->lvUsers->HideSelection = false;
			this->lvUsers->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(1) { listViewItem1 });
			this->lvUsers->Location = System::Drawing::Point(0, 0);
			this->lvUsers->MultiSelect = false;
			this->lvUsers->Name = L"lvUsers";
			this->lvUsers->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lvUsers->Size = System::Drawing::Size(284, 261);
			this->lvUsers->TabIndex = 0;
			this->lvUsers->UseCompatibleStateImageBehavior = false;
			this->lvUsers->View = System::Windows::Forms::View::Details;
			this->lvUsers->ItemActivate += gcnew System::EventHandler(this, &FrmListUser::lvUsers_ItemActivate);
			// 
			// chName
			// 
			this->chName->Text = L"Usuários";
			this->chName->Width = 282;
			// 
			// FrmListUser
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->lvUsers);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"FrmListUser";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Lista de usuários";
			this->ResumeLayout(false);

		}
#pragma endregion
		private: System::Void lvUsers_ItemActivate(System::Object^ sender, System::EventArgs^ e) 
		{
			ListView^ lv = (System::Windows::Forms::ListView^)sender;
			ListViewItem^ item = lv->SelectedItems[0];
			System::Windows::Forms::DialogResult result;
			
			result = MessageBox::Show("Deseja logar como: \n\r" + item->Text, "Chat", MessageBoxButtons::YesNo, MessageBoxIcon::Information);
			
			if (result == System::Windows::Forms::DialogResult::Yes) {
				user = item->SubItems[0]->Text;
				pass = item->SubItems[1]->Text;
				userId = item->SubItems[2]->Text;
				this->DialogResult = System::Windows::Forms::DialogResult::OK;
				this->Close();
			} else {
				this->DialogResult = System::Windows::Forms::DialogResult::Ignore;
				this->Close();
			}
		}
};
}
