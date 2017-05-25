#include "mainform.h"
#include "mapform.h"

System::Void Evrika::mapform::gMapControl1_OnMapDrag()
{
	mainform::my_handle->UpdateMapPos();
}
