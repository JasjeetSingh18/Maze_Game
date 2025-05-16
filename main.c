/*
    THE MAZE GAME

    By Jasjeet Singh Soor

*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include "maze.h"
#include "player.h"
#include "solver.h"

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 800
#define CELL_SIZE 20
#define MAZE_OFFSET_X 100
#define MAZE_OFFSET_Y 100
#define TEXT_OFFSET_Y (MAZE_OFFSET_Y - 50)
#define KEY_GUIDE_Y (MAZE_OFFSET_Y + ROWS * CELL_SIZE + 40)

extern char mazes[3][ROWS][COLS];
extern int player_row, player_col;
extern int end_row, end_col;
extern int find_path(node *maze_list[ROWS * COLS], int start_id, int end_id);

void renderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, SDL_Color color)
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void renderMaze(SDL_Renderer *renderer)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            SDL_Rect cell = {MAZE_OFFSET_X + j * CELL_SIZE, MAZE_OFFSET_Y + i * CELL_SIZE, CELL_SIZE, CELL_SIZE};
            if (maze[i][j] == '#')
            {
                SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            }
            SDL_RenderFillRect(renderer, &cell);

            if (maze[i][j] == 'S' || maze[i][j] == 'E')
            {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderFillRect(renderer, &cell);
            }
        }
    }

    SDL_Rect player = {MAZE_OFFSET_X + player_col * CELL_SIZE, MAZE_OFFSET_Y + player_row * CELL_SIZE, CELL_SIZE, CELL_SIZE};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &player);
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    int start_id, end_id, total_moves;
    int first_run = 0;

    int n = load_mazes("assets/mazes.txt");
    if (n == 0)
    {
        fprintf(stderr, "No mazes loaded\n");
        return 1;
    }
    pick_random_maze(maze);

    // Get the start and the end position of the maze
    get_end(maze);
    get_start(maze);

    SDL_Window *window = SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font *font = TTF_OpenFont("assets/OpenSansHebrew-Regular.ttf", 24);
    if (!font)
    {
        printf("Failed to load font: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Color black = {0, 0, 0, 255};

    bool running = true;
    SDL_Event event;
    char movesText[32];

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                int new_row = player_row;
                int new_col = player_col;

                switch (event.key.keysym.sym)
                {
                case SDLK_w:
                    new_row--;
                    break;
                case SDLK_s:
                    new_row++;
                    break;
                case SDLK_a:
                    new_col--;
                    break;
                case SDLK_d:
                    new_col++;
                    break;
                }

                // Check if the move is legal
                if (new_row >= 0 && new_row < ROWS && new_col >= 0 && new_col < COLS && maze[new_row][new_col] != '#' &&
                    (new_row != player_row || new_col != player_col))
                {
                    player_row = new_row;
                    player_col = new_col;
                    // Check for win
                    if (maze[player_row][player_col] == 'E')
                    {
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "You Win!", "Congratulations! You found the exit!", NULL);
                        running = false;
                    }

                    total_moves--; // Update the total moves counter if the player made a valid move

                    // Check for loss
                    if (total_moves <= 0 && maze[player_row][player_col] != 'E')
                    {
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "You Lose!", "You ran out of moves.", NULL);
                        running = false;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 230, 210, 255);
        SDL_RenderClear(renderer);

        renderMaze(renderer);
        // Remaining moves text
        node *maze_list[ROWS * COLS];
        // Clear the list to ensure no junk in the nodes
        for (int i = 0; i < ROWS * COLS; i++)
        {
            maze_list[i] = NULL;
        }
        maze_to_graph(maze, maze_list);

        // Check if this is the first while command of program
        if (first_run == 0)
        {
            // Get the start_id and the end_id
            start_id = player_row * COLS + player_col;
            end_id = end_row * COLS + end_col;

            // Print the total remaining moves for the first time
            total_moves = find_path(maze_list, start_id, end_id);
            sprintf(movesText, "Remaining moves: %d", total_moves);
            renderText(renderer, font, movesText, MAZE_OFFSET_X + 130, TEXT_OFFSET_Y, black);
        }

        sprintf(movesText, "Remaining moves: %d", total_moves);
        renderText(renderer, font, movesText, MAZE_OFFSET_X + 130, TEXT_OFFSET_Y, black);

        // WASD control labels
        renderText(renderer, font, "Controls:", MAZE_OFFSET_X + 210, KEY_GUIDE_Y - 30, black);
        renderText(renderer, font, "W", MAZE_OFFSET_X + 250, KEY_GUIDE_Y + 10, black);
        renderText(renderer, font, "A", MAZE_OFFSET_X + 203, KEY_GUIDE_Y + 50, black);
        renderText(renderer, font, "S", MAZE_OFFSET_X + 253, KEY_GUIDE_Y + 50, black);
        renderText(renderer, font, "D", MAZE_OFFSET_X + 303, KEY_GUIDE_Y + 50, black);

        SDL_RenderPresent(renderer);

        first_run = 1;
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
