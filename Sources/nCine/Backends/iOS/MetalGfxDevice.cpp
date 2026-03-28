#include "MetalGfxDevice.h"

namespace nCine::Backends
{
	char MetalGfxDevice::monitorName_[MaxMonitorNameLength];

	MetalGfxDevice::MetalGfxDevice(const WindowMode& windowMode, const GLContextInfo& glContextInfo, const DisplayMode& displayMode)
		: IGfxDevice(windowMode, glContextInfo, displayMode)
	{
		updateMonitors();
		initDevice();
	}

	MetalGfxDevice::~MetalGfxDevice()
	{
	}

	void MetalGfxDevice::update()
	{
		// Metal swap buffers / present
	}

	const IGfxDevice::VideoMode& MetalGfxDevice::currentVideoMode(unsigned int monitorIndex) const
	{
		return monitors_[0].videoModes[0];
	}

	bool MetalGfxDevice::setVideoMode(unsigned int modeIndex)
	{
		return false;
	}

	void MetalGfxDevice::initDevice()
	{
		// Metal device and command queue initialization
	}

	void MetalGfxDevice::updateMonitors()
	{
		numMonitors_ = 1;
		monitors_[0].name = "iOS Display";
		monitors_[0].position.X = 0;
		monitors_[0].position.Y = 0;
		monitors_[0].scale.X = 1.0f; // This should be UIScreen.main.scale
		monitors_[0].scale.Y = 1.0f;

		monitors_[0].numVideoModes = 1;
		monitors_[0].videoModes[0].width = 0; // Should be screen width
		monitors_[0].videoModes[0].height = 0; // Should be screen height
		monitors_[0].videoModes[0].refreshRate = 60.0f;
	}
}
