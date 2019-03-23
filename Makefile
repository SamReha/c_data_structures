MAKE_PATHS = $(wildcard */)

unit_test :
	for path in $(MAKE_PATHS); do \
		 $(MAKE) -C $$path unit_test; \
	done

clean :
	for path in $(MAKE_PATHS); do \
		$(MAKE) -C $$path clean; \
	done

