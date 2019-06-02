target=game
obj1=game.o
obj2=wall.o

$(target) : $(obj1) $(obj2)
	g++ $^ -o $@

clean :
	rm -f *.o
