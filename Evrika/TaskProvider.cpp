#include <stdint.h>
#include <fstream>
#include <Windows.h>
#include <Psapi.h>

#include "emath.h"
#include "mainform.h"
#include "misc.h"
#include "TaskProvider.h"

Evrika::Tasks::Task::Task(TaskType type, uint32_t addr, uint32_t param)
{
	tt = type;
	Addr = addr;
	Param = param;
}

bool Evrika::Tasks::Task::Work()
{
	switch (tt) {
		//A
	case TaskType::TestConnect:
		Commands::Class_0x0A::TestConnect();
		break;
	case TaskType::GetLocalAddr:
		Commands::Class_0x0A::GetLocalAddr();
		break;
	case TaskType::GetVoltage:
		Commands::Class_0x0A::GetVoltage(Addr);
		break;
	case TaskType::GetRelayState:
		Commands::Class_0x0A::GetRelayState(Addr);
		break;
	case TaskType::SetRelayState:
		Commands::Class_0x0A::SetRelayState(Addr, Param);
		break;
	case TaskType::ProgrammReset:
		Commands::Class_0x0A::ProgrammReset(Addr);
		break;
		//B
	case TaskType::SetGPSPowerState:
		Commands::Class_0x0B::SetGPSPowerState(Addr, Param);
		break;
	case TaskType::GetGPSPowerState:
		Commands::Class_0x0B::GetGPSPowerState(Addr);
		break;
	case TaskType::GetGPSStatus:
		Commands::Class_0x0B::GetGPSStatus(Addr);
		break;
	case TaskType::GetGPSPosition:
		Commands::Class_0x0B::GetGPSPosition(Addr);
		break;
	case TaskType::ToggleGPSAntenna:
		Commands::Class_0x0B::ToggleGPSAntenna(Addr, Param);
		break;
	case TaskType::GetGPSUsingAntenna:
		Commands::Class_0x0B::GetGPSUsingAntenna(Addr);
		break;
		//C
	case TaskType::WakeUp:
		Commands::Class_0x0C::WakeUp(Addr, Param);
		break;
	case TaskType::GetRadioTagsParam:
		Commands::Class_0x0C::GetRadioTagsParam(Addr, Param);
		break;
	case TaskType::RequestRadioTagParam:
		Commands::Class_0x0C::RequestRadioTagParam(Addr, Param);
		break;
	case TaskType::GetRadioTagParam:
		Commands::Class_0x0C::GetRadioTagParam(Addr, Param);
		break;
	case TaskType::ResetCC1101:
		Commands::Class_0x0C::ResetCC1101(Addr);
		break;
		//D
	case TaskType::StartSearchRepeaters:
		Commands::Class_0x0D::StartSearchRepeaters(Addr);
		break;
	case TaskType::GetRepeatersParam:
		Commands::Class_0x0D::GetRepeatersParam(Addr, Param);
		break;
	case TaskType::GlobalResetRepeaters:
		Commands::Class_0x0D::GlobalResetRepeaters(Addr);
		break;
		//
	default:
		return false;
	}
	return true;
}

Evrika::Tasks::TaskType Evrika::Tasks::Task::GetType()
{
	return tt;
}

Evrika::Tasks::TaskProvider::TaskProvider(mainform^ hndl)
{
	tl = gcnew List<Task^>;
	sem = gcnew Semaphore(0, 3);
	this->hndl = hndl;
	//fg = gcnew Floodgate(true);
	sync = gcnew Semaphore(0, 5);
}

void Evrika::Tasks::TaskProvider::Go()
{
	sem->Release();
}

void Evrika::Tasks::TaskProvider::Add(Task ^ tsk)
{
	tl->Add(tsk);
}

int Evrika::Tasks::TaskProvider::Count()
{
	return tl->Count;
}

void Evrika::Tasks::TaskProvider::ProceedTasks()
{
	if (working) return;
	working = true;
	while (1) {
		//fg->TrySwoosh();
		//fg->Lock();
		//mut->WaitOne();
		//sync->WaitOne();
		if (tl->Count) {
			try {
				if (!tl[0]->Work()) {
					mainform::my_handle->Invoke(gcnew Action<String^>(mainform::my_handle, &mainform::WriteLog), "Ошибка отправки");
				}
				else {
#ifdef _DEBUG
					mainform::my_handle->Invoke(gcnew Action<String^>(mainform::my_handle, &mainform::WriteLog), "D: Отправлено, ожидает " + (tl->Count - 1).ToString());
#endif
					if (!sem->WaitOne(5000)) {
						mainform::my_handle->Invoke(gcnew Action<String^>(mainform::my_handle, &mainform::WriteLog), "Превышен предел ожидания ответа от ретранслятора");
					}
					else {
#ifdef _DEBUG
						mainform::my_handle->Invoke(gcnew Action<String^>(mainform::my_handle, &mainform::WriteLog), "D: Выполнено, ожидает " + (tl->Count - 1).ToString());
#endif
					}
				}
			}
			catch (...) {
				mainform::my_handle->Invoke(gcnew Action<String^>(mainform::my_handle, &mainform::WriteLog), "Критическая ошибка");
			}
			tl->RemoveAt(0);
		}
		if (tl->Count > 10) Clear();
		//mainform::my_handle
		//if (true)
		if (hndl->Created)
			hndl->Invoke(gcnew Action<int>(hndl, &mainform::UpdateTaskCounter), tl->Count);
		//fg->Unlock();
		//mut->ReleaseMutex();
		//sync->Release();
		System::Threading::Thread::Sleep(10);
	}
}

void Evrika::Tasks::TaskProvider::Clear()
{
	Dictionary<int, int> types;
#ifdef _DEBUG
	int counter = 0;
#endif
	for (int i = 0; i < tl->Count; i++) {
		if (!types.ContainsKey((int)tl[i]->GetType())) {
			types.Add((int)tl[i]->GetType(), 1);
		}
		else {
			types[(int)tl[i]->GetType()]++;
			if (types[(int)tl[i]->GetType()] > 5) {
				tl->RemoveAt(i--);
#ifdef _DEBUG
				counter++;
#endif
			}
		}
	}
#ifdef _DEBUG
	mainform::my_handle->Invoke(gcnew Action<String^>(mainform::my_handle, &mainform::WriteLog), "D: Выполнена очистка, удалено " + counter.ToString());
#endif
}
