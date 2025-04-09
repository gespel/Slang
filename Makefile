main:
	gcc -Wall -o test tester.c -Lbuild/ -lslang -Wl,-rpath,build
