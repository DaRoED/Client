#pragma once
#include "Scene.h"

class GameObject;
class Creature;
class Player;

struct PQNode
{
	PQNode(int32 cost, Vec2Int pos) : cost(cost), pos(pos) {}

	bool operator<(const PQNode& other) const { return cost < other.cost; }
	bool operator>(const PQNode& other) const { return cost > other.cost; }

	int32 cost;
	Vec2Int pos;
};

class DevScene : public Scene
{
	using Super = Scene;
public:
	DevScene();
	virtual ~DevScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void AddActor(Actor* actor) override;
	virtual void RemoveActor(Actor* actor) override;

public:
	void LoadMap();
	void LoadPlayer();
	void LoadMonster();
	void LoadProjectile();
	void LoadEffect();
	void LoadTileMap();

	template<typename T>
	T* SpawnObject(Vec2Int pos)
	{
		auto isGameObject = std::is_convertible_v<T*, GameObject*>;
		assert(isGameObject);

		T* ret = new T();
		ret->SetCellPos(pos, true);
		AddActor(ret);

		ret->Init();

		return ret;
	}

	template<typename T>
	T* SpawnObjectAtRandomPos()
	{
		Vec2Int randPos = GetRandomEmptyCellPos();
		return SpawnObject<T>(randPos);
	}

public:
	void Handle_S_AddObject(Protocol::S_AddObject& pkt);
	void Handle_S_RemoveObject(Protocol::S_RemoveObject& pkt);

public:
	GameObject* GetObject(uint64 id);

	Player* FindClosestPlayer(Vec2Int cellPos);
	bool FindPath(Vec2Int src, Vec2Int dest, vector<Vec2Int>& path, int32 maxDapth = 10);

public:
	bool CanGo(Vec2Int cellPos);
	Vec2 ConvertPos(Vec2Int celPos);
	Vec2Int GetRandomEmptyCellPos();

	Creature* GetCreatureAt(Vec2Int pos);


private:
	void TickMonsterSpawn();

private:
	const int32 DESIRED_MONSTER_COUNT = 20;
	int32 _monsterCount = 0;

public:
	class TileMapActor* _tileMapActor = nullptr;
};