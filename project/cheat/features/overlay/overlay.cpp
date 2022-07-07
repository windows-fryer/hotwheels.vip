//
// Created by liga on 7/1/2022.
//

#include "overlay.hpp"
#include "../visuals/visuals.hpp"

#include "../../cheat.hpp"
#include "../../helpers/configs/config.hpp"
#include "../../helpers/driver/driver.hpp"

#include <Windows.h>
#include <algorithm>
#include <dwmapi.h>
#include <iostream>
#include <shlobj.h>

void create_render_target( )
{
	ID3D11Texture2D* back_buffer;
	overlay::swap_chain->GetBuffer( 0, IID_PPV_ARGS( &back_buffer ) );
	overlay::device->CreateRenderTargetView( back_buffer, NULL, &overlay::render_target_view );
	back_buffer->Release( );
}

bool create_device( HWND window_handle )
{
	// Setup swap chain
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof( sd ) );
	sd.BufferCount                        = 2;
	sd.BufferDesc.Width                   = 0;
	sd.BufferDesc.Height                  = 0;
	sd.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator   = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags                              = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow                       = window_handle;
	sd.SampleDesc.Count                   = 1;
	sd.SampleDesc.Quality                 = 0;
	sd.Windowed                           = TRUE;
	sd.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;

	UINT createDeviceFlags = 0;
	// createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[ 2 ] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0,
	};
	if ( D3D11CreateDeviceAndSwapChain( NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd,
	                                    &overlay::swap_chain, &overlay::device, &featureLevel, &overlay::device_context ) != S_OK )
		return false;

	create_render_target( );
	return true;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

LRESULT WINAPI wnd_proc( HWND window, UINT message, WPARAM parameter, LPARAM long_parameter )
{
	if ( ImGui_ImplWin32_WndProcHandler( window, message, parameter, long_parameter ) )
		return true;

	switch ( message ) {
	case WM_SYSCOMMAND:
		if ( ( parameter & 0xFFF0 ) == SC_KEYMENU ) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage( 0 );
		return 0;
	}

	return DefWindowProc( window, message, parameter, long_parameter );
}

void overlay::init( )
{
	WNDCLASSEX wnd_class;

	wnd_class.cbSize        = sizeof( WNDCLASSEX );
	wnd_class.cbClsExtra    = NULL;
	wnd_class.cbWndExtra    = NULL;
	wnd_class.hCursor       = LoadCursor( 0, IDC_ARROW );
	wnd_class.hIcon         = LoadIcon( 0, IDI_APPLICATION );
	wnd_class.hIconSm       = LoadIcon( 0, IDI_APPLICATION );
	wnd_class.hbrBackground = ( HBRUSH )CreateSolidBrush( RGB( 0, 0, 0 ) );
	wnd_class.hInstance     = GetModuleHandle( NULL );
	wnd_class.lpfnWndProc   = wnd_proc;
	wnd_class.lpszClassName = "Hotwheels001";
	wnd_class.lpszMenuName  = "Hotwheels Overlay";
	wnd_class.style         = CS_VREDRAW | CS_HREDRAW;

	RegisterClassEx( &wnd_class );

	HWND window_handle = CreateWindowEx( WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW, wnd_class.lpszClassName, "", WS_POPUP, 0, 0, 1920,
	                                     1080, nullptr, nullptr, nullptr, nullptr );

	SetLayeredWindowAttributes( window_handle, 0, 255, LWA_ALPHA );
	SetLayeredWindowAttributes( window_handle, RGB( 0, 0, 0 ), 0, ULW_COLORKEY );

	MARGINS margin = { 0, 1920, 0, 1080 };

	DwmExtendFrameIntoClientArea( window_handle, &margin );

	bool created = create_device( window_handle );

	ShowWindow( window_handle, SW_SHOWNORMAL );

	IMGUI_CHECKVERSION( );
	ImGui::CreateContext( );

	ImGuiIO& io    = ImGui::GetIO( );
	ImVec4* colors = ImGui::GetStyle( ).Colors;

	io.IniFilename = nullptr;

	colors[ ImGuiCol_Text ]                  = ImVec4( 1.00f, 1.00f, 1.00f, 1.00f );
	colors[ ImGuiCol_TextDisabled ]          = ImVec4( 0.50f, 0.50f, 0.50f, 1.00f );
	colors[ ImGuiCol_WindowBg ]              = ImVec4( 0.06f, 0.06f, 0.06f, 0.94f );
	colors[ ImGuiCol_ChildBg ]               = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
	colors[ ImGuiCol_PopupBg ]               = ImVec4( 0.08f, 0.08f, 0.08f, 0.94f );
	colors[ ImGuiCol_Border ]                = ImVec4( 0.43f, 0.43f, 0.50f, 0.50f );
	colors[ ImGuiCol_BorderShadow ]          = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
	colors[ ImGuiCol_FrameBg ]               = ImVec4( 1.00f, 0.60f, 0.92f, 0.54f );
	colors[ ImGuiCol_FrameBgHovered ]        = ImVec4( 1.00f, 0.49f, 0.90f, 0.54f );
	colors[ ImGuiCol_FrameBgActive ]         = ImVec4( 1.00f, 0.43f, 0.88f, 0.54f );
	colors[ ImGuiCol_TitleBg ]               = ImVec4( 0.04f, 0.04f, 0.04f, 1.00f );
	colors[ ImGuiCol_TitleBgActive ]         = ImVec4( 1.00f, 0.62f, 0.92f, 0.54f );
	colors[ ImGuiCol_TitleBgCollapsed ]      = ImVec4( 0.00f, 0.00f, 0.00f, 0.51f );
	colors[ ImGuiCol_MenuBarBg ]             = ImVec4( 0.14f, 0.14f, 0.14f, 1.00f );
	colors[ ImGuiCol_ScrollbarBg ]           = ImVec4( 0.02f, 0.02f, 0.02f, 0.53f );
	colors[ ImGuiCol_ScrollbarGrab ]         = ImVec4( 0.31f, 0.31f, 0.31f, 1.00f );
	colors[ ImGuiCol_ScrollbarGrabHovered ]  = ImVec4( 0.41f, 0.41f, 0.41f, 1.00f );
	colors[ ImGuiCol_ScrollbarGrabActive ]   = ImVec4( 0.51f, 0.51f, 0.51f, 1.00f );
	colors[ ImGuiCol_CheckMark ]             = ImVec4( 1.00f, 0.87f, 0.97f, 0.54f );
	colors[ ImGuiCol_SliderGrab ]            = ImVec4( 1.00f, 0.60f, 0.92f, 0.54f );
	colors[ ImGuiCol_SliderGrabActive ]      = ImVec4( 1.00f, 0.60f, 0.92f, 0.54f );
	colors[ ImGuiCol_Button ]                = ImVec4( 1.00f, 0.60f, 0.92f, 0.54f );
	colors[ ImGuiCol_ButtonHovered ]         = ImVec4( 1.00f, 0.69f, 0.93f, 0.54f );
	colors[ ImGuiCol_ButtonActive ]          = ImVec4( 1.00f, 0.48f, 0.89f, 0.54f );
	colors[ ImGuiCol_Header ]                = ImVec4( 1.00f, 0.60f, 0.92f, 0.54f );
	colors[ ImGuiCol_HeaderHovered ]         = ImVec4( 1.00f, 0.68f, 0.93f, 0.54f );
	colors[ ImGuiCol_HeaderActive ]          = ImVec4( 1.00f, 0.51f, 0.90f, 0.54f );
	colors[ ImGuiCol_Separator ]             = ImVec4( 0.43f, 0.43f, 0.50f, 0.50f );
	colors[ ImGuiCol_SeparatorHovered ]      = ImVec4( 0.72f, 0.50f, 0.68f, 0.54f );
	colors[ ImGuiCol_SeparatorActive ]       = ImVec4( 0.80f, 0.45f, 0.72f, 0.54f );
	colors[ ImGuiCol_ResizeGrip ]            = ImVec4( 1.00f, 0.60f, 0.92f, 0.54f );
	colors[ ImGuiCol_ResizeGripHovered ]     = ImVec4( 1.00f, 0.66f, 0.93f, 0.54f );
	colors[ ImGuiCol_ResizeGripActive ]      = ImVec4( 0.99f, 0.55f, 0.90f, 0.54f );
	colors[ ImGuiCol_Tab ]                   = ImVec4( 0.90f, 0.42f, 0.80f, 0.54f );
	colors[ ImGuiCol_TabHovered ]            = ImVec4( 0.99f, 0.68f, 0.92f, 0.54f );
	colors[ ImGuiCol_TabActive ]             = ImVec4( 1.00f, 0.56f, 0.91f, 0.54f );
	colors[ ImGuiCol_TabUnfocused ]          = ImVec4( 0.07f, 0.10f, 0.15f, 0.97f );
	colors[ ImGuiCol_TabUnfocusedActive ]    = ImVec4( 0.41f, 0.13f, 0.36f, 0.54f );
	colors[ ImGuiCol_PlotLines ]             = ImVec4( 0.61f, 0.61f, 0.61f, 1.00f );
	colors[ ImGuiCol_PlotLinesHovered ]      = ImVec4( 1.00f, 0.43f, 0.35f, 1.00f );
	colors[ ImGuiCol_PlotHistogram ]         = ImVec4( 0.90f, 0.70f, 0.00f, 1.00f );
	colors[ ImGuiCol_PlotHistogramHovered ]  = ImVec4( 1.00f, 0.60f, 0.00f, 1.00f );
	colors[ ImGuiCol_TableHeaderBg ]         = ImVec4( 0.19f, 0.19f, 0.20f, 1.00f );
	colors[ ImGuiCol_TableBorderStrong ]     = ImVec4( 0.31f, 0.31f, 0.35f, 1.00f );
	colors[ ImGuiCol_TableBorderLight ]      = ImVec4( 0.23f, 0.23f, 0.25f, 1.00f );
	colors[ ImGuiCol_TableRowBg ]            = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
	colors[ ImGuiCol_TableRowBgAlt ]         = ImVec4( 1.00f, 1.00f, 1.00f, 0.06f );
	colors[ ImGuiCol_TextSelectedBg ]        = ImVec4( 1.00f, 0.71f, 0.94f, 0.54f );
	colors[ ImGuiCol_DragDropTarget ]        = ImVec4( 1.00f, 1.00f, 0.00f, 0.90f );
	colors[ ImGuiCol_NavHighlight ]          = ImVec4( 1.00f, 0.41f, 0.88f, 0.54f );
	colors[ ImGuiCol_NavWindowingHighlight ] = ImVec4( 1.00f, 1.00f, 1.00f, 0.70f );
	colors[ ImGuiCol_NavWindowingDimBg ]     = ImVec4( 0.80f, 0.80f, 0.80f, 0.20f );
	colors[ ImGuiCol_ModalWindowDimBg ]      = ImVec4( 0.80f, 0.80f, 0.80f, 0.35f );

	ImGui::GetStyle( ).WindowBorderSize = 1.f;

	ImGui_ImplWin32_Init( window_handle );
	ImGui_ImplDX11_Init( device, device_context );

	bool open = true;

	while ( !cheat::requested_shutdown ) {
		static bool did_close{ };

		MSG message;

		while ( PeekMessage( &message, window_handle, 0, 0, PM_REMOVE ) ) {
			TranslateMessage( &message );
			DispatchMessage( &message );
		}

		if ( GetAsyncKeyState( VK_INSERT ) & 1 ) {
			open = !open;
		}

		ImGui_ImplDX11_NewFrame( );
		ImGui_ImplWin32_NewFrame( );
		ImGui::NewFrame( );

		static float current_animation = 0;

		auto increment_per_frame = 1.f / ( 0.6f / ( 1.f / ImGui::GetIO( ).Framerate ) );

		current_animation = std::clamp( current_animation + ( open ? increment_per_frame : -increment_per_frame ), 0.f, 1.f );

		auto ease_in_out = []( float x ) -> float {
			if ( *g_config.find< bool >( "menu_open_smooth" ) ) {
				return x == 0.f   ? 0.f
				       : x == 1.f ? 1.f
				       : x < 0.5f ? powf( 2.f, 20.f * x - 10.f ) / 2.f
				                  : ( 2.f - powf( 2.f, -20.f * x + 10.f ) ) / 2.f;
			} else {
				float c1 = 1.70158f;
				float c2 = c1 * 1.525f;

				return x < 0.5f ? ( powf( 2.f * x, 2.f ) * ( ( c2 + 1.f ) * 2.f * x - c2 ) ) / 2.f
				                : ( powf( 2.f * x - 2.f, 2.f ) * ( ( c2 + 1.f ) * ( x * 2.f - 2.f ) + c2 ) + 2.f ) / 2.f;
			}
		};

		auto ease_animation = ease_in_out( current_animation );

		//		ImGui::GetStyle( ).AntiAliasedLines = false;

		visuals::routine( );

		ImGui::PushStyleVar( ImGuiStyleVar_Alpha, ease_animation );

		if ( open || current_animation > increment_per_frame * 2 ) {
			did_close = false;

			float current_position = 0.f;

			ImGui::SetNextWindowSize( ImVec2( 175, 0 ) );
			ImGui::SetNextWindowPos( ImVec2( 10.f + ( 5.f + 175.f ) * current_position++ * ease_animation, 10 ) );
			if ( ImGui::Begin( "Aimbot", nullptr, ImGuiWindowFlags_AlwaysAutoResize ) ) {
				ImGui::Checkbox( "RCS", g_config.find< bool >( "aimbot_rcs" ) );

				if ( *g_config.find< bool >( "aimbot_rcs" ) ) {
					ImGui::PushItemWidth( -1 );
					ImGui::SliderFloat( "##RCS X", g_config.find< float >( "aimbot_rcs_x" ), 0, 150.f, "X: %0.1f%" );
					ImGui::SliderFloat( "##RCS Y", g_config.find< float >( "aimbot_rcs_y" ), 0, 150.f, "Y: %0.1f%" );
					ImGui::SliderFloat( "##RCS SMOOTH", g_config.find< float >( "aimbot_rcs_smooth" ), 0, 2.f, "Smooth: %0.1f%" );

					ImGui::PopItemWidth( );

					ImGui::Checkbox( "RCS Error", g_config.find< bool >( "aimbot_rcs_error" ) );
				}

				ImGui::End( );
			}

			ImGui::SetNextWindowSize( ImVec2( 175, 0 ) );
			ImGui::SetNextWindowPos( ImVec2( 10.f + ( 5.f + 175.f ) * current_position++ * ease_animation, 10 ) );
			if ( ImGui::Begin( "Visuals", nullptr, ImGuiWindowFlags_AlwaysAutoResize ) ) {
				ImGui::Checkbox( "Boxes", g_config.find< bool >( "visuals_boxes" ) );
				ImGui::SameLine( );

				ImGui::ColorEdit4( "##Boxes Color",
				                   reinterpret_cast< float* >( g_config.find< ImVec4 >( "visuals_boxes_color" ) ),
				                   ImGuiColorEditFlags_NoInputs );

				ImGui::Checkbox( "Recoil Crosshair", g_config.find< bool >( "visuals_recoil_crosshair" ) );
				ImGui::SameLine( );

				ImGui::ColorEdit4( "##Recoil Crosshair Color",
				                   reinterpret_cast< float* >( g_config.find< ImVec4 >( "visuals_recoil_crosshair_color" ) ),
				                   ImGuiColorEditFlags_NoInputs );

				ImGui::End( );
			}

			ImGui::SetNextWindowSize( ImVec2( 175, 0 ) );
			ImGui::SetNextWindowPos( ImVec2( 10.f + ( 5.f + 175.f ) * current_position++ * ease_animation, 10 ) );
			if ( ImGui::Begin( "Movement", nullptr, ImGuiWindowFlags_AlwaysAutoResize ) ) {
				ImGui::Checkbox( "Bunny Hop", g_config.find< bool >( "movement_bunny_hop" ) );

				ImGui::End( );
			}

			ImGui::SetNextWindowSize( ImVec2( 175, 0 ) );
			ImGui::SetNextWindowPos( ImVec2( 10.f + ( 5.f + 175.f ) * current_position++ * ease_animation, 10 ) );
			if ( ImGui::Begin( "Misc", nullptr, ImGuiWindowFlags_AlwaysAutoResize ) ) {
				ImGui::Checkbox( "Smooth Open", g_config.find< bool >( "menu_open_smooth" ) );

				ImGui::End( );
			}

			ImGui::SetNextWindowSize( ImVec2( 175, 0 ) );
			ImGui::SetNextWindowPos( ImVec2( 10.f + ( 5.f + 175.f ) * current_position++ * ease_animation, 10 ) );
			if ( ImGui::Begin( "Configs", nullptr, ImGuiWindowFlags_AlwaysAutoResize ) ) {
				static CHAR my_documents[ MAX_PATH ]{ };
				static HRESULT result = SHGetFolderPath( NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents );

				if ( result == S_OK ) {
					static char config_name[ 64 ]{ };

					ImGui::PushItemWidth( -1 );
					ImGui::InputText( "##config_name", config_name, 64 );
					ImGui::PopItemWidth( );

					if ( ImGui::Button( "Save", ImVec2( ImGui::GetWindowSize( ).x * 0.43f, 0 ) ) ) {
						g_config.save( std::string( my_documents ) + "/hotwheels/" + std::string( config_name ) + std::string( ".vip" ) );
					}
					ImGui::SameLine( );
					if ( ImGui::Button( "Load", ImVec2( ImGui::GetWindowSize( ).x * 0.43f, 0 ) ) ) {
						g_config.load( std::string( my_documents ) + "/hotwheels/" + std::string( config_name ) + std::string( ".vip" ) );
					}
				}

				ImGui::End( );
			}
		} else {
			did_close = true;
		}

		ImGui::PopStyleVar( );

		SetWindowLong( window_handle, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | ( open ? 0 : WS_EX_LAYERED ) );

		ImGui::EndFrame( );

		ImGui::Render( );

		const float clear_color_with_alpha[ 4 ] = { 0, 0, 0, 0 };
		device_context->OMSetRenderTargets( 1, &render_target_view, NULL );
		device_context->ClearRenderTargetView( render_target_view, clear_color_with_alpha );
		ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData( ) );

		swap_chain->Present( 0, 0 );

		Sleep( 6.9f );
	}
}
