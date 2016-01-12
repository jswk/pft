#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static int nx;
static int ny;
static int nz;

double *get(double* V, int i, int j, int k);
void restore_electrode(double* V, double V0, int i, int j, int k, int ni, int nj, int nk);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]);
    nx = 51;
    ny = 51;
    nz = 26;
    double dx = 10;
    double dy = 10;
    double dz = 10;

    int nz_well = 10;
    int nz_el = 15;

    double *Vn = (double*) malloc(sizeof(double)*nx*ny*nz);
    double *V  = (double*) malloc(sizeof(double)*nx*ny*nz);
    memset(Vn, 0, sizeof(double)*nx*ny*nz);
    memset(V,  0, sizeof(double)*nx*ny*nz);

    int step = 0;
    double c1 = 1./(2./dx/dx+2./dy/dy+2./dz/dz);
    while (step < n) {
        for (int i = 1; i < nx-1; i++) {
            for (int j = 1; j < ny-1; j++) {
                for (int k = 1; k < nz-1; k++) {
                    *get(Vn, i, j, k) = c1*(
                        (*get(V,i-1,j,k)+*get(V,i+1,j,k))/dx/dx +
                        (*get(V,i,j-1,k)+*get(V,i,j+1,k))/dy/dy +
                        (*get(V,i,j,k-1)+*get(V,i,j,k+1))/dz/dz);
                }
            }
        }
        restore_electrode(Vn, 800, 0,  0,  nz_el, 20, 10, 1);
        restore_electrode(Vn, 800, 30, 0,  nz_el, 20, 10, 1);
        restore_electrode(Vn, 800, 0,  40, nz_el, 20, 10, 1);
        restore_electrode(Vn, 800, 30, 40, nz_el, 20, 10, 1);
        restore_electrode(Vn, 650, 0,  20, nz_el, 10, 10, 1);
        restore_electrode(Vn, 650, 40, 20, nz_el, 10, 10, 1);

        for (int i = 0; i < nx; i++) {
            for (int j = 0; j < ny; j++) {
                *get(Vn, i, j, nz-1) = *get(Vn, i, j, nz-2);
            }
        }
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                *get(Vn, 0, j, k) = *get(Vn, 1, j, k);
                *get(Vn, nx-1, j, k) = *get(Vn, nx-2, j, k);
            }
        }
        for (int i = 0; i < nx; i++) {
            for (int k = 0; k < nz; k++) {
                *get(Vn, i, 0, k) = *get(Vn, i, 1, k);
                *get(Vn, i, ny-1, k) = *get(Vn, i, ny-2, k);
            }
        }

        double* tmp = Vn;
        Vn = V;
        V = tmp;

        step++;

        if (step%100 == 0) {
            printf("%d %f\n", step, *get(Vn, nx/2, ny/2, nz_well));
        }
    }

    free(Vn);
    free(V);
}

inline double *get(double* V, int i, int j, int k) {
    return V + nx*ny*k + nx*j + i;
}

void restore_electrode(double* V, double V0, int i, int j, int k, int ni, int nj, int nk) {
    for (int ii = 0; ii <= ni; ii++) {
        for (int ij = 0; ij <= nj; ij++) {
            for (int ik = 0; ik <= nk; ik++) {
                *get(V,i+ii,j+ij,k+ik) = V0;
            }
        }
    }
}
