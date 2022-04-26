app:
	qmake -o build/Makefile ICP-projekt.pro
	make -C build/ -f Makefile
	
run: app
	./build/ICP-projekt
	
doxygen:
	doxygen doc/Doxyfile
	
clean:
	rm -rf build

pack:
	zip -r xmacho12-xlanro00 README.txt Makefile src res ICP-projekt.pro doc/Doxyfile


