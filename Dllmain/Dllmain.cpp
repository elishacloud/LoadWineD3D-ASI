/**
* Copyright (C) 2017 Elisha Riedlinger
*
* This software is  provided 'as-is', without any express  or implied  warranty. In no event will the
* authors be held liable for any damages arising from the use of this software.
* Permission  is granted  to anyone  to use  this software  for  any  purpose,  including  commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*   1. The origin of this software must not be misrepresented; you must not claim that you  wrote the
*      original  software. If you use this  software  in a product, an  acknowledgment in the product
*      documentation would be appreciated but is not required.
*   2. Altered source versions must  be plainly  marked as such, and  must not be  misrepresented  as
*      being the original software.
*   3. This notice may not be removed or altered from any source distribution.
*/

#include <vector>
#include "Dllmain.h"
#include "Logging.h"
#include "..\Hooking\Hook.h"

VISIT_PROCS(CREATE_PROC_STUB)

// Dll main function
bool APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);

	static std::vector<HMODULE> LoadedDLLs;

	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		// Declare vars
		DWORD Counter = 0;
		FARPROC wrapper_func[61] = { nullptr };
		DLLEXPORTS dllexports[ArraySize];

		// Setup Proc arrays
		VISIT_PROCS(SET_FUNC_STUB);
		VISIT_EXPORTS(SET_DLL_EXPORTS);

		// Enable logging
		char path[MAX_PATH];
		GetModuleFileName(hModule, path, MAX_PATH);
		strcpy_s(strrchr(path, '.'), MAX_PATH - strlen(path), ".log");
		Logging::Log().open(path, std::ios::trunc);

		// Loop through each WineD3D file
		for (int x = 0; x < ArraySize; x++)
		{
			// Load dll from script folder
			GetModuleFileName(hModule, path, MAX_PATH);
			strcpy_s(strrchr(path, '\\'), MAX_PATH - strlen(path), "\\");
			strcat_s(path, MAX_PATH, dllname[x]);
			HMODULE Script_dll = LoadLibrary(path);
			Logging::Log() << "Checking " << path << "\n";

			// If WineD3D dll found
			if (Script_dll)
			{
				Logging::Log() << "Found " << dllname[x] << "!\n";

				// Record loaded dll
				LoadedDLLs.push_back(Script_dll);

				// Get System32 dll handle
				GetSystemDirectory(path, MAX_PATH);
				strcat_s(path, MAX_PATH, "\\");
				strcat_s(path, MAX_PATH, dllname[x]);
				HMODULE System32_dll = Hook::GetModuleHandle(path);

				// If no handle then load dll from System32 folder
				if (!System32_dll)
				{
					HMODULE t_System32_dll = LoadLibrary(path);
					System32_dll = Hook::GetModuleHandle(path);

					// Record loaded dll
					if (t_System32_dll)
					{
						LoadedDLLs.push_back(t_System32_dll);
					}
					Logging::Log() << path << " loadaddr=" << t_System32_dll << " moduleaddr=" << System32_dll << "\n";
				}
				else
				{
					Logging::Log() << path << " addr=" << System32_dll << "\n";
				}

				// Check dlls
				if (System32_dll)
				{
					// Loop through each export item
					for (int y = 0; y < dllexports[x].ArraySize; y++)
					{
						Logging::Log() << "Checking " << dllexports[x].Export[y] << " ...\n";

						// Get export address
						FARPROC Script_proc = GetProcAddress(Script_dll, dllexports[x].Export[y]);
						FARPROC System32_proc = Hook::GetProcAddress(System32_dll, dllexports[x].Export[y]);

						// Check export addresses
						if (Script_proc && System32_proc)
						{
							// Wrapper -> Script
							switch (Counter)
							{
								VISIT_PROCS(SET_PROC_STUB);
							default:
								Logging::Log() << "Too many APIs too hook...\n";
								return true;
							}

							// System -> Wrapper
							Hook::HOOKING NewHook;
							NewHook.apiname = dllexports[x].Export[y];
							NewHook.hookproc = wrapper_func[Counter];
							NewHook.apiproc = System32_proc;
							if ((DWORD)Hook::HotPatch(System32_proc, dllexports[x].Export[y], wrapper_func[Counter]) > 1)
							{
								// Update counter
								Counter++;

								// Logging
								Logging::Log() << "Hooked " << dllexports[x].Export[y] << " count " << Counter << " addr=" << System32_proc << "\n";
							}
						}
					}
				}
			}
		}
	}
	break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
	{
		// Unhook apis
		Logging::Log() << "Unhooking procs...\n";
		Hook::UnHotPatchAll();

		// Unload dlls
		Logging::Log() << "Unloading dlls...\n";
		while (LoadedDLLs.size() != 0)
		{
			// Unload dll
			FreeLibrary(LoadedDLLs.back());
			LoadedDLLs.pop_back();
		}
		LoadedDLLs.clear();

		// Quiting
		Logging::Log() << "Quiting LoadWineD3D\n";
	}
	break;
	}
	return true;
}
