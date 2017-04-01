.phony:all clean

srcs=$(shell ls *.c)
target=$(srcs:.c=)



all:$(target)
	echo "building with src ${srcs}"
	echo "target : ${target}"

%:%.c
	gcc -g -o $< -lpthread
