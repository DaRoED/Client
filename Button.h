#pragma once
#include "UI.h"

class Sprite;

enum ButtonState
{
	BS_Defalut,
	// BS_Hovered,
	BS_Pressed,
	BS_Clicked,
	// ...
	BS_MaxCount,
};

class Button : public UI
{
	using Super = UI;
public:
	Button();
	virtual ~Button() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	Sprite* GetSprite(ButtonState state) { _sprites[_state]; }

	void SetCurrentSprite(Sprite* sprite) { _currentSprite = sprite; }
	void SetSprite(Sprite* sprite, ButtonState state) { _sprites[state] = sprite; }
	void SetButtonState(ButtonState state);

	void OnClickButton() {  }

protected:
	Sprite* _currentSprite = nullptr;
	Sprite* _sprites[BS_MaxCount] = {};
	ButtonState _state = BS_Defalut;
	// ...
	float _sumTime = 0.f;

	std::function<void(void)> _onClick = nullptr;

public:
	template<typename T>
	void AddOnClickDelegate(T* owner, void(T::* func)())
	{
		_onClick = [owner, func]()
		{
			(owner->*func)();
		};
	}
};

