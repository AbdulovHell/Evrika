#pragma once
namespace Evrika {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// Сводка для device_prop
	/// </summary>
	public ref class device_prop : public System::Windows::Forms::Form
	{
	public:
		device_prop(void)
		{
			InitializeComponent();

		}
		device_prop(Evrika::Device^ dev, System::IO::Ports::SerialPort^ _comport)
		{
			InitializeComponent();

			comboBox1->SelectedIndex = 0;
			comboBox2->SelectedIndex = 6;
			this->Text = "Метка " + dev->IdInHex();
			curDev = dev;
			comport = _comport;
			dataGridView1->Rows->Add(1);
			if (curDev->missing_counter == 0)
				dataGridView1->Rows[0]->Cells[0]->Value = curDev->IdInHex();	//id
			else
				dataGridView1->Rows[0]->Cells[0]->Value = curDev->IdInHex() + " (!)";	//id
			dataGridView1->Rows[0]->Cells[1]->Value = curDev->signal_lvl;	//sgnl lvl
			dataGridView1->Rows[0]->Cells[2]->Value = curDev->signal_quality;	//quality
			dataGridView1->Rows[0]->Cells[3]->Value = curDev->battery_lvl;	//batt lvl
			dataGridView1->Rows[0]->Cells[4]->Value = curDev->work_mode;	//mode
			sMeasDist = gcnew Semaphore(0, 3);
			chart = chart1;
			chkbox = checkBox1;
			PowerIndex = comboBox2;
			SignLvlDistLabel = label6;
			hDevice_prop = this;
			my_log = textBox1;
			my_log->Clear();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~device_prop()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  reset_cc;
	protected:

	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  MeasTime;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	protected:

	public:

	private:

		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::Button^  button1;
			 System::IO::Ports::SerialPort^ comport;
			 KalmanFilter^ cycles_filt = gcnew KalmanFilter(1, 1, 2000, 60);
			 bool ststate = true;
			 int MeasCycles = 0;
			 bool MeasModeIsTime = false;
			 List<int64_t>^ global_cpu_cycles;
			 void MeasDist();
			 void print_meters(float m);
			 int power_index = 3;
			 void DrawPoint(double);
			 int64_t offset = 113405;
			 int64_t last_num = 0;
			 List<int> Last10RSSI;
			 int LastRSSI;
			 void ChangeParam();
			 void CheckRadioBtn(RadioButton^ rbtn);
			 void ChangeBWMode(int ind);
	public:
		Device^ curDev;
		
		void SaveCycles(List<int64_t>^ cpu_cycles,int RSSI);
		static System::Threading::Semaphore^ sMeasDist;
		double ProceedPoints(List<int64_t>^ cpu_cycles);
		static device_prop^ hDevice_prop;
		static System::Windows::Forms::CheckBox^ chkbox;
		static System::Windows::Forms::TextBox^ kTextBox;
		static System::Windows::Forms::TextBox^ my_log;
		static System::Windows::Forms::ComboBox^ PowerIndex;
		static System::Windows::Forms::Label^ SignLvlDistLabel;
		static  System::Windows::Forms::DataVisualization::Charting::Chart^  chart;
	public: System::Windows::Forms::DataGridView^  dataGridView1;
			System::Windows::Forms::DataGridViewTextBoxColumn^  UniqueID;
			System::Windows::Forms::DataGridViewTextBoxColumn^  SignalLVL;
			System::Windows::Forms::DataGridViewTextBoxColumn^  QualityLVL;
			System::Windows::Forms::DataGridViewTextBoxColumn^  BatteryLVL;
			System::Windows::Forms::DataGridViewTextBoxColumn^  WorkMode;
private: System::Windows::Forms::Button^  ChangeParamBtn;
public:

	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;

	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::ComponentModel::IContainer^  components;


#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Требуемый метод для поддержки конструктора — не изменяйте 
			 /// содержимое этого метода с помощью редактора кода.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
				 System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
				 System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
				 System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
				 System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
				 this->reset_cc = (gcnew System::Windows::Forms::Button());
				 this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
				 this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->MeasTime = (gcnew System::Windows::Forms::Button());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
				 this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
				 this->UniqueID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->SignalLVL = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->QualityLVL = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->BatteryLVL = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->WorkMode = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->ChangeParamBtn = (gcnew System::Windows::Forms::Button());
				 this->textBox1 = (gcnew System::Windows::Forms::TextBox());
				 this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
				 this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
				 this->textBox2 = (gcnew System::Windows::Forms::TextBox());
				 this->textBox3 = (gcnew System::Windows::Forms::TextBox());
				 this->label6 = (gcnew System::Windows::Forms::Label());
				 this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				 this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
				 this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
				 this->label7 = (gcnew System::Windows::Forms::Label());
				 this->textBox6 = (gcnew System::Windows::Forms::TextBox());
				 this->button1 = (gcnew System::Windows::Forms::Button());
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
				 this->groupBox1->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // reset_cc
				 // 
				 this->reset_cc->Location = System::Drawing::Point(9, 181);
				 this->reset_cc->Name = L"reset_cc";
				 this->reset_cc->Size = System::Drawing::Size(121, 23);
				 this->reset_cc->TabIndex = 0;
				 this->reset_cc->Text = L"Сброс";
				 this->reset_cc->UseVisualStyleBackColor = true;
				 this->reset_cc->Click += gcnew System::EventHandler(this, &device_prop::button1_Click);
				 // 
				 // comboBox1
				 // 
				 this->comboBox1->FormattingEnabled = true;
				 this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(9) {
					 L"GFSK_BR4800", L"FSK_BR4800", L"GFSK_BR10K", L"FSK_BR10K",
						 L"GFSK_BR100K", L"FSK_BR100K", L"GFSK_BR250K", L"FSK_BR250K", L"MSK_BR500K"
				 });
				 this->comboBox1->Location = System::Drawing::Point(9, 85);
				 this->comboBox1->Name = L"comboBox1";
				 this->comboBox1->Size = System::Drawing::Size(121, 21);
				 this->comboBox1->TabIndex = 1;
				 // 
				 // numericUpDown1
				 // 
				 this->numericUpDown1->Location = System::Drawing::Point(6, 33);
				 this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				 this->numericUpDown1->Name = L"numericUpDown1";
				 this->numericUpDown1->Size = System::Drawing::Size(115, 20);
				 this->numericUpDown1->TabIndex = 3;
				 this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(6, 69);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(42, 13);
				 this->label1->TabIndex = 4;
				 this->label1->Text = L"Режим";
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(3, 17);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(83, 13);
				 this->label2->TabIndex = 5;
				 this->label2->Text = L"Кол-во циклов:";
				 // 
				 // MeasTime
				 // 
				 this->MeasTime->Location = System::Drawing::Point(6, 59);
				 this->MeasTime->Name = L"MeasTime";
				 this->MeasTime->Size = System::Drawing::Size(115, 23);
				 this->MeasTime->TabIndex = 6;
				 this->MeasTime->Text = L"Однократное";
				 this->MeasTime->UseVisualStyleBackColor = true;
				 this->MeasTime->Click += gcnew System::EventHandler(this, &device_prop::MeasTime_Click);
				 // 
				 // label3
				 // 
				 this->label3->AutoSize = true;
				 this->label3->Location = System::Drawing::Point(6, 109);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(60, 13);
				 this->label3->TabIndex = 7;
				 this->label3->Text = L"Мощность";
				 // 
				 // comboBox2
				 // 
				 this->comboBox2->FormattingEnabled = true;
				 this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(8) {
					 L" 0  dBm", L" 3  dBm", L" 6  dBm", L" 9  dBm",
						 L"12 dBm", L"15 dBm", L"20 dBm", L"27 dBm"
				 });
				 this->comboBox2->Location = System::Drawing::Point(9, 125);
				 this->comboBox2->Name = L"comboBox2";
				 this->comboBox2->Size = System::Drawing::Size(121, 21);
				 this->comboBox2->TabIndex = 8;
				 this->comboBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &device_prop::comboBox2_SelectedIndexChanged);
				 // 
				 // dataGridView1
				 // 
				 this->dataGridView1->AllowUserToAddRows = false;
				 this->dataGridView1->AllowUserToDeleteRows = false;
				 this->dataGridView1->AllowUserToResizeRows = false;
				 this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
				 this->dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
				 this->dataGridView1->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::Raised;
				 this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
				 this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
					 this->UniqueID,
						 this->SignalLVL, this->QualityLVL, this->BatteryLVL, this->WorkMode
				 });
				 this->dataGridView1->Dock = System::Windows::Forms::DockStyle::Top;
				 this->dataGridView1->Location = System::Drawing::Point(0, 0);
				 this->dataGridView1->MultiSelect = false;
				 this->dataGridView1->Name = L"dataGridView1";
				 this->dataGridView1->ReadOnly = true;
				 this->dataGridView1->RowHeadersVisible = false;
				 this->dataGridView1->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::CellSelect;
				 this->dataGridView1->Size = System::Drawing::Size(525, 63);
				 this->dataGridView1->TabIndex = 18;
				 // 
				 // UniqueID
				 // 
				 dataGridViewCellStyle1->BackColor = System::Drawing::Color::White;
				 this->UniqueID->DefaultCellStyle = dataGridViewCellStyle1;
				 this->UniqueID->HeaderText = L"Уникальный  ID";
				 this->UniqueID->Name = L"UniqueID";
				 this->UniqueID->ReadOnly = true;
				 this->UniqueID->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 // 
				 // SignalLVL
				 // 
				 this->SignalLVL->HeaderText = L"Уровень сигнала";
				 this->SignalLVL->Name = L"SignalLVL";
				 this->SignalLVL->ReadOnly = true;
				 this->SignalLVL->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 // 
				 // QualityLVL
				 // 
				 dataGridViewCellStyle2->ForeColor = System::Drawing::Color::Green;
				 this->QualityLVL->DefaultCellStyle = dataGridViewCellStyle2;
				 this->QualityLVL->HeaderText = L"Качество приема сигнала";
				 this->QualityLVL->Name = L"QualityLVL";
				 this->QualityLVL->ReadOnly = true;
				 this->QualityLVL->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 // 
				 // BatteryLVL
				 // 
				 this->BatteryLVL->HeaderText = L"Уровень заряда батареи";
				 this->BatteryLVL->Name = L"BatteryLVL";
				 this->BatteryLVL->ReadOnly = true;
				 this->BatteryLVL->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 // 
				 // WorkMode
				 // 
				 this->WorkMode->HeaderText = L"Режим работы";
				 this->WorkMode->Name = L"WorkMode";
				 this->WorkMode->ReadOnly = true;
				 this->WorkMode->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 // 
				 // ChangeParamBtn
				 // 
				 this->ChangeParamBtn->Location = System::Drawing::Point(9, 152);
				 this->ChangeParamBtn->Name = L"ChangeParamBtn";
				 this->ChangeParamBtn->Size = System::Drawing::Size(121, 23);
				 this->ChangeParamBtn->TabIndex = 19;
				 this->ChangeParamBtn->Text = L"Смена параметров";
				 this->ChangeParamBtn->UseVisualStyleBackColor = true;
				 this->ChangeParamBtn->Click += gcnew System::EventHandler(this, &device_prop::ChangeParam_Click);
				 // 
				 // textBox1
				 // 
				 this->textBox1->Location = System::Drawing::Point(9, 220);
				 this->textBox1->Multiline = true;
				 this->textBox1->Name = L"textBox1";
				 this->textBox1->Size = System::Drawing::Size(304, 131);
				 this->textBox1->TabIndex = 20;
				 // 
				 // chart1
				 // 
				 chartArea1->Name = L"ChartArea1";
				 this->chart1->ChartAreas->Add(chartArea1);
				 this->chart1->Dock = System::Windows::Forms::DockStyle::Bottom;
				 legend1->Name = L"Legend1";
				 this->chart1->Legends->Add(legend1);
				 this->chart1->Location = System::Drawing::Point(0, 357);
				 this->chart1->Name = L"chart1";
				 series1->ChartArea = L"ChartArea1";
				 series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Area;
				 series1->Legend = L"Legend1";
				 series1->Name = L"RSSI";
				 series1->YValuesPerPoint = 2;
				 this->chart1->Series->Add(series1);
				 this->chart1->Size = System::Drawing::Size(525, 151);
				 this->chart1->TabIndex = 21;
				 this->chart1->Text = L"chart1";
				 // 
				 // checkBox1
				 // 
				 this->checkBox1->AutoSize = true;
				 this->checkBox1->Location = System::Drawing::Point(6, 89);
				 this->checkBox1->Name = L"checkBox1";
				 this->checkBox1->Size = System::Drawing::Size(50, 17);
				 this->checkBox1->TabIndex = 22;
				 this->checkBox1->Text = L"Авто";
				 this->checkBox1->UseVisualStyleBackColor = true;
				 this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &device_prop::checkBox1_CheckedChanged);
				 // 
				 // textBox2
				 // 
				 this->textBox2->Location = System::Drawing::Point(414, 76);
				 this->textBox2->Name = L"textBox2";
				 this->textBox2->Size = System::Drawing::Size(100, 20);
				 this->textBox2->TabIndex = 23;
				 this->textBox2->TextChanged += gcnew System::EventHandler(this, &device_prop::recalc);
				 // 
				 // textBox3
				 // 
				 this->textBox3->Location = System::Drawing::Point(414, 106);
				 this->textBox3->Name = L"textBox3";
				 this->textBox3->Size = System::Drawing::Size(100, 20);
				 this->textBox3->TabIndex = 24;
				 this->textBox3->TextChanged += gcnew System::EventHandler(this, &device_prop::recalc);
				 // 
				 // label6
				 // 
				 this->label6->AutoSize = true;
				 this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(204)));
				 this->label6->Location = System::Drawing::Point(319, 221);
				 this->label6->Name = L"label6";
				 this->label6->Size = System::Drawing::Size(45, 16);
				 this->label6->TabIndex = 31;
				 this->label6->Text = L"label6";
				 // 
				 // groupBox1
				 // 
				 this->groupBox1->Controls->Add(this->radioButton2);
				 this->groupBox1->Controls->Add(this->radioButton1);
				 this->groupBox1->Controls->Add(this->label7);
				 this->groupBox1->Controls->Add(this->textBox6);
				 this->groupBox1->Controls->Add(this->MeasTime);
				 this->groupBox1->Controls->Add(this->numericUpDown1);
				 this->groupBox1->Controls->Add(this->label2);
				 this->groupBox1->Controls->Add(this->checkBox1);
				 this->groupBox1->Location = System::Drawing::Point(136, 69);
				 this->groupBox1->Name = L"groupBox1";
				 this->groupBox1->Size = System::Drawing::Size(272, 135);
				 this->groupBox1->TabIndex = 36;
				 this->groupBox1->TabStop = false;
				 this->groupBox1->Text = L"Измерение расстояния";
				 // 
				 // radioButton2
				 // 
				 this->radioButton2->AutoSize = true;
				 this->radioButton2->Location = System::Drawing::Point(143, 38);
				 this->radioButton2->Name = L"radioButton2";
				 this->radioButton2->Size = System::Drawing::Size(116, 17);
				 this->radioButton2->TabIndex = 26;
				 this->radioButton2->Text = L"Временной метод";
				 this->radioButton2->UseVisualStyleBackColor = true;
				 // 
				 // radioButton1
				 // 
				 this->radioButton1->AutoSize = true;
				 this->radioButton1->Checked = true;
				 this->radioButton1->Location = System::Drawing::Point(143, 15);
				 this->radioButton1->Name = L"radioButton1";
				 this->radioButton1->Size = System::Drawing::Size(123, 17);
				 this->radioButton1->TabIndex = 25;
				 this->radioButton1->TabStop = true;
				 this->radioButton1->Text = L"По уровню сигнала";
				 this->radioButton1->UseVisualStyleBackColor = true;
				 this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &device_prop::change_dist_meas_method);
				 // 
				 // label7
				 // 
				 this->label7->AutoSize = true;
				 this->label7->Location = System::Drawing::Point(148, 90);
				 this->label7->Name = L"label7";
				 this->label7->Size = System::Drawing::Size(55, 13);
				 this->label7->TabIndex = 24;
				 this->label7->Text = L"период, с";
				 // 
				 // textBox6
				 // 
				 this->textBox6->Location = System::Drawing::Point(62, 85);
				 this->textBox6->Name = L"textBox6";
				 this->textBox6->Size = System::Drawing::Size(80, 20);
				 this->textBox6->TabIndex = 23;
				 this->textBox6->Text = L"10";
				 // 
				 // button1
				 // 
				 this->button1->Location = System::Drawing::Point(424, 159);
				 this->button1->Name = L"button1";
				 this->button1->Size = System::Drawing::Size(75, 23);
				 this->button1->TabIndex = 37;
				 this->button1->Text = L"calibrate";
				 this->button1->UseVisualStyleBackColor = true;
				 this->button1->Click += gcnew System::EventHandler(this, &device_prop::button1_Click_1);
				 // 
				 // device_prop
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(525, 508);
				 this->Controls->Add(this->button1);
				 this->Controls->Add(this->groupBox1);
				 this->Controls->Add(this->label6);
				 this->Controls->Add(this->textBox3);
				 this->Controls->Add(this->textBox2);
				 this->Controls->Add(this->chart1);
				 this->Controls->Add(this->textBox1);
				 this->Controls->Add(this->ChangeParamBtn);
				 this->Controls->Add(this->dataGridView1);
				 this->Controls->Add(this->comboBox2);
				 this->Controls->Add(this->label3);
				 this->Controls->Add(this->label1);
				 this->Controls->Add(this->comboBox1);
				 this->Controls->Add(this->reset_cc);
				 this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
				 this->MaximizeBox = false;
				 this->MinimizeBox = false;
				 this->Name = L"device_prop";
				 this->Text = L"device_prop";
				 this->Load += gcnew System::EventHandler(this, &device_prop::device_prop_Load);
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
				 this->groupBox1->ResumeLayout(false);
				 this->groupBox1->PerformLayout();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		try {
			if (!comport->IsOpen)
				comport->Open();
			ConstructCMD(comport, CMDtype::RESET);
		}
		catch (IO::IOException ^ioexception) {
			textBox1->AppendText("\r\n" + ioexception->Message);
		}
	}
	private: System::Void device_prop_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void MeasTime_Click(System::Object^  sender, System::EventArgs^  e) {
		MeasCycles = Decimal::ToInt32(numericUpDown1->Value);
		Thread^ tMeasDist = gcnew Thread(gcnew ThreadStart(this, &device_prop::MeasDist));
		tMeasDist->Start();
	}
	private: System::Void ChangeParam_Click(System::Object^  sender, System::EventArgs^  e) {
		ChangeParam();
	}
	private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (checkBox1->Checked) {
			MeasTime->Text = "Пуск";
		}
		else {
			MeasTime->Text = "Однократное";
		}
	}
	private: System::Void recalc(System::Object^  sender, System::EventArgs^  e);
	private: System::Void change_dist_meas_method(System::Object^  sender, System::EventArgs^  e);
	private: System::Void comboBox2_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		power_index = comboBox2->SelectedIndex;
	}
	private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
		offset = last_num;
	}
	};
}
