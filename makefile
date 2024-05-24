keys.out: keys.o utils.o prime.o modulo.o euklides.o extended_euklides.o
	gcc -no-pie -ggdb -o keys.out keys.o utils.o prime.o modulo.o euklides.o extended_euklides.o

keys.o: keys.asm
	nasm -f elf64 -g -F dwarf keys.asm -l keys.lst

euklides.o: euklides.asm
	nasm -f elf64 -g -F dwarf euklides.asm -l euklides.lst

extended_euklides.o: extended_euklides.asm
	nasm -f elf64 -g -F dwarf extended_euklides.asm -l extended_euklides.lst

modulo.o: modulo.asm
	nasm -f elf64 -g -F dwarf modulo.asm -l modulo.lst

power.o: power.asm
	nasm -f elf64 -g -F dwarf power.asm -l power.lst

prime.o: prime.asm
	nasm -f elf64 -g -F dwarf prime.asm -l prime.lst

utils.o: utils.c
	gcc -ggdb -c -o utils.o utils.c
