#include <time.h>
#include<stdio.h>
#include <stdlib.h>

int fifo(int *frame, int numOfFrames, int numOfPages, int *pages) {
  int count = 0;
  for(int i = 0; i < numOfFrames; i++)
    frame[i]= -1;
  int j = 0;
  // printf("\tref string\t page frames\n");
  for(int i = 1; i <= numOfPages; i++) {
    // printf("%d\t\t", pages[i]);
    int avail = 0;
    for(int k = 0; k < numOfFrames; k++)
      if(frame[k] == pages[i])
        avail = 1;
      if (avail == 0) {
        frame[j] = pages[i];
        j = (j+1) % numOfFrames;
        count++;
      }
    // printf("\n");
  }
  return count;
}

int lru(int *frame, int numOfFrames, int numOfPages, int *pages) {
  int count = 0;
  int flag = 0;
  int used[10], index, temp;
  for(int i = 0; i < numOfFrames; i++)
    frame[i] = -1;
  for(int i = 0; i < numOfPages; i++) {
    flag = 0;
    for(int j = 0; j < numOfFrames; j++) {
      if(frame[j] == pages[i]) {
        // printf("\n\t");
        flag = 1; break;
      }
    }
    if(flag == 0) {
      for(int j = 0; j < numOfFrames; j++)
        used[j] = 0;
      for(int j = 0,temp = i - 1; j < numOfFrames - 1; j++, temp--) {
        for(int k = 0; k < numOfFrames; k++) {
          if(frame[k] == pages[temp])
            used[k] = 1;
        }
      }
      for(int j = 0; j < numOfFrames; j++)
        if(used[j] == 0)
          index = j;
      frame[index] = pages[i];
      // printf("\nFault:  ");
      count++;
    }

  }
  return count;
}

int optimal(int *frame, int numOfFrames, int numOfPages, int *pages) {
  int j, flag = 0, count = 0;
  int max, lp[10], index, m;
  for(j = 0; j < numOfFrames; j++) {
    frame[j] = pages[j];
    flag = 1;
    count++;
  }
  for(j = numOfFrames; j < numOfPages; j++) {
    flag = 0;
    for(int i = 0; i < numOfFrames; i++) {
      if(frame[i] == pages[j]){
        flag=1;
        break;
      }
    }
    if(flag == 0) {
      for(int i = 0; i < numOfFrames; i++)
        lp[i] = 0;
      for(int i = 0; i < numOfFrames; i++) {
        for(m = j + 1; m < numOfPages; m++) {
          if(frame[i] == pages[m]) {
            lp[i]=m-j;
            break;
          }
        }
      }
      max = lp[0];
      index = 0;
      for(int i = 0; i < numOfFrames; i++) {
        if(lp[i] == 0) {
          index = i;
          break;
        } else {
          if(max < lp[i]) {
            max = lp[i];
            index = i;
          }
        }
      }
      frame[index] = pages[j];
      count++;
    }
  }
  return count;
}


int main(int argc, char* argv[]) {
  int n, a[50], frame[10], no;
  // printf("\n ENTER THE NUMBER OF PAGES:\n");
  // scanf("%d", &n);
  srand(time(NULL));
  n = (rand() % 9) + 1;
  // printf("\n ENTER THE PAGE NUMBER :\n");
  printf("Page number list: ");
  // -- randomly generate a list of page numbers
  for(int i = 1; i <= n; i++) {
    // scanf("%d", &a[i]);
    a[i] = rand() % 9;
    printf("%d ", a[i]);
  }
  printf("\n");
  // printf("\n ENTER THE NUMBER OF FRAMES :");
  // scanf("%d", &no);
  no = rand() % 6;
  no = no + 1;
  printf("Number of Frames: %d\n", no);
  int fifoCount = fifo(frame, no, n, a);
  printf("\nFIFO Page Fault Is %d", fifoCount);
  int lruCount = lru(frame, no, n, a);
  printf("\nLRU Page Fault Is %d", lruCount);
  int optimalCount = optimal(frame, no, n, a);
  printf("\nOptimal Page Fault Is %d \n", optimalCount);
  return 0;
}
