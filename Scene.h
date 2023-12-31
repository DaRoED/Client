#pragma once

class Actor;
class UI;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;

public:
	virtual void AddActor(Actor* actor);
	virtual void RemoveActor(Actor* actor);

public:
	vector<Actor*> _actors[LAYER_MAXCOUNT];
	vector<UI*>	_uis;
};

