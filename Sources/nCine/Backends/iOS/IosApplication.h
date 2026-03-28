#pragma once

#include "../../Application.h"

namespace nCine
{
	/** @brief Main entry point and handler for iOS applications */
	class IosApplication : public Application
	{
	public:
		/** @brief Entry point method to be called from the iOS app delegate */
		static void Run(CreateAppEventHandlerDelegate createAppEventHandler);

		/** @brief Returns true if the application has already called `Init()` */
		inline bool IsInitialized() const {
			return isInitialized_;
		}

		bool OpenUrl(StringView url) override;

		/** @brief Processes a single frame */
		void ProcessStep();

		/** @brief Handles changes of content bounds (e.g., orientation changes) */
		void HandleContentBoundsChanged(Recti bounds);

		bool CanShowScreenKeyboard() override;
		bool ToggleScreenKeyboard() override;
		bool ShowScreenKeyboard() override;
		bool HideScreenKeyboard() override;

	private:
		bool isInitialized_;

		CreateAppEventHandlerDelegate createAppEventHandler_;
		
		void PreInit();
		/** @brief Must be called at the beginning to initialize the application */
		void Init();
		/** @brief Must be called before exiting to shut down the application */
		void Shutdown();

		IosApplication();
		~IosApplication();

		IosApplication(const IosApplication&) = delete;
		IosApplication& operator=(const IosApplication&) = delete;

		/** @brief Returns the singleton reference to the iOS application */
		static IosApplication& theIosApplication() {
			return static_cast<IosApplication&>(theApplication());
		}

		friend Application& theApplication();
	};

	/** @brief Returns application instance */
	Application& theApplication();

}
