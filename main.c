#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#define COLS 128
#define ROWS 64
#define CELL_SIZE 10



void fillArray(int arr[COLS][ROWS]);
void printArray(int arr[COLS][ROWS]);
void drawGrid(int arr[COLS][ROWS], SDL_Renderer *renderer);
void cycleLife(int arr[COLS][ROWS], int arr2[COLS][ROWS], SDL_Renderer *renderer);

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        "Mein Spiel",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 640,
        0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,0);

    int running = 1;
    SDL_Event event;

    int arr[COLS][ROWS];
    int next[COLS][ROWS];
    fillArray(arr);
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    int delay = 50;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == SDL_SCANCODE_UP) delay += 10;
                if (event.key.keysym.scancode == SDL_SCANCODE_DOWN && delay > 0) delay -= 10;
            }
        }
        drawGrid(arr, renderer);
        if (keys[SDL_SCANCODE_R]) fillArray(arr);
        SDL_Delay(delay);
        cycleLife(arr, next, renderer);
        SDL_RenderPresent(renderer);
    }



    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void fillArray(int arr[COLS][ROWS]) {
    int x,y;

    for (x = 0; x < COLS; x++) {
        for (y = 0; y < ROWS; y++) {
            arr[x][y] = rand() % 2;
        }
    }
}

void printArray(int arr[COLS][ROWS]) {
    int x,y;
    for (x = 0; x < COLS; x++) {
        for (y = 0; y < ROWS; y++) {
            printf("%d ", arr[x][y]);
        }
    }
}

void drawGrid(int arr[COLS][ROWS], SDL_Renderer *renderer) {
    SDL_Rect rect;
    rect.x = CELL_SIZE;
    rect.y = CELL_SIZE;
    rect.w = CELL_SIZE;
    rect.h = CELL_SIZE;

    int x,y;

    for (x = 0; x < COLS; x++) {
        for (y = 0; y < ROWS; y++) {
            rect.x = x * CELL_SIZE;
            rect.y = y * CELL_SIZE;
            if (arr[x][y] == 1) {
                SDL_SetRenderDrawColor(renderer,255,255,255,255);
            }else {
                SDL_SetRenderDrawColor(renderer,0,0,0,255);
            }
            SDL_RenderFillRect(renderer,&rect);
        }
    }
}

int countNeighbors(int arr[COLS][ROWS], int x, int y) {
    int links  = (x - 1 + COLS) % COLS;
    int rechts = (x + 1) % COLS;
    int oben   = (y - 1 + ROWS) % ROWS;
    int unten  = (y + 1) % ROWS;

    int count = 0;
    if (arr[rechts][y] == 1) count++;
    if (arr[links][y] == 1) count++;
    if (arr[x][unten] == 1) count++;
    if (arr[x][oben] == 1) count++;
    if (arr[rechts][unten] == 1) count++;
    if (arr[links][oben] == 1) count++;
    if (arr[links][unten] == 1) count++;
    if (arr[rechts][oben] == 1) count++;

    return count;
}

void cycleLife(int arr[COLS][ROWS], int arr2[COLS][ROWS], SDL_Renderer *renderer) {
    int x,y, neighbors;
    for (x = 0; x < COLS; x++) {
        for (y = 0; y < ROWS; y++) {
            neighbors = countNeighbors(arr, x, y);
            if (neighbors < 2) arr2[x][y] = 0;
            if (arr[x][y] == 1 && (neighbors == 2 || neighbors == 3)) arr2[x][y] = 1;
            if (arr[x][y] == 0 && neighbors == 3) arr2[x][y] = 1;
            if (neighbors > 3) arr2[x][y] = 0;
        }
    }
    for (x = 0; x < COLS; x++)
        for (y = 0; y < ROWS; y++)
            arr[x][y] = arr2[x][y];
}