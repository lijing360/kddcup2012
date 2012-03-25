#include "rep.h"
void sample_parse()
{
	FILE *i = fopen("sample.txt", "r");
	FILE *o = fopen("sample.dat", "w");
	char buf[4096];
	size_t click, imp, url, adid, advid, depth, pos, qid, kv, title, desc, uid;
	while(fgets(buf, sizeof buf, i))
	{
		sscanf(buf, "%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu", &click, &imp, &url, &adid, &advid, &depth, &pos, &qid, &kv, &title, &desc, &uid);
		T t;
		t.adid=adid;
		t.qid=qid;
		t.uid=uid;
		t.click=click;
		t.imp=imp;
		fwrite(&t, sizeof(T), 1, o);
	}
	fclose(i);
	fclose(o);
}

void sample_split()
{
	FILE *i = fopen("sample.dat", "r");
	FILE *o1 = fopen("train.dat", "w");
	FILE *o2 = fopen("test.dat", "w");
	T t;
	srand(123);
	while(1 == fread(&t, sizeof(T), 1, i))
		fwrite(&t, sizeof(T), 1, rand() % 10 ? o1 : o2);
	fclose(i);
	fclose(o2);
	fclose(o1);
}

void PredictorBase::run()
{
	FILE *train = fopen("train.dat", "r");
	T t;
	//train
	while(1 == fread(&t, sizeof(T), 1, train))
		update(t);	
	fclose(train);
	//predict
	FILE *test = fopen("test.dat", "r");
	while(1 == fread(&t, sizeof(T), 1, test))
		printf("%d %d %lf\n", t.click, t.imp, predict(t));
	fclose(test);
}
