app:
	qmake -o build/Makefile ICP-projekt.pro
	make -C build/ -f Makefile
	
run: app
	./build/ICP-projekt
	
doxygen:
	doxygen doc/Doxyfile
	
clean:
	rm -rf build
	rm -rf /doc/html

pack:
	zip -r 1-xmacho12-xlanro00.zip \
	README.txt \
	Makefile \
	src \
	res \
	inc \
	ICP-projekt.pro \
	doc/Doxyfile \
	examples


