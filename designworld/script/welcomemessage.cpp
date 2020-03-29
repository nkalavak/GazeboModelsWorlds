#include <gazebo/gazebo.hh>

namespace gazebo
{
    class WorldPluginMobileRobot : public WorldPlugin
    {
	public : WorldPluginMobileRobot(): WorldPlugin()
	    {
		printf("Welcome to Nivii's World!\n");
	    }
	public : void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
	    {
	    }
    };
    GZ_REGISTER_WORLD_PLUGIN(WorldPluginMobileRobot)
}
