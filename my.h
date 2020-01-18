#ifndef MY_H_
# define MY_H_

/* #define NB_SAMPLES 3 */
/* #define NB_TRACES 10 */
#define NB_SAMPLES 980
#define NB_TRACES 2000
#define OFFSET_RES 31




void get_traces(double **traces, int**input);
double **alloc_trace();
int **alloc_input();
void free_ressources(double **traces, int **input);

#endif
