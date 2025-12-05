main:
	gcc -Wall -g -o test tester.c -Lbuild/ -lslang_modules -lslang  -lm -Wl,-rpath,build
	gcc -Wall -g -o slang slang.c -Lbuild/ -lslang_modules -lslang  -lm -Wl,-rpath,build
