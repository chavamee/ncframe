all:
	make -C ./src all
dev:
	make -C ./src dev
install:
	make -C ./src install
uninstall:
	make -C ./src uninstall
clean:
	make -C ./src clean
	make -C ./unit_test clean
test:
	make -C ./unit_test all
