//
// Created by Liga on 6/21/2022.
//

#ifndef HOTWHEELS_BF4_SNAKEIFY_HPP
#define HOTWHEELS_BF4_SNAKEIFY_HPP

#define hinstance                        HINSTANCE
#define dll_main                         DllMain
#define create_thread( function )        CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )function, 0, 0, 0 )
#define fnv( string )                    fnv::hash( string )
#define get_proc_address( module, name ) GetProcAddress( module, name )
#define get_module_handle( name )        GetModuleHandle( name )
#define set_window_long                  SetWindowLongPtrW
#define find_window                      FindWindowA
#define call_window_proc                 CallWindowProcA
#define free_library_and_exit_thread     FreeLibraryAndExitThread
#define close_handle                     CloseHandle
#define free_console                     FreeConsole
#define disable_thread_library_calls     DisableThreadLibraryCalls
#define win_api                          WINAPI
#define exception_execute_handler        EXCEPTION_EXECUTE_HANDLER

#define ROUND_UP( value ) static_cast< int >( static_cast< float >( value ) + 0.5f )

#define COMBINE( lhs, rhs ) lhs##rhs
#define CONCAT( lhs, rhs )  COMBINE( lhs, rhs )
#define PAD( size )                                                                                                                                  \
private:                                                                                                                                             \
	std::uint8_t CONCAT( pad, __COUNTER__ )[ size ];                                                                                                 \
                                                                                                                                                     \
public:

#define VIRTUAL_PAD( )                                                                                                                               \
private:                                                                                                                                             \
	virtual void CONCAT( pad, __COUNTER__ )( ) = 0;                                                                                                  \
                                                                                                                                                     \
public:

#endif // HOTWHEELS_BF4_SNAKEIFY_HPP
