CC = gcc
OBJS = matamikya_order.o matamikya_product.o matamikya.o matamikya_print.o matamikya_main.o matamikya_tests.o
OBJS_AMOUNT_SET = amount_set_str.o amount_set_str_main.o amount_set_str_tests.o
EXEC_NAME = matamikya
DEBUG = -g # now empty, assign -g for debug
CFLAGS = -std=c99 -Wall -pedantic-errors -Werror $(DEBUG)

$(EXEC_NAME): $(OBJS)
	$(CC) $(CFLAGS) $(DEBUG) $(OBJS) -L. -las -lmtm -lm -o $@

amount_set_str: $(OBJS_AMOUNT_SET)
	$(CC) $(CFLAGS) $(DEBUG) $(OBJS) -o $@

amount_set_str.o: amount_set_str.c amount_set_str.h
	$(CC) $(CFLAGS) $(DEBUG) -c -o $@ $<
amount_set_str_main.o: amount_set_str_main.c amount_set_str_tests.h \
 tests/test_utilities.h
	$(CC) $(CFLAGS) $(DEBUG) -c -o $@ $<
amount_set_str_tests.o: amount_set_str_tests.c amount_set_str_tests.h \
 amount_set_str.h tests/test_utilities.h
	$(CC) $(CFLAGS) $(DEBUG) -c -o $@ $<

amount_set.o: amount_set.c amount_set.h
	$(CC) $(CFLAGS) $(DEBUG) -c -o $@ $<
matamikya.o: Matamikya.c Matamikya.h set.h Product.h \
 Order.h Print.h
	$(CC) $(CFLAGS) $(DEBUG) -c -o $@ $<
matamikya_order.o: Order.c Order.h set.h \
 Product.h Matamikya.h
	$(CC) $(CFLAGS) $(DEBUG) -c -o $@ $<
matamikya_print.o: Print.c Print.h
	$(CC) $(CFLAGS) $(DEBUG) -c -o $@ $<
matamikya_product.o: Product.c Product.h Matamikya.h
	$(CC) $(CFLAGS) $(DEBUG) -c -o $@ $<MA
matamikya_main.o: tests/matamikya_main.c tests/matamikya_tests.h \
 tests/test_utilities.h
	$(CC) $(CFLAGS) $(DEBUG) -c -o $@ $<
matamikya_tests.o: tests/matamikya_tests.c tests/matamikya_tests.h \
 Matamikya.h tests/test_utilities.h
	$(CC) $(CFLAGS) $(DEBUG) -c -o $@ $<

clean:
	rm -f $(OBJS) $(EXEC_NAME)

