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

#include "hooked_events.h"
#include "services.h"

HANDLE hModulesLoaded;
HANDLE hOptionsInitialize;

#define HOST "http://eblis.tla.ro/projects"

#define YAHOOGROUPS_VERSION_URL HOST "/miranda/YahooGroups/updater/YahooGroups.html"
#define YAHOOGROUPS_UPDATE_URL HOST "/miranda/YahooGroups/updater/YahooGroups.zip"
#define YAHOOGROUPS_VERSION_PREFIX "Yahoo Groups version "

int HookEvents()
{
	hModulesLoaded = HookEvent(ME_SYSTEM_MODULESLOADED, OnModulesLoaded);
	hOptionsInitialize = HookEvent(ME_OPT_INITIALISE, OnOptionsInitialise);
	
	return 0;
}

int UnhookEvents()
{
	UnhookEvent(hModulesLoaded);
	UnhookEvent(hOptionsInitialize);
	
	return 0;
}

int OnModulesLoaded(WPARAM wParam, LPARAM lParam)
{
	char buffer[1024];
	Update update = {0};
	update.cbSize = sizeof(Update);
	update.szComponentName = __PLUGIN_DISPLAY_NAME;
	update.pbVersion = (BYTE *) CreateVersionString(VERSION, buffer);
	update.cpbVersion = strlen((char *) update.pbVersion);
	update.szUpdateURL = UPDATER_AUTOREGISTER;
	update.szBetaVersionURL = YAHOOGROUPS_VERSION_URL;
	update.szBetaUpdateURL = YAHOOGROUPS_UPDATE_URL;
	update.pbBetaVersionPrefix = (BYTE *) YAHOOGROUPS_VERSION_PREFIX;
	update.cpbBetaVersionPrefix = strlen(YAHOOGROUPS_VERSION_PREFIX);
	CallService(MS_UPDATE_REGISTER, 0, (LPARAM) &update);
	
	int autoMove = DBGetContactSettingByte(NULL, ModuleName, "MoveAutomatically", 0);
	if (autoMove)
	{
		CallService(MS_YAHOOGROUPS_MOVE, 0, 0);
	}
	
	return 0;
}

int OnOptionsInitialise(WPARAM wParam, LPARAM lParam)
{
	OPTIONSDIALOGPAGE odp = {0};
	
	odp.cbSize = sizeof(odp);
	odp.position = 100000000;
	odp.hInstance = hInstance;
	odp.pszTemplate = MAKEINTRESOURCEA(IDD_OPTIONS);
	odp.ptszTitle = TranslateT("Yahoo Groups");
	odp.ptszGroup = TranslateT("Plugins");
	odp.groupPosition = 810000000;
	odp.flags= ODPF_BOLDGROUPS;
	odp.pfnDlgProc = DlgProcOptions;
	CallService(MS_OPT_ADDPAGE, wParam, (LPARAM)&odp);

	return 0;
}
