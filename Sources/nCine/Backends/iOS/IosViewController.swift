import UIKit
import GLKit

class ViewController: UIViewController {
    private var glLayer: CAEAGLLayer?
    private var displayLink: CADisplayLink?

    override func viewDidLoad() {
        super.viewDidLoad()
        
        setupGLLayer()
        
        // Start the game loop after the view has loaded
        startDisplayLink()
    }
    
    private func setupGLLayer() {
        glLayer = CAEAGLLayer()
        glLayer?.frame = view.bounds
        glLayer?.isOpaque = true
        glLayer?.drawableProperties = [
            kEAGLDrawablePropertyRetainedBacking: false,
            kEAGLDrawablePropertyColorFormat: kEAGLColorFormatRGBA8
        ]
        
        if let layer = glLayer {
            view.layer.addSublayer(layer)
        }
    }
    
    private func startDisplayLink() {
        displayLink = CADisplayLink(target: self, selector: #selector(renderLoop))
        displayLink?.add(to: .main, forMode: .common)
    }
    
    @objc private func renderLoop() {
        // Bridge call to C++ application's ProcessStep() or similar
        // For now, it's a placeholder
        ios_bridge_process_frame()
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        for touch in touches {
            let point = touch.location(in: view)
            let scale = UIScreen.main.scale
            ios_bridge_handle_touch(0, Int32(point.x * scale), Int32(point.y * scale), Int32(touch.hash))
        }
    }
    
    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?) {
        for touch in touches {
            let point = touch.location(in: view)
            let scale = UIScreen.main.scale
            ios_bridge_handle_touch(1, Int32(point.x * scale), Int32(point.y * scale), Int32(touch.hash))
        }
    }
    
    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
        for touch in touches {
            let point = touch.location(in: view)
            let scale = UIScreen.main.scale
            ios_bridge_handle_touch(2, Int32(point.x * scale), Int32(point.y * scale), Int32(touch.hash))
        }
    }
    
    override func touchesCancelled(_ touches: Set<UITouch>, with event: UIEvent?) {
        for touch in touches {
            let point = touch.location(in: view)
            let scale = UIScreen.main.scale
            ios_bridge_handle_touch(2, Int32(point.x * scale), Int32(point.y * scale), Int32(touch.hash))
        }
    }
    
    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        glLayer?.frame = view.bounds
        
        // Notify C++ side of resize
        let scale = UIScreen.main.scale
        let width = Int32(view.bounds.width * scale)
        let height = Int32(view.bounds.height * scale)
        ios_bridge_handle_resize(width, height)
    }
    
    // C-style interface functions that will be called from C++ side to manage the view
    @_cdecl("ios_bridge_process_frame")
    public func iosBridgeProcessFrame() {
        // This will call IosApplication::ProcessStep()
    }
    
    @_cdecl("ios_bridge_handle_resize")
    public func iosBridgeHandleResize(_ width: Int32, _ height: Int32) {
        // This will call IosApplication::HandleContentBoundsChanged()
    }
    
    @_cdecl("ios_bridge_handle_touch")
    public func iosBridgeHandleTouch(_ type: Int32, _ x: Int32, _ y: Int32, _ pointerId: Int32) {
        // This will call IosInputManager::HandleTouch()
    }
}
