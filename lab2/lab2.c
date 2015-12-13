#include<math.h>
#include<stdio.h>
#include<stdlib.h>

void print_record(double t, double *record);
double get_energy(double *record);

static double alpha;
static double g = 10.;

int main(int argc, char *argv[]) {
    if (argc != 8) {
        fprintf(stderr, "Usage: %s n dt alpha fi' fi z' z\n", argv[0]);
        exit(1);
    }

    int steps = atoi(argv[1]);
    double dt = atof(argv[2]);
    alpha = atof(argv[3])*M_PI/180.;

    double *curr = (double*) malloc(sizeof(double)*4);
    double *prev = (double*) malloc(sizeof(double)*4);
    for (int i = 0; i < 4; i++) {
        prev[i] = atof(argv[i+4]);
    }
    // omega
    // fi
    // v
    // z

    double cos2sin = cos(alpha)*cos(alpha)/sin(alpha);
    double sincos2 = sin(alpha)*cos(alpha)*cos(alpha);
    double sin2 = sin(alpha)*sin(alpha);

    double t = 0.;
    print_record(t, prev);
    for(int i = 0; i < steps; i++) {
        curr[0] = prev[0] - dt*(g*cos2sin*sin(prev[1])/prev[3]+2*prev[2]*prev[0]/prev[3]);
        curr[1] = prev[1] + curr[0]*dt;
        curr[2] = prev[2] + dt*(sin2*prev[3]*pow(prev[0],2)-g*sincos2*(1-cos(prev[1])));
        curr[3] = prev[3] + curr[2]*dt;

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
    printf("%f %f %f %f\n", t, record[1], record[3], get_energy(record));
}

double get_energy(double *record) {
    return .5*(pow(tan(alpha)*record[3]*record[0],2)+pow(record[2]/cos(alpha),2))+
        g*record[3]*sin(alpha)*(1-cos(record[1]));
}
