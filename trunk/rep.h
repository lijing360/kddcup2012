#if !defined(REP_H)
#define REP_H
#include <stdio.h>
#include <stdlib.h>
#include <map>
struct T
{
	int adid, qid, uid;
	int click, imp;
};

typedef std::pair<int, int> I2;
typedef std::map<int, I2> II2;

void sample_parse();
void sample_split();

struct PredictorBase
{
	virtual void update(const T&) = 0;
	virtual double predict(const T&) = 0;
	void run();
};

#endif
