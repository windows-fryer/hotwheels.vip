#include <ShlObj.h>
#include <fstream>
#include <iostream>

#include "../../json/json.hpp"

#include "config.h"

bool c::init( )
{
	if ( !std::filesystem::is_directory( fs_path ) ) {
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
	if ( fs_file_path.extension( ) != ".hw" )
		fs_file_path.replace_extension( ".hw" );

	const std::string file = std::filesystem::path( fs_path / fs_file_path ).string( );
	nlohmann::json config  = { };

	try {
		for ( auto& variable : vec_variables ) {
			nlohmann::json entry = { };

			entry[ "name-id" ] = variable.name_hash;
			entry[ "type-id" ] = variable.type_hash;

			switch ( variable.type_hash ) {
			case fnv1a::hash_const( "int" ): {
				entry[ "value" ] = variable.get< int >( );
				break;
			}
			case fnv1a::hash_const( "float" ): {
				entry[ "value" ] = variable.get< float >( );
				break;
			}
			case fnv1a::hash_const( "bool" ): {
				entry[ "value" ] = variable.get< bool >( );
				break;
			}
			case fnv1a::hash_const( "std::string" ): {
				entry[ "value" ] = variable.get< std::string >( );
				break;
			}
			case fnv1a::hash_const( "color" ): {
				const auto& colVariable = variable.get< color >( );

				nlohmann::json sub = { };

				sub.push_back( colVariable.get< color_r >( ) );
				sub.push_back( colVariable.get< color_g >( ) );
				sub.push_back( colVariable.get< color_b >( ) );
				sub.push_back( colVariable.get< color_a >( ) );

				entry[ "value" ] = sub.dump( );
				break;
			}
			case fnv1a::hash_const( "std::vector<bool>" ): {
				const auto& vecBools = variable.get< std::vector< bool > >( );

				nlohmann::json sub = { };

				for ( const auto&& bValue : vecBools )
					sub.push_back( static_cast< bool >( bValue ) );

				entry[ "value" ] = sub.dump( );
				break;
			}
			case fnv1a::hash_const( "std::vector<int>" ): {
				const auto& vecInts = variable.get< std::vector< int > >( );

				nlohmann::json sub = { };

				for ( const auto& iValue : vecInts )
					sub.push_back( iValue );

				entry[ "value" ] = sub.dump( );
				break;
			}
			case fnv1a::hash_const( "std::vector<float>" ): {
				const auto& vecFloats = variable.get< std::vector< float > >( );

				nlohmann::json sub = { };

				for ( const auto& flValue : vecFloats )
					sub.push_back( flValue );

				entry[ "value" ] = sub.dump( );
				break;
			}
			default:
				break;
			}

			config.push_back( entry );
		}
	} catch ( const nlohmann::detail::exception& ex ) {
		return false;
	}

	std::ofstream ofsOutFile( file, std::ios::out | std::ios::trunc );

	if ( !ofsOutFile.good( ) )
		return false;

	try {
		ofsOutFile << config.dump( 4 );
		ofsOutFile.close( );
	} catch ( std::ofstream::failure& ex ) {
		return false;
	}

	c::saved_config_file_name = file_name.data( );

	return true;
}

bool c::load( std::string_view file_name )
{
	const std::string file = std::filesystem::path( fs_path / file_name ).string( );
	nlohmann::json config  = { };

	std::ifstream ifsInputFile( file, std::ios::in );

	if ( !ifsInputFile.good( ) )
		return false;

	try {
		config = nlohmann::json::parse( ifsInputFile, nullptr, false );

		if ( config.is_discarded( ) )
			return false;

		ifsInputFile.close( );
	} catch ( std::ifstream::failure& ex ) {
		return false;
	}

	try {
		for ( const auto& variable : config ) {
			const std::size_t index = get_variable_index( variable[ "name-id" ].get< fnv1a_t >( ) );

			if ( index == c_invalid_variable )
				continue;

			auto& entry = vec_variables.at( index );

			switch ( variable[ "type-id" ].get< fnv1a_t >( ) ) {
			case fnv1a::hash_const( "bool" ): {
				entry.set< bool >( variable[ "value" ].get< bool >( ) );
				break;
			}
			case fnv1a::hash_const( "float" ): {
				entry.set< float >( variable[ "value" ].get< float >( ) );
				break;
			}
			case fnv1a::hash_const( "int" ): {
				entry.set< int >( variable[ "value" ].get< int >( ) );
				break;
			}
			case fnv1a::hash_const( "std::string" ): {
				entry.set< std::string >( variable[ "value" ].get< std::string >( ) );
				break;
			}
			case fnv1a::hash_const( "color" ): {
				const nlohmann::json vector = nlohmann::json::parse( variable[ "value" ].get< std::string >( ) );

				entry.set< color >( color( vector.at( 0 ).get< std::uint8_t >( ), vector.at( 1 ).get< std::uint8_t >( ),
				                           vector.at( 2 ).get< std::uint8_t >( ), vector.at( 3 ).get< std::uint8_t >( ) ) );

				break;
			}
			case fnv1a::hash_const( "std::vector<bool>" ): {
				const nlohmann::json vector = nlohmann::json::parse( variable[ "value" ].get< std::string >( ) );
				auto& vecBools              = entry.get< std::vector< bool > >( );

				for ( std::size_t i = 0U; i < vector.size( ); i++ ) {
					if ( i < vecBools.size( ) )
						vecBools.at( i ) = vector.at( i ).get< bool >( );
				}

				break;
			}
			case fnv1a::hash_const( "std::vector<int>" ): {
				const nlohmann::json vector = nlohmann::json::parse( variable[ "value" ].get< std::string >( ) );
				auto& vecInts               = entry.get< std::vector< int > >( );

				for ( std::size_t i = 0U; i < vector.size( ); i++ ) {
					if ( i < vecInts.size( ) )
						vecInts.at( i ) = vector.at( i ).get< int >( );
				}

				break;
			}
			case fnv1a::hash_const( "std::vector<float>" ): {
				const nlohmann::json vector = nlohmann::json::parse( variable[ "value" ].get< std::string >( ) );
				auto& vecFloats             = entry.get< std::vector< float > >( );

				for ( std::size_t i = 0U; i < vector.size( ); i++ ) {
					if ( i < vecFloats.size( ) )
						vecFloats.at( i ) = vector.at( i ).get< float >( );
				}

				break;
			}
			default:
				break;
			}
		}
	} catch ( const nlohmann::detail::exception& ex ) {
		return false;
	}

	c::loaded_config_file_name = file_name.data( );

	return true;
}

void c::remove( const std::size_t index )
{
	const std::string& file_name = vec_file_names.at( index );

	const std::string file = std::filesystem::path( fs_path / file_name ).string( );

	if ( std::filesystem::remove( file ) ) {
		vec_file_names.erase( vec_file_names.cbegin( ) + static_cast< std::ptrdiff_t >( index ) );
	}
}

void c::refresh( )
{
	vec_file_names.clear( );

	for ( const auto& it : std::filesystem::directory_iterator( fs_path ) ) {
		if ( it.path( ).filename( ).extension( ) == ".hw" ) {
			vec_file_names.push_back( it.path( ).filename( ).string( ) );
		}
	}
}

std::size_t c::get_variable_index( const fnv1a_t name_hash )
{
	for ( std::size_t i = 0U; i < vec_variables.size( ); i++ ) {
		if ( vec_variables.at( i ).name_hash == name_hash )
			return i;
	}

	return c_invalid_variable;
}

std::filesystem::path c::get_working_path( )
{
	std::filesystem::path fs_working_path;

	if ( PWSTR path_to_documents; SUCCEEDED( SHGetKnownFolderPath( FOLDERID_Documents, 0UL, nullptr, &path_to_documents ) ) ) {
		fs_working_path.assign( path_to_documents );
		fs_working_path.append( "hotwheels" );
		CoTaskMemFree( path_to_documents );
	}

	if ( not std::filesystem::is_directory( fs_working_path ) ) {
		std::filesystem::create_directories( fs_working_path );
	}

	return fs_working_path;
}
