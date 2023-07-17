CHAINPATH=
CHAIN=$(CHAINPATH)arm-none-eabi
CFLAGS=-std=c99 -Wall -mfpu=neon -mhard-float -mcpu=cortex-a8
AFLAGS=-mfpu=neon
IPATH=-Iinc/
SRC=src/
OBJ=obj/
BIN=bin/

all: app

app: start.o interrupt.o timer.o uart.o main.o
	$(CHAIN)-ld $(OBJ)start.o $(OBJ)interrupt.o $(OBJ)timer.o $(OBJ)uart.o $(OBJ)main.o -T $(SRC)memmap.ld -o $(OBJ)main.elf
	$(CHAIN)-objcopy $(OBJ)main.elf $(BIN)spl.boot -O binary
	cp $(BIN)spl.boot /tftpboot/appTimer.bin

start.o: $(SRC)start.s
	$(CHAIN)-as $(AFLAGS) $(SRC)start.s -o $(OBJ)start.o

interrupt.o: $(SRC)interrupt.c
	$(CHAIN)-gcc $(CFLAGS) $(IPATH) -c $(SRC)interrupt.c -o $(OBJ)interrupt.o

timer.o: $(SRC)timer.c
	$(CHAIN)-gcc $(CFLAGS) $(IPATH) -c $(SRC)timer.c -o $(OBJ)timer.o

uart.o: $(SRC)uart.c
	$(CHAIN)-gcc $(CFLAGS) $(IPATH) -c $(SRC)uart.c -o $(OBJ)uart.o

main.o: $(SRC)main.c
	$(CHAIN)-gcc $(CFLAGS) $(IPATH) -c $(SRC)main.c -o $(OBJ)main.o
                                        
copy:
	cp $(BIN)spl.boot /tftpboot/appTimer.bin

clean:
	rm -rf $(OBJ)*.o
	rm -rf $(OBJ)*.elf
	rm -rf $(BIN)*.boot

dump:
	$(CHAIN)-objdump -D $(OBJ)main.elf
