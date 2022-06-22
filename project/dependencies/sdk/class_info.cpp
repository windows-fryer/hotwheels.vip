#include "class_info.h"

namespace big
{
	void update_class_info( )
	{
		class_info.MissileEntity    = FindClassInfo( "VeniceClientMissileEntity" );
		class_info.ExplosionEntity  = FindClassInfo( "ClientExplosionPackEntity" );
		class_info.VehicleEntity    = FindClassInfo( "ClientVehicleEntity" );
		class_info.WarningComponent = FindClassInfo( "ClientWarningSystemComponent" );
	}
} // namespace big