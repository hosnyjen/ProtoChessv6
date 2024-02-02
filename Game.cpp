#include "Game.hpp"

Game::Game(int setup, int layout[][8], RenderWindow& window){
    visBoard = new VisualBoard(layout);
    
    switch(setup){
        case 0:
            wPlayer = new HumanPlayer(0);
            bPlayer = new HumanPlayer(1);
    }
    currentPlayer = wPlayer;
    currTeam = 13;

    handleMovement(window);
}

void Game::switchTurn(){
    currentPlayer = currentPlayer == wPlayer ? bPlayer : wPlayer;
    currTeam = currTeam == 13 ? 14 : 13;
}

void Game::displayPopup(const string& message) {
    sf::RenderWindow popup(sf::VideoMode(450, 100), "Game Over", sf::Style::Close);

    sf::Font font;
    font.loadFromFile("../Lato-Black.ttf"); // Replace with the path to your font file

    sf::Text text(message, font);
    text.setCharacterSize(70);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);

    while(popup.isOpen()) {
        //cout << "hi";
        sf::Event event;
        while (popup.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                popup.close();
                visBoard->reset();
            }
        }

        popup.clear();
        popup.draw(text);
        popup.display();
    }
}

void Game::handleMovement(RenderWindow& window){
    window.setFramerateLimit(60);

    int arrowStartSq = -1;
    int arrowEndSq = -1;

    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            } 
            
            if(event.type == sf::Event::KeyPressed){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
                    int mouseX = Mouse::getPosition(window).x / 100.0;
                    int mouseY = Mouse::getPosition(window).y / 100.0;

                    //visBoard.printDebugInfo(mouseX, mouseY);
                }
            } else if(currentPlayer->isHuman && Mouse::isButtonPressed(Mouse::Left)){
                window.setFramerateLimit(60);
                double mouseX = Mouse::getPosition(window).x / 100.0;
                double mouseY = Mouse::getPosition(window).y / 100.0;

                if(mouseX >= 0 && mouseX <= 8 && mouseY >= 0 && mouseY <= 8){
                    Square* currSquare = &visBoard->gridSquares[(int)mouseX][(int)mouseY];
                    
                    if(visBoard->selectedSquare == nullptr){
                        if(currSquare->piece != nullptr && visBoard->hasBit(visBoard->boardFlags[currTeam], visBoard->getIndex(currSquare->x, currSquare->y))){
                            visBoard->selectedSquare = currSquare;
                            currentPossMoves = visBoard->getPossMoves(visBoard->getIndex(currSquare->x, currSquare->y), regular);
                            visBoard->highPossMoves(currSquare);
                            visBoard->selectedSquare->piece->isDragged = true;
                            visBoard->selectedSquare->piece->locX = mouseX;
                            visBoard->selectedSquare->piece->locY = mouseY;
                        }
                    } else {
                        visBoard->selectedSquare->piece->locX = mouseX;
                        visBoard->selectedSquare->piece->locY = mouseY;
                    }
                }
            } else if(currentPlayer->isHuman && event.type == Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                int mouseX = Mouse::getPosition(window).x / 100.0;
                int mouseY = Mouse::getPosition(window).y / 100.0;

                if(mouseX >= 0 && mouseX <= 8 && mouseY >= 0 && mouseY <= 8){
                    Square* clickedSquare = &visBoard->gridSquares[mouseX][mouseY];

                    if(visBoard->selectedSquare != nullptr){
                        if(clickedSquare == visBoard->selectedSquare){
                            visBoard->selectedSquare->piece->isDragged = false;
                            visBoard->unHighlight();
                            visBoard->selectedSquare = nullptr;
                        } else {
                            visBoard->selectedSquare->piece->isDragged = false;
                            vector<Move> possMoves = visBoard->getPossMoves(visBoard->getIndex(visBoard->selectedSquare->x, visBoard->selectedSquare->y), regular);
                            Move selectedMove;
                            for(int i = 0; i < possMoves.size(); i++){
                                if(visBoard->getIndex(clickedSquare->x, clickedSquare->y) == possMoves[i].targetIndex){
                                    selectedMove = possMoves[i];
                                    break;
                                }
                            }
                            visBoard->unHighlight();
                            visBoard->selectedSquare = nullptr;
                            
                            if(visBoard->checkedMove(selectedMove)){
                                if(selectedMove.targetIndex == 0 && visBoard->isCheckMate(1)){
                                    displayPopup("White Wins!");
                                } else if(selectedMove.targetIndex == 1 && visBoard->isCheckMate(0)){
                                    displayPopup("Black Wins!");
                                } else {
                                    switchTurn();
                                }
                            }
                        }
                    }
                }
            } else if(currentPlayer->isHuman && event.type == Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                window.setFramerateLimit(10);
                int mouseX = Mouse::getPosition(window).x / 100.0;
                int mouseY = Mouse::getPosition(window).y / 100.0;

                if(mouseX >= 0 && mouseX <= 8 && mouseY >= 0 && mouseY <= 8){
                    Square* releasedSquare = &visBoard->gridSquares[mouseX][mouseY];

                    if(visBoard->selectedSquare != nullptr){
                        if(releasedSquare == visBoard->selectedSquare){
                            visBoard->selectedSquare->piece->isDragged = false;
                        } else {
                            visBoard->selectedSquare->piece->isDragged = false;
                            vector<Move> possMoves = visBoard->getPossMoves(visBoard->getIndex(visBoard->selectedSquare->x, visBoard->selectedSquare->y), regular);
                            Move selectedMove;
                            for(int i = 0; i < possMoves.size(); i++){
                                if(visBoard->getIndex(releasedSquare->x, releasedSquare->y) == possMoves[i].targetIndex){
                                    selectedMove = possMoves[i];
                                    break;
                                }
                            }
                            visBoard->unHighlight();
                            visBoard->selectedSquare = nullptr;
                            //cout << "hi2";
                            if(visBoard->checkedMove(selectedMove)){
                                if(visBoard->getTeam(selectedMove.targetIndex) == 0 && visBoard->isCheckMate(1)){
                                    cout << "White Wins!";
                                    displayPopup("White Wins!");
                                } else if(visBoard->getTeam(selectedMove.targetIndex) == 1 && visBoard->isCheckMate(0)){
                                    cout << "Black Wins!";
                                    displayPopup("Black Wins!");
                                } else {
                                    switchTurn();
                                }
                            }
                        }
                    }
                }
            } else if(currentPlayer->isHuman && event.type == Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                int mouseX = Mouse::getPosition(window).x / 100.0;
                int mouseY = Mouse::getPosition(window).y / 100.0;

                arrowStartSq = visBoard->getIndex(mouseX, mouseY);
            } else if(currentPlayer->isHuman && event.type == Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {
                int mouseX = Mouse::getPosition(window).x / 100.0;
                int mouseY = Mouse::getPosition(window).y / 100.0;

                arrowEndSq = visBoard->getIndex(mouseX, mouseY);

                if(arrowStartSq != arrowEndSq){
                    visBoard->addArrow(arrowStartSq, arrowEndSq);
                } else {
                    visBoard->gridSquares[mouseX][mouseY].isMarked = !visBoard->gridSquares[mouseX][mouseY].isMarked;
                }

                arrowStartSq = -1;
                arrowEndSq = -1;
            }

        }

        window.clear(Color::Black);
        visBoard->draw(window);
        window.display();
    }
}