#include <stdio.h>
#include <stdlib.h>

void mergeSort(int ds[], int p, int r);
void merge(int ds[], int p, int q, int r);

int main(void)
{
	int dataSet[] = { 12, 70, 30, 20, 55, 25, 40, 50 };
	int length = sizeof(dataSet) / sizeof(dataSet[0]);

	int j = 0;

	mergeSort(dataSet, 0, length - 1);

	for (j = 0; j < length; j++)
	{
		printf("%d ", dataSet[j]);
	}

	printf("\n");

	return 0;
}

void mergeSort(int ds[], int p, int r)
{
	int q;
	if (p < r)
	{
		q = (p + r) / 2;
		mergeSort(ds, p, q);
		mergeSort(ds, q + 1, r);
		merge(ds, p, q, r);
	}
}

void merge(int ds[], int p, int q, int r)
{
	int *tmp, i, j, t;

	tmp = malloc(sizeof(int)*r);

	i = p;
	j = q + 1;
	t = 0;

	while (i <= q && j <= r)
	{
		if (ds[i] >= ds[j])
			tmp[t++] = ds[i++];
		else
			tmp[t++] = ds[j++];
	}

	while (i <= q)
	{
		tmp[t++] = ds[i++];
	}
	while (j <= r)
	{
		tmp[t++] = ds[j++];
	}

	i = p;
	t = 0;

	while (i <= r)
		ds[i++] = tmp[t++];

	free(tmp);
}
