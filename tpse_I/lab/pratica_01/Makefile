all: app

CC= arm-none-eabi-gcc
ASM=arm-none-eabi-as
LD=arm-none-eabi-ld
#CC= gcc

app: start.o main.o 
	$(LD) obj/start.o obj/main.o -T src/memmap.ld -o bin/app.elf

start.o: src/start.s
	$(ASM) src/start.s -o obj/start.o 
main.o: src/main.c
	$(CC) -c src/main.c -Iinc -o obj/main.o

clean:
	rm obj/*.o bin/app.elf
