/*
YahooGroups plugin for Miranda IM

Copyright � 2007 Cristian Libotean

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "commonheaders.h"

char ModuleName[] = "YahooGroups";
HINSTANCE hInstance;

PLUGINLINK *pluginLink;

int bUnicodeMiranda = 0;
UINT currentCodePage = 0;

PLUGININFOEX pluginInfo = {
	sizeof(PLUGININFOEX),
	__PLUGIN_DISPLAY_NAME,
	VERSION,
	__DESC,
	__AUTHOR,
	__AUTHOREMAIL,
	__COPYRIGHT,
	__AUTHORWEB,
	0, //unicode aware
	0,
	{0x2f3fe8b9, 0x7327, 0x4008, {0xa6, 0x0d, 0x93, 0xf0, 0xf4, 0xf7, 0xf0, 0xf1}} //{2f3fe8b9-7327-4008-a60d-93f0f4f7f0f1}	
	}; //not used
	
OLD_MIRANDAPLUGININFO_SUPPORT;

extern "C" __declspec(dllexport) PLUGININFOEX *MirandaPluginInfoEx(DWORD mirandaVersion) 
{
	return &pluginInfo;
}

static const MUUID interfaces[] = {MIID_CMDLINE, MIID_LAST};

extern "C" __declspec(dllexport) const MUUID *MirandaPluginInterfaces()
{
	return interfaces;
}

extern "C" int __declspec(dllexport) Load(PLUGINLINK *link)
{
	LogInit();
	
	pluginLink = link;
	
	char build[1024] = {0};
	CallService(MS_SYSTEM_GETVERSIONTEXT, (WPARAM) sizeof(build), (LPARAM) build);
	_strlwr(build);
	bUnicodeMiranda = (strstr(build, "unicode") > 0) ? 1 : 0;
	
	currentCodePage = (UINT) CallService(MS_LANGPACK_GETCODEPAGE, 0, 0);

	
	InitializeMirandaMemFunctions();
	
	InitServices();
	
	HookEvents();
	
	return 0;
}

extern "C" int __declspec(dllexport) Unload()
{
	DestroyServices();

	UnhookEvents();
	
	return 0;
}

bool WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	hInstance = hinstDLL;
	if (fdwReason == DLL_PROCESS_ATTACH)
		{
			DisableThreadLibraryCalls(hinstDLL);
		}
		
	return TRUE;
}
