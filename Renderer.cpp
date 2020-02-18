#include "Renderer.h"

Renderer::Renderer(int screenWidth, int screenHeight) {
    mScreenWidth = screenWidth;
    mScreenHeight = screenHeight;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL Could not be initialized. " << SDL_GetError() << std::endl;
    }

    // Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        std::cout << "Warning: Linear texture filtering not enabled." << std::endl;
    }
    
    // Create Window
    window = SDL_CreateWindow("Multiplayer Pong", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, mScreenWidth,
                               mScreenHeight, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        std::cerr << "Window could not be created." << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        std::cerr << "Renderer could not be created. " << SDL_GetError() << std::endl;
    }

    // Initialize renderer color
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Initialize PNG Loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not be initialized. " << IMG_GetError() << std::endl;
    }    
}

Renderer::~Renderer() {
    //TODO : Free loaded images
    
    //Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}
