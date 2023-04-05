src = $(wildcard ./src/*.c)
myopt = -Wall -g -I ./include -lpthread
target = server

ALL:$(target)

$(target):$(src)
	gcc $^ -o $@ $(myopt)

clean:
	-rm -rf $(target)

.PHONY: ALL clean
