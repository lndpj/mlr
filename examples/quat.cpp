#include <mlr/quat.hpp>

int main(int argc, char** argv)
{
	quat<double> a = quat<double>::id(SSIZE_MAX);
	quat<double> b = { 4, 5.0f, 6.0, 3 };
	printf("[%+e %+e %+e %+e]\n", a.x(),a.y(),a.z(),a.w());
	b = a.inv();
	printf("[%+e %+e %+e %+e]\n", b.x(),b.y(),b.z(),b.w());
	a *= a.inv();
	printf("[%+e %+e %+e %+e]\n", a.x(),a.y(),a.z(),a.w());
	b *= b.inv();
	printf("[%+e %+e %+e %+e]\n", b.x(),b.y(),b.z(),b.w());
	exit(EXIT_SUCCESS);
}
