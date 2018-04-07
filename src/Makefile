CC	= /opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j

.PHONY: all clean build game
all: build

build: main.gb
	cp main.gb ../bin/

%.o:	%.c
	$(CC) -c -o $@ $<

%.s:	%.c
	$(CC) -S -o $@ $<

%.o:	%.s
	$(CC) -c -o $@ $<

main.gb: main.o
	$(CC) -o main.gb main.o

clean:
	rm -f *.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm