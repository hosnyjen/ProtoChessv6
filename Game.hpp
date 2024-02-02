#include "Player.hpp"
#include "VisualBoard.hpp"

class Game {
    public:
        VisualBoard* visBoard;
        Player* wPlayer;
        Player* bPlayer;
        
    public:
        Player* currentPlayer;
        vector<Move> currentPossMoves;
        int currTeam;

        Game(int setup, int layout[][8], RenderWindow& window);

        void switchTurn();

        void displayPopup(const string& message);

        void handleMovement(RenderWindow& window);
};