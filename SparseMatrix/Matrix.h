#pragma once

typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:
    int nr_lines;   // um die Anzahl der Zeilen zu speichern
    int nr_cols;    // um die Anzahl der Spalten zu speichern
    int size;       // Anzahl der Elementen != NULL_TElem
    int* Zeile;     // Initialisierung eines Arrays fur Zeilen
    int* Spalte;    // Initialisierung eines Arrays fur Spalten
    TElem* Werte;   // Initialisierung eines Arrays fur TElems
    int capWerte;   // Kapazitat 1

public:
    // Konstruktor
    Matrix(int nrLines, int nrCols);

    // gibt die Anzahl der Zeilen aus
    int nrLines() const;

    // gibt die Anzahl der Spalten aus
    int nrCols() const;

    // gibt der Element an der Position(i,j) aus
    // Indexierung startet von 0
    // gibt ein Exception aus, falls Element(i,j) in der Matrix nicht vorhanden ist
    TElem element(int i, int j) const;

    void resize_up();

    void resize_down();

    void insertElement(int i, int j, TElem e);

    void removeElement(int i, int j);

    // wechselt den Wert des Elementes(i,j)
    // gibt zuruck den Wert des vorherigen Elementes
    // gibt ein Exception aus, falls das Element(i,j) in der Matrix nicht vorhanden ist
    TElem modify(int i, int j, TElem e);

    // Destruktor
    ~Matrix();
};