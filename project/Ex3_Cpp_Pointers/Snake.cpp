#include "Snake.hpp"
#include "SnakeBody.hpp"

Snake::Snake() {
}

// This is called every time the snake should move.
void Snake::move(){
    int currentHeadPosX = snakeHead->x;
    int currentHeadPosY = snakeHead->y;

    snakeHead->moveTo(currentHeadPosX+this->moveX, currentHeadPosY+this->moveY);

}

// This is called whenever one arrow key is pressed.
// Values are [-1,0,1] for x and y and describe how much the snake moves in each update
void Snake::setMoveDirection(int moveX, int moveY) {
    // TODO prevent move direction to be the opposite of the current direction
    if(this->moveX + moveX != 0)
        this->moveX = moveX;
    if(this->moveY + moveY != 0)
        this->moveY = moveY;

}

// Initialize game. This is called every time the game starts or restarts.
void Snake::init(int initialLength, int x, int y, int moveX, int moveY) {
    length = initialLength;
    this->moveX = moveX;
    this->moveY = moveY;

    // TODO clean up and initialize the new snake. Make sure not to leak memory.

    delete snakeHead;
    snakeHead = new SnakeBody(x,y);
    snakeHead->next = new SnakeBody(x-1, y);
    SnakeBody* nextBody = snakeHead->next;
    for (int i = 2; i < initialLength; i++) {
        nextBody->next = new SnakeBody(x-i, y);
        nextBody = nextBody->next;
    }
    SnakeBody::totalSnakeBodies = initialLength;
}

// Should increment the length and append a SnakeBody
void Snake::grow() {
    // TODO add a SnakeBody to the snake.
    auto lastBody = snakeHead;
    while (lastBody->next != nullptr)
        lastBody = lastBody->next;
    lastBody->next = new SnakeBody(lastBody->x,lastBody->y);
}

// Returns true if the snake collides with itself
bool Snake::collide(int x, int y) {
    // TODO check if there is any snake segment at coord (x,y) and return true if that is the case
    auto check = snakeHead;
     do {
        if (check->x == x && check->y == y) return true;
        check = check->next;
    } while(check != nullptr);

    return false;
}
