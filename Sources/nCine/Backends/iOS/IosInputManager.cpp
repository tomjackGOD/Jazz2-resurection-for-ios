#include "IosInputManager.h"
#include "../../Input/IInputEventHandler.h"

namespace nCine::Backends
{
	IosKeyboardState IosInputManager::keyboardState_;
	IosMouseState IosInputManager::mouseState_;
	IosJoystickState IosInputManager::nullJoystickState_;
	TouchEvent IosInputManager::touchEvent_;
	MouseEvent IosInputManager::mouseEvent_;

	IosInputManager::IosInputManager()
	{
	}

	IosInputManager::~IosInputManager()
	{
	}

	bool IosMouseState::isButtonDown(MouseButton button) const
	{
		return false;
	}

	void IosInputManager::HandleTouch(int type, int x, int y, int pointerId)
	{
		if (inputEventHandler_ == nullptr) {
			return;
		}

		touchEvent_.count = 1;
		touchEvent_.pointers[0].id = pointerId;
		touchEvent_.pointers[0].x = static_cast<float>(x);
		touchEvent_.pointers[0].y = static_cast<float>(y);

		switch (type) {
			case 0: // TouchesBegan
				inputEventHandler_->OnTouchDown(touchEvent_);
				
				// Map to mouse for UI interaction
				mouseEvent_.x = x;
				mouseEvent_.y = y;
				mouseEvent_.button = MouseButton::Left;
				inputEventHandler_->OnMouseDown(mouseEvent_);
				break;
			case 1: // TouchesMoved
				inputEventHandler_->OnTouchMove(touchEvent_);
				
				mouseEvent_.x = x;
				mouseEvent_.y = y;
				inputEventHandler_->OnMouseMove(mouseEvent_);
				break;
			case 2: // TouchesEnded / TouchesCancelled
				inputEventHandler_->OnTouchUp(touchEvent_);
				
				mouseEvent_.x = x;
				mouseEvent_.y = y;
				mouseEvent_.button = MouseButton::Left;
				inputEventHandler_->OnMouseUp(mouseEvent_);
				break;
		}
	}
}

extern "C" {
	void ios_bridge_handle_touch(int type, int x, int y, int pointerId) {
		nCine::Backends::IosInputManager::HandleTouch(type, x, y, pointerId);
	}
}
