comp=clang
src=src/*.c
incl=-Iinclude
out=xmlx
libs=
std=-std=c99

all:
	@$(comp) -o $(out) $(src) $(incl) $(libs) $(std)

debug:
	@$(comp) -o $(out) $(src) $(incl) $(libs) $(std) -g

run:
	@echo "Usage: ./$(out) FILE"
