#pragma once
#include <ECS.hpp>

class PositionComponent : public Component
{
    private:
        int xpos_;
        int ypos_;

    public:
        int X() { return xpos_; }
        int Y() { return ypos_; }

        void Init() override
        {
            xpos_ = 0;
            ypos_ = 0;
        }

        void Update() override
        {
            xpos_++;
            ypos_++;
        }

        void SetPos(int x, int y)
        {
            xpos_ = x;
            ypos_ = y;

        }
};
