#ifndef GEN_H
#define GEN_H
#include <string>
#include <boost/lexical_cast.hpp>
namespace cham{
    namespace util{
        inline std::string constr(int val){return boost::lexical_cast<std::string>(val);}
        inline int conint(std::string val){return boost::lexical_cast<int>(val);}
        template<class T>
        struct cell{
            cell<T> *left;
            cell<T> *right;
            T data;
        };
        template<class T>
        inline cell<T> *cons(cell<T> *base, cell<T> *val){
            base->right = val;
            return base;
        }
        template<class T>
        inline cell<T> *car(cell<T> *base){return base;}
        template<class T>
        inline cell<T> *cdr(cell<T> *base){return base->right;}
    }
}
#endif
