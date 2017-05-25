#pragma once

namespace Evrika {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// —водка дл€ loading_page
	/// </summary>
	public ref class loading_page : public System::Windows::Forms::Form
	{
	public:
		delegate void change_stat(String^, int);
		change_stat^ csDelegate;

		loading_page(void)
		{
			mut = gcnew Semaphore(0,3);
			ldngpg = this;
			InitializeComponent();
			//pictureBox1->Visible = false;	//убийца котов
			//
			//TODO: добавьте код конструктора
			//
			System::ComponentModel::ComponentResourceManager^ resource = (gcnew System::ComponentModel::ComponentResourceManager(loading_page::typeid));
			pictureBox1->Image = (safe_cast<System::Drawing::Image^>(resource->GetObject("4IAzyrhy9rkis")));
			label = label1;
			progressBar = progressBar1;
			//this->Invoke(this->csDelegate);
			this->BringToFront();
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~loading_page()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	protected:
	private: System::Windows::Forms::Label^  label1;

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		static Label^ label;
		static ProgressBar^ progressBar;
		/// </summary>
		System::ComponentModel::Container ^components;
	public:
		static Semaphore^ mut;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	public:
		static loading_page^ ldngpg;
		static Semaphore^ getMutex() {
			return mut;
		}
		static void change_lbl(String^ str) {
			label->Text = str;
		}
		static void change_bar(int stat) {
			progressBar->Value = stat;
		}
		static Label^ getLabel() {
			return label;
		}
		static ProgressBar^ getPBar() {
			return progressBar;
		}
		static loading_page^ getHandle() {
			return ldngpg;
		}
		static void Suicide() {
			Sleep(100);
			ldngpg->~loading_page();
		}
	private:
#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// progressBar1
			// 
			this->progressBar1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->progressBar1->Location = System::Drawing::Point(0, 213);
			this->progressBar1->Maximum = 8;
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(250, 23);
			this->progressBar1->Step = 1;
			this->progressBar1->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
			this->progressBar1->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(2, 191);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(45, 16);
			this->label1->TabIndex = 1;
			this->label1->Text = L"label1";
			this->label1->Click += gcnew System::EventHandler(this, &loading_page::label1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(250, 188);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			// 
			// loading_page
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(250, 236);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->progressBar1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"loading_page";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"loading_page";
			this->Load += gcnew System::EventHandler(this, &loading_page::loading_page_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void loading_page_Load(System::Object^  sender, System::EventArgs^  e) {
		mut->Release();
	}
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}
