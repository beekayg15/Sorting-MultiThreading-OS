#include <stdio.h>
#include <time.h>
#include <pthread.h>

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
  n = 500000;

  FILE * filePointer; 
  filePointer = fopen("input.txt", "r");
  for(int i=0;i<n;i++) {
    fscanf(filePointer, "%d", &arr[i]);
  }
  fclose(filePointer);

  int left_positions[2],right_positions[2];
  int left_positionsn[2],right_positionsn[2];
  left_positions[0] = 0;
  left_positions[1] = n/4;
  right_positions[0] = n/4;
  right_positions[1] = n/2;
  left_positionsn[0] = n/2;
  left_positionsn[1] = (3 * n) / 4;
  right_positionsn[0] = (3 * n) / 4;
  right_positionsn[1] = n;

  pthread_t left,right,leftn,rightn;

  clock_t t = clock();
  pthread_create(&left,NULL,(void*)mergeSort,left_positions);
  pthread_create(&right,NULL,(void*)mergeSort,right_positions);
  pthread_create(&leftn,NULL,(void*)mergeSort,left_positionsn);
  pthread_create(&rightn,NULL,(void*)mergeSort,right_positionsn);

  pthread_join(left, NULL);
  pthread_join(right, NULL);
  pthread_join(leftn, NULL);
  pthread_join(rightn, NULL);
  
  merge(arr, 0, n/4, n/2);
  merge(arr, n/2, (3 * n) / 4, n);
  merge(arr, 0, n/2, n);
  t = clock() - t;

  /*
  printf("\nSorted Array : ");
  for(int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  */

  printf("%.4f",(double)t/(double)CLOCKS_PER_SEC);
  return 0;
}