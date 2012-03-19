#include <stdio.h>
struct T
{
	int adid, qid, uid;
	int click, imp;
};
int main()
{
	FILE *i = fopen("i", "r");
	FILE *o = fopen("o", "w");
	char buf[4096];
	size_t click, imp, url, adid, advid, depth, pos, qid, kv, title, desc, uid;
	while(fgets(buf, sizeof buf, i))
	{
		sscanf(buf, "%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu", &click, &imp, &url, &adid, &advid, &depth, &pos, &qid, &kv, &title, &desc, &uid);
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
	return 0;
}
