#include <stdio.h>
#include "naive_bay.h"
#include <dlib/svm.h>
using namespace dlib;
int main()
{
	//sample_parse();
	//sample_split();
	//NaiveBay().run();
	
	svm_c_linear_trainer<sparse_linear_kernel<std::vector<std::pair<uint32_t, double> > > > a;
	return 0;
}
