app:
	qmake -o qMakefile icp-projekt.pro
	make -f qMakefile
	
run: app
	./icp-projekt
	
doxygen:
	doxygen doc/Doxyfile
	
clean:
	rm -f icp-projekt *.o qMakefile

zip:
	zip -r xmacho12-xlanro00 README.txt Makefile src res icp-projekt.pro doc/Doxyfile


