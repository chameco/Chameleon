import os
try:
	from setuptools.core import setup
except ImportError:
	from distutils.core import setup
os.system("bjam")
setup(name="Chameleon",
version="1.0",
data_files=[("lib/python2.7/dist-packages", ["chameleon.so"])]
)
