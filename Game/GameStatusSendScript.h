#pragma once
#include <SocketScript.hpp>

enum GameStatus : int {
	PLAYING = 1,
	WON = 2,
	LOST = 3
};

class GameStatusSendScript :
	public spic::SocketScript {
public:
	GameStatusSendScript();
	void SetGameStatus(GameStatus newGameStatus);
	virtual void Send(std::shared_ptr<spic::GameObject> entity) override;
	virtual void CreateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity) override;
	virtual void DestroyEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity) override;
	virtual void SyncEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity) override;
	virtual void UpdateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity) override;
private:
	GameStatus gameStatus;
};