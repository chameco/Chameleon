#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <map>
#include <boost/python.hpp>
#include <boost/python/stl_iterator.hpp>
namespace chameleon {

	class Event {
		public:
			Event(const std::string &n, boost::python::object d);
			std::string getName() {return name;}
			void setName(const std::string &name_) {name = name_;}
			boost::python::object getData() {return data;}
			void setData(boost::python::object d) {data = d;}

		private:
			std::string name;
			boost::python::object data;
	};

	class Listener {
		public:
			Listener();
			void notify(Event &e);
			void setResponse(const std::string &n, boost::python::object c);

		private:
			std::map<std::string, boost::python::object> responses;
	};

	class Manager {
		public:
			Manager();
			void alert(Event &e);
			void reg(const std::string &n, Listener &l);

		private:
			std::map<std::string, boost::python::list> listeners;
	};
}
#endif
