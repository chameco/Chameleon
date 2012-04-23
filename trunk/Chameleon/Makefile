CPPINSTALLDIR = /usr/include
PYINSTALLDIR = /usr/lib/python2.7/dist-packages
chameleon.so : wrapper.o
	"g++"    -o "chameleon.so" -Wl,-h -Wl,chameleon.so -shared -Wl,--start-group "wrapper.o" -Wl,-Bstatic  -Wl,-Bdynamic -lutil -lpthread -ldl -lboost_python-py27 -Wl,--end-group -g
wrapper.o : wrapper.cpp
	"g++"  -ftemplate-depth-128 -O0 -fno-inline -Wall -g -fPIC -I"/usr/include/python2.7" -c -o "wrapper.o" "wrapper.cpp"
clean :
	rm -f "wrapper.o" "chameleon.so"
install :
	mkdir -p $(DESTDIR)$(PYINSTALLDIR)
	mkdir -p $(DESTDIR)$(CPPINSTALLDIR)
	cp chameleon.so $(DESTDIR)$(PYINSTALLDIR)
	cp cham.h $(DESTDIR)$(CPPINSTALLDIR)
	cp -r chameleon $(DESTDIR)$(CPPINSTALLDIR)
builddeb:
	# build the source package in the parent directory
	# then rename it to project_version.orig.tar.gz
	make source
	# build the package
	dpkg-buildpackage -i -I -rfakeroot
source :
	tar -cf ../chameleon_1.0.orig.tar.gz chameleon wrapper.cpp cham.h
