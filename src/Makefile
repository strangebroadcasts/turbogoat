CC	= /opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j

SPRITES = sprites/player.o sprites/bullet.o sprites/enemy.o

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

main.gb: main.o $(SPRITES)
	$(CC) -o main.gb main.o $(SPRITES)

clean:
	rm -f *.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm