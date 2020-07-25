#pragma once
#include <ECS/Components.hpp>

class PositionComponent : public Component
{
    private:
        int xpos_;
        int ypos_;

    public:
        PositionComponent()
        {
            xpos_ = 0;
            ypos_ = 0;
        }

        PositionComponent(int x, int y)
        {
            xpos_ = x;
            ypos_ = y;
        }

        void Update() override
        {
            xpos_++;
            ypos_++;
        }

        int X()
        {
            return xpos_;
        }
        void X(int x)
        {
            xpos_ = x;
        }

        int Y()
        {
            return ypos_;
        }
        void Y(int y)
        {
            ypos_ = y;
        }
};
