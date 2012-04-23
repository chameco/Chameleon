#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <map>
#include "set.h"
#include <boost/array.hpp>
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#ifdef PYTHON_BUILD
#include <boost/python.hpp>
#endif
namespace cham{
	namespace event{
		typedef boost::function<void (
#ifdef PYTHON_BUILD
			boost::python::object
#else
			std::string
#endif
			d)> callback;
		class event{
			public:
				event(std::string n,
#ifdef PYTHON_BUILD 
					boost::python::object
#else
					std::string
#endif
					 d){
					name = n;
					data = d;
				}
				std::string getName(){return name;}
				void setName(std::string name_){name = name_;}
#ifdef PYTHON_BUILD
				boost::python::object
#else
				std::string
#endif
				getData(){return data;}
				void setData(boost::python::object data_){data = data_;}
			private:
				std::string name;
#ifdef PYTHON_BUILD
				boost::python::object
#else
				std::string
#endif
				data;
		};
		template <class T> // We need this so we can create a manager reference in listener.
		class _manager{
			public:
				_manager(){}
				void alert(event e){
					if (listeners[e.getName()].size()){
						listeners[e.getName()].apply(boost::bind(&T::alert, _1, e));
					}
				}
				void reg(std::string n, T *l){
					l->setManager(this);
					listeners[n].add(l);
				}
				void cleanreg(std::string n, T *l){
					l->setManager(this);
					listeners[n].empty();
					listeners[n].add(l);
				}
				void unregister(std::string n, T *l){listeners[n].remove(l);}
			private:
				std::map<std::string, cham::util::set<T *> > listeners;
		};
		template <class T> // T is a function type: either boost::function or boost::python::object.
		class _listener{
			public:
				_listener(){}
				void alert(event e){
					if (responses[e.getName()])
						responses[e.getName()](e.getData());
				}
				void setResponse(std::string n, T c){responses.insert(make_pair(n, c));}
				void setManager(_manager<_listener<T> > *m){manager = m;}
			private:
				std::map<std::string, T> responses;
				_manager<_listener<T> > *manager;
		};
		typedef _listener<callback> listener;
		typedef _manager<listener> manager;
#ifdef PYTHON_BUILD
		typedef _listener<boost::python::object> python_listener;
		typedef _manager<python_listener> python_manager;
#endif
	}
}
#endif