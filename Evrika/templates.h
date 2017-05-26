namespace Evrika {
	using namespace System;

	ref class TimeAndDate;

	public ref class Device {

	public:
		int unique_id;
		int signal_lvl;
		int signal_quality;
		double battery_lvl;
		int work_mode;
		void* pWork_mode;
		bool Processed;
		int missing_counter;

		ref class work_mode1 {
			double Latitude;
			double Longitude;
			int Precision;
			TimeAndDate^ dt;
		};
		ref class work_mode2 {
			int Freq_ch;
			int tPulse;
			int tPause;
			int PulseCount;
		};
		ref class work_mode3 {
			TimeAndDate^ inSleep;
			TimeAndDate^ outSleep;
			int Mode_out;
		};
		ref class work_mode4 {
			int bSwitch;
		};

		Device()
		{
			int unique_id = NULL;
			int signal_lvl = NULL;
			int signal_quality = NULL;
			double battery_lvl = NULL;
			int work_mode = NULL;
			void* pWork_mode = NULL;
			bool Processed = NULL;
			int missing_counter = NULL;
		}
		~Device() {}
		Device(int _unique_id, int _signal_lvl, int _signal_quality, double _battery_lvl, int _work_mode, void* _pWork_mode)
		{
			unique_id = _unique_id;
			signal_lvl = _signal_lvl;
			signal_quality = _signal_quality;
			battery_lvl = _battery_lvl;
			work_mode = _work_mode;
			pWork_mode = _pWork_mode;
			Processed = false;
			missing_counter = 0;
		}
		String^ Device::IdInHex();
		void Device::copy(Device^);
	};

	public ref class TimeAndDate {

	public:
		int day;
		int month;
		int year;
		int hours;
		int minutes;
		int seconds;

		TimeAndDate() {

		}
		TimeAndDate(int _dd, int _mm, int _yyyy, int _hh, int _min, int _sec) {
			day = _dd;
			month = _mm;
			year = _yyyy;
			hours = _hh;
			minutes = _min;
			seconds = _sec;
		}
		int GetCurrentTimeAndDate();
		String^ ToSysString();
		void copy(TimeAndDate^);
	};
	public ref class Event {
	public:
		enum class EventCode : int {
			EMPTY = 0,
			DEV_CONNECTED = 1,
			DEV_DISCONNECTED = 2
		};

		TimeAndDate^ td;
		String^ sEvent;
		EventCode eCode;
		Device^ device;
	public:
		String^ toStr(EventCode _eCode) {
			switch (_eCode) {
			case EventCode::DEV_CONNECTED:
				return "”стройство найдено";
			case EventCode::DEV_DISCONNECTED:
				return "—игнал потер€н";
			default:
				return "Unresolved";
			}
		}

		//default
		Event() {
			td = gcnew TimeAndDate();
			device = gcnew Device();
			sEvent = "null";
		}
		~Event() {
			delete td;
			delete device;
		}
		//this td, in dev&event
		Event(Device^ _device, EventCode _eCode) {
			td = gcnew TimeAndDate();
			device = gcnew Device();
			device->copy(_device);
			td->GetCurrentTimeAndDate();
			eCode = _eCode;
			sEvent = toStr(eCode);
		}
		Event(Device^ _device, TimeAndDate^ _td, EventCode _eCode) {
			td = gcnew TimeAndDate();
			device = gcnew Device();
			device->copy(_device);
			td->copy(_td);
			eCode = _eCode;
			sEvent = toStr(eCode);
		}
	};

	public ref class KalmanFilter {
		double X0, P0, F, H, R, Q, Covariance, B;

	public:
		double State;

		//1, 1, 200, 15
		KalmanFilter() {
			Q = 15;
			R = 200;
			F = 1;
			H = 1;
			B = 0;
		}

		KalmanFilter(double f, double h, double r, double q) {
			Q = q;
			R = r;
			F = f;
			H = h;
			B = 0;
		}

		void SetState(double state, double covariance) {
			State = state;
			Covariance = covariance;
		}

		void Correct(double data) {
			X0 = F * State;
			P0 = F * Covariance * F + Q;

			double K = H * P0 / (H * P0 * H + R);
			State = X0 + K * (data - H * X0);
			Covariance = (1 - K * H) * P0;
		}
	};

	enum class CMDtype : unsigned char {
		CHECK_COM = 1,
		RESET = 2,
		GETGPS = 3,
		GPSSTAT = 4
	};
	// онструктор команды на пробуждение меток
	bool ConstructCMD(System::IO::Ports::SerialPort^, uint32_t);
	// онструктор команды запроса параметров конкретной метки
	bool ConstructCMD(System::IO::Ports::SerialPort^, uint32_t, uint16_t dummy);
	// онструктор команд без аргументов
	bool ConstructCMD(System::IO::Ports::SerialPort^, CMDtype);
	// онструктор команды изменени€ параметров
	bool ConstructCMD(System::IO::Ports::SerialPort^, uint32_t, uint8_t, uint32_t, uint8_t, uint8_t, uint8_t);
	// онструктор команды запуска цикла измерени€ задержек
	bool ConstructCMD(System::IO::Ports::SerialPort^, uint32_t, uint8_t);
	// онструктор команды вкл/выкл GPS
	bool ConstructCMD(System::IO::Ports::SerialPort^, bool);
	// онструктор команды переключени€ в режим измерени€ задержек
	bool ConstructCMD(System::IO::Ports::SerialPort^ port, uint32_t addr, bool enable);

	double CyclesToMeters(int);
	double dBToW(double lvl, double offset);
	double SignalLvlToMeters(double lvl, double tdB);
	double ConvertToMeters(double RSSI,double n,double A);
	//CK_A[size-2],CK_B[size-1]
	void CalcSum(cli::array<unsigned char>^, size_t);
	void PasteInBuffer(cli::array<unsigned char>^, size_t, uint32_t);
	double GetDoubleFromBuf(cli::array<wchar_t>^, size_t offset);
	float GetFloatFromBuf(cli::array<wchar_t>^, size_t offset);
	
}
