#pragma once
#include <memory>

class IPlayerListener {
public:
	virtual ~IPlayerListener() = default;
	virtual void onPlayerEliminated() = 0;
};

using PlayerListenerPtr = std::shared_ptr<IPlayerListener>;
using PlayerListenerWeakPtr = std::weak_ptr<IPlayerListener>;