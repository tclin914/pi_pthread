pi: pi.c
	gcc $< -o $@ -lm -pthread
