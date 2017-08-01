output: new.o
	gcc new.o -o executable -lm
new.o: new.c set.h voronoi.h
	gcc -c new.c
clean:
	rm -f *.o executable
	rm -rf your_data
	mkdir your_data
	cd your_data && mkdir plots
	cp ignore.txt your_data
	cd your_data && cp ignore.txt plots
run:
	./executable
plot:
	cd your_data && gnuplot -e "load 'plot.plt'; exit;"
video:
	cd your_data/plots && ffmpeg -r 20 -f image2 -s 1920x1080 -i img%04d.jpeg -vcodec libx264 -crf 25  -pix_fmt yuv420p test.mp4
