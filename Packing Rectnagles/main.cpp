/*
NAME:popina
TASK: packrec
LANG: C++
*/
#include <cstdio>

#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>

using namespace std;

struct Rect
{
	int width;
	int height;
};

Rect rotate(Rect r)
{
	Rect nr;
	nr.width = r.height;
	nr.height = r.width;
	return nr;
}

int total;
int bestarea;
int bestheight[101];

void record(Rect r)
{
	int area = r.width * r.height;
	if (area < total)
		*(long *)0 = 0;

	if (area < bestarea || bestarea == 0) {
		bestarea = area;
		for (int i = 0; i <= 100; i++)
			bestheight[i] = 0;
	}
	if (area == bestarea)
		bestheight[min(r.width, r.height)] = 1;
}

void check(Rect *r)
{
	Rect big;

	// schema 1: all lined up next to each other
	big.width = 0;
	big.height = 0;
	for (int i = 0; i < 4; i++) {
		big.width += r[i].width;
		big.height = max(big.height, r[i].height);
	}
	record(big);

	// schema 2: first three lined up, fourth on bottom
	big.width = 0;
	big.height = 0;
	for (int i = 0; i < 3; i++) {
		big.width += r[i].width;
		big.height = max(big.height, r[i].height);
	}
	big.height += r[3].height;
	big.width = max(big.width, r[3].width);
	record(big);

	// schema 3: first two lined up, third under them, fourth to side
	big.width = r[0].width + r[1].width;
	big.height = max(r[0].height, r[1].height);
	big.height += r[2].height;
	big.width = max(big.width, r[2].width);
	big.width += r[3].width;
	big.height = max(big.height, r[3].height);
	record(big);

	// schema 4, 5: first two rectangles lined up, next two stacked
	big.width = r[0].width + r[1].width;
	big.height = max(r[0].height, r[1].height);
	big.width += max(r[2].width, r[3].width);
	big.height = max(big.height, r[2].height + r[3].height);
	record(big);

	/* schema 6: first two pressed next to each other, next two on top, like
	 * 2 3
	 * 0 1
	 */
	big.height = max(r[0].height + r[2].height, r[1].height + r[3].height);
	big.width = r[0].width + r[1].width;

	// do e2 and 1 touch?
	if (r[0].height < r[1].height)
		big.width = max(big.width, r[2].width + r[1].width);
	// do 2 and 3 touch?
	if (r[0].height + r[2].height > r[1].height)
		big.width = max(big.width, r[2].width + r[3].width);
	// do 0 and 3 touch?
	if (r[1].height < r[0].height)
		big.width = max(big.width, r[0].width + r[3].width);

	// maybe 2 or 3 sits by itself
	big.width = max(big.width, r[2].width);
	big.width = max(big.width, r[3].width);
	record(big);
}

void checkrotate(Rect *r, int n)
{
	if (n == 4) {
		check(r);
		return;
	}
	checkrotate(r, n + 1);
	r[n] = rotate(r[n]);
	checkrotate(r, n + 1);
	r[n] = rotate(r[n]);
}

void checkpermute(Rect *r, int n)
{
	if (n == 4)
		checkrotate(r, 0);

	for (int i = n; i < 4; i++) {
		swap(r[i], r[n]);
		checkpermute(r, n + 1);
		swap(r[i], r[n]);
	}
}

int main()
{
		FILE *fin, *fout;
	Rect r[4];

		fin = fopen("packrec.in", "r");
		fout = fopen("packrec.out", "w");
		assert(fin != NULL && fout != NULL);

	for (int i = 0; i < 4; i++)
				fscanf(fin, "%d %d", &r[i].width, &r[i].height);

	total = (r[0].width * r[0].height + r[1].width * r[1].height + r[2].width * r[2].height + r[3].width * r[3].height);

	checkpermute(r, 0);
		fprintf(fout, "%d\n", bestarea);
	for (int i = 0; i <= 100; i++)
	if (bestheight[i])
				fprintf(fout, "%d %d\n", i, bestarea / i);


	return 0;
}
