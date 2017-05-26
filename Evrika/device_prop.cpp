#include <iostream>
#include "templates.h"
#include "mainform.h"
#include <Windows.h>
#include <Psapi.h>
#include "device_prop.h"

using namespace System::Collections::Generic;

void Evrika::device_prop::MeasDist()
{
	do {
		if (radioButton1->Checked) {	//RSSI
			List<int>^ RSSIs = gcnew List<int>;
			int64_t mid = 0;
			for (int i = 0; i < MeasCycles; i++) {
				try {
					if (comport->IsOpen) {
						//ConstructCMD(comport, curDev->unique_id, (uint8_t)Decimal::ToInt16(numericUpDown1->Value));
						ConstructCMD(comport, curDev->unique_id, (uint16_t)NULL);
					}
					else {
						//закрыт, ошибк
						throw(gcnew IO::IOException("COM-порт закрыт"));
					}
				}
				catch (IO::IOException ^ioexception) {
					textBox1->AppendText("\r\n" + ioexception->Message);
				}
				sMeasDist->WaitOne(1000);
				RSSIs->Add(curDev->signal_lvl);
				mid += curDev->signal_lvl;
			}
			mid /= RSSIs->Count;
			double powers[] = { 0,3,6,9,12,15,20,27 };
			float dist_m = (float)(SignalLvlToMeters(mid, 9.0)*1.4);
			this->Invoke(gcnew Action<float>(this, &device_prop::print_meters), dist_m);
			this->Invoke(gcnew Action<float>(mainform::my_handle, &mainform::AddNewPoint), dist_m);
		}
		else if (radioButton2->Checked) {

		}

		uint32_t sleep = 0;
		try {
			sleep = uint32_t::Parse(textBox6->Text);
		}
		catch (...) {
			//ошибка ввода
		}
		Sleep(sleep * 1000);
	} while (checkBox1->Checked);
}

void Evrika::device_prop::print_meters(float m)
{
	label6->Text = m.ToString();
}

void Evrika::device_prop::ProceedPoints(List<int64_t>^ cpu_cycles)
{
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
			cycles_filt->SetState((double)cpu_cycles[i], 0.1);
			ststate = false;
		}
		cycles_filt->Correct((double)cpu_cycles[i]);
		kMid += (int64_t)cycles_filt->State;
		device_prop::chart->Series[0]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(i + 1, (double)(cpu_cycles[i] - int::Parse(textBox4->Text))));
		device_prop::chart->Series[1]->Points->Add(gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(i + 1, cycles_filt->State - int::Parse(textBox4->Text)));
	}
	kMid /= cpu_cycles->Count;
	device_prop::chart->Series[0]->Name = "1: " + (kMid - int::Parse(textBox4->Text)).ToString();
	device_prop::chart->Series[1]->Name = "2: " + kMid.ToString();
	meters += kMid - int::Parse(textBox4->Text);
	probes++;
	if (probes == 10) {
		meters /= 10.0;
		label5->Text = CyclesToMeters((int)meters).ToString() + " m.";
		meters = 0;
		probes = 0;
	}
}

System::Void Evrika::device_prop::recalc(System::Object ^ sender, System::EventArgs ^ e)
{
	try {
		if (dynamic_cast<TextBox^>(sender) == textBox2) {
			int m = int::Parse(textBox2->Text);
			uint32_t c = 300000000;
			double t = (double)m / (double)c;
			const double cycle = 0.000000010;
			int32_t cycles = (int32_t)(t / cycle);
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
