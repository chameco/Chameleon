#define PYTHON_BUILD
#include "event.h"
#include <boost/python.hpp>
#include <string>
using namespace boost::python;
using namespace chameleon;
BOOST_PYTHON_MODULE(chameleon)
{
	class_<Event>("Event", init<const std::string &, boost::python::object>())
		.add_property("name", &Event::getName, &Event::setName)
		.add_property("data", &Event::getData, &Event::setData)
	;
	class_<Manager>("Manager", init<>())
		.def("alert", &Manager::alert)
		.def("reg", &Manager::reg)
	;
	class_<Listener>("Listener", init<>())
		.def("notify", &Listener::notify)
		.def("setResponse", &Listener::setResponse)
	;
}
