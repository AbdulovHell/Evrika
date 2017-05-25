#pragma once
#include <iostream>
namespace Evrika {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

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
			comboBox2->SelectedIndex = 3;
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
			chart = chart1;
			g_auto_meas_time = auto_meas_time;
			chkbox = checkBox1;
			PowerIndex=comboBox2;
			SignLvlDistLabel = label6;
			hDevice_prop = this;
			kTextBox = textBox5;
			my_log=textBox1;
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
		Device^ curDev;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Label^  label4;



	private: System::Windows::Forms::Label^  label5;

			 System::IO::Ports::SerialPort^ comport;
			 KalmanFilter^ cycles_filt = gcnew KalmanFilter(1, 1, 2000, 60);
			 bool ststate = true;
			 int probes = 0;
	private: System::Windows::Forms::Label^  label6;

	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::GroupBox^  groupBox1;
			 double meters = 0;
	public:
		void ProceedPoints(List<int64_t>^ cpu_cycles) {
			/*int64_t mid = 0, min = -1;
			for (int i = 0; i < cpu_cycles->Count; i++)
			{
				cpu_cycles[i] -= int::Parse(textBox4->Text);//226824
				if (cpu_cycles[i] < min) min = cpu_cycles[i];
				mid += cpu_cycles[i];
			}
			mid /= cpu_cycles->Count;
			KalmanFilter^ mid_cycles = gcnew KalmanFilter(1, 1, int::Parse(textBox5->Text), int::Parse(textBox6->Text));
			device_prop::chart->Series[0]->Points->Clear();
			device_prop::chart->Series[1]->Points->Clear();
			int32_t kMid = 0;
			for (int i = 0; i < cpu_cycles->Count; i++)
			{
				if (cpu_cycles[i] > (mid * 5))
					cpu_cycles[i] = mid;
				if (i == 0) mid_cycles->SetState(cpu_cycles[i], double::Parse(textBox7->Text));
				mid_cycles->Correct(cpu_cycles[i]);
				kMid += mid_cycles->State;
				device_prop::chart->Series[0]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(i + 1, cpu_cycles[i]));
				device_prop::chart->Series[1]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(i + 1, mid_cycles->State));
			}
			kMid /= cpu_cycles->Count;
			device_prop::chart->Series[0]->Name = "Raw: " + mid.ToString();
			device_prop::chart->Series[1]->Name = "Filt: " + kMid.ToString();
			label5->Text = CyclesToMeters(kMid).ToString()+" m.";
			*/
			int64_t kMid = 0, mid = 0;
			device_prop::chart->Series[0]->Points->Clear();
			device_prop::chart->Series[1]->Points->Clear();
			for (int i = 0; i < cpu_cycles->Count; i++) {
				cpu_cycles[i] /= 2;
				mid += cpu_cycles[i];
			}
			mid /= cpu_cycles->Count;
			for (int i = 0; i < cpu_cycles->Count; i++)
			{
				if ((cpu_cycles[i] > (mid + 300)) || (cpu_cycles[i] < (-800 - mid)))
					cpu_cycles[i] = mid;
				if (i == 0 && ststate) {
					cycles_filt->SetState(cpu_cycles[i], 0.1);
					ststate = false;
				}
				cycles_filt->Correct(cpu_cycles[i]);
				kMid += cycles_filt->State;
				device_prop::chart->Series[0]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(i + 1, cpu_cycles[i] - int::Parse(textBox4->Text)));
				device_prop::chart->Series[1]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(i + 1, cycles_filt->State - int::Parse(textBox4->Text)));
			}
			kMid /= cpu_cycles->Count;
			device_prop::chart->Series[0]->Name = "1: " + (kMid - int::Parse(textBox4->Text)).ToString();
			device_prop::chart->Series[1]->Name = "2: " + kMid.ToString();
			meters += kMid - int::Parse(textBox4->Text);
			probes++;
			if (probes == 10) {
				meters /= 10.0;
				label5->Text = CyclesToMeters(meters).ToString() + " m.";
				meters = 0;
				probes = 0;
			}
			if (device_prop::chkbox->Checked)
				device_prop::g_auto_meas_time->Enabled = true;
		}
		static device_prop^ hDevice_prop;
		static System::Windows::Forms::CheckBox^ chkbox;
		static System::Windows::Forms::TextBox^ kTextBox;
		static System::Windows::Forms::TextBox^ my_log;
		static System::Windows::Forms::ComboBox^ PowerIndex;
		static System::Windows::Forms::Label^ SignLvlDistLabel;
		static System::Windows::Forms::Timer^ g_auto_meas_time;
		static  System::Windows::Forms::DataVisualization::Charting::Chart^  chart;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  UniqueID;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  SignalLVL;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  QualityLVL;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  BatteryLVL;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  WorkMode;
	private: System::Windows::Forms::Button^  ChangeParam;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	private: System::Windows::Forms::Timer^  auto_meas_time;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::ComponentModel::IContainer^  components;


#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Требуемый метод для поддержки конструктора — не изменяйте 
			 /// содержимое этого метода с помощью редактора кода.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
				 System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
				 System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
				 System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
				 System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
				 System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
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
				 this->ChangeParam = (gcnew System::Windows::Forms::Button());
				 this->textBox1 = (gcnew System::Windows::Forms::TextBox());
				 this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
				 this->auto_meas_time = (gcnew System::Windows::Forms::Timer(this->components));
				 this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
				 this->textBox2 = (gcnew System::Windows::Forms::TextBox());
				 this->textBox3 = (gcnew System::Windows::Forms::TextBox());
				 this->textBox4 = (gcnew System::Windows::Forms::TextBox());
				 this->label4 = (gcnew System::Windows::Forms::Label());
				 this->label5 = (gcnew System::Windows::Forms::Label());
				 this->label6 = (gcnew System::Windows::Forms::Label());
				 this->button2 = (gcnew System::Windows::Forms::Button());
				 this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
				 this->textBox5 = (gcnew System::Windows::Forms::TextBox());
				 this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
				 this->groupBox1->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // reset_cc
				 // 
				 this->reset_cc->Location = System::Drawing::Point(301, 132);
				 this->reset_cc->Name = L"reset_cc";
				 this->reset_cc->Size = System::Drawing::Size(75, 23);
				 this->reset_cc->TabIndex = 0;
				 this->reset_cc->Text = L"reset";
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
				 this->comboBox1->Location = System::Drawing::Point(12, 66);
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
				 this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 50, 0, 0, 0 });
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(9, 50);
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
				 this->label3->Location = System::Drawing::Point(9, 90);
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
				 this->comboBox2->Location = System::Drawing::Point(12, 106);
				 this->comboBox2->Name = L"comboBox2";
				 this->comboBox2->Size = System::Drawing::Size(121, 21);
				 this->comboBox2->TabIndex = 8;
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
				 this->dataGridView1->Size = System::Drawing::Size(719, 44);
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
				 // ChangeParam
				 // 
				 this->ChangeParam->Location = System::Drawing::Point(12, 133);
				 this->ChangeParam->Name = L"ChangeParam";
				 this->ChangeParam->Size = System::Drawing::Size(121, 23);
				 this->ChangeParam->TabIndex = 19;
				 this->ChangeParam->Text = L"Смена параметров";
				 this->ChangeParam->UseVisualStyleBackColor = true;
				 this->ChangeParam->Click += gcnew System::EventHandler(this, &device_prop::ChangeParam_Click);
				 // 
				 // textBox1
				 // 
				 this->textBox1->Location = System::Drawing::Point(12, 167);
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
				 this->chart1->Location = System::Drawing::Point(0, 305);
				 this->chart1->Name = L"chart1";
				 series1->ChartArea = L"ChartArea1";
				 series1->Legend = L"Legend1";
				 series1->Name = L"Series1";
				 series2->ChartArea = L"ChartArea1";
				 series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
				 series2->Legend = L"Legend1";
				 series2->Name = L"Series2";
				 this->chart1->Series->Add(series1);
				 this->chart1->Series->Add(series2);
				 this->chart1->Size = System::Drawing::Size(719, 168);
				 this->chart1->TabIndex = 21;
				 this->chart1->Text = L"chart1";
				 // 
				 // auto_meas_time
				 // 
				 this->auto_meas_time->Interval = 200;
				 this->auto_meas_time->Tick += gcnew System::EventHandler(this, &device_prop::auto_meas_time_Tick);
				 // 
				 // checkBox1
				 // 
				 this->checkBox1->AutoSize = true;
				 this->checkBox1->Location = System::Drawing::Point(36, 88);
				 this->checkBox1->Name = L"checkBox1";
				 this->checkBox1->Size = System::Drawing::Size(50, 17);
				 this->checkBox1->TabIndex = 22;
				 this->checkBox1->Text = L"Авто";
				 this->checkBox1->UseVisualStyleBackColor = true;
				 this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &device_prop::checkBox1_CheckedChanged);
				 // 
				 // textBox2
				 // 
				 this->textBox2->Location = System::Drawing::Point(433, 126);
				 this->textBox2->Name = L"textBox2";
				 this->textBox2->Size = System::Drawing::Size(100, 20);
				 this->textBox2->TabIndex = 23;
				 this->textBox2->TextChanged += gcnew System::EventHandler(this, &device_prop::recalc);
				 // 
				 // textBox3
				 // 
				 this->textBox3->Location = System::Drawing::Point(433, 156);
				 this->textBox3->Name = L"textBox3";
				 this->textBox3->Size = System::Drawing::Size(100, 20);
				 this->textBox3->TabIndex = 24;
				 this->textBox3->TextChanged += gcnew System::EventHandler(this, &device_prop::recalc);
				 // 
				 // textBox4
				 // 
				 this->textBox4->Location = System::Drawing::Point(485, 93);
				 this->textBox4->Name = L"textBox4";
				 this->textBox4->Size = System::Drawing::Size(100, 20);
				 this->textBox4->TabIndex = 25;
				 this->textBox4->Text = L"113405";
				 // 
				 // label4
				 // 
				 this->label4->AutoSize = true;
				 this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(204)));
				 this->label4->Location = System::Drawing::Point(428, 93);
				 this->label4->Name = L"label4";
				 this->label4->Size = System::Drawing::Size(62, 17);
				 this->label4->TabIndex = 26;
				 this->label4->Text = L"Cycles - ";
				 // 
				 // label5
				 // 
				 this->label5->AutoSize = true;
				 this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(204)));
				 this->label5->Location = System::Drawing::Point(430, 59);
				 this->label5->Name = L"label5";
				 this->label5->Size = System::Drawing::Size(46, 17);
				 this->label5->TabIndex = 30;
				 this->label5->Text = L"label5";
				 // 
				 // label6
				 // 
				 this->label6->AutoSize = true;
				 this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(204)));
				 this->label6->Location = System::Drawing::Point(339, 212);
				 this->label6->Name = L"label6";
				 this->label6->Size = System::Drawing::Size(45, 16);
				 this->label6->TabIndex = 31;
				 this->label6->Text = L"label6";
				 // 
				 // button2
				 // 
				 this->button2->Location = System::Drawing::Point(278, 56);
				 this->button2->Name = L"button2";
				 this->button2->Size = System::Drawing::Size(123, 23);
				 this->button2->TabIndex = 33;
				 this->button2->Text = L"Режим изм. времени";
				 this->button2->UseVisualStyleBackColor = true;
				 this->button2->Click += gcnew System::EventHandler(this, &device_prop::button2_Click);
				 // 
				 // checkBox2
				 // 
				 this->checkBox2->AutoSize = true;
				 this->checkBox2->Location = System::Drawing::Point(301, 83);
				 this->checkBox2->Name = L"checkBox2";
				 this->checkBox2->Size = System::Drawing::Size(83, 17);
				 this->checkBox2->TabIndex = 34;
				 this->checkBox2->Text = L"Вкл./Выкл.";
				 this->checkBox2->UseVisualStyleBackColor = true;
				 // 
				 // textBox5
				 // 
				 this->textBox5->Location = System::Drawing::Point(342, 242);
				 this->textBox5->Name = L"textBox5";
				 this->textBox5->Size = System::Drawing::Size(59, 20);
				 this->textBox5->TabIndex = 35;
				 this->textBox5->Text = L"1,4";
				 // 
				 // groupBox1
				 // 
				 this->groupBox1->Controls->Add(this->MeasTime);
				 this->groupBox1->Controls->Add(this->numericUpDown1);
				 this->groupBox1->Controls->Add(this->label2);
				 this->groupBox1->Controls->Add(this->checkBox1);
				 this->groupBox1->Location = System::Drawing::Point(139, 50);
				 this->groupBox1->Name = L"groupBox1";
				 this->groupBox1->Size = System::Drawing::Size(127, 111);
				 this->groupBox1->TabIndex = 36;
				 this->groupBox1->TabStop = false;
				 this->groupBox1->Text = L"Измерение времени";
				 // 
				 // device_prop
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(719, 473);
				 this->Controls->Add(this->groupBox1);
				 this->Controls->Add(this->textBox5);
				 this->Controls->Add(this->checkBox2);
				 this->Controls->Add(this->button2);
				 this->Controls->Add(this->label6);
				 this->Controls->Add(this->label5);
				 this->Controls->Add(this->textBox4);
				 this->Controls->Add(this->label4);
				 this->Controls->Add(this->textBox3);
				 this->Controls->Add(this->textBox2);
				 this->Controls->Add(this->chart1);
				 this->Controls->Add(this->textBox1);
				 this->Controls->Add(this->ChangeParam);
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
		try {
			if (!comport->IsOpen)
				comport->Open();
			ConstructCMD(comport, curDev->unique_id, (uint8_t)Decimal::ToInt16(numericUpDown1->Value));
		}
		catch (IO::IOException ^ioexception) {
			textBox1->AppendText("\r\n" + ioexception->Message);
		}
	}
	private: System::Void ChangeParam_Click(System::Object^  sender, System::EventArgs^  e) {
		try {
			if (!comport->IsOpen)
				comport->Open();
			ConstructCMD(comport, curDev->unique_id, comboBox1->SelectedIndex, 900000000, comboBox2->SelectedIndex, NULL, NULL);
		}
		catch (IO::IOException ^ioexception) {
			textBox1->AppendText("\r\n" + ioexception->Message);
		}
	}
	private: System::Void auto_meas_time_Tick(System::Object^  sender, System::EventArgs^  e) {
		MeasTime_Click(sender, e);
		auto_meas_time->Enabled = false;
	}
	private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		auto_meas_time->Enabled = checkBox1->Checked;
	}
	private: System::Void recalc(System::Object^  sender, System::EventArgs^  e) {
		try {
			if (dynamic_cast<TextBox^>(sender) == textBox2) {
				int m = int::Parse(textBox2->Text);
				uint32_t c = 300000000;
				double t = (double)m / (double)c;
				const double cycle = 0.000000010;
				int32_t cycles = t / cycle;
				textBox3->TextChanged -= gcnew System::EventHandler(this, &device_prop::recalc);
				textBox3->Text = cycles.ToString();
				textBox3->TextChanged += gcnew System::EventHandler(this, &device_prop::recalc);
			}
			else if (dynamic_cast<TextBox^>(sender) == textBox3) {
				int32_t cycles = int::Parse(textBox3->Text);
				const double cycle = 0.000000010;
				double t = cycles*cycle;
				uint32_t c = 300000000;
				double m = (double)c*t;
				textBox2->TextChanged -= gcnew System::EventHandler(this, &device_prop::recalc);
				textBox2->Text = m.ToString();
				textBox2->TextChanged += gcnew System::EventHandler(this, &device_prop::recalc);
			}
		}
		catch (...) {
			MessageBoxA(0, "pzdc", "Device_prop exception", 0);
		}
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		ConstructCMD(comport, curDev->unique_id ,checkBox2->Checked);
	}
};
}
