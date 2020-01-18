#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "my.h"

void get_traces(double **traces, int**input){
  FILE *stream;
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  int i;
  int j;

  stream = fopen("files/traces.raw", "r");
  if (stream == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  j = 0;
  i=0;
  while ((nread = getline(&line, &len, stream)) != -1) {
    line[nread-1] = '\0';
    traces[j][i] = atof(line);
    i++;
    if (i == NB_SAMPLES){
      j++;
      i =0;
    }
  }
  fclose(stream);


  
  //------ get input
  stream = fopen("files/input.raw", "r");
  if (stream == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  j = 0;
  i=0;
  while ((nread = getline(&line, &len, stream)) != -1) {
    line[nread-1] = '\0';
    input[j][i] = atoi(line);
    i++;
    if (i == 16){
      j++;
      i = 0;
    }
  }
  free(line);
  fclose(stream);
}

double **alloc_trace(){
  double **traces;
  int i;
  
  traces = malloc(sizeof(double*)*NB_TRACES);
  for (i=0;i<NB_TRACES;i++)
    traces[i] = malloc(sizeof(double)*NB_SAMPLES);
  return traces;
}

int **alloc_input(){
  int **input;
  int i;
  
  input = malloc(sizeof(int*)*NB_TRACES);
  for (i=0;i<NB_TRACES;i++)
    input[i] = malloc(sizeof(int)*16);
  return input;
}

void free_ressources(double **traces, int **input){
  int i;

  for (i=0;i<NB_TRACES;i++)
    free(input[i]);
  free(input);
  for (i=0;i<NB_TRACES;i++)
    free(traces[i]);
  free(traces);
}
