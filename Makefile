CC = clang++

.PHONY: lib tests clean

all: lib tests

lib: 
	@cd src;\
	make

tests:
	@cd tests;\
	make

clean:
	@cd src;\
	make clean;
	@echo
	@cd tests;\
	make clean;