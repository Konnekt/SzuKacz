/*
 * License - http://www.gnu.org/licenses/lgpl.txt
 */

#pragma once

//definicje
#define _WIN32_WINNT 0x501

//standardowe
#include <string>
#include <list>
#include <map>
#include <algorithm>
#include <deque>

//windowsowe
#include <windows.h>
#include <commctrl.h>

//konnektowe
#include <konnekt/lib.h>
#include <konnekt/plug_export.h>
#include <konnekt/ui.h>
#include <konnekt/plug_func.h>

//Stamina.lib
#ifdef _DEBUG
  #pragma comment(lib, "stamina_d.lib")
#else
  #pragma comment(lib, "stamina.lib")
#endif
#include <stamina/object.h>
#include <stamina/objectimpl.h>
#include <stamina/helpers.h>

//boost
#include <boost/signal.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/regex.hpp>