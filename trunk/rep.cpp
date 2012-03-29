#include "rep.h"
#include <dlib/string.h>
void repo_save()
{
	FILE *i = fopen("descriptionid_tokensid.txt", "r");
	FILE *oidx = fopen("desc.idx", "w");
	FILE *odat = fopen("desc.dat", "w");
	char buf[4096 * 1000];
	char toks[4096*1000];
	int idx[2] = {0, 0};
	while(fgets(buf, sizeof buf, i))
	{
		sscanf(buf, "%d\t%s", idx + 1, toks);
		std::vector<std::string> ts = dlib::split(std::string(toks), "|");
		idx[1] = ts.size();
		fwrite(idx, sizeof(int), 2, oidx);
		idx[0] += ts.size();
		for(std::vector<std::string>::const_iterator it = ts.begin(); it != ts.end(); ++it)
		{
			int x = atoi(it->c_str());
			fwrite(&x, sizeof(int), 1, odat);
		}
	}
	fclose(i);
	fclose(oidx);
	fclose(odat);
}

void repo_dump()
{
	FILE * fidx = fopen("desc.idx", "rb");
	FILE* fdat = fopen("desc.dat", "rb");
	int idx[2];
	int x[10*10*1000];
	int k=0;
	while(2==fread(idx, sizeof(int), 2, fidx))
	{
		fseek(fdat, sizeof(int)*idx[0], SEEK_SET);
		fread(x, sizeof(int), idx[1], fdat);
		printf("%d\t", k++);
		for(int i=0;i<idx[1];++i)
			printf("%d%c", x[i], i==idx[1]-1 ? '\n' : '|');
	}
}

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
