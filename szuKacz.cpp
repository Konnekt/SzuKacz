#include "stdafx.h"
#include "includes.h"

int __stdcall IMessageProc(sIMessage_base* msgBase)
{
	return SzuKacz::Controller::getInstance()->process(msgBase);
}