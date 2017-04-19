Building
===============
##Dependancies
* libconfig-1.5 (1.6 will probably work)

##Using gcc
`gcc -Wall -Wpedantic -Wno-pedantic-ms-format -g main.c cpu.c ram.c errors.c ./2204/copy.c -L<path to libconfig-1.5>/lib/.libs -lconfig -o 2204`
