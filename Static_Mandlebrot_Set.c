#include<stdio.h>
#include<SDL2/SDL.h>
#include<complex.h>
#include<math.h>
 
#define WIDTH 900
#define HEIGHT 600 
#define COLOR_WHITE 0xffffff
#define COLOR_BLACK 0x000000
#define MANDEL_LIMIT 1000
#define ZOOM 200
#define OFFSET_X 75
double cabs(double _Complex num){
    return sqrt(pow(creal(num), 2) + pow(cimag(num), 2));
}

int check_mandelbrot(double real,double imag){
    double _Complex c= real + I*imag;
    double _Complex z=0;
    
    for(int i=0;i<30;++i){

        z=cpow(z,2) + c;
    }
    // Is z exceeding a limit?
    return cabs(z)<MANDEL_LIMIT;
}

void  visualize_mandelbrot_screen(SDL_Surface *surface){
    for(int x=0;x < WIDTH; ++x){
        for(int y=0;y < HEIGHT; ++y){
            double r =((double)(x - WIDTH/2 - OFFSET_X))/ZOOM;
            double i =-((double)(y - HEIGHT/2))/ZOOM;
            if(check_mandelbrot(r, i)){
                SDL_Rect pixel = (SDL_Rect) {x, y, 1, 1};
                SDL_FillRect(surface, &pixel, COLOR_WHITE);
                
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
    
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    int running=1;
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
       visualize_mandelbrot_screen(surface);
       SDL_UpdateWindowSurface(window);
       SDL_Delay(1000);
       
    }
    // SDL_Delay(5000);
}
