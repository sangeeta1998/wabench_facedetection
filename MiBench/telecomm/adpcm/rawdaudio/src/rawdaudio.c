/* testd - Test adpcm decoder */

#include "adpcm.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <timestamps.h>
struct adpcm_state state;

#define NSAMPLES 1000

char	abuf[NSAMPLES/2];
short	sbuf[NSAMPLES];

int main() {
    int n;
	timestamp_t start_timestamp= timestamp();
    print_timestamp("main", start_timestamp);

	timestamp_t start_time = timestamp();
	print_timestamp("start", start_time);

    while(1) {
		n = read(0, abuf, NSAMPLES/2);
		if ( n < 0 ) {
	    	perror("input file");
	    	exit(1);
		}
		if ( n == 0 ) break;
		adpcm_decoder(abuf, sbuf, n*2, &state);
		write(1, sbuf, n*4);
    }

	timestamp_t end_time = timestamp();
	print_timestamp("end", end_time);
    print_elapsed_time("accumulated", end_time - start_time);

    fprintf(stderr, "Final valprev=%d, index=%d\n",
	    state.valprev, state.index);
    exit(0);
}
