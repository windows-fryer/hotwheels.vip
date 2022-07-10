//
// Created by liga on 7/1/2022.
//

#ifndef HOTWHEELS_CSGO_EXTERNAL_ENTRY_HPP
#define HOTWHEELS_CSGO_EXTERNAL_ENTRY_HPP

#include <iostream>

#define hinstance HINSTANCE

#define dll_main                         DllMain
#define create_thread( function )        CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )function, 0, 0, 0 )
#define fnv( string )                    fnv::hash( string )
#define get_proc_address( module, name ) GetProcAddress( module, name )
#define get_module_handle( name )        GetModuleHandle( name )
#define set_window_long                  SetWindowLongA
#define find_window                      FindWindowA
#define call_window_proc                 CallWindowProcA
#define free_library_and_exit_thread     FreeLibraryAndExitThread
#define close_handle                     CloseHandle
#define free_console                     FreeConsole
#define disable_thread_library_calls     DisableThreadLibraryCalls
#define win_api                          WINAPI

inline FILE* g_stdin{ };
inline FILE* g_stdout{ };

#endif // HOTWHEELS_CSGO_EXTERNAL_ENTRY_HPP
