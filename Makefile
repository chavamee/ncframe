all:
	make -C ./src all
	make -C ./samples all
dev:
	make -C ./src dev
	make -C ./samples dev
install:
	make -C ./src install
uninstall:
	make -C ./src uninstall
clean:
	make -C ./src clean
	make -C ./unit_test clean
	make -C ./samples clean
test:
	make -C ./unit_test all
sample_test:
	make -C ./samples all
