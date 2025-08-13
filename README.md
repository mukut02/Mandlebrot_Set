# Mandlebrot_Set
Algorithm 

Generating relation:
Z_n+1 = Z_n^2 + c (c initiator value)

TO RUN:
gcc mandlebrot.c -o md `sdl2-config --cflags --libs` -lSDL2_ttf -lm  &&./md
