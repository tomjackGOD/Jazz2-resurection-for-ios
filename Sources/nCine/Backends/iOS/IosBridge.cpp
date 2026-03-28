#include "IosBridge.h"
#include "IosApplication.h"

extern "C" {
    const char* ios_bridge_get_preferred_language();
    bool ios_bridge_is_screen_round();
    bool ios_bridge_has_external_storage_permission();
    void ios_bridge_request_external_storage_permission();
    bool ios_bridge_open_url(const char* url);
    void ios_bridge_handle_touch(int type, int x, int y, int pointerId);

	void ios_bridge_process_frame() {
		static_cast<nCine::IosApplication&>(nCine::theApplication()).ProcessStep();
	}

	void ios_bridge_handle_resize(int width, int height) {
		static_cast<nCine::IosApplication&>(nCine::theApplication()).HandleContentBoundsChanged(nCine::Recti(0, 0, width, height));
	}
}

namespace nCine::Backends
{
    void IosBridge::Init()
    {
    }

    String IosBridge::GetPreferredLanguage()
    {
        const char* lang = ios_bridge_get_preferred_language();
        return (lang != nullptr ? String(lang) : String());
    }

    bool IosBridge::IsScreenRound()
    {
        return ios_bridge_is_screen_round();
    }

    bool IosBridge::HasExternalStoragePermission()
    {
        return ios_bridge_has_external_storage_permission();
    }

    void IosBridge::RequestExternalStoragePermission()
    {
        ios_bridge_request_external_storage_permission();
    }

    bool IosBridge::OpenUrl(StringView url)
    {
        return ios_bridge_open_url(url.data());
    }
}
