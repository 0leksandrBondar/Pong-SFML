
#include "GameState.h"

GameState::PlayerStatistics* GameState::getPlayerStatistics(const Player& player)
{
	auto it =
		std::find_if(_statistics.begin(), _statistics.end(), [&player](PlayerStatistics stat) { return stat.player == &player; });

	if (it == _statistics.end())
	{
		return nullptr;
	}

	return &*it;
}

void GameState::registerPlayer(Player& player)
{
	PlayerStatistics ps;
	ps.player = &player;

	_statistics.push_back(std::move(ps));
}

void GameState::unregisterPlayer(Player& player)
{
	_statistics.erase(std::remove_if(
		_statistics.begin(), _statistics.end(), [&player](const PlayerStatistics& ps) { return ps.player == &player; }), _statistics.end());
}
