#include "IosApplication.h"
#include "IosBridge.h"
#include "IosInputManager.h"
#include "MetalGfxDevice.h"

namespace nCine
{
	IosApplication::IosApplication()
		: Application(), isInitialized_(false)
	{
	}

	IosApplication::~IosApplication()
	{
		Shutdown();
	}

	void IosApplication::Run(CreateAppEventHandlerDelegate createAppEventHandler)
	{
		IosApplication& app = theIosApplication();
		app.createAppEventHandler_ = createAppEventHandler;
		
		// This will be called from Swift's @main or similar
		// For now, we initialize everything
		app.PreInit();
		app.Init();
	}

	bool IosApplication::OpenUrl(StringView url)
	{
		return Backends::IosBridge::OpenUrl(url);
	}

	void IosApplication::ProcessStep()
	{
		if (isInitialized_) {
			Step();
		}
	}

	void IosApplication::HandleContentBoundsChanged(Recti bounds)
	{
		if (isInitialized_) {
			// Update the graphics device and application viewports
			Backends::MetalGfxDevice& gfxDevice = static_cast<Backends::MetalGfxDevice&>(*gfxDevice_);
			gfxDevice.setResolution(false, bounds.W, bounds.H);
			
			screenViewport_->setRect(bounds);
		}
	}

	bool IosApplication::CanShowScreenKeyboard() { return true; }
	bool IosApplication::ToggleScreenKeyboard() { return false; }
	bool IosApplication::ShowScreenKeyboard() { return false; }
	bool IosApplication::HideScreenKeyboard() { return false; }

	void IosApplication::PreInit()
	{
		// Set up the bridge
		Backends::IosBridge::Init();
	}

	void IosApplication::Init()
	{
		if (isInitialized_) {
			return;
		}

		// Initialize input manager
		inputManager_ = std::make_unique<Backends::IosInputManager>();

		// Initialize graphics device
		gfxDevice_ = std::make_unique<Backends::MetalGfxDevice>(WindowMode(), GLContextInfo(), DisplayMode());

		// Initialize application
		appEventHandler_ = createAppEventHandler_();
		appEventHandler_->OnPreInitialize(appCfg_);

		// Common initialization
		// ...

		isInitialized_ = true;
	}

	void IosApplication::Shutdown()
	{
		if (!isInitialized_) {
			return;
		}

		// Shutdown engine components
		appEventHandler_.reset();
		gfxDevice_.reset();
		inputManager_.reset();

		isInitialized_ = false;
	}

	Application& theApplication()
	{
		static IosApplication application;
		return application;
	}
}
