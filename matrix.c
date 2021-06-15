#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

void mx_free(TMatrix *m) {
	if (m != NULL)
		if (m->a != NULL) {
			free(m->a);
			free(m);
		}
}

void mx_print(TMatrix *m) {
	unsigned int i, j;

	if (m != NULL) {
		if (m->a != NULL) {
			for (i = 0; i < m->m; i++) {
				for (j = 0; j < m->n; j++)
					printf("%8.2lf", m->a[i * m->n + j]);
				printf("\n");
			}
		}
	}
}

TMatrix *mx_identity(unsigned int n) {
	unsigned int i, j;
	TMatrix *m = NULL;

	m = (TMatrix*)malloc(sizeof(TMatrix));
	if (m != NULL) {
		m->a = (double*)malloc(n * n * sizeof(double));
		if (m->a != NULL) {
			m->n = m->m = n;
			for (i = 0; i < m->m; i++)
				for (j = 0; j < m->n; j++)
					m->a[i * n + j] = i == j ? 1 : 0;
		}
		else {
			free(m);
			m = NULL;
		}
	}

	return m;
}

void mx_swap_rows(TMatrix *m, int row1, int row2) {
    unsigned int i;
    double temp;
    
    for(i = 0; i < m->n; i++) {
        temp = m->a[m->n * row1 + i];
        m->a[m->n * row1 + i] = m->a[m->n * row2 + i];
        m->a[m->n * row2 + i] = temp;
    }
}

void mx_descending_row_sort(TMatrix *m, int col) {
    unsigned int i, j;
    
    for(i = 0; i < m->n - 1; i++)
    {
        for(j = 0; j < m->n - i - 1; j++)
            if(m->a[j * m->n + col] < m->a[(j + 1) * m->n + col])
                mx_swap_rows(m, j, j + 1);
    }
}
