#include <stdio.h>
#include <pthread.h>
#include <time.h>

int arr[10000000];
static int flag = 0;

void swap(int *arr, int i, int j) {
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
  return;
}

int partition(int *arr, int start, int end) {
  int insert = start;
  int pivot = arr[end];
  for(int i = start; i <= end; i++) {
    if(arr[i] <= pivot) {
      swap(arr, i, insert++);
    }
  }
  return insert - 1;
}

void* quicksort(int position[]) {

  int start = position[0];
  int end = position[1];

  if(start >= end) {
    return NULL;
  }

  int pos = partition(arr, start, end);

  int left_position[2];
  left_position[0] = start;
  left_position[1] = pos - 1;

  int right_position[2];
  right_position[0] = pos + 1;
  right_position[1] = end;
    
  quicksort(left_position);
  quicksort(right_position);
  return NULL;
}

int main(void) {
  int n;
  //printf("Enter the number of elements : ");
  //scanf("%d",&n);
  //printf("The randomly generated elements : ");
  n = 900000;

  FILE * filePointer; 
  filePointer = fopen("input.txt", "r");
  for(int i=0;i<n;i++) {
    fscanf(filePointer, "%d", &arr[i]);
  }
  fclose(filePointer);

  clock_t t = clock();
  int x = partition(arr, 0, n - 1);

  int left_position[2];
  left_position[0] = 0;
  left_position[1] = x - 1;

  int right_position[2];
  right_position[0] = x + 1;
  right_position[1] = n - 1;

  pthread_t left, right;

  pthread_create(&left, NULL, (void*)quicksort, left_position);
  pthread_create(&right, NULL, (void*)quicksort, right_position);

  pthread_join(left, NULL);
  pthread_join(right, NULL);
  t = clock()-t;

  /*printf("\nSorted Array : ");
  for(int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }*/

  printf("%.4f",(double)t/(double)CLOCKS_PER_SEC);
  return 0;
}