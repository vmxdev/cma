/*
 * cumulative moving average tests
 *
 * Copyright (c) 2019, Vladimir Misyurov
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

static int window = 1024 * 10;
static int data_size = 1024 * 1024;

static void
fill_sin(uint8_t *data)
{
	int i;

	for (i=0; i<data_size; i++) {
		int off;

		off = (sin((double)i / 50000.0) + 2.0) * 3;
		if (off <= 0) {
			off = 1;
		}
		if ((i % off) == 0) {
			/* add some randomness */
			data[i] = rand() % 50;
		} else {
			data[i] = 0;
		}
	}
}

/* constant acceleration */
static void
fill_constacc(uint8_t *data)
{
	double v  = 100.0f;
	double dv = 0.00012;
	int i;

	for (i=0; i<data_size; i++) {
		int off;

		v -= dv;
		off = v;

		if (off <= 0) {
			off = 1;
		}
		if ((i % off) == 0) {
			data[i] = rand() % 50;
		} else {
			data[i] = 0;
		}
	}
}

static double
precise_avg(uint8_t *data, int off)
{
	double sum = 0.0f;
	int i, start, end;

	start = off - window;
	if (start < 0) {
		start = 0;
	}

	end = off;
	if (end > data_size) {
		end = data_size;
	}

	if ((end - start) == 0) {
		return 0.0f;
	}

	for (i=start; i<end; i++) {
		sum += data[i];
	}

	return sum / (end - start);
}

static double
cma_avg_n(double cur, int tmdiff, uint8_t val)
{
	double res;

	res = cur - (double)tmdiff / window * cur + val;
	return res;
}

int
main()
{
	uint8_t *data;
	int i;
	double p_avg, c_avg = 0.0f;
	int prev_i = 0;

	data = malloc(data_size);
	if (!data) {
		perror("malloc() failed");
		return EXIT_FAILURE;
	}

	/* fill data */
	fill_sin(data);
	/*fill_constacc(data);*/

	for (i=0; i<data_size; i++) {
		p_avg = precise_avg(data, i);
		if (data[i]) {
			c_avg = cma_avg_n(c_avg, i - prev_i, data[i]);
			prev_i = i;
		}
		printf("%d\t%f\t%f\n", i, p_avg, c_avg / window);
	}

	free(data);

	return EXIT_SUCCESS;
}

