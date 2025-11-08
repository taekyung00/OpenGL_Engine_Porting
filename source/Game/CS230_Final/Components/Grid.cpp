#include "Grid.h"
#include "../../../Engine/Input.hpp"
#include "../../../Engine/TextureManager.hpp"
#include "../../../Engine/Window.hpp"

Grid::Grid()
{
    window_size = Engine::GetWindow().GetSize();
    white_dot   = Engine::GetTextureManager().Load("Assets/images/CS230_Final/WhiteDot.png");
    black_dot   = Engine::GetTextureManager().Load("Assets/images/CS230_Final/BlackDot.png");
    red_dot     = Engine::GetTextureManager().Load("Assets/images/CS230_Final/RedDot.png");
    blue_dot    = Engine::GetTextureManager().Load("Assets/images/CS230_Final/BlueDot.png");
}

void Grid::Update([[maybe_unused]] double dt)
{
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Tab))
    {
        draw = !draw;
    }
    if(window_size != Engine::GetWindow().GetSize()){
        window_size = Engine::GetWindow().GetSize();
    }
}

void Grid::Draw(DotColor dc)
{
    if (draw)
    {
        for (int i = 0; i <= window_size.y / 10; ++i)
        {
            for (int j = 0; j <= window_size.x / 10; ++j)
            {
                Math::TransformationMatrix draw_matrix = Math::TranslationMatrix(Math::ivec2{ j * 10, i * 10 }) /** Math::TranslationMatrix(-camera.GetPosition())*/;
                if (i == 0 && j == 0)
                {
                    blue_dot->Draw(draw_matrix * Math::ScaleMatrix(4.0));
                }
                else if (i == 0 || i == window_size.y / 10 || j == 0 || j == window_size.x / 10)
                {
                    red_dot->Draw(draw_matrix * Math::ScaleMatrix(2.0));
                }
                else
                {
                    switch (dc)
                    {
                    case DotColor::white:
                        white_dot->Draw(draw_matrix);
                        break;
                    
                    case DotColor::black:
                        black_dot->Draw(draw_matrix);
                        break;
                    }
                    
                }
            }
        }
    }
}
