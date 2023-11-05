//
// Created by ryousuke kaga on 2023/11/01.
//

#include "Game.h"
#include "Vector2.h"

class Pong : public Game {
public:
    Pong(int width, int height, int thickness);
private:
    void _GenerateOutput() override;
    void _ProcessInput(SDL_Event event) override;
    void _UpdateGame(float deltaTime) override;
    int mThickness;
    Vector2 mPaddlePos;
    Vector2 mBallPos;
    Vector2 mBallVel;
    int mPaddleLength;
    int mPaddleDir;
};

Pong::Pong(int width, int height, int thickness) :
        Game(width, height),
        mThickness(thickness),
        mBallPos(Vector2(width/2.0, height/2.0)),
        mPaddlePos(Vector2(thickness, height/2.0)),
        mBallVel(Vector2(-300.0, 335.0)),
        mPaddleLength(100),
        mPaddleDir(0) {}

void Pong::_ProcessInput(SDL_Event event) {
    switch (event.type)
    {
        // If we get an SDL_QUIT event, end loop
        case SDL_QUIT:
            mIsRunning = false;
            break;
    }

    const Uint8* state = SDL_GetKeyboardState(nullptr);

    mPaddleDir = 0;
    if(state[SDL_SCANCODE_W])
        mPaddleDir -= 1;
    if(state[SDL_SCANCODE_S])
        mPaddleDir += 1;
}

void Pong::_UpdateGame(float deltaTime) {
    mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
    mPaddlePos = max(mPaddlePos, Vector2(mPaddlePos.x, mThickness*2));
    mPaddlePos = min(mPaddlePos, Vector2(mPaddlePos.x, mHeight - mPaddleLength - mThickness));

    if((mBallPos.y <= 2*mThickness && mBallVel.y < 0.0) || (mBallPos.y >= mHeight - 2*mThickness && mBallVel.y > 0.0))
        mBallVel.y *= -1;

    Vector2 diff = mPaddlePos - mBallPos;
    if((abs(diff.y) <= mPaddleLength / 2.0 &&
        mPaddlePos.x >= mPaddlePos.x &&
        mBallPos.x <= mPaddlePos.x + mThickness &&
        mBallVel.x < 0.0) ||
            (mBallPos.x >= mWidth - 2*mThickness && mBallVel.x > 0.0))
        mBallVel.x *= -1;
    mBallPos += mBallVel * deltaTime;
}

void Pong::_GenerateOutput() {
    SDL_SetRenderDrawColor(
            mRender,
            112, 120, 125,
            255
    );
    SDL_Rect wall {
            0,
            0,
            mWidth,
            mThickness
    };
    SDL_RenderFillRect(mRender, &wall);

    wall.y = mHeight - mThickness;
    SDL_RenderFillRect(mRender, &wall);

    wall.x = mWidth - mThickness;
    wall.y = 0;
    wall.w = mThickness;
    wall.h = mHeight;
    SDL_RenderFillRect(mRender, &wall);

    SDL_SetRenderDrawColor(
            mRender,
            255, 255, 255,
            255
    );

    SDL_Rect ball {
        static_cast<int>(mBallPos.x - mThickness/2.0),
        static_cast<int>(mBallPos.y - mThickness/2.0),
        mThickness,
        mThickness
    };
    SDL_RenderFillRect(mRender, &ball);

    SDL_SetRenderDrawColor(
            mRender,
            0, 0, 0,
            255
    );

    SDL_Rect paddle {
            static_cast<int>(mPaddlePos.x - mThickness/2.0),
            static_cast<int>(mPaddlePos.y - mThickness/2.0),
            mThickness,
            mPaddleLength
    };
    SDL_RenderFillRect(mRender, &paddle);
}

int main() {
    Pong game(1024, 769, 10);
    bool success = game.Initialize();
    if(success)
        game.RunLoop();
    game.Shutdown();
}