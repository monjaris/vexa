/*=============================================*\

 vexa implementation of <GAME> (vexa-<VERSION>)

 Copyright (c) <YEAR> @<USER>

\*=============================================*/

#include "vexa/Renderer.hpp"
#include "vexa/core/MouseBtn.hpp"
#include "vexa/core/colors.hpp"
#include "vexa/core/vec.hpp"
#include "vexa/time.hpp"
#include "vexa/vexa.hpp"
#include <random>
#include <string>
#include <vector>

#define MINE_COUNT 5

using namespace vexa;

bool running = true;
bool first_press = false;

class Grid 
{
    public:
        Grid();
        void initialize();
        int grid[5][5];
        int numRows;
        int numCols;
        int cellSize;
};

struct Cell {
    bool isMine;
    bool isOpen;
    bool isFlagged;
    int adjacentMines;
};

Grid::Grid() 
{
    numRows = 5;
    numCols = 5;
    cellSize = 100;
    initialize();
}

void Grid::initialize()
{
    for (int row = 0; row < numRows; row++) 
    {
        for (int column = 0; column < numCols; column++)
        {
            grid[row][column] = 0;
        }
    }
}

void mineSet(std::vector<std::vector<Cell>>& board)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 4);

    int mineset = 0;

    while (mineset < MINE_COUNT)
    {
        int rows = dist(gen);
        int cols = dist(gen);

        if(board[cols][rows].isMine) continue;

        if(!board[cols][rows].isMine)
        {
            board[cols][rows].isMine = true;
            mineset++;
        }
    }
}

bool isPos(int x, int y)
{
    if (x >= 0 && x < 5 && y >= 0 && y < 5)
    {
        return true;
    }
    
    else return false;
}

bool collisionMineCheck(std::vector<std::vector<Cell>>& board, int x, int y)
{
    return board[x][y].isMine;
}

void numerizer(std::vector<std::vector<Cell>>& board)
{

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            int count = 0;
            
            if (!board[col][row].isMine)
            {
                if (isPos(col+1, row))
                {
                    if (collisionMineCheck(board, col+1, row)) { count++; }
                }
                if (isPos(col+1, row+1))
                {
                    if (collisionMineCheck(board, col+1, row+1)) { count++; }
                }
                if (isPos(col, row+1))
                {
                    if (collisionMineCheck(board, col, row+1)) { count++; }
                }
                if (isPos(col-1, row+1))
                {
                    if (collisionMineCheck(board, col-1, row+1)) { count++; }
                }
                if (isPos(col-1, row))
                {
                    if (collisionMineCheck(board, col-1, row)) { count++; }
                }
                if (isPos(col-1, row-1))
                {
                    if (collisionMineCheck(board, col-1, row-1)) { count++; }
                }
                if (isPos(col, row-1))
                {
                    if (collisionMineCheck(board, col, row-1)) { count++; }
                }
                if (isPos(col+1, row-1))
                {
                    if (collisionMineCheck(board, col+1, row-1)) { count++; }
                }

                board[col][row].adjacentMines = count;
                count = 0;
            }
        }
    }
}

void revealCell(std::vector<std::vector<Cell>>& board, int x, int y)
{
    if (!board[x][y].isOpen && !board[x][y].isFlagged)
    {
        if (board[x][y].isMine)
        {
            running = false;
        }
        else
        {
            board[x][y].isOpen = true;
        }
    }
}

void flagCell(std::vector<std::vector<Cell>>& board, int x, int y)
{
    if (!board[x][y].isOpen && !board[x][y].isFlagged)
    {
        board[x][y].isFlagged = true;
    }
}

void unflagCell(std::vector<std::vector<Cell>>& board, int x, int y)
{
    if (!board[x][y].isOpen && board[x][y].isFlagged)
    {
        board[x][y].isFlagged = false;
    }
}

void firstPress(std::vector<std::vector<Cell>>& board, int x, int y)
{
    board[x][y].isOpen = true;

    if (isPos(x, y+1))
    {
        if (!collisionMineCheck(board, x, y+1))
        {
            board[x][y+1].isOpen = true;
        }
    }
    if (isPos(x+1, y+1))
    {
        if (!collisionMineCheck(board, x+1, y+1))
        {
            board[x+1][y+1].isOpen = true;
        }
    }
    if (isPos(x+1, y))
    {
        if (!collisionMineCheck(board, x+1, y))
        {
            board[x+1][y].isOpen = true;
        }
    }
    if (isPos(x+1, y-1))
    {
        if (!collisionMineCheck(board, x+1, y-1))
        {
            board[x+1][y-1].isOpen = true;
        }
    }
    if (isPos(x, y-1))
    {
        if (!collisionMineCheck(board, x, y-1))
        {
            board[x][y-1].isOpen = true;
        }
    }

    first_press = true;
}

bool winCheck(std::vector<std::vector<Cell>>& board)
{
    int count = 0;

    for (int col = 0; col < 5; col++)
    {
        for (int row = 0; row < 5; row++)
        {
            if (board[col][row].isMine && board[col][row].isFlagged)
            {
                count++;
            }
        }
    }

    if (count == MINE_COUNT)
    {
        return true;
    }
    else
    {
        count = 0;
        return false;
    }
}

int main()
{
    initCores(Core::FONT);

    auto window = Window{}
        .setSize({500, 500})
        .setRenderer(Renderer::Cfg{})
        .create();

    auto& gfx = window.renderer();

    gfx.setMode(Renderer::STRETCH);

    std::vector<std::vector<Cell>> board (5, std::vector<Cell>(5));
    Grid grid = Grid();
    Font font = Font::Load("/usr/share/fonts/Adwaita/AdwaitaMono-Bold.ttf", sizeof(Font));

    mineSet(board);
    numerizer(board);

    while (running)
    {
        while (auto event = Event::Poll()) {
            switch (event->type())
            {
                case Event::QUIT: { running = false; }

                case Event::MOUSE_BUTTON_DOWN: {
                    auto mouse = event->mouse().button;
                    auto mouse_pos = event->mouse().pos;

                    int col = mouse_pos.x / grid.cellSize;
                    int row = mouse_pos.y / grid.cellSize;

                    if (mouse == MouseBtn::LEFT)
                    {
                            if (!first_press)
                            {
                                firstPress(board, col, row);
                            }
                            else
                            {
                                revealCell(board, col, row);
                            }
                    }
                    if (mouse == MouseBtn::RIGHT)
                    {
                        if (!board[col][row].isFlagged)
                        {
                            flagCell(board, col, row);
                        }
                        else
                        {
                            unflagCell(board, col, row);
                        }
                    }
                }

                default: { break; }
            }
        }

        gfx.start(ColorF32::BLACK);
        for (int r = 0; r < grid.numRows; r++)
        {
            for (int c = 0; c < grid.numCols; c++)
            {
                gfx.rectFill(Rect{c * grid.cellSize + 1.0f, r * grid.cellSize + 1.0f, grid.cellSize - 1.0f, grid.cellSize - 1.0f}, ColorF32::GREY);
                if (board[c][r].isOpen)
                {
                    std::string numero = std::to_string(board[c][r].adjacentMines);
                    const char* num = numero.c_str();
                    gfx.drawText(font, num, Vec2{c * grid.cellSize + 50.0f, r * grid.cellSize + 50.0f}, Color::BLACK);
                }
                else if (board[c][r].isMine && board[c][r].isOpen)
                {
                    gfx.drawText(font, "B", Vec2(c * grid.cellSize + 50.0f, r * grid.cellSize + 50.0f), Color::RED);
                }
                else if (board[c][r].isFlagged)
                {
                    gfx.drawText(font, "F", Vec2(c * grid.cellSize + 50.0f, r * grid.cellSize + 50.0f), Color::BLUE);
                }
            }
        }
        if (winCheck(board))
        {
            gfx.drawText(font, "You Won!", Vec2(180, 240), Color::MAGENTA);
            for (int r = 0; r < grid.numRows; r++)
            {
                for (int c = 0; c < grid.numCols; c++)
                {
                    if (!board[c][r].isMine && !board[c][r].isFlagged)
                    {
                        board[c][r].isOpen = true;
                    }
                }
            }
        }
        gfx.finish();
        time::sleep(time::Millis(16.67));
    }
}

