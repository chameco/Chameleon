#include <cmath>
#include <stdarg.h>
#include "/home/samuel/Programs/Chameleon/util/set.h"
using namespace std;
namespace cham{
    namespace space{
        class point {
            public:
                point(double ax, double ay, double az){
                    x = ax;
                    y = ay;
                }
                double getx(){return x;}
                double gety(){return y;}
                double getz(){return z;}
                bool operator==(point o){
                    if (o.x == x && o.y == y && o.z == z){
                        return 1;
                    }
                    return 0;
                }
            private:
                double x;
                double y;
                double z;
        };
        class line {
            public:
                line(point *s, point *f){
                    start = s;
                    finish = f;
                }
                double getlen(){return sqrt((pow(start->getx(), 2) - pow(finish->getx(), 2)) + (pow(start->gety(), 2) - pow(finish->gety(), 2)) + (pow(start->getz(), 2) - pow(finish->getz(), 2)));}
                point *getmidpoint(){return new point((start->getx() - finish->getx()) / 2, (start->gety() - finish->gety()) / 2, (start->getz() - finish->getz()) / 2);}
                point *getstart(){return start;}
                point *getfinish(){return finish;}
                bool operator==(line o){
                    if (o.start == start && o.finish == finish){
                        return 1;
                    }
                    return 0;
                }
            private:
                point *start;
                point *finish;
        };
        class plane {
            public:
                plane(int sc, line *edge1, line *edge2, line *edge3, ...){
                    edgecount = sc;
                    edges.add(edge1);
                    edges.add(edge2);
                    edges.add(edge3);
                    va_list args;
                    va_start(args, edge3);
                    for (int counter = 0; counter < edgecount - 3; counter++){
                        edges.add(va_arg(args, line *));
                    }
                va_end(args);
                }
                line *getedge(int s){return edges[s];}
                cham::util::set<line *> getedges(){return edges;}
                int getedgecount(){return edgecount;}
                bool operator==(plane o){
                    if (edges == o.getedges()){
                        return 1;
                    }
                    return 0;
                }
            private:
                cham::util::set<line *> edges;
                int edgecount;
        };
    }
}
