#include <stdio.h>

//#define SELECT
#define BUBBLE
//#define INSERT
//#define QUICK

#ifdef SELECT
int theLargest(int dataSet[], int last) {
	int largest = 0;
	int i = 0;
	for (i = 0; i <= last; i++)
		if (dataSet[i] > dataSet[largest])
			largest = i;
	return largest;
}

void selectionSort(int dataSet[], int n) {
	int last;
	int k;
	int tmp;

	for (last = n - 1; last >= 1; last--) {
		k = theLargest(dataSet, last);

		//swap
		tmp = dataSet[k];
		dataSet[k] = dataSet[last];
		dataSet[last] = tmp;

		printf("%d ", dataSet[last]);
	}
}
#endif

#ifdef BUBBLE
void bubbleSort(int dataSet[], int n) {
	int last, i, tmp;
	int flag = 1;

	for (last = n - 1; last >= 1; last--) {
		
		if (!flag)
			break;

		flag = 0;
		for (i = 0; i <= last - 1; i++) {	
			if (dataSet[i] > dataSet[i + 1]) {
				tmp = dataSet[i];
				dataSet[i] = dataSet[i + 1];
				dataSet[i + 1] = tmp;
				flag = 1;
			}
		}
	}
}
#endif

#ifdef INSERT
void insertionSort(int dataSet[],int n) {
    int i, loc, newItem;

    for(i = 1 ; i < n ; i ++){

        loc = i - 1;
        newItem = dataSet[i];

        while ( loc >= 0 && newItem < dataSet[loc]) {

            dataSet[loc+1] = dataSet[loc];
            loc--;
        }

        dataSet[loc+1] = newItem;
    }
}
#endif

#ifdef QUICK
int partition(int dataSet[], int p, int r){
    int i, j, pivot, tmp;
    
    pivot = dataSet[r];
    i = p-1;

    for( j = p; j < r ; j++ ){

        if( dataSet[j] <= pivot ){
            //swap
            tmp = dataSet[++i];
            dataSet[i] = dataSet[j];
            dataSet[j] = tmp;
        }
    }

    //swap
    tmp = dataSet[i+1];
    dataSet[i+1] = dataSet[r];
    dataSet[r] = tmp;

    return i+1;
}

void quickSort(int dataSet[], int p, int r){
    int q;

    if(p < r){
        q = partition(dataSet, p, r);
        quickSort(dataSet, p, q-1);
        quickSort(dataSet, q+1, r);
    }
}

#endif
int main()
{
	int DataSet[] = { 12, 70, 30, 20, 55, 25, 40, 50 };
	int Length = sizeof (DataSet)/ sizeof (DataSet[0]);
	int i = 0;

#ifdef SELECT
	selectionSort(DataSet, Length);

	printf(" selection Sort  \n");
#endif

#ifdef BUBBLE
    bubbleSort(DataSet, Length);

    printf("bubble sort \n");
#endif
    
#ifdef INSERT
    insertionSort(DataSet, Length);

    printf("insert sort \n");
#endif

#ifdef QUICK
    quickSort(DataSet, 0, Length);

    printf("quick sort \n");
#endif

	for (i = 0; i < Length; i++)
	{
		printf("%d ", DataSet[i]);
	}
    printf("\n");

	return 0;
}
