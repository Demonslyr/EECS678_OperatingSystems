# Add the dp_asymmetric and dp_waiter targets to all as you implement
# them
#
STUDENT_ID = "2213976"
MY_LAST_NAME = "murtha"

all: sorter # dp_asymmetric dp_waiter

sorter: sorter.c
	gcc -g sorter.c -lpthread -lm -o sorter
    
clean:
	rm -f sorter

tar: 
	make clean
	mkdir $(STUDENT_ID)-lab-08
	cp Makefile sorter.c $(STUDENT_ID)-lab-08/
	tar cvzf $(STUDENT_ID)-lab-08.tar.gz $(STUDENT_ID)-lab-08
	rm -rf $(STUDENT_ID)-lab-08

