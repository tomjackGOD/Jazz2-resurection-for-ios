import Foundation
import UIKit

@_cdecl("ios_bridge_get_preferred_language")
public func iosBridgeGetPreferredLanguage() -> UnsafePointer<Int8>? {
    if let languageCode = Locale.current.languageCode {
        let fullCode: String
        if let regionCode = Locale.current.regionCode {
            fullCode = "\(languageCode)-\(regionCode)"
        } else {
            fullCode = languageCode
        }
        return (fullCode as NSString).utf8String
    }
    return nil
}

@_cdecl("ios_bridge_is_screen_round")
public func iosBridgeIsScreenRound() -> Bool {
    return false
}

@_cdecl("ios_bridge_has_external_storage_permission")
public func iosBridgeHasExternalStoragePermission() -> Bool {
    return true
}

@_cdecl("ios_bridge_request_external_storage_permission")
public func iosBridgeRequestExternalStoragePermission() {
}

@_cdecl("ios_bridge_open_url")
public func iosBridgeOpenUrl(_ urlStringPointer: UnsafePointer<Int8>) -> Bool {
    let urlString = String(cString: urlStringPointer)
    guard let url = URL(string: urlString) else { return false }
    if UIApplication.shared.canOpenURL(url) {
        UIApplication.shared.open(url, options: [:], completionHandler: nil)
        return true
    }
    return false
}
