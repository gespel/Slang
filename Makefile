main:
	gcc -Wall -o test tester.c -Lbuild/ -lslang -Wl,-rpath,build
	gcc -Wall -o slang slang.c -Lbuild/ -lslang -Wl,-rpath,build
