#include <iostream>
#include "templates.h"
#include <Windows.h>
#include <Psapi.h>
#include "device_prop.h"

System::Void Evrika::device_prop::recalc(System::Object ^ sender, System::EventArgs ^ e)
{
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
