#pragma once
#include <functional>
#include <map>

#include "../../cfg/config.h"
#include "../gui.h"

namespace gui::helpers
{
	inline auto render_tab = []( const char* tab_title, int tab_number ) {
		auto id = ImGui::GetCurrentWindow( )->GetID( tab_title );

		static std::map< ImGuiID, float > clicked_animation;
		auto it_filled = clicked_animation.find( id );
		if ( it_filled == clicked_animation.end( ) ) {
			clicked_animation.insert( { id, 0.f } );
			it_filled = clicked_animation.find( id );
		}
		it_filled->second =
			ImClamp( it_filled->second + ( 2.35f * ImGui::GetIO( ).DeltaTime * ( gui::g_data.m_tab == tab_number ? 2.f : -2.f ) ), 0.5f, 1.f );
		it_filled->second *= c::get< color >( vars.color_menu_accent ).base< color_a >( );

		ImGui::TextColored( gui::g_data.m_tab == tab_number ? c::get< color >( vars.color_menu_accent ).get_imvec4( it_filled->second )
		                                                    : ImVec4( 1.f, 1.f, 1.f, 0.5f ),
		                    tab_title );
		if ( ImGui::IsItemClicked( ) )
			gui::g_data.m_tab = tab_number;
		ImGui::SameLine( );
	};

	inline auto render_color_picker = []( const char* label, color* col, bool alpha, int sameline, bool text ) {
		if ( text )
			ImGui::Text( label );

		ImVec4 output_color = col->get_imvec4( );

		auto alpha_slider_flag = alpha ? ImGuiColorEditFlags_AlphaBar : ImGuiColorEditFlags_NoAlpha;
		ImGui::SameLine( ImGui::GetWindowWidth( ) - sameline );

		if ( ImGui::ColorEdit4( std::string( "##" ).append( label ).c_str( ), &output_color.x,
		                        alpha_slider_flag | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip ) ) {
			*col = color( output_color.x, output_color.y, output_color.z, output_color.w );
			return true;
		}

		return false;
	};

	inline auto render_keybind = []( const char* label, int* key, int* keystyle, int sameline, bool text ) {
		if ( text )
			ImGui::Text( label );

		ImGui::Keybind( std::string( "##" ).append( label ).c_str( ), key, keystyle, sameline );
	};

	inline auto render_combo = []( const char* label, int* current_item, const char* items_separated_by_zeros, int pos_x ) {
		auto id = ImGui::GetCurrentWindow( )->GetID( label );
		static std::map< ImGuiID, float > opened_animation;
		auto opened_frame = opened_animation.find( id );
		if ( opened_frame == opened_animation.end( ) ) {
			opened_animation.insert( { id, 0.f } );
			opened_frame = opened_animation.find( id );
		}
		opened_frame->second =
			ImClamp( opened_frame->second + ( 2.35f * ImGui::GetIO( ).DeltaTime * ( ImGui::IsPopupOpen( label ) ? 2.f : -2.f ) ), 0.0f, 1.f );
		opened_frame->second *= ImGui::GetStyle( ).Alpha;

		ImGui::PushStyleColor( ImGuiCol_PopupBg, ImVec4( 20 / 255.f, 20 / 255.f, 20 / 255.f, opened_frame->second ) );
		ImGui::PushStyleColor( ImGuiCol_WindowBg, ImVec4( 20 / 255.f, 20 / 255.f, 20 / 255.f, opened_frame->second ) );
		ImGui::PushStyleVar( ImGuiStyleVar_FramePadding, ImVec2( ImGui::GetStyle( ).FramePadding.x, 1 ) );
		ImGui::SetCursorPosX( pos_x );
		ImGui::Combo( label, current_item, items_separated_by_zeros );
		ImGui::PopStyleVar( );
		ImGui::PopStyleColor( );
		ImGui::PopStyleColor( );
	};

	inline auto render_multi_combo = []( const char* label, bool* values, const std::string_view* items, int items_count, int pos_x ) -> bool {
		ImGuiContext& g     = *GImGui;
		ImGuiWindow* window = g.CurrentWindow;

		if ( window->SkipItems )
			return false;

		const ImGuiStyle& style  = g.Style;
		const ImVec2 label_size  = ImGui::CalcTextSize( label, nullptr, true );
		const float active_width = ImGui::CalcItemWidth( ) - ( label_size.x > 0.0f ? style.ItemInnerSpacing.x + ImGui::GetFrameHeight( ) : 0.0f );

		std::vector< std::string_view > active_items = { };

		for ( int i = 0; i < items_count; i++ ) {
			if ( values[ i ] )
				active_items.push_back( items[ i ] );
		}

		std::string buffer = { };
		for ( std::size_t i = 0U; i < active_items.size( ); i++ ) {
			buffer.append( active_items[ i ] );

			if ( i < active_items.size( ) - 1U )
				buffer.append( ", " );
		}

		if ( buffer.empty( ) )
			buffer.assign( "none" );
		else {
			const char* szWrapPosition =
				g.Font->CalcWordWrapPositionA( ImGui::GetCurrentWindow( )->FontWindowScale, &buffer[ 0 ], buffer.data( ) + buffer.length( ),
			                                   active_width - style.FramePadding.x * 2.0f );
			const std::size_t nWrapLength = szWrapPosition - &buffer[ 0 ];

			if ( nWrapLength > 0U && nWrapLength < buffer.length( ) ) {
				buffer.resize( nWrapLength );
				buffer.append( "..." );
			}
		}

		auto id = ImGui::GetCurrentWindow( )->GetID( label );
		static std::map< ImGuiID, float > opened_animation;
		auto opened_frame = opened_animation.find( id );
		if ( opened_frame == opened_animation.end( ) ) {
			opened_animation.insert( { id, 0.f } );
			opened_frame = opened_animation.find( id );
		}
		opened_frame->second =
			ImClamp( opened_frame->second + ( 2.35f * ImGui::GetIO( ).DeltaTime * ( ImGui::IsPopupOpen( id ) ? 2.f : -2.f ) ), 0.0f, 1.f );
		opened_frame->second *= ImGui::GetStyle( ).Alpha;

		ImGui::PushStyleColor( ImGuiCol_PopupBg, ImVec4( 20 / 255.f, 20 / 255.f, 20 / 255.f, opened_frame->second ) );
		ImGui::PushStyleColor( ImGuiCol_WindowBg, ImVec4( 20 / 255.f, 20 / 255.f, 20 / 255.f, opened_frame->second ) );

		ImGui::SetCursorPosX( pos_x );
		ImGui::PushStyleVar( ImGuiStyleVar_FramePadding, ImVec2( ImGui::GetStyle( ).FramePadding.x, 1 ) );
		bool value_changed = false;
		if ( ImGui::BeginCombo( label, buffer.c_str( ) ) ) {
			for ( int i = 0; i < items_count; i++ ) {
				if ( ImGui::Selectable( items[ i ].data( ), values[ i ], ImGuiSelectableFlags_DontClosePopups ) ) {
					values[ i ]   = !values[ i ];
					value_changed = true;
				}
			}

			ImGui::EndCombo( );
		}

		ImGui::PopStyleVar( );
		ImGui::PopStyleColor( );
		ImGui::PopStyleColor( );

		return value_changed;
	};

	inline auto render_listbox = []( const char* label, int* current_item, std::function< const char*( int ) > lambda, int items_count,
	                                 int height_in_items ) {
		auto do_list_box = [ & ]( ) {
			return ImGui::ListBox(
				label, current_item,
				[]( void* data, int index, const char** out_text ) {
					*out_text = ( *static_cast< std::function< const char*( int ) >* >( data ) )( index );
					return true;
				},
				&lambda, items_count, height_in_items );
		};

		do_list_box( );
	};
} // namespace gui::helpers