#pragma once
#include <SocketScript.hpp>

class TargetReceiveScript :
	public spic::SocketScript {
public:
	TargetReceiveScript();
	virtual void Send(std::shared_ptr<spic::GameObject> entity) override;
	virtual void CreateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity) override;
	virtual void DestroyEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity) override;
	virtual void SyncEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity) override;
	virtual void UpdateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity) override;
};