#include <stdio.h>

void main(int argc, char *argv[]) {
    int id;
    id = fork();

    if(id > 0) {
      printf("Parent");
      sleep(20);
    }
    if(id == 0)
      printf("child");
}
