#include<stdio.h>
#include<SDL2/SDL.h>
#include<complex.h>
#include<math.h>
 
#define WIDTH 900
#define HEIGHT 600 
#define COLOR_WHITE 0xffffff
#define COLOR_BLACK 0x000000
#define MANDEL_LIMIT 1000
#define OFFSET_X 75
double cabs(double _Complex num){
    return sqrt(pow(creal(num), 2) + pow(cimag(num), 2));
}

int check_mandelbrot(double real,double imag){
    double _Complex c= real + I*imag;
    double _Complex z=0;
    
    for(int i=0;i<25;++i){

        z=cpow(z,2) + c;
        if(cabs(z)>2) return 0;
        // z>2 gets out of bound to inf
    }
    // Is z exceeding a limit?
    return cabs(z)<MANDEL_LIMIT;
}

void  visualize_mandelbrot_screen(SDL_Surface *surface, double zoomin,double centerX, double centerY){
     Uint32 *pixels = (Uint32 *)surface->pixels;
     // used pixel buffer to inc performance
    for(int x=0;x < WIDTH; ++x){
        for(int y=0;y < HEIGHT; ++y){
            double r =((double)(x - WIDTH/2 - OFFSET_X))/zoomin + centerX;
            double i =-((double)(y - HEIGHT/2))/zoomin + centerY;
            if(check_mandelbrot(r, i)){
                // SDL_Rect pixel = (SDL_Rect) {x, y, 1, 1};
                // SDL_FillRect(surface, &pixel, COLOR_WHITE);
                pixels[y * WIDTH + x] = COLOR_WHITE;
            }
        }
    }
}




int main(){
    printf("Mandlebrot\n");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Mandlebrot Set",
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        0
    );

     int dragging = 0;
    int lastMouseX, lastMouseY;
    
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    int running=1;
    double zoomin = 200;      // starting zoom
    double centerX = -0.5;  // focus point X
    double centerY = 0;     // focus point Y
   SDL_Rect erase_rect = (SDL_Rect){0,0,WIDTH,HEIGHT};
    while(running){
       SDL_Event event;
       while(SDL_PollEvent(&event)){
          switch(event.type){
              case SDL_QUIT:
                running=0;
                break;

                
          }

          
       }
    //    SDL_Rect rect={0,0,100,100};
    //    SDL_FillRect(surface, &rect, COLOR_WHITE);
       SDL_FillRect(surface,&erase_rect, COLOR_BLACK);
       visualize_mandelbrot_screen(surface, zoomin, centerX, centerY);
       SDL_UpdateWindowSurface(window);
        zoomin *= 1.02; 
         centerY -= 0.005;
         centerX -= 0.005;
       SDL_Delay(16);
       
    }
    // SDL_Delay(5000);
}
