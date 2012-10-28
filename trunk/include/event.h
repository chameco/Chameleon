#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <map>
//#include "set.h"
#include <list>
//#include <boost/array.hpp>
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#ifdef PYTHON_BUILD
#include <boost/python.hpp>
#include <boost/python/stl_iterator.hpp>
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
				void setData(
#ifdef PYTHON_BUILD
				boost::python::object
#else
				std::string
#endif
				data_){data = data_;}
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
#ifdef PYTHON_BUILD
                    boost::python::stl_input_iterator<T> begin(listeners[e.getName()]), end;
					for (; begin != end; begin++){
						(*begin).attr("_alert")(e);
					}
#else
					for (typename std::list<T>::iterator it = listeners[e.getName()].begin(); it != listeners[e.getName()].end(); it++){
						(*it)->alert(e);
					}
#endif
					//listeners[e.getName()].apply(boost::bind(&T::alert, _1, e));
				}
				void reg(std::string n, T l){
#ifdef PYTHON_BUILD
					listeners[n].append(l);
#else
					listeners[n].push_back(l);
#endif
				}
#ifdef PYTHON_BUILD
                void unregister(std::string n, T l){
					listeners[n].remove(l);
				}
#endif
			private:
#ifdef PYTHON_BUILD
		        std::map<std::string, boost::python::list> listeners;
#else
                std::map<std::string, std::list<T> > listeners;
#endif
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
			private:
				std::map<std::string, T> responses;
		};
		typedef _listener<callback> listener;
		typedef _manager<listener *> manager;
#ifdef PYTHON_BUILD
		typedef _listener<boost::python::object> python_listener;
		typedef _manager<boost::python::object> python_manager;
#endif
	}
}
#endif
