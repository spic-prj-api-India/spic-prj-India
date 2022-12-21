#pragma once
#include <SocketScript.hpp>

enum DestroyType : int{
	OBSTACLE = 1,
	TARGET = 2
};

class RocketSendScript :
	public spic::SocketScript {
public:
	RocketSendScript();
	void Destroy(DestroyType type);
	virtual void Send(std::shared_ptr<spic::GameObject> entity) override;
	virtual void CreateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity) override;
	virtual void DestroyEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity) override;
	virtual void SyncEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity) override;
	virtual void UpdateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity) override;
};