#include <shlobj.h>
#include <json.hpp>

#include "config.h"
#include "../sdk/interfaces/interfaces.h"

bool c::init( )
{
	if ( !std::filesystem::is_directory( fs_path ) )
	{
		std::filesystem::remove( fs_path );
		if ( !std::filesystem::create_directories( fs_path ) )
			return false;
	}

	refresh( );

	return true;
}

bool c::save( std::string_view file_name )
{
	std::filesystem::path fs_file_path( file_name );
	if ( fs_file_path.extension( ) != _( ".hw" ) )
		fs_file_path.replace_extension( _( ".hw" ) );

	const std::string file = std::filesystem::path( fs_path / fs_file_path ).string( );
	nlohmann::json config = { };

	try
	{
		for ( auto& variable : vec_variables )
		{
			nlohmann::json entry = { };

			entry[ _( "name-id" ) ] = variable.name_hash;
			entry[ _( "type-id" ) ] = variable.type_hash;

			switch ( variable.type_hash )
			{
			case fnv1a::hash_const( "int" ):
			{
				entry[ _( "value" ) ] = variable.get<int>( );
				break;
			}
			case fnv1a::hash_const( "float" ):
			{
				entry[ _( "value" ) ] = variable.get<float>( );
				break;
			}
			case fnv1a::hash_const( "bool" ):
			{
				entry[ _( "value" ) ] = variable.get<bool>( );
				break;
			}
			case fnv1a::hash_const( "std::string" ):
			{
				entry[ _( "value" ) ] = variable.get<std::string>( );
				break;
			}
			case fnv1a::hash_const( "color" ):
			{
				const auto& colVariable = variable.get<color>( );

				nlohmann::json sub = { };

				sub.push_back( colVariable.get<color_r>( ) );
				sub.push_back( colVariable.get<color_g>( ) );
				sub.push_back( colVariable.get<color_b>( ) );
				sub.push_back( colVariable.get<color_a>( ) );

				entry[ _( "value" ) ] = sub.dump( );
				break;
			}
			case fnv1a::hash_const( "std::vector<bool>" ):
			{
				const auto& vecBools = variable.get<std::vector<bool>>( );

				nlohmann::json sub = { };

				for ( const auto&& bValue : vecBools )
					sub.push_back( static_cast< bool >( bValue ) );

				entry[ _( "value" ) ] = sub.dump( );
				break;
			}
			case fnv1a::hash_const( "std::vector<int>" ):
			{
				const auto& vecInts = variable.get<std::vector<int>>( );

				nlohmann::json sub = { };

				for ( const auto& iValue : vecInts )
					sub.push_back( iValue );

				entry[ _( "value" ) ] = sub.dump( );
				break;
			}
			case fnv1a::hash_const( "std::vector<float>" ):
			{
				const auto& vecFloats = variable.get<std::vector<float>>( );

				nlohmann::json sub = { };

				for ( const auto& flValue : vecFloats )
					sub.push_back( flValue );

				entry[ _( "value" ) ] = sub.dump( );
				break;
			}
			default:
				break;
			}

			config.push_back( entry );
		}
	}
	catch ( const nlohmann::detail::exception& ex )
	{
		logging::push_console_color( FOREGROUND_RED );
		logging::print( _( "[hotwheels] - error - json save failed: {}" ), ex.what( ) );
		logging::pop_console_color( );
		return false;
	}

	std::ofstream ofsOutFile( file, std::ios::out | std::ios::trunc );

	if ( !ofsOutFile.good( ) )
		return false;

	try
	{
		ofsOutFile << config.dump( 4 );
		ofsOutFile.close( );
	}
	catch ( std::ofstream::failure& ex )
	{
		logging::push_console_color( FOREGROUND_RED );
		logging::print( _( "[hotwheels] - error - failed to save configuration: {}" ), ex.what( ) );
		logging::pop_console_color( );
		return false;
	}

	c::saved_config_file_name = file_name.data( );
	logging::print( _( "[hotwheels] - success - saved configuration at: {}" ), file );

	if ( c::get<bool>( vars.log_config_print ) )
		if ( i::engine_client->in_game( ) )
			i::client_mode->m_chat_element( )->print( 0, _( "##saved config" ) );

	return true;
}

bool c::load( std::string_view file_name )
{
	const std::string file = std::filesystem::path( fs_path / file_name ).string( );
	nlohmann::json config = { };

	std::ifstream ifsInputFile( file, std::ios::in );

	if ( !ifsInputFile.good( ) )
		return false;

	try
	{
		config = nlohmann::json::parse( ifsInputFile, nullptr, false );

		if ( config.is_discarded( ) )
			return false;

		ifsInputFile.close( );
	}
	catch ( std::ifstream::failure& ex )
	{
		logging::push_console_color( FOREGROUND_RED );
		logging::print( _( "[hotwheels] - error - failed to load configuration: {}" ), ex.what( ) );
		logging::pop_console_color( );
		return false;
	}

	try
	{
		for ( const auto& variable : config )
		{
			const std::size_t index = get_variable_index( variable[ _( "name-id" ) ].get<fnv1a_t>( ) );

			if ( index == c_invalid_variable )
				continue;

			auto& entry = vec_variables.at( index );

			switch ( variable[ _( "type-id" ) ].get<fnv1a_t>( ) )
			{
			case fnv1a::hash_const( "bool" ):
			{
				entry.set<bool>( variable[ _( "value" ) ].get<bool>( ) );
				break;
			}
			case fnv1a::hash_const( "float" ):
			{
				entry.set<float>( variable[ _( "value" ) ].get<float>( ) );
				break;
			}
			case fnv1a::hash_const( "int" ):
			{
				entry.set<int>( variable[ _( "value" ) ].get<int>( ) );
				break;
			}
			case fnv1a::hash_const( "std::string" ):
			{
				entry.set<std::string>( variable[ _( "value" ) ].get<std::string>( ) );
				break;
			}
			case fnv1a::hash_const( "color" ):
			{
				const nlohmann::json vector = nlohmann::json::parse( variable[ _( "value" ) ].get<std::string>( ) );

				entry.set<color>( color(
					vector.at( 0 ).get<std::uint8_t>( ),
					vector.at( 1 ).get<std::uint8_t>( ),
					vector.at( 2 ).get<std::uint8_t>( ),
					vector.at( 3 ).get<std::uint8_t>( )
				) );

				break;
			}
			case fnv1a::hash_const( "std::vector<bool>" ):
			{
				const nlohmann::json vector = nlohmann::json::parse( variable[ _( "value" ) ].get<std::string>( ) );
				auto& vecBools = entry.get<std::vector<bool>>( );

				for ( std::size_t i = 0U; i < vector.size( ); i++ )
				{
					if ( i < vecBools.size( ) )
						vecBools.at( i ) = vector.at( i ).get<bool>( );
				}

				break;
			}
			case fnv1a::hash_const( "std::vector<int>" ):
			{
				const nlohmann::json vector = nlohmann::json::parse( variable[ _( "value" ) ].get<std::string>( ) );
				auto& vecInts = entry.get<std::vector<int>>( );

				for ( std::size_t i = 0U; i < vector.size( ); i++ )
				{
					if ( i < vecInts.size( ) )
						vecInts.at( i ) = vector.at( i ).get<int>( );
				}

				break;
			}
			case fnv1a::hash_const( "std::vector<float>" ):
			{
				const nlohmann::json vector = nlohmann::json::parse( variable[ _( "value" ) ].get<std::string>( ) );
				auto& vecFloats = entry.get<std::vector<float>>( );

				for ( std::size_t i = 0U; i < vector.size( ); i++ )
				{
					if ( i < vecFloats.size( ) )
						vecFloats.at( i ) = vector.at( i ).get<float>( );
				}

				break;
			}
			default:
				break;
			}
		}
	}
	catch ( const nlohmann::detail::exception& ex )
	{
		logging::push_console_color( FOREGROUND_RED );
		logging::print( _( "[hotwheels] - error - json load failed: {}" ), ex.what( ) );
		logging::pop_console_color( );
		return false;
	}

	c::loaded_config_file_name = file_name.data( );
	logging::print( _( "[hotwheels] - success - loaded configuration at: {}" ), file );

	if ( c::get<bool>( vars.log_config_print ) )
		if ( i::engine_client->in_game( ) )
			i::client_mode->m_chat_element( )->print( 0, _( "##loaded config" ) );

	return true;
}

void c::remove( const std::size_t index )
{
	const std::string& file_name = vec_file_names.at( index );

	const std::string file = std::filesystem::path( fs_path / file_name ).string( );

	if ( std::filesystem::remove( file ) )
	{
		vec_file_names.erase( vec_file_names.cbegin( ) + static_cast< std::ptrdiff_t >( index ) );
		logging::print( _( "[hotwheels] - success - removed configuration at: {}" ), file );
	}
}

void c::refresh( )
{
	vec_file_names.clear( );

	for ( const auto& it : std::filesystem::directory_iterator( fs_path ) )
	{
		if ( it.path( ).filename( ).extension( ) == _( ".hw" ) )
		{
			logging::print( _( "[hotwheels] - success - found configuration file: {}" ), it.path( ).filename( ).string( ) );
			vec_file_names.push_back( it.path( ).filename( ).string( ) );
		}
	}
}

std::size_t c::get_variable_index( const fnv1a_t name_hash )
{
	for ( std::size_t i = 0U; i < vec_variables.size( ); i++ )
	{
		if ( vec_variables.at( i ).name_hash == name_hash )
			return i;
	}

	return c_invalid_variable;
}

std::filesystem::path c::get_working_path( )
{
	std::filesystem::path fs_working_path;

	if ( PWSTR path_to_documents; SUCCEEDED( SHGetKnownFolderPath( FOLDERID_Documents, 0UL, nullptr, &path_to_documents ) ) )
	{
		fs_working_path.assign( path_to_documents );
		fs_working_path.append( _( "hotwheels" ) );
		CoTaskMemFree( path_to_documents );
	}

	return fs_working_path;
}
