#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

static int window = 1024 * 10;
static int data_size = 1024 * 1024;


static double
precise_avg(uint8_t *data, int off)
{
	double sum = 0.0f;
	int i, start, end;

	start = off;
	if (off < 0) {
		start = 0;
	}

	end = off + window;
	if (end > data_size) {
		end = data_size;
	}

	for (i=start; i<end; i++) {
		if (data[i]) {
			sum += 1.0f;
		}
	}

	if ((end - start) == 0) {
		return 0.0f;
	}

	return sum / (end - start);
}

int
main()
{
	uint8_t *data;
	double p_avg;
	int i;

	data = malloc(data_size);
	if (!data) {
		perror("malloc() failed");
		return EXIT_FAILURE;
	}

	/* fill data */
	for (i=0; i<data_size; i++) {
		if ((i % 5) == 0) {
			data[i] = 1;
		} else {
			data[i] = 0;
		}
	}

	for (i=-window; i<data_size; i++) {
		p_avg = precise_avg(data, i);
		printf("%d\t%f\n", i, p_avg);
	}

	free(data);

	return EXIT_SUCCESS;
}

