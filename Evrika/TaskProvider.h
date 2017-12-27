#pragma once
#include <stdint.h>
namespace Evrika {
	namespace Tasks
	{
		using namespace System::Collections::Generic;
		using namespace System::Threading;

		enum class TaskType : int {
			Empty,
			TestConnect,
			GetLocalAddr,
			GetVoltage,
			GetRelayState,
			SetRelayState,
			ProgrammReset,
			SetGPSPowerState,
			GetGPSPowerState,
			GetGPSStatus,
			GetGPSPosition,
			ToggleGPSAntenna,
			GetGPSUsingAntenna,
			WakeUp,
			GetRadioTagsParam,
			RequestRadioTagParam,
			GetRadioTagParam,
			ResetCC1101,
			StartSearchRepeaters,
			GetRepeatersParam,
			GlobalResetRepeaters
		};

		ref class Task {
			TaskType tt;
			uint32_t Addr;
			uint32_t Param;

		public:
			Task(TaskType type, uint32_t addr, uint32_t param);
			bool Work();
			TaskType GetType();
		};

		static ref class TaskProvider {
			static Semaphore^ sem;
			static Floodgate^ fg;
			static List<Task^>^ tl;
			static bool working = false;
		public:
			TaskProvider();
			static void Go();
			static void Add(Task^ tsk);
			static int Count();
			static void ProceedTasks();
			static void Clear();
		};
	}
}