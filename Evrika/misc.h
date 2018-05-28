namespace Evrika {
	using namespace System;
	using namespace System::Collections::Generic;
	using namespace Evrika::EMath;

	ref class TimeAndDate;
	ref class RadioTag;

	double CyclesToMeters(uint32_t cycles);
	double TimeToMeters(double time);
	double dBToW(double lvl, double offset);
	double SignalLvlToMeters(double lvl, double tdB);
	double ConvertToMeters(double RSSI, double n, double RSSI_In_1_m);
	double LinCycleToMeters(uint32_t cycles, uint8_t bitrate);
	//CK_A[size-2],CK_B[size-1]
	void CalcSum(cli::array<unsigned char>^, size_t);
	void PasteInBuffer(cli::array<unsigned char>^, size_t, uint32_t);
	double GetDoubleFromBuf(cli::array<wchar_t>^, size_t offset);
	float GetFloatFromBuf(cli::array<wchar_t>^, size_t offset);
	uint32_t ToInt32FromBuf(cli::array<wchar_t>^, size_t offset);

	/*public ref class Floodgate {
		System::Threading::Mutex^ mut;
		bool work;

	public:
		Floodgate(bool init_state) {
			mut = gcnew System::Threading::Mutex();
			work = init_state;
		}

		bool TrySwoosh() {
			if (work) {
				return false;
			}
			return mut->WaitOne();
		}

		void Lock() {
			work = false;
		}

		void Unlock() {
			work = true;
			try {
				mut->ReleaseMutex();
			}catch(...){}
		}

		bool State() {
			return work;
		}
	};*/

	public ref class Device {
		uint32_t Addr;

		int8_t rssi;
		int8_t lqi;
		float vbatt;

		bool relay;
	public:
		bool Processed;
		int missing_counter;

		Device(uint32_t _addr)
		{
			Addr = _addr;
			Processed = false;
			missing_counter = 0;
			vbatt = 0;
			rssi = 0;
			lqi = 0;
		}

		virtual void Fill(float _vbatt, int8_t _rssi, int8_t _lqi) {
			vbatt = _vbatt;
			rssi = _rssi;
			lqi = _lqi;
		}
		void SaveRelayStat(bool _r) {
			relay = _r;
		}
		String^ Device::IdInHex();
		uint32_t GetAddr() { return Addr; }
		int8_t GetSignalLvl() { return rssi; }
		int8_t GetSignalQuality() { return lqi; }
		float GetBatteryLvl() { return vbatt; }
		virtual void copy(Device^ dev) {
			Addr = dev->Addr;
			rssi = dev->rssi;
			lqi = dev->lqi;
			vbatt = dev->vbatt;
			relay = dev->relay;
			Processed = dev->Processed;
			missing_counter = dev->missing_counter;
		}
		virtual int GetDevType() {
			return 0;
		}
	};

	public ref class Repeater : public Device {
		uint8_t gps_stat;
	public:
		bool isLocal;
		double Lat = 0;
		double Lon = 0;
		List<RadioTag^>^ RadioTags;

		Repeater(uint32_t _addr, bool local) : Device(_addr) { isLocal = local; RadioTags = gcnew List<RadioTag^>; }

		void GetInfo();
		void SetGPSStat(uint8_t _gps_stat) { gps_stat = _gps_stat; }
		bool IfKnownPos() { return (bool)gps_stat; }

		void copy(Repeater^ rep) {
			isLocal = rep->isLocal;
			Device::copy(rep);
		}
		virtual int GetDevType() override {
			return 1;
		}
	};

	public ref class RadioTag : public Device {
		uint32_t time;
		int8_t adaptive_rssi;
		float adaptive_time;
		uint8_t adaptive_bitrate;
		double distance_t;
	public:
		bool ping;

		RadioTag(uint32_t _addr) : Device(_addr) { ping = false; }

		virtual void Fill(uint32_t _time, int8_t _adaptive_rssi, float _adaptive_time, uint8_t _adaptive_bitrate) {
			time = _time;
			adaptive_rssi = _adaptive_rssi;
			adaptive_time = _adaptive_time;
			adaptive_bitrate = _adaptive_bitrate;
		}

		virtual void copy(RadioTag^ dev) {
			time = dev->time;
			adaptive_rssi = dev->adaptive_rssi;
			adaptive_time = dev->adaptive_time;
			adaptive_bitrate = dev->adaptive_bitrate;
			Device::copy(dev);
		}
		virtual int GetDevType() override {
			return 2;
		}
		//сохраняет последнюю расчитанную дистанцию временным методом
		void SaveDist(double m) {
			if (m > 1000)
				distance_t = 1000.0;
			else
				distance_t = m;
		}
		//возвращает дистанцию до маяка
		double GetDistance() {
			//если полоса 2 или 3, вернем расстояние от временного метода
			if (adaptive_bitrate > 1) {
				return distance_t * ScaleCoef;
			}
			//если все плохо, то амплитудным
			else
			{
				return ConvertToMeters(adaptive_rssi, 2.472, 26) * ScaleCoef;
			}
		}
		double GetDistance(double n, double SignalLvlAt1m) {
			return ConvertToMeters(adaptive_rssi, n, SignalLvlAt1m) * ScaleCoef;
		}
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
			DEV_DISCONNECTED = 2,
			SIGNAL_FOUND = 3,
			SIGNAL_LOST = 4
		};

		TimeAndDate^ td;
		String^ sEvent;
		EventCode eCode;
		Device^ device;
	public:
		String^ toStr(EventCode _eCode) {
			switch (_eCode) {
			case EventCode::DEV_CONNECTED:
				return "Соединение установлено";
			case EventCode::DEV_DISCONNECTED:
				return "Соединение потеряно";
			case EventCode::SIGNAL_FOUND:
				return "Устройство обнаружено";
			case EventCode::SIGNAL_LOST:
				return "Сигнал потерян";
			default:
				return "Unresolved";
			}
		}

		//default
		Event() {
			td = gcnew TimeAndDate();
			device = gcnew Device(NULL);
			sEvent = "null";
		}
		~Event() {
			delete td;
			delete device;
		}
		//this td, in dev&event
		Event(Device^ _device, EventCode _eCode) {
			td = gcnew TimeAndDate();
			device = gcnew Device(_device->GetAddr());
			device->copy(_device);
			//device->copy(_device);
			td->GetCurrentTimeAndDate();
			eCode = _eCode;
			sEvent = toStr(eCode);
		}
		Event(Device^ _device, TimeAndDate^ _td, EventCode _eCode) {
			td = gcnew TimeAndDate();
			device = gcnew Device(_device->GetAddr());
			device->copy(_device);
			//device->copy(_device);
			td->copy(_td);
			eCode = _eCode;
			sEvent = toStr(eCode);
		}
	};

	template<typename T> std::string mToStr(T num) {
		char buf[10];
		sprintf_s(buf, 10, "%.2f", num);
		for (int i = 0; i < 10; i++)
			if (buf[i] == '.')
				buf[i] = ',';
		return std::string(buf);
	}

	template<typename T> void PushBack(cli::array<T>^ arr, T num) {
		for (int i = 0; i < arr->Length - 1; i++) {
			arr[i] = arr[i + 1];
		}
		arr[arr->Length - 1] = num;
	}

	public ref class Commands {
		static System::IO::Ports::SerialPort^ port;
		static void ConstructCMD(uint32_t Addr, uint8_t msg_class, uint8_t msg_id);
		static void ConstructCMD(uint32_t Addr, uint8_t msg_class, uint8_t msg_id, uint16_t msg_len, uint8_t msg_data);
		static void ConstructCMD(uint32_t Addr, uint8_t msg_class, uint8_t msg_id, uint16_t msg_len, uint32_t msg_data);
	public:
		Commands(System::IO::Ports::SerialPort^ _port) { port = _port; }

		//Предоставляет методы управления ретрансляторами и блоками управления
		ref class Class_0x0A {
		public:
			//Проверка соединения, id 0
			static void TestConnect();
			//Запрос локального адреса, id 1
			static void GetLocalAddr();
			//Запрос напряжений, id 2. В качестве параметра - адрес ретранслятора, для получения с локального у-ва - NULL
			static void GetVoltage(uint32_t Addr);
			//Запрос состояния реле, id 88
			static void GetRelayState(uint32_t Addr);
			//Управление реле, id 89
			static void SetRelayState(uint32_t Addr, uint8_t state);
			//Программный сброс, id 99
			static void ProgrammReset(uint32_t Addr);
		};
		//Содержит методы для управления GPS
		ref class Class_0x0B {
		public:
			//Вкл/Выкл GPS, id 1
			static void SetGPSPowerState(uint32_t Addr, uint8_t state);
			//Запрос состояния питания GPS, id 2
			static void GetGPSPowerState(uint32_t Addr);
			//Запрос статуса GPS, id 3
			static void GetGPSStatus(uint32_t Addr);
			//Запрос данных местоположения GPS, id 4
			static void GetGPSPosition(uint32_t Addr);
			//Переключение антенны GPS, id 5. 0 - внутренняя, 1 - внешняя антенна.
			static void ToggleGPSAntenna(uint32_t Addr, uint8_t state);
			//Запрос используемой антенны GPS, id 6.
			static void GetGPSUsingAntenna(uint32_t Addr);
		};
		//Методы управления радиометками
		ref class Class_0x0C {
		public:
			//Запуск цикла пробуждения радиометок, id 1. Addr - используемый ретранслятор, Timeout - время ожидания ответа.
			static void WakeUp(uint32_t Addr, uint32_t Timeout);
			//Запрос параметров найденных радиометок, id 2. Count - количество найденных после WakeUp радиометок.
			static void GetRadioTagsParam(uint32_t Addr, uint8_t Count);
			//Запуск цикла измерения временных задержек, id 3
			//static void StartTimeDelayMeasure();
			//Запрос данных измерения временных задержек, id 4
			//static void GetTimeDelayMeasureData();
			//Запрос параметров метки по адресу, id 5
			static void RequestRadioTagParam(uint32_t Addr, uint32_t TagAddress);
			//Считывание параметров метки по адресу, id 6
			static void GetRadioTagParam(uint32_t Addr, uint32_t TagAddress);
			//Сброс СС1101 к первоначальным установкам, id 7
			static void ResetCC1101(uint32_t Addr);
		};
		//Методы управления ретрансляторами
		ref class Class_0x0D {
		public:
			//Запуск цикла поиска ретрансляторов, id 1
			static void StartSearchRepeaters(uint32_t Addr);
			//Запрос параметров найденных ретрансляторов, id 2
			static void GetRepeatersParam(uint32_t Addr, uint8_t Count);
			//Глобальный сброс всех ретрансляторов, id 99
			static void GlobalResetRepeaters(uint32_t Addr);
		};
	};
}
