target=game
obj1=game.o
obj2=wall.o
obj3=snake.o
obj4=food.o

target_rwlock=game_rwlock
obj_rwlock=game_rwlock.o

target_sem=game_sem
obj_sem=game_sem.o

$(target_sem) : $(obj_sem) $(obj2) $(obj3) $(obj4)
	g++ $^ -o $@ -lpthread

$(target) : $(obj1) $(obj2) $(obj3) $(obj4)
	g++ -g $^ -o $@ -lpthread 

$(target_rwlock) : $(obj_rwlock) $(obj2) $(obj3) $(obj4)
	g++ $^ -o $@ -lpthread

clean :
	rm -f *.o
