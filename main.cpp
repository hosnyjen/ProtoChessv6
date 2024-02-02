#include "VisualBoard.hpp"
#include "Game.hpp"
#include <iostream>
#include <bitset>

int main() {
    
    RenderWindow window(VideoMode(windowWidth, windowLength), "ChessEngine", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);
    VisualBoard visBoard(standard1);
    //Game mainGame(0, standard1);

    /*bitset<64> boardBits(visBoard.occupiedSquares);
    cout << "Chessboard state: " << boardBits << endl;

    bitset<64> boardBits1(visBoard.whitePieces);
    cout << "White pieces: " << boardBits1 << endl;

    bitset<64> boardBits2(visBoard.blackPieces);
    cout << "Black pieces: " << boardBits2 << endl;

    bitset<64> boardBits3(visBoard.noMoves);
    cout << "No moves: " << boardBits3 << endl;*/

    Clock clock;
    Time deltaTime;

    /*while(window.isOpen()){
        deltaTime = clock.restart();
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
            }/* else {
                mainGame.handleMovement(event, window);
            }
            
             else if(Mouse::isButtonPressed(Mouse::Left)){
                window.setFramerateLimit(60);
                double mouseX = Mouse::getPosition(window).x / 100.0;
                double mouseY = Mouse::getPosition(window).y / 100.0;

                if(mouseX >= 0 && mouseX <= 8 && mouseY >= 0 && mouseY <= 8){
                    Square* currSquare = &visBoard.gridSquares[(int)mouseX][(int)mouseY];
                    
                    if(visBoard.selectedSquare == nullptr){
                        if(currSquare->piece != nullptr){
                            visBoard.selectedSquare = currSquare;
                            visBoard.highPossMoves(currSquare);
                            visBoard.selectedSquare->piece->isDragged = true;
                            visBoard.selectedSquare->piece->locX = mouseX;
                            visBoard.selectedSquare->piece->locY = mouseY;
                        }
                    } else {
                        visBoard.selectedSquare->piece->locX = mouseX;
                        visBoard.selectedSquare->piece->locY = mouseY;
                    }
                }
            } else if(event.type == Event::MouseButtonPressed){
                int mouseX = Mouse::getPosition(window).x / 100.0;
                int mouseY = Mouse::getPosition(window).y / 100.0;

                if(mouseX >= 0 && mouseX <= 8 && mouseY >= 0 && mouseY <= 8){
                    Square* clickedSquare = &visBoard.gridSquares[mouseX][mouseY];

                    if(visBoard.selectedSquare != nullptr){
                        if(clickedSquare == visBoard.selectedSquare){
                            visBoard.selectedSquare->piece->isDragged = false;
                            visBoard.unHighlight();
                            visBoard.selectedSquare = nullptr;
                        } else {
                            visBoard.selectedSquare->piece->isDragged = false;
                            vector<Move> possMoves = visBoard.getPossMoves(visBoard.getIndex(visBoard.selectedSquare->x, visBoard.selectedSquare->y), regular);
                            Move selectedMove;
                            for(int i = 0; i < possMoves.size(); i++){
                                if(visBoard.getIndex(clickedSquare->x, clickedSquare->y) == possMoves[i].targetIndex){
                                    selectedMove = possMoves[i];
                                    break;
                                }
                            }
                            visBoard.checkedMove(selectedMove);
                            bitset<64> boardBits(visBoard.blackKing);
                            cout << "Chessboard state: " << boardBits << endl;
                            visBoard.unHighlight();
                            visBoard.selectedSquare = nullptr;
                        }
                    }
                }
            } else if(event.type == Event::MouseButtonReleased) {
                window.setFramerateLimit(10);
                int mouseX = Mouse::getPosition(window).x / 100.0;
                int mouseY = Mouse::getPosition(window).y / 100.0;

                if(mouseX >= 0 && mouseX <= 8 && mouseY >= 0 && mouseY <= 8){
                    Square* releasedSquare = &visBoard.gridSquares[mouseX][mouseY];

                    if(visBoard.selectedSquare != nullptr){
                        if(releasedSquare == visBoard.selectedSquare){
                            visBoard.selectedSquare->piece->isDragged = false;
                        } else {
                            visBoard.selectedSquare->piece->isDragged = false;
                            vector<Move> possMoves = visBoard.getPossMoves(visBoard.getIndex(visBoard.selectedSquare->x, visBoard.selectedSquare->y), regular);
                            Move selectedMove;
                            for(int i = 0; i < possMoves.size(); i++){
                                if(visBoard.getIndex(releasedSquare->x, releasedSquare->y) == possMoves[i].targetIndex){
                                    selectedMove = possMoves[i];
                                    break;
                                }
                            }
                            visBoard.checkedMove(selectedMove);
                            bitset<64> boardBits(visBoard.blackKing);
                            cout << "Chessboard state: " << boardBits << endl;
                            visBoard.unHighlight();
                            visBoard.selectedSquare = nullptr;
                        }
                    }
                }
            }
        }

        window.clear(Color::Black);
        visBoard.draw(window);
        window.display();
        //}
    }*/
    
    Game mainGame(0, standard1, window);

    return 0;
}