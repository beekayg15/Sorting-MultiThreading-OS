#include <stdio.h>
#include <time.h>

int arr[1000000];

void merge(int arr[], int start, int middle, int end) {
  int x = start;
  int y = middle;
  int z = 0;

  int new_arr[end - start];

  while (x < middle && y < end) {
    if(arr[x] < arr[y]) {
      new_arr[z++] = arr[x++];
    }
    else {
      new_arr[z++] = arr[y++];
    }
  }

  while(x < middle) {
    new_arr[z++] = arr[x++];
  }

  while(y < end) {
    new_arr[z++] = arr[y++];
  }

  for(int i = 0; i < z; i++) {
    arr[i + start] = new_arr[i];
  }
}

void* mergeSort(int positions[]) {
  int start = positions[0];
  int end = positions[1];

  if(start >= end - 1) {
    return NULL;
  } 

  int middle = (end + start) / 2;

  int left_positions[2],right_positions[2];
  left_positions[0] = start;
  left_positions[1] = middle;
  right_positions[0] = middle;
  right_positions[1] = end;

  mergeSort(left_positions);
  mergeSort(right_positions);
  merge(arr, start, middle, end);
  return NULL;
}

int main(void) {
  int n;
  //printf("Enter the number of elements : ");
  //scanf("%d",&n);
  //printf("Enter the elements : ");
  n = 500000;

  FILE * filePointer; 
  filePointer = fopen("input.txt", "r");
  for(int i=0;i<n;i++) {
    fscanf(filePointer, "%d", &arr[i]);
  }
  fclose(filePointer);

  int positions[2];
  positions[0] = 0;
  positions[1] = n;

  clock_t t = clock();
  mergeSort(positions);
  t = clock()-t;

  /*
  printf("\nSorted Array : ");
  for(int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  */

  printf("%.4f",(double)t/(double)CLOCKS_PER_SEC);
  return 0;
}