#pragma once

namespace Evrika {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	public ref class merge {
		//classes
	public: static ref class ColSetting {
	public:
		ColSetting() {
			voltCol = gcnew cli::array<Drawing::Color>(3);
			SignlLvlCol = gcnew cli::array<Drawing::Color>(3);
			voltLvl.Add(0);
			voltLvl.Add(0);
			voltLvl.Add(0);
			signlLvl.Add(0);
			signlLvl.Add(0);
			signlLvl.Add(0);

			fstream input("settings.e", ios::in | ios::binary);

			//getting batt color
			Evrika::ProgSettings::BatColor::LowLvl set1;
			if (!set1.ParseFromIstream(&input)) {
				set_default();
				return;
			}
			voltCol[0] = Drawing::Color::FromArgb(set1.r(), set1.g(), set1.b());
			voltLvl[0] = set1.voltage();
			Evrika::ProgSettings::BatColor::MidLvl set2;
			if (!set2.ParseFromIstream(&input)) {
				//WriteLog("Error loading settings.");
			}
			voltCol[1] = Drawing::Color::FromArgb(set2.r(), set2.g(), set2.b());
			voltLvl[1] = set2.voltage();
			Evrika::ProgSettings::BatColor::HighLvl set3;
			if (!set3.ParseFromIstream(&input)) {
				//WriteLog("Error loading settings.");
			}
			voltCol[2] = Drawing::Color::FromArgb(set3.r(), set3.g(), set3.b());
			voltLvl[2] = set3.voltage();

			//getting singl lvl color
			Evrika::ProgSettings::SignalLvlColor::LowLvl set4;
			if (!set4.ParseFromIstream(&input)) {
				//WriteLog("Error loading settings.");
			}
			SignlLvlCol[0] = Drawing::Color::FromArgb(set4.r(), set4.g(), set4.b());
			signlLvl[0] = set4.lvl();
			Evrika::ProgSettings::SignalLvlColor::MidLvl set5;
			if (!set5.ParseFromIstream(&input)) {
				//WriteLog("Error loading settings.");
			}
			SignlLvlCol[1] = Drawing::Color::FromArgb(set5.r(), set5.g(), set5.b());
			signlLvl[1] = set5.lvl();
			Evrika::ProgSettings::SignalLvlColor::HighLvl set6;
			if (!set6.ParseFromIstream(&input)) {
				//WriteLog("Error loading settings.");
			}
			SignlLvlCol[2] = Drawing::Color::FromArgb(set6.r(), set6.g(), set6.b());
			signlLvl[2] = set6.lvl();
		}
		void SaveToFile() {
			fstream output("settings.e", ios::out | ios::trunc | ios::binary);
			//writting batt color
			Evrika::ProgSettings::BatColor::LowLvl set1;
			set1.set_r(voltCol[0].R);
			set1.set_g(voltCol[0].B);
			set1.set_b(voltCol[0].G);
			set1.set_voltage(voltLvl[0]);
			if (!set1.SerializeToOstream(&output)) {
				//WriteLog("Error loading settings.");
			}

			Evrika::ProgSettings::BatColor::MidLvl set2;
			set2.set_r(voltCol[1].R);
			set2.set_g(voltCol[1].B);
			set2.set_b(voltCol[1].G);
			set2.set_voltage(voltLvl[1]);
			if (!set2.SerializeToOstream(&output)) {
				//WriteLog("Error loading settings.");
			}

			Evrika::ProgSettings::BatColor::HighLvl set3;
			set3.set_r(voltCol[2].R);
			set3.set_g(voltCol[2].B);
			set3.set_b(voltCol[2].G);
			set3.set_voltage(voltLvl[2]);
			if (!set3.SerializeToOstream(&output)) {
				//WriteLog("Error loading settings.");
			}

			//getting singl lvl color
			Evrika::ProgSettings::SignalLvlColor::LowLvl set4;
			set4.set_r(SignlLvlCol[0].R);
			set4.set_g(SignlLvlCol[0].B);
			set4.set_b(SignlLvlCol[0].G);
			set4.set_lvl(signlLvl[0]);
			if (!set4.SerializeToOstream(&output)) {
				//WriteLog("Error loading settings.");
			}

			Evrika::ProgSettings::SignalLvlColor::MidLvl set5;
			set5.set_r(SignlLvlCol[1].R);
			set5.set_g(SignlLvlCol[1].B);
			set5.set_b(SignlLvlCol[1].G);
			set5.set_lvl(signlLvl[1]);
			if (!set5.SerializeToOstream(&output)) {
				//WriteLog("Error loading settings.");
			}

			Evrika::ProgSettings::SignalLvlColor::HighLvl set6;
			set6.set_r(SignlLvlCol[2].R);
			set6.set_g(SignlLvlCol[2].B);
			set6.set_b(SignlLvlCol[2].G);
			set6.set_lvl(signlLvl[2]);
			if (!set6.SerializeToOstream(&output)) {
				//WriteLog("Error loading settings.");
			}
		}
		void setup_batt(Color low, Color mid, Color Hi, double dLow, double dMid, double dHi) {
			voltCol[0] = low;
			voltCol[1] = mid;
			voltCol[2] = Hi;
			voltLvl[0] = dLow;
			voltLvl[1] = dMid;
			voltLvl[2] = dHi;
		}
		void setup_SignlLvl(Color low, Color mid, Color Hi, int dLow, int dMid, int dHi) {
			SignlLvlCol[0] = low;
			SignlLvlCol[1] = mid;
			SignlLvlCol[2] = Hi;
			signlLvl[0] = dLow;
			signlLvl[1] = dMid;
			signlLvl[2] = dHi;
		}
		void set_default() {
			voltCol[0] = System::Drawing::Color::Red;
			voltCol[1] = System::Drawing::Color::Orange;
			voltCol[2] = System::Drawing::Color::LimeGreen;
			voltLvl[0] = 3.0;
			voltLvl[1] = 3.5;
			voltLvl[2] = 4.0;

			SignlLvlCol[0] = System::Drawing::Color::Red;
			SignlLvlCol[1] = System::Drawing::Color::Orange;
			SignlLvlCol[2] = System::Drawing::Color::LimeGreen;
			signlLvl[0] = -90;
			signlLvl[1] = -60;
			signlLvl[2] = -20;
		}
	private:
		cli::array<Drawing::Color>^ voltCol;
		List<double> voltLvl;
		cli::array<Drawing::Color>^ SignlLvlCol;
		List<int> signlLvl;
	};
			 //function&metods		 
			 static ColSetting^ GetColSettingP() {
				 return colsetting;
			 }
			 static void InitColSettings() {
				 colsetting = gcnew ColSetting();
			 }
			 //variables
	private:
		static ColSetting^ colsetting;
	};
}