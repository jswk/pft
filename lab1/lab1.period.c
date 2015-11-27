#include<math.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s steps dt r n\n", argv[0]);
        exit(1);
    }

    double g = 10.;
    double r = atof(argv[3]);
    double dt = atof(argv[2]);
    double beta = sqrt(g/r);
    int steps = atoi(argv[1]);
    double *curr = (double*) malloc(2*sizeof(double));
    double *prev = (double*) malloc(2*sizeof(double));
    int N = atoi(argv[4]);

    for (int n = 0; n < N; n++) {
        double angle = M_PI * (n+1) / (N+2);
        prev[0] = 0;
        prev[1] = angle;

        double t0 = -1;
        double t1 = -1;
        int step = 0;
        while (t1 == -1 && step < steps) {
            curr[0] = prev[0] - beta*beta*sin(prev[1])*dt;
            curr[1] = prev[1] + curr[0]*dt;

            if (prev[1]*curr[1] <= 0) {
                double t = step*dt - prev[1]*dt/(curr[1] - prev[1]);
                if (t0 == -1) {
                    t0 = t;
                } else {
                    t1 = t;
                }
            }
            double *tmp = prev;
            prev = curr;
            curr = tmp;
            step++;
        }
        double angle_degrees = angle/M_PI*180;
        if (t1 != -1) {
            double T = 2 * (t1 - t0);
            printf("%f %f\n", angle_degrees, T);
        } else {
            printf("%f 0\n", angle_degrees);
        }
    }

    free(curr);
    free(prev);
}
