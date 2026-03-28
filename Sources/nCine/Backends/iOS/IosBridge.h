#pragma once

#include <Containers/String.h>
#include <Containers/StringView.h>

using namespace Death;

namespace nCine::Backends
{
	/** @brief A bridge class that provides access to iOS-specific functionality */
	class IosBridge
	{
	public:
		/** @brief Initializes the bridge */
		static void Init();

		/** @brief Returns the preferred language and region code (e.g., "en-US") */
		static String GetPreferredLanguage();

		/** @brief Returns true if the screen is round */
		static bool IsScreenRound();

		/** @brief Returns true if the application has permission to access external storage */
		static bool HasExternalStoragePermission();

		/** @brief Requests permission to access external storage */
		static void RequestExternalStoragePermission();

		/** @brief Opens the specified URL in the system browser */
		static bool OpenUrl(StringView url);
	};
}
