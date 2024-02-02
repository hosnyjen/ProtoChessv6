#include <SFML/System/Clock.hpp>

using namespace sf;

class Player {
    public:
        bool isHuman;
        int team;
        Clock timeRemaining;

        Player(bool isHuman, int team) {
            this->isHuman = isHuman;
            this->team = team;
        }

        
};

class HumanPlayer : public Player {
    public:
        HumanPlayer(int team) : Player(true, team) {

        }
};

class AIPlayer : public Player {
    public:
        AIPlayer(int team) : Player(false, team) {

        }
};