all:
	$(MAKE) -f Makefile.1xx install
	$(MAKE) -f Makefile.hge install
	$(MAKE) -f Makefile.input install
	$(MAKE) -C Box2D install

1xx:
	$(MAKE) -f Makefile.1xx install
	$(MAKE) -f Makefile.hge install
	$(MAKE) -f Makefile.input install
	$(MAKE) -C Box2D install

3xx:
	$(MAKE) -f Makefile.3xx install
	$(MAKE) -f Makefile.hge install
	$(MAKE) -f Makefile.input install
	$(MAKE) -C Box2D install

clean:
	$(MAKE) -f Makefile.1xx clean
	$(MAKE) -f Makefile.3xx clean
	$(MAKE) -f Makefile.hge clean
	$(MAKE) -f Makefile.input clean
	$(MAKE) -C Box2D clean
