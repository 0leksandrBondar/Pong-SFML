#pragma once

#include <vector>
#include <memory>

template<class T>
class Singleton
{
public:
	inline static T& instance()
	{
		static std::unique_ptr<T> ptr;

		if (!ptr)
		{
			ptr = std::unique_ptr<T>(new T);
		}

		return *ptr;
	}
};

class Player;

class GameState : public Singleton<GameState>
{
public:
	struct PlayerStatistics
	{
		Player* player = nullptr;
		int score = 0;
		int bouncedBallsCount = 0;
	};

	void registerPlayer(Player& player);
	void unregisterPlayer(Player& player);
	[[nodiscard]] PlayerStatistics* getPlayerStatistics(const Player& player);

protected:
	GameState() = default;
	friend class Singleton<GameState>;

private:
	std::vector<PlayerStatistics> _statistics;
};

[[nodiscard]] inline GameState& GetGameState()
{
	return GameState::instance();
}