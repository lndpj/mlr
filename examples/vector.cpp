#include <mlr/vector.hpp>

int main(int argc, char** argv)
{
	f64<3> a = { 1, 2, 3 };
	f64<4> b = { 4, 5.0f, 6.0, 3 };
	f64<3> c = cross3(a,b);
	printf("%f\n",dot(a,b,2,0));
	printf("[%+e %+e %+e]\n",c[0],c[1],c[2]);
	f64<3> d = 0;
	d +=3 * (a+ b/c) / 3;
	printf("[%+e %+e %+e]: %+e\n",d[0],d[1],d[2],d.norm());
	d.normalize();
	printf("[%+e %+e %+e]: %+e\n",d[0],d[1],d[2],d.norm());
	col<4,uint8_t> color = { 23, 24, 25, 35 };
	printf("%hhu %hhu %hhu]: %+f\n", color.r(),color.g(),color.b(),color.norm());
	exit(EXIT_SUCCESS);
}
