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
				return "���������� �������";
			case EventCode::DEV_DISCONNECTED:
				return "������ �������";
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

	public ref class Commands {
		static System::IO::Ports::SerialPort^ port;
		static void ConstructCMD(uint32_t Addr, uint8_t msg_class, uint8_t msg_id);
		static void ConstructCMD(uint32_t Addr, uint8_t msg_class, uint8_t msg_id, uint16_t msg_len, uint8_t msg_data);
		static void ConstructCMD(uint32_t Addr, uint8_t msg_class, uint8_t msg_id, uint16_t msg_len, uint32_t msg_data);
	public:
		Commands(System::IO::Ports::SerialPort^ _port) { port = _port; }

		//������������� ������ ���������� ��������������� � ������� ����������
		ref class Class_0x0A {
		public:
			//�������� ����������, id 0
			static void TestConnect();
			//������ ���������� ������, id 1
			static void GetLocalAddr();
			//������ ����������, id 2. � �������� ��������� - ����� �������������, ��� ��������� � ���������� �-�� - NULL
			static void GetVoltage(uint32_t Addr);
			//������ ��������� ����, id 88
			static void GetRelayState(uint32_t Addr);
			//���������� ����, id 89
			static void SetRelayState(uint32_t Addr, uint8_t state);
			//����������� �����, id 99
			static void ProgrammReset(uint32_t Addr);
		};
		//�������� ������ ��� ���������� GPS
		ref class Class_0x0B {
		public:
			//���/���� GPS, id 1
			static void SetGPSPowerState(uint32_t Addr, uint8_t state);
			//������ ��������� ������� GPS, id 2
			static void GetGPSPowerState(uint32_t Addr);
			//������ ������� GPS, id 3
			static void GetGPSStatus(uint32_t Addr);
			//������ ������ �������������� GPS, id 4
			static void GetGPSPosition(uint32_t Addr);
			//������������ ������� GPS, id 5. 0 - ����������, 1 - ������� �������.
			static void ToggleGPSAntenna(uint32_t Addr, uint8_t state);
			//������ ������������ ������� GPS, id 6.
			static void GetGPSUsingAntenna(uint32_t Addr);
		};
		//������ ���������� ������������
		ref class Class_0x0C {
		public:
			//������ ����� ����������� ����������, id 1. Addr - ������������ ������������, Timeout - ����� �������� ������.
			static void WakeUp(uint32_t Addr, uint32_t Timeout);
			//������ ���������� ��������� ����������, id 2. Count - ���������� ��������� ����� WakeUp ����������.
			static void GetRadioTagsParam(uint32_t Addr, uint8_t Count);
			//������ ����� ��������� ��������� ��������, id 3
			//static void StartTimeDelayMeasure();
			//������ ������ ��������� ��������� ��������, id 4
			//static void GetTimeDelayMeasureData();
			//������ ���������� ����� �� ������, id 5
			static void RequestRadioTagParam(uint32_t Addr, uint32_t TagAddress);
			//���������� ���������� ����� �� ������, id 6
			static void GetRadioTagParam(uint32_t Addr, uint32_t TagAddress);
			//����� ��1101 � �������������� ����������, id 7
			static void ResetCC1101(uint32_t Addr);
		};
		//������ ���������� ���������������
		ref class Class_0x0D {
		public:
			//������ ����� ������ ��������������, id 1
			static void StartSearchRepeaters(uint32_t Addr);
			//������ ���������� ��������� ��������������, id 2
			static void GetRepeatersParam(uint32_t Addr, uint8_t Count);
			//���������� ����� ���� ��������������, id 99
			static void GlobalResetRepeaters(uint32_t Addr);
		};
	};

	double CyclesToMeters(int);
	double dBToW(double lvl, double offset);
	double SignalLvlToMeters(double lvl, double tdB);
	double ConvertToMeters(double RSSI, double n, double A);
	//CK_A[size-2],CK_B[size-1]
	void CalcSum(cli::array<unsigned char>^, size_t);
	void PasteInBuffer(cli::array<unsigned char>^, size_t, uint32_t);
	double GetDoubleFromBuf(cli::array<wchar_t>^, size_t offset);
	float GetFloatFromBuf(cli::array<wchar_t>^, size_t offset);

}
