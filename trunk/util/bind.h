#ifndef BIND_H
#define BIND_H
#define BIND_BEGIN \
class _bind_func{public: virtual void operator()(){}}
#define BIND_ARGS0 \
class _bind_func_usable : public _bind_func{public: virtual R operator()(){
namespace cham{
    namespace util{
        BIND_BEGIN;
        template<class R>
    }
}
#endif
