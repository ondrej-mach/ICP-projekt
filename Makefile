app:
	qmake -o build/qMakefile icp-projekt.pro
	make -C build/ -f build/qMakefile
	
run: app
	./build/icp-projekt
	
doxygen:
	doxygen doc/Doxyfile
	
clean:
	rm -f icp-projekt *.o qMakefile

zip:
	zip -r xmacho12-xlanro00 README.txt Makefile src res icp-projekt.pro doc/Doxyfile


