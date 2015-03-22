#include "event.h"

chameleon::Event::Event(const std::string &n, boost::python::object d) : name(n), data(d) {}

chameleon::Listener::Listener() {}

void chameleon::Listener::notify(chameleon::Event &e) {
	if (responses[e.getName()]) {
		responses[e.getName()](e.getData());
	}
}

void chameleon::Listener::setResponse(const std::string &n, boost::python::object c) {
	responses[n] = c;
}

chameleon::Manager::Manager() {}

void chameleon::Manager::alert(chameleon::Event &e) {
	boost::python::stl_input_iterator<chameleon::Listener> begin(listeners[e.getName()]), end;
	for (; begin != end; begin++){
		(*begin).notify(e);
	}
}

void chameleon::Manager::reg(const std::string &n, chameleon::Listener &l) {
	listeners[n].append(l);
}
