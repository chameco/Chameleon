#ifndef DRAW_H
#define DRAW_H
#include "SDL/SDL.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
SDL_Rect _origin;
#define origin (&_origin)
struct _updateCallback{
    template<class T>
    void operator()(T val){
        val->update();
    }
};

struct _tickCallback{
    template<class T>
    void operator()(T val){
        val->tick();
    }
};

namespace cham{
    namespace draw{
		SDL_Event getSDLEvent(){
			SDL_Event t;
			int i = SDL_PollEvent(&t);
			if (i) {return t;}
			else {return NULL;}
		}
		std::string getSDLKeyName(SDL_Key key){
			return SDL_GetKeyName(key);
		}
		class rect{
			public:
				rect(int x, int y, int width, int height){//x and y of topleft corner.
					baserect.x = x;
					baserect.y = y;
					baserect.w = width;
					baserect.h = height;
				}
				SDL_Rect *base(){
					return &baserect;
				}
				void setCenter(int x, int y){
					int offsetx, offsety;
					offsetx = x - (baserect.x + (baserect.w / 2));
					offsety = y - (baserect.y + (baserect.h / 2));
					baserect.x += offsetx;
					baserect.y += offsety;
				}
			private:
				SDL_Rect baserect;
		};
        class surface{
			public:
				surface(int width, int height){
					Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
					rmask = 0xff000000;
					gmask = 0x00ff0000;
					bmask = 0x0000ff00;
					amask = 0x000000ff;
#else
					rmask = 0x000000ff;
					gmask = 0x0000ff00;
					bmask = 0x00ff0000;
					amask = 0xff000000;
#endif
					SDL_Surface *t = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, rmask, gmask, bmask, amask);
					surf = SDL_DisplayFormat(t);
					SDL_FreeSurface(t);
				}
				surface(const char *filename){// We use C-style strings here because SDL likes them.
					SDL_Surface *t = SDL_LoadBMP(filename);
					surf = SDL_DisplayFormat(t);
					SDL_FreeSurface(t);
				}
				surface(){
					surf = SDL_GetVideoSurface();
				}
				
				~surface(){
					SDL_FreeSurface(surf);
				}
				SDL_Surface *base(){
					return surf;
				}
				void blit(const surface &source, rect dest, rect area){
					SDL_BlitSurface(source.base(), area.base(), surf, dest.base());
				}
				void blit(const surface &source, rect dest){
					SDL_BlitSurface(source.base(), NULL, surf, dest.base());
				}
				void fill(rect dest, int color){
					SDL_FillRect(surf, destbase(), color);
				}
				void fill(int color){
					SDL_FillRect(surf, NULL, color);
				}
				void setColorKey(int color){//Set the transparent color.
					SDL_SetColorKey(surf, (SDL_SRCCOLORKEY | SDL_RLEACCEL), color);
				}
			private:
				SDL_Surface *surf;
		};
        template<class T>
        class _group{
            public:
                _group(){
                    setTickCallback(_tickCallback());
                    setUpdateCallback(_updateCallback());
                }
                void update(){contains.apply(updateCallback);}
                void tick(){contains.apply(tickCallback);}
                cham::util::set<T> sprites(){return contains;}
                _group<T> copy(){return *this;}
                void add(T val){contains.add(val);}
                void remove(T val){contains.remove(val);}
                bool has(T val){return contains.in(val);}
                void draw(const surface &dest){
                    for (int counter = 0; counter < contains.size(); counter++){
                        dest.blit(contains[counter]->getImage(), contains[counter]->getRect());
                    }
                }
                void clear(const surface &dest, const surface &background){
                    for (int counter = 0; counter < prevdraw.size(); counter++){
                        dest->blit(background, prevdraw[counter]);
                    }
                }
                void clear(const surface &dest, boost::function<void (const surface &dest, rect area)> callb){
                    for (int counter = 0; counter < prevdraw.size(); counter++){
                        callb(dest, prevdraw[counter]);
                    }
                }
                void empty(){contains.empty();}
            private:
                void setUpdateCallback(boost::function<void (T val)> func){updateCallback = func;};
                void setTickCallback(boost::function<void (T val)> func){tickCallback = func;};
                cham::util::set<T> contains;
                cham::util::set<rect> prevdraw;
                boost::function<void (T val)> updateCallback;
                boost::function<void (T val)> tickCallback;
        };
        class sprite{
            public:
                sprite(){}
                void add(_group<sprite *> *g){
                    g->add(this);
                    _groups.add(g);
                }
                void remove(_group<sprite *> *g){
                    g->remove(this);
                    _groups.remove(g);
                }
                void kill(){_groups.apply(boost::bind(&sprite::killCallback, this, _1));}
                bool alive(){return _alive;}
                cham::util::set<_group<sprite *> *> groups(){return _groups;}
                void setImage(const surface &i){image = i;}
                void setRect(rect r){brect = r;}
                surface getImage(){return image;}
                rect getRect(){return brect;}
                void setUpdate(boost::function<void ()> c){update = c;}
                void setTick(boost::function<void ()> c){tick = c;}
                boost::function<void ()> update;
                boost::function<void ()> tick;
            private:
                surface &image;
                rect brect;
                bool _alive;
                cham::util::set<_group<sprite *> *> _groups;
                void killCallback(_group<sprite *> *val){
                    val->remove(this);
                    _groups.remove(val);
                }
        };
        typedef _group<sprite *> group;
        typedef boost::function<void ()> callback;
    }
}
#endif
