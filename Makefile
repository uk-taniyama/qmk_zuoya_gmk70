build:
	sh ./scripts/build.sh

build-default:
	km=default sh ./scripts/build.sh

build-mine:
	km=mine sh ./scripts/build.sh

clean:
	sh ./scripts/clean.sh

rebuild: clean build

format:
	find keyboards -name "*.[ch]" | xargs clang-format -i
