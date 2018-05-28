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

		ref class TaskProvider {
			Semaphore^ sem;
			//static Floodgate^ fg;
			Semaphore^ sync;
			List<Task^>^ tl;
			bool working = false;

			mainform^ hndl;

		public:
			TaskProvider(mainform^ hndl);
			void Go();
			void Add(Task^ tsk);
			int Count();
			void ProceedTasks();
			void Clear();
		};
	}
}