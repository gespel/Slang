main:
	gcc -Wall -g -o test tester.c -Lbuild/ -lslang -Wl,-rpath,build
	gcc -Wall -g -o slang slang.c -Lbuild/ -lslang -lslang_modules -lm -Wl,-rpath,build
