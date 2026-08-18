//#define X0 1234
//#define Y0 5678
//#define U0 4321
//#define C1 4736
//#define C2 6732

typedef short data_t;

data_t diffeq(data_t a, data_t dx, data_t X0, data_t Y0, data_t U0, data_t C1, data_t C2)
{
	data_t x = X0;
	data_t y = Y0;
	data_t u = U0;

	data_t x1, y1, u1;

	bool stop = false;

	l1: while (!stop) {
//#pragma HLS ALLOCATION operation instances=mul limit=1
//#pragma HLS PIPELINE II=1
//#pragma HLS LOOP_TRIPCOUNT min=100 max=100
		x1 = x + dx;
		u1 = u - (C1 * x * u * dx) - (C2 * y * dx);
		y1 = y + u * dx;
		x = x1;
		u = u1;
		y = y1;
		stop = (x1 >= a);
	}
	return y;
}
