#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<float.h>

int main(int argc, char *argv[]) {
    if (argc != 8) {
        fprintf(stderr, "Usage: %s steps expddt expdtmin expdtmax r q q'\n", argv[0]);
        exit(1);
    }

    double g = 10.;
    double expddt = atof(argv[2]);
    double expdtmin = atof(argv[3]);
    double expdtmax = atof(argv[4]);
    double r = atof(argv[5]);
    double q0 = atof(argv[6]);
    double qp0 = atof(argv[7]);
    double beta = sqrt(g/r);
    int steps = atoi(argv[1]);
    double *curr = (double*) malloc(2*sizeof(double));
    double *prev = (double*) malloc(2*sizeof(double));

    double curr_exp = expdtmin;

    while (curr_exp <= expdtmax) {
        double dt = pow(10, curr_exp);

        prev[0] = qp0;
        prev[1] = q0;

        double minE = DBL_MAX;
        double maxE = -DBL_MAX;
        int zeros = 0;
        int step = 0;
        while (zeros < 2 && step < steps) {
            curr[0] = prev[0] - beta*beta*sin(prev[1])*dt;
            curr[1] = prev[1] + curr[0]*dt;

            if (prev[1]*curr[1] <= 0 && maxE != minE) {
                zeros++;
            }
            if (zeros == 1) {
                double E = r*r*curr[0]*curr[0]/2. - g*r*cos(curr[1]);
                if (E > maxE) {
                    maxE = E;
                }
                if (E < minE) {
                    minE = E;
                }
            }

            double *tmp = prev;
            prev = curr;
            curr = tmp;
            step++;
        }

        if (steps > step) {
            printf("%f %f\n", dt, maxE-minE);
        } else {
            printf("%f X\n", dt);
        }
        curr_exp += expddt;
    }

    free(curr);
    free(prev);
}
