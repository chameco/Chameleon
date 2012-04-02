#define PYTHON_BUILD
#include <boost/python.hpp>
#include "cham.h"
#include <string>
using namespace boost::python;
using namespace cham::event;
//using namespace cham::draw;
BOOST_PYTHON_MODULE(chameleon)
{
	class_<event>("event", init<std::string, boost::python::object>())
		.add_property("name", &event::getName, &event::setName)
		.add_property("data", &event::getData, &event::setData)
	;
	class_<python_manager>("manager", init<>())
		.def("alert", &python_manager::alert)
		.def("reg", &python_manager::reg)
		.def("cleanreg", &python_manager::cleanreg)
		.def("unregister", &python_manager::unregister)
	;
	class_<python_listener>("listener", init<>())
		.def("alert", &python_listener::alert)
		.def("setResponse", &python_listener::setResponse)
		.def("setManager", &python_listener::setManager)
	;
/*
	class_<rect>("rect", init<int, int, int, int>())
		.def("setCenter", &rect::setCenter)
	;
	void (surface::*blit1)(surface *, rect *) = &surface::blit;
	void (surface::*blit2)(surface *, rect *, rect *) = &surface::blit;
	void (surface::*fill1)(rect *, int) = &surface::fill;
	void (surface::*fill2)(int) = &surface::fill;
	class_<surface>("rect", init<int, int>())
		.def(init<const char *>())
		.def(init<>())
		.def("blit", blit1)
		.def("blit", blit2)
		.def("fill", fill1)
		.def("fill", fill2)
		.def("setColorKey", &surface::setColorKey)
	;
	void (group::*clear1)(surface *, surface *) = &group::clear;
	void (group::*clear2)(surface *, boost::function<void (surface *dest, rect *area)>) = &group::clear;
	class_<group>("group", init<>())
		.def("update", &group::update)
		.def("tick", &group::tick)
		.def("sprites", &group::sprites)
		.def("copy", &group::copy)
		.def("add", &group::add)
		.def("remove", &group::remove)
		.def("has", &group::has)
		.def("draw", &group::draw)
		.def("clear", clear1)
		.def("clear", clear2)
		.def("empty", &group::empty)
	;
	class_<sprite>("sprite", init<>())
		.def("add", &sprite::add)
		.def("remove", &sprite::remove)
		.def("kill", &sprite::kill)
		.def("alive", &sprite::alive)
		.def("groups", &sprite::groups)
		.add_property("image", &sprite::getImage, &sprite::setImage)
		.add_property("rect", &sprite::getRect, &sprite::setRect)
		.def("setUpdate", &sprite::setUpdate)
		.def("setTick", &sprite::setTick)
	;
*/
}
