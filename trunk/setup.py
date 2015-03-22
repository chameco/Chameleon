#Copyright 2010-2012 Samuel Breese, alias chameco
from setuptools import setup, Extension
setup(
    name="chameleon",
    version="1.0",
    description="C++ and Python library used to implement a listener-manager event system.",
    long_description="""\
Chameleon is a library that takes the concept of event-based coding to a whole new level. Each
event that is raised can be handled by multiple listener classes, allowing for things such as
asynchronous network servers to be implemented with ease, and letting you add new listeners to
your existing codebase without touching your old code. This comes in handy when writing scalable
servers, games with plugins, etc. In addition, there is no main loop (you're responsible for
raising all of the events), so it can be integrated with existing systems like Twisted, GLUT,
GTK+, and Qt.""",
    author="Samuel Breese",
    author_email="sbreese@xitol.net",
    url="https://github.com/chameco/Chameleon",
    ext_modules = [Extension("chameleon", ["wrapper.cpp", "src/event.cpp"], include_dirs = ["include"], libraries=["boost_python"])],
)
