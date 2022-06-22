#include <functional>
#include <thread>
#include <array>

#include "gui.h"
#include "../cfg/config.h"
#include "../hooks/hooks.h"
#include "helpers/helpers.h"
#include "../sdk/interfaces/interfaces.h"

static int comboint = 0;

void gui::init( IDirect3DDevice9* device )
{
	ImGui::CreateContext( );

	ImGui_ImplWin32_Init( gui::input::window );
	ImGui_ImplDX9_Init( device );

	ImGuiStyle& style = ImGui::GetStyle( );

	/* colors */
	{
		style.Colors[ ImGuiCol_Border ] = ImVec4( 30 / 255.f, 30 / 255.f, 30 / 255.f, 0.5f );

		style.Colors[ ImGuiCol_ScrollbarBg ] = ImVec4( 1.f, 1.f, 1.f, 0.0f );
		style.Colors[ ImGuiCol_ScrollbarGrab ] = ImVec4( 1.f, 1.f, 1.f, 0.0f );
		style.Colors[ ImGuiCol_ScrollbarGrabActive ] = ImVec4( 1.f, 1.f, 1.f, 0.0f );
		style.Colors[ ImGuiCol_ScrollbarGrabHovered ] = ImVec4( 1.f, 1.f, 1.f, 0.0f );

		style.Colors[ ImGuiCol_WindowBg ] = ImVec4( 10 / 255.f, 10 / 255.f, 10 / 255.f, 1.00f );
		style.Colors[ ImGuiCol_PopupBg ] = ImVec4( 20 / 255.f, 20 / 255.f, 20 / 255.f, 1.00f );
		style.Colors[ ImGuiCol_ChildBg ] = ImVec4( 15 / 255.f, 15 / 255.f, 15 / 255.f, 1.0f );
	}

	/* style */
	{
		style.WindowRounding = 3.f;
		style.ChildRounding = 2.f;
		style.FrameRounding = 3.f;
		style.GrabRounding = 2.f;
		style.PopupRounding = 2.f;
		style.ScrollbarRounding = 4.f;
		style.TabRounding = 3.f;

		style.WindowBorderSize = 2.f;
		style.FrameBorderSize = 0.f;
		style.ChildBorderSize = 1.;

		style.ScrollbarSize = 1.f;

		style.FramePadding = ImVec2( 4, -1 );
		style.WindowPadding = ImVec2( 8, 8 );
		style.ItemSpacing = ImVec2( 8, 4 );
		style.ItemInnerSpacing = ImVec2( 4, 4 );
		style.WindowMinSize = ImVec2( 32, 32 );
		style.WindowTitleAlign = ImVec2( 0.5f, 0.5f );
		style.ButtonTextAlign = ImVec2( 0.5f, 0.4f );

		style.Alpha = 1.f;
	}

	ImGuiIO& io = ImGui::GetIO( );

	ImFontConfig im_verdana_font_config = { };
	im_verdana_font_config.RasterizerFlags = ImGuiFreeType::Monochrome | ImGuiFreeType::MonoHinting;
	fonts::verdana = io.Fonts->AddFontFromFileTTF( ( "C:\\Windows\\Fonts\\Verdana.ttf" ), 11.f, &im_verdana_font_config, io.Fonts->GetGlyphRangesCyrillic( ) );
	fonts::verdanab = io.Fonts->AddFontFromFileTTF( ( "C:\\Windows\\Fonts\\Verdanab.ttf" ), 11.f, &im_verdana_font_config, io.Fonts->GetGlyphRangesCyrillic( ) );

	gui::g_data.m_initialised = ImGuiFreeType::BuildFontAtlas( io.Fonts, 0x0 );
}

void gui::revert( )
{
	if ( gui::g_data.m_opened )
		gui::g_data.m_opened = false;

	ImGui_ImplDX9_Shutdown( );
	ImGui_ImplWin32_Shutdown( );
	ImGui::DestroyContext( );
}

void gui::render( )
{
	if ( c::get<bool>( vars.menu_fade ) )
	{
		float delta_time = ( 1.0f / 0.2f ) * ImGui::GetIO( ).DeltaTime;
		static float menu_alpha = 1.f;
		if ( gui::g_data.m_opened )
			menu_alpha = ImMin( menu_alpha + 1.f * delta_time, 1.f );
		else
			menu_alpha = ImMax( 0.f, menu_alpha - 1.f * delta_time );

		ImGui::GetStyle( ).Alpha = c::get<bool>( vars.menu_fade ) ? menu_alpha : 1.f;
	}
	else if ( !c::get<bool>( vars.menu_fade ) && !gui::g_data.m_opened )
		return;

	ImGui::SetNextWindowSize( ImVec2( 500, 400 ), ImGuiCond_Always );
	ImGui::Begin( _( "hw-main-window" ), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar );
	{
		ImGui::GetWindowDrawList( )->AddRectFilledMultiColor( ImVec2( ImGui::GetWindowPos( ).x, ImGui::GetWindowPos( ).y + 25 ), ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetWindowSize( ).x / 2, ImGui::GetWindowPos( ).y + 25 + 1 ), ImColor( 1.f, 1.f, 1.f, 0.f ), c::get<color>( vars.color_menu_accent ).get_u32( ), c::get<color>( vars.color_menu_accent ).get_u32( ), c::get<color>( vars.color_menu_accent ).get_u32( 0.f ) );
		ImGui::GetWindowDrawList( )->AddRectFilledMultiColor( ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetWindowSize( ).x / 2, ImGui::GetWindowPos( ).y + 25 ), ImVec2( ( ImGui::GetWindowPos( ).x + ImGui::GetWindowSize( ).x / 2 ) + ImGui::GetWindowSize( ).x / 2, ImGui::GetWindowPos( ).y + 25 + 1 ), c::get<color>( vars.color_menu_accent ).get_u32( ), c::get<color>( vars.color_menu_accent ).get_u32( 0.f ), c::get<color>( vars.color_menu_accent ).get_u32( 0.f ), c::get<color>( vars.color_menu_accent ).get_u32( ) );

		ImGui::PushFont( fonts::verdanab );
		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 - fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, _( "hotwheels.vip" ) ).x / 2 );
		ImGui::Text( _( "hotwheels" ) );
		ImGui::SameLine( 0, 0 );
		ImGui::TextColored( c::get<color>( vars.color_menu_accent ).get_imvec4( ), _( ".vip" ) );
		ImGui::PopFont( );

		ImGui::PushFont( fonts::verdana );

		ImGui::Spacing( );
		ImGui::Spacing( );

		switch ( gui::g_data.m_tab )
		{
		case 0:
		{
			gui::tabs::aimbot( );
			break;
		}
		case 1:
		{
			gui::tabs::visuals( );
			break;
		}
		case 2:
		{
			gui::tabs::misc( );
			break;
		}
		case 3:
		{
			gui::tabs::movement( );
			break;
		}
		case 4:
		{
			gui::tabs::skins( );
			break;
		}
		case 5:
		{
			gui::tabs::settings( );
			break;
		}
		case 6:
		{
			gui::tabs::fonts( );
			break;
		}
		}

		ImGui::GetWindowDrawList( )->AddRectFilledMultiColor( ImVec2( ImGui::GetWindowPos( ).x, ImGui::GetWindowPos( ).y + ImGui::GetWindowSize( ).y - 25 ), ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetWindowSize( ).x / 2, ImGui::GetWindowPos( ).y + ImGui::GetWindowSize( ).y - 25 + 1 ), c::get<color>( vars.color_menu_accent ).get_u32( 0.f ), c::get<color>( vars.color_menu_accent ).get_u32( ), c::get<color>( vars.color_menu_accent ).get_u32( ), c::get<color>( vars.color_menu_accent ).get_u32( 0.f ) );
		ImGui::GetWindowDrawList( )->AddRectFilledMultiColor( ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetWindowSize( ).x / 2, ImGui::GetWindowPos( ).y + ImGui::GetWindowSize( ).y - 25 ), ImVec2( ( ImGui::GetWindowPos( ).x + ImGui::GetWindowSize( ).x / 2 ) + ImGui::GetWindowSize( ).x / 2, ImGui::GetWindowPos( ).y + ImGui::GetWindowSize( ).y - 25 + 1 ), c::get<color>( vars.color_menu_accent ).get_u32( ), c::get<color>( vars.color_menu_accent ).get_u32( 0.f ), c::get<color>( vars.color_menu_accent ).get_u32( 0.f ), c::get<color>( vars.color_menu_accent ).get_u32( ) );

		ImGui::SetCursorPos( ImVec2( ImGui::GetWindowSize( ).x / 2 - fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, _( "aimbotvisualsmiscmovementskinssettingsfonts" ) ).x / 2 - 25, ImGui::GetWindowSize( ).y - 20 ) );
		gui::helpers::render_tab( _( "aimbot" ), 0 ); ImGui::SameLine( );
		gui::helpers::render_tab( _( "visuals" ), 1 ); ImGui::SameLine( );
		gui::helpers::render_tab( _( "misc" ), 2 ); ImGui::SameLine( );
		gui::helpers::render_tab( _( "movement" ), 3 ); ImGui::SameLine( );
		gui::helpers::render_tab( _( "skins" ), 4 ); ImGui::SameLine( );
		gui::helpers::render_tab( _( "settings" ), 5 ); ImGui::SameLine( );
		gui::helpers::render_tab( _( "fonts" ), 6 );

		ImGui::PopFont( );
	}
	ImGui::End( );
}

bool gui::input::init( )
{
	D3DDEVICE_CREATION_PARAMETERS creation_params = { };
	while ( FAILED( i::direct_device->GetCreationParameters( &creation_params ) ) )
		std::this_thread::sleep_for( 200ms );

	window = creation_params.hFocusWindow;

	if ( window == nullptr )
		return false;

	old_wnd_proc = reinterpret_cast< WNDPROC >( SetWindowLongPtrW( window, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( h::wnd_proc ) ) );

	if ( old_wnd_proc == nullptr )
		return false;

	return true;
}

void gui::input::revert( )
{
	if ( old_wnd_proc != nullptr )
	{
		SetWindowLongPtrW( window, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( old_wnd_proc ) );
		old_wnd_proc = nullptr;
	}

	i::input_system->enable_input( true );
}