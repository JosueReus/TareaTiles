
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<list>
#include "PersonajeJugador.h"
#include "NPC.h"
#include "Goku.h"
#include "Krillin.h"
#include <stdlib.h>     /* srand, rand */
#include<fstream>
#include<vector>
#include<fstream>


using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*character,*tileset_texture;
SDL_Rect rect_background,rect_character;
int x=0;
int y=0;

class tile
{
public:
    int fuente_x;
    int fuente_y;
    int destino_x;
    int destino_y;
    tile(int fuente_x, int fuente_y, int destino_x, int destino_y)
    {
        this->fuente_x=fuente_x;
        this->fuente_y=fuente_y;
        this->destino_x=destino_x;
        this->destino_y=destino_y;
    }
};
void dibujarTile(SDL_Texture* texture, SDL_Renderer* renderer,int fuente_x, int fuente_y, int destino_x, int destino_y)
{

        SDL_Rect fuente,destino;
        fuente.x=32*fuente_x;
        fuente.y=32*fuente_y;
        fuente.w=32;
        fuente.h=32;


        destino.x=32*destino_x;
        destino.y=32*destino_y;
        destino.w=32;
        destino.h=32;

            SDL_RenderCopy(renderer, texture, &fuente, &destino);
}
void getPos(string path)
{
    ifstream in(path.c_str());
    string str;

    getline(in,str);
    x = atoi(str.c_str());
    cout<<"Lectura: "<<str;
    getline(in,str);
    y = atoi(str.c_str());
    cout<<"Lectura: "<<str<<endl;
    in.close();

    cout<<x<<endl;
    cout<<y<<endl;

}

vector<tile*> cargarTiles(string path)
{
    vector<tile*> tiles;
    ifstream archivo(path.c_str());
    int num;
    for(int destino_y=0;destino_y<8;destino_y++)
    {
    for(int destino_x=0;destino_x<16;destino_x++)
    {
        int fuente_x;
        int fuente_y;
        archivo>>fuente_x;
        archivo>>fuente_y;
        tiles.push_back(new tile(fuente_x,fuente_y,destino_x,destino_y));

    }


    }
    archivo.close();
    return tiles;
}
vector<tile*> cargarTiles2(string path)
{
    vector<tile*> tiles;
    ifstream archivo(path.c_str());
    int num;
    for(int destino_y=0;destino_y<4;destino_y++)
    {
    for(int destino_x=0;destino_x<5;destino_x++)
    {
        int fuente_x;
        int fuente_y;
        archivo>>fuente_x;
        archivo>>fuente_y;
        tiles.push_back(new tile(fuente_x,fuente_y,destino_x,destino_y));

    }


    }
    archivo.close();
    return tiles;
}
void saveTilePos(string path,int x, int y)
{
    ifstream in(path.c_str());

}

int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 500/*WIDTH*/, 250/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0; rect_background.y = 0; rect_background.w = w; rect_background.h = h;

    character = IMG_LoadTexture(renderer, "assets/personaje/down.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character.x = 0;
    rect_character.y = 100;
    rect_character.w = w;
    rect_character.h = h;


    list<Personaje*>personajes;
    getPos("texto.txt");
   personajes.push_back(new PersonajeJugador (x,y,renderer,&personajes));
  //  PersonajeJugador* test=new PersonajeJugador(300,100,renderer,&personajes);

    personajes.push_back(new Goku (110,110,renderer,&personajes));

    personajes. push_back(new Krillin (468,0,renderer,&personajes));
//    personajes.push_back(new Goku (340,0,renderer,&personajes));
    //Goku* gk=new Goku(100,0,renderer,&personajes);


//    personajes.push_back(new Goku (343,0,renderer,&personajes));
//    personajes.push_back(new Goku (218,0,renderer,&personajes));
//    personajes.push_back(new NPC (50,50,renderer,&personajes));
//    personajes.push_back(new NPC (100,200,renderer,&personajes));
//    personajes.push_back(new NPC (100,300,renderer,&personajes));
//    personajes.push_back(new NPC (150,50,renderer,&personajes));
//    personajes.push_back(new NPC (50,150,renderer,&personajes));

    SDL_Texture* tileset_texture = IMG_LoadTexture(renderer, "assets/terrain.png");

    //Main Loop
    int frame=0;
//    int x=6;
//    int y=6;
    vector<tile*>tiles=cargarTiles("Hola.txt");
    vector<tile*>tiles2=cargarTiles2("2.txt");

    while(true)
    {

//        frame++;
//        x++;
//        y++;
//        int radio=24;
//
//        if(frame%25==0){
//            gk->x=test->rectangulo.x;
//            gk->y=test->rectangulo.y;
//            //personajes.push_back(new NPC (100,rand() % 100,renderer,&personajes));
//        }
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
        }

        for(list<Personaje*>::iterator i = personajes.begin();
                i!=personajes.end();
                i++)
            (*i)->logic((Uint8*)SDL_GetKeyboardState( NULL ));
//            gk->logic((Uint8*)SDL_GetKeyboardState( NULL ));
//            test->logic((Uint8*)SDL_GetKeyboardState( NULL ));


        SDL_RenderCopy(renderer, background, NULL, &rect_background);
    for(int i=0;i<tiles.size();i++)
    {

         dibujarTile(tileset_texture, renderer,tiles[i]->fuente_x,tiles[i]->fuente_y,tiles[i]->destino_x,tiles[i]->destino_y);
    }
    for(int i=0;i<tiles2.size();i++)
    {
        dibujarTile(tileset_texture, renderer,tiles2[i]->fuente_x,tiles2[i]->fuente_y,tiles2[i]->destino_x,tiles2[i]->destino_y);
    }
    dibujarTile(tileset_texture,renderer,30,18,0,0);

        for(list<Personaje*>::iterator i = personajes.begin();
                i!=personajes.end();
                i++)
            (*i)->render(renderer);
//            gk->render(renderer);
//            test->render(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(16.66);
    }

	return 0;
}
