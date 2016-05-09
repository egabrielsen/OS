#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int average;
int min;
int max;
int size = 0;
void *find_avg(void *arg);
void *find_max(void *arg);

int main(int argc, char* argv[]) {
  pthread_t thread1;
  pthread_t thread2;
  pthread_attr_t attr;
  pthread_attr_t attr2;

  int nums[argc];

  if (argc < 2) {
    fprintf(stderr, "usage: a.out <int>\n");
    return -1;
  }
  for (int i = 1; i < argc; i++) {
    if (atoi(argv[i]) < 0) {
      fprintf(stderr, "%d must be >= 0\n", atoi(argv[i]));
      return -1;
    } else {
      nums[i - 1] = atoi(argv[i]);
      // printf("%d\n", nums[i-1]);
      size++;
    }
  }
  pthread_attr_init(&attr);
  pthread_attr_init(&attr2);
  pthread_create(&thread2, &attr2, find_max, (void*)nums);
  pthread_create(&thread1, &attr, find_avg, (void*)nums);
  min = nums[0];
  for (int i = 1; i < size; i++) {
    if (nums[i] < min) {
      min = nums[i];
    }
  }
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  printf("The Average Value is = %d \n", average);
  printf("The Minimum Value is = %d \n", max);
  printf("The Minimum Value is = %d \n", min);

  return 0;
}

void *find_avg(void *arg) {
  int *val_p = (int *) arg;
  int sum = 0;
  for(int i = 0; i < size; i++){
    sum += val_p[i];
  }
  average = sum / (size);

  pthread_exit(0);
}

void *find_max(void *arg) {
  int *val_p = (int *) arg;
  max = 0;
  for (int i = 0; i < size; i++) {
    if (val_p[i] > max) {
      max = val_p[i];
    }
  }
  pthread_exit(0);
}
