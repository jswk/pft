#include<math.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 6) {
        fprintf(stderr, "Usage: %s steps dt r q q'\n", argv[0]);
        exit(1);
    }

    double g = 10.;
    double r = atof(argv[3]);
    double dt = atof(argv[2]);
    double beta = sqrt(g/r);
    int steps = atoi(argv[1]);
    int tabsize = steps+1;
    double *w = (double*)malloc(tabsize*sizeof(double));
    double *q = (double*)malloc(tabsize*sizeof(double));
    if (w == 0 || q == 0) {
        fprintf(stderr, "Couldn't allocate enough memory");
        exit(1);
    }
    
    q[0] = atof(argv[4]);
    w[0] = atof(argv[5]);

    for(int i = 0; i < steps; i++) {
        w[i+1] = w[i] - beta*beta*sin(q[i])*dt;
        q[i+1] = q[i] + w[i+1]*dt;
    }

    printf("time position velocity energy\n");
    for(int i = 0; i < tabsize; i++) {
        double E = r*r*w[i]*w[i]/2. - g*r*cos(q[i]);
        printf("%f %f %f %f\n", i*dt, q[i], w[i], E);
    }

    free(w);
    free(q);
}
