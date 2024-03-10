#include "Matrix.h"
#include <exception>

using namespace std;

Matrix::Matrix(int nrLines, int nrCols) {

    if ((nrLines <= 0) || (nrCols <= 0)) {
        throw exception();
    }

    nr_lines = nrLines;
    nr_cols = nrCols;
    size = 0;
    capWerte = 5;
    Zeile = new int[capWerte];
    Spalte = new int[capWerte];

    for (int idx = 0; idx <= nr_cols; idx++) {
        Spalte[idx] = 0;
    }
}

int Matrix::nrLines() const {
    return nr_lines;
}

int Matrix::nrCols() const {
    return nr_cols;
}

TElem Matrix::element(int i, int j) const {

    if((i < 0) || (j < 0) || i >= nrLines() || j >= nrCols()) {
        throw exception();
    }
    else {
        int col_start = Spalte[j];
        int col_end = Spalte[j + 1];
        int elem_count = col_end - col_start;
        if (elem_count == 0) {
            return NULL_TELEM;
        }

        for (int k = col_start; k < col_end; k++) {
            if(Zeile[k] == i) {
                return Werte[k];
            }
        }

        return NULL_TELEM;
    }
}

void Matrix::resize_up() {

    int* auxZeile;
    TElem* auxWerte;

    auxZeile = new int[capWerte * 2];
    auxWerte = new TElem[capWerte * 2];

    for (int idx = 0; idx < size; ++idx) {
        auxZeile[idx] = Zeile[idx];
        auxWerte[idx] = Werte[idx];
    }

    delete[] Zeile;
    delete[] Werte;

    Zeile = auxZeile;
    Werte = auxWerte;
    capWerte = capWerte * 2;
}

void Matrix::resize_down() {

    int* auxZeile;
    TElem* auxWerte;

    auxZeile = new int[capWerte / 2];
    auxWerte = new TElem[capWerte / 2];

    for (int idx = 0; idx < size; ++idx) {
        auxZeile[idx] = Zeile[idx];
        auxWerte[idx] = Werte[idx];
    }

    delete[] Zeile;
    delete[] Werte;

    Zeile = auxZeile;
    Werte = auxWerte;
    capWerte = capWerte / 2;
}

void Matrix::insertElement(int i, int j, TElem e) {

    if (size + 1 == capWerte) {
        resize_up();
    }

    int col_end = Spalte[j + 1];
    for (int k = size; k > col_end; k--) {
        Zeile[k] = Zeile[k - 1];
        Werte[k] = Werte[k - 1];
    }

    Zeile[col_end] = i;
    Werte[col_end] = e;

    for (int k = j + 1; k <= nrCols(); k++) {
        Spalte[k]++;
    }

    size++;
}

void Matrix::removeElement(int i,int j) {

    if (size - 1 <= capWerte / 2) {
        resize_down();
    }

    int col_start = Spalte[j];
    int col_end = Spalte[j + 1];
    for (int k = col_start; k < col_end; k++) {
        if (Zeile[k] == i) {
            for (int t = k; t < size - 1; t++) {
                Zeile[t] = Zeile[t + 1];
                Werte[t] = Werte[t + 1];
            }

            break;
        }
    }

    for (int k = j + 1; k <= nrCols(); k++) {
        Spalte[k]--;
    }

    size--;
}

TElem Matrix::modify(int i, int j, TElem e) {

    if ((i < 0) || (j < 0) || i >= nrLines() || j >= nrCols()) {
        throw exception();
    }

    int col_start = Spalte[j];
    int col_end = Spalte[j + 1];
    int previous = element(i,j);

    // Fall 1: old_value = 0 AND new_value = 0
    if (e == NULL_TELEM && previous == NULL_TELEM) {
        return NULL_TELEM;
    }

    // Fall 2: old_value = 0 AND new_value != 0
    if (e != NULL_TELEM && previous == NULL_TELEM) {
        insertElement(i,j,e);
    }

    // Fall 3: old_value != 0 AND new_value = 0
    if (e == NULL_TELEM && previous != 0) {
        removeElement(i,j);
    }

    // Fall 4: old_value != 0 AND new_value != 0
    if ( e != 0 && previous != 0) {
        int col_start = Spalte[j];
        int col_end = Spalte[j + 1];
        for (int k = col_start; k < col_end; k++) {
            if (Zeile[k] == i) {
                Werte[k] = e;
                break;
            }
        }
    }

    return NULL_TELEM;
}

Matrix::~Matrix() {
    delete[] Werte;
    delete[] Zeile;
    delete[] Spalte;
}