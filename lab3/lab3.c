#include<math.h>
#include<stdio.h>
#include<stdlib.h>

void print_record(double t, double *record);
double get_energy(double *record);

static double B;
static double p_fi;
static double e = 1.;
static double em = 1.;

int main(int argc, char *argv[]) {
    if (argc != 8) {
        fprintf(stderr, "Usage: %s n dt B p_fi fi0 p_r0 r0\n", argv[0]);
        exit(1);
    }

    int steps = atoi(argv[1]);
    double dt = atof(argv[2]);
    B = atof(argv[3]);
    p_fi = atof(argv[4]);

    double *curr = (double*) malloc(sizeof(double)*3);
    double *prev = (double*) malloc(sizeof(double)*3);
    for (int i = 0; i < 3; i++) {
        prev[i] = atof(argv[i+5]);
    }
    // fi
    // p_r
    // r


    double t = 0.;
    print_record(t, prev);
    for(int i = 0; i < steps; i++) {
        curr[0] = prev[0] + (p_fi/em/pow(prev[2],2)-e*B/2./em)*dt;
        curr[1] = prev[1] + (pow(p_fi,2)/pow(prev[2],3)-pow(e*B,2)*prev[2]/4.)/em*dt; 
        curr[2] = prev[2] + curr[1]/em*dt; 

        t += dt;
        print_record(t, curr);

        double *tmp = curr;
        curr = prev;
        prev = tmp;
    }

    free(curr);
    free(prev);
}

void print_record(double t, double *record) {
    double x = record[2]*cos(record[0]);
    double y = record[2]*sin(record[0]);
    printf("%f %f %f %f\n", t, x, y, get_energy(record));
}

double get_energy(double *record) {
    double p_r = record[1];
    double r = record[2];
    return .5/em*(pow(p_r,2)+pow(p_fi/r,2))-e*B/2./em*p_fi+pow(e*B*r,2)/8./em;
}
