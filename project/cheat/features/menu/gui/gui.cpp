#include <array>
#include <functional>
#include <thread>

#include "../cfg/config.h"
#include "gui.h"
#include "helpers/helpers.h"

static int comboint = 0;

void gui::init( ID3D11Device* device, ID3D11DeviceContext* context )
{
	ImGui::CreateContext( );

	ImGui_ImplWin32_Init( find_window( nullptr, "Battlefield 4" ) );
	ImGui_ImplDX11_Init( device, context );

	ImGuiStyle& style = ImGui::GetStyle( );

	/* colors */
	{
		style.Colors[ ImGuiCol_Border ] = ImVec4( 30 / 255.f, 30 / 255.f, 30 / 255.f, 0.5f );

		style.Colors[ ImGuiCol_ScrollbarBg ]          = ImVec4( 1.f, 1.f, 1.f, 0.0f );
		style.Colors[ ImGuiCol_ScrollbarGrab ]        = ImVec4( 1.f, 1.f, 1.f, 0.0f );
		style.Colors[ ImGuiCol_ScrollbarGrabActive ]  = ImVec4( 1.f, 1.f, 1.f, 0.0f );
		style.Colors[ ImGuiCol_ScrollbarGrabHovered ] = ImVec4( 1.f, 1.f, 1.f, 0.0f );

		style.Colors[ ImGuiCol_WindowBg ] = ImVec4( 10 / 255.f, 10 / 255.f, 10 / 255.f, 1.00f );
		style.Colors[ ImGuiCol_PopupBg ]  = ImVec4( 20 / 255.f, 20 / 255.f, 20 / 255.f, 1.00f );
		style.Colors[ ImGuiCol_ChildBg ]  = ImVec4( 15 / 255.f, 15 / 255.f, 15 / 255.f, 1.0f );
	}

	/* style */
	{
		style.WindowRounding    = 3.f;
		style.ChildRounding     = 2.f;
		style.FrameRounding     = 3.f;
		style.GrabRounding      = 2.f;
		style.PopupRounding     = 2.f;
		style.ScrollbarRounding = 4.f;
		style.TabRounding       = 3.f;

		style.WindowBorderSize = 2.f;
		style.FrameBorderSize  = 0.f;
		style.ChildBorderSize  = 1.;

		style.ScrollbarSize = 1.f;

		style.FramePadding     = ImVec2( 4, -1 );
		style.WindowPadding    = ImVec2( 8, 8 );
		style.ItemSpacing      = ImVec2( 8, 4 );
		style.ItemInnerSpacing = ImVec2( 4, 4 );
		style.WindowMinSize    = ImVec2( 32, 32 );
		style.WindowTitleAlign = ImVec2( 0.5f, 0.5f );
		style.ButtonTextAlign  = ImVec2( 0.5f, 0.4f );

		style.Alpha = 1.f;
	}

	ImGuiIO& io = ImGui::GetIO( );

	ImFontConfig im_verdana_font_config    = { };
	im_verdana_font_config.RasterizerFlags = ImGuiFreeType::Monochrome | ImGuiFreeType::MonoHinting;
	fonts::verdana =
		io.Fonts->AddFontFromFileTTF( ( "C:\\Windows\\Fonts\\Verdana.ttf" ), 11.f, &im_verdana_font_config, io.Fonts->GetGlyphRangesCyrillic( ) );
	fonts::verdanab =
		io.Fonts->AddFontFromFileTTF( ( "C:\\Windows\\Fonts\\Verdanab.ttf" ), 11.f, &im_verdana_font_config, io.Fonts->GetGlyphRangesCyrillic( ) );

	gui::g_data.m_initialised = ImGuiFreeType::BuildFontAtlas( io.Fonts, 0x0 );
}

void gui::revert( )
{
	if ( gui::g_data.m_opened )
		gui::g_data.m_opened = false;

	ImGui_ImplDX11_Shutdown( );
	ImGui_ImplWin32_Shutdown( );
	ImGui::DestroyContext( );
}

void gui::render( )
{
	if ( c::get< bool >( vars.menu_fade ) ) {
		float delta_time        = ( 1.0f / 0.2f ) * ImGui::GetIO( ).DeltaTime;
		static float menu_alpha = 1.f;
		if ( gui::g_data.m_opened )
			menu_alpha = ImMin( menu_alpha + 1.f * delta_time, 1.f );
		else
			menu_alpha = ImMax( 0.f, menu_alpha - 1.f * delta_time );

		ImGui::GetStyle( ).Alpha = c::get< bool >( vars.menu_fade ) ? menu_alpha : 1.f;
	} else if ( !c::get< bool >( vars.menu_fade ) && !gui::g_data.m_opened )
		return;

	ImGui::SetNextWindowSize( ImVec2( 500, 400 ), ImGuiCond_Always );
	ImGui::Begin( "hw-main-window", nullptr,
	              ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar );
	{
		ImGui::GetWindowDrawList( )->AddRectFilledMultiColor(
			ImVec2( ImGui::GetWindowPos( ).x, ImGui::GetWindowPos( ).y + 25 ),
			ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetWindowSize( ).x / 2, ImGui::GetWindowPos( ).y + 25 + 1 ), ImColor( 1.f, 1.f, 1.f, 0.f ),
			c::get< color >( vars.color_menu_accent ).get_u32( ), c::get< color >( vars.color_menu_accent ).get_u32( ),
			c::get< color >( vars.color_menu_accent ).get_u32( 0.f ) );
		ImGui::GetWindowDrawList( )->AddRectFilledMultiColor(
			ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetWindowSize( ).x / 2, ImGui::GetWindowPos( ).y + 25 ),
			ImVec2( ( ImGui::GetWindowPos( ).x + ImGui::GetWindowSize( ).x / 2 ) + ImGui::GetWindowSize( ).x / 2, ImGui::GetWindowPos( ).y + 25 + 1 ),
			c::get< color >( vars.color_menu_accent ).get_u32( ), c::get< color >( vars.color_menu_accent ).get_u32( 0.f ),
			c::get< color >( vars.color_menu_accent ).get_u32( 0.f ), c::get< color >( vars.color_menu_accent ).get_u32( ) );

		ImGui::PushFont( fonts::verdanab );
		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 -
		                      fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, "hotwheels.vip" ).x / 2 );
		ImGui::Text( "hotwheels" );
		ImGui::SameLine( 0, 0 );
		ImGui::TextColored( c::get< color >( vars.color_menu_accent ).get_imvec4( ), ".vip" );
		ImGui::PopFont( );

		ImGui::PushFont( fonts::verdana );

		ImGui::Spacing( );
		ImGui::Spacing( );

		switch ( gui::g_data.m_tab ) {
		case 0: {
			gui::tabs::aimbot( );
			break;
		}
		case 1: {
			gui::tabs::visuals( );
			break;
		}
		case 2: {
			gui::tabs::misc( );
			break;
		}
		case 3: {
			gui::tabs::movement( );
			break;
		}
		case 4: {
			gui::tabs::skins( );
			break;
		}
		case 5: {
			gui::tabs::settings( );
			break;
		}
		case 6: {
			gui::tabs::fonts( );
			break;
		}
		}

		ImGui::GetWindowDrawList( )->AddRectFilledMultiColor(
			ImVec2( ImGui::GetWindowPos( ).x, ImGui::GetWindowPos( ).y + ImGui::GetWindowSize( ).y - 25 ),
			ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetWindowSize( ).x / 2, ImGui::GetWindowPos( ).y + ImGui::GetWindowSize( ).y - 25 + 1 ),
			c::get< color >( vars.color_menu_accent ).get_u32( 0.f ), c::get< color >( vars.color_menu_accent ).get_u32( ),
			c::get< color >( vars.color_menu_accent ).get_u32( ), c::get< color >( vars.color_menu_accent ).get_u32( 0.f ) );
		ImGui::GetWindowDrawList( )->AddRectFilledMultiColor(
			ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetWindowSize( ).x / 2, ImGui::GetWindowPos( ).y + ImGui::GetWindowSize( ).y - 25 ),
			ImVec2( ( ImGui::GetWindowPos( ).x + ImGui::GetWindowSize( ).x / 2 ) + ImGui::GetWindowSize( ).x / 2,
		            ImGui::GetWindowPos( ).y + ImGui::GetWindowSize( ).y - 25 + 1 ),
			c::get< color >( vars.color_menu_accent ).get_u32( ), c::get< color >( vars.color_menu_accent ).get_u32( 0.f ),
			c::get< color >( vars.color_menu_accent ).get_u32( 0.f ), c::get< color >( vars.color_menu_accent ).get_u32( ) );

		ImGui::SetCursorPos( ImVec2(
			ImGui::GetWindowSize( ).x / 2 -
				fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, "aimbotvisualsmiscmovementskinssettingsfonts" ).x / 2 - 25,
			ImGui::GetWindowSize( ).y - 20 ) );
		gui::helpers::render_tab( "aimbot", 0 );
		ImGui::SameLine( );
		gui::helpers::render_tab( "visuals", 1 );
		ImGui::SameLine( );
		gui::helpers::render_tab( "misc", 2 );
		ImGui::SameLine( );
		gui::helpers::render_tab( "movement", 3 );
		ImGui::SameLine( );
		gui::helpers::render_tab( "skins", 4 );
		ImGui::SameLine( );
		gui::helpers::render_tab( "settings", 5 );
		ImGui::SameLine( );
		gui::helpers::render_tab( "fonts", 6 );

		ImGui::PopFont( );
	}
	ImGui::End( );
}