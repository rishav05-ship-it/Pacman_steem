game.tos: Game.o EVENTS.o MODEL.o pos_sta.o RASTER.o RENDERER.o BITMAPS.o 
	cc68x -g Game.o EVENTS.o MODEL.o pos_sta.o RASTER.o RENDERER.o BITMAPS.o -o game.tos

Game.o: Game.c 
	cc68x -g -c Game.c
	
EVENTS.o: EVENTS.c EVENTS.h
	cc68x -g -c EVENTS.c

MODEL.o: MODEL.c MODEL.h
	cc68x -g -c MODEL.c
	
pos_sta.o: pos_sta.c pos_sta.h
	cc68x -g -c pos_sta.c

BITMAPS.o: BITMAPS.c BITMAPS.h
	cc68x -g -c BITMAPS.c

RASTER.o: RASTER.c RASTER.h
	cc68x -g -c RASTER.c

RENDERER.o: RENDERER.c RENDERER.h
	cc68x -g -c RENDERER.c

clean:
	remove.tos
