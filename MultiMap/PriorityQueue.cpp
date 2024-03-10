#include "PriorityQueue.h"
#include <exception>

using namespace std;


PriorityQueue::PriorityQueue(Relation r) { //θ(n)
    //TODO - Implementation
    this->cap = 10; //initiale Kapazitat ist ein random int
    this->elems = new SLLA[this->cap]; // neues array
    //this->next=new SLLA[this->cap];
    this->head = -1; //head beginnt immer mit -1
    for (int i = 1; i <= this->cap - 1; i++) {
        //alle Elementen des Arrays haben freie Positionen, und der "Next" des letzten elements ist immer -1
        this->elems[i].next = i + 1;
    }
    this->elems[this->cap - 1].next = -1;  // hier weisen wir -1 zu den letzten element, so dass er im "NILL" pointiert
    this->firstEmpty = 1; //first empty ist am anfang 1 denn wir fugen dort die elementen
    this->rel = r; //relation
    this->nrElems=0;

}


void PriorityQueue::push(TElem e, TPriority p) { //best case θ(1), average case θ(n), worst case θ(n)
    //TODO - Implementation
    if (this->firstEmpty == -1) //wenn wir ein resize brauchen
    {
        int neue_kapazitat = this->cap * 2; //neue kapazitat ist alte kapazitat *2
        SLLA *new_elems = new SLLA[neue_kapazitat]; //neues array
        for (int idx = 0; idx < this->cap; idx++) {
            //wir addieren die alte elemente in den neuen array
            new_elems[idx].info = this->elems[idx].info;
            new_elems[idx].next = this->elems[idx].next;
        }

        //angefangen von der alte kapazitat, bis zu die neue kapazitat, addieren wir "leere positionen"
        for (int idx = this->cap; idx < neue_kapazitat; idx++) {
            new_elems[idx].next = idx + 1;
        }

        new_elems[neue_kapazitat - 1].next = -1; //letzes wert pointiert auf -1
        int number_elems = this->cap; //so wiele elemente wie kapazitat
        delete[] this->elems; //loschen den alten array, den wir nicht mehr brauchen
        this->cap = neue_kapazitat; //neue kapazitat updatieren
        this->elems = new_elems; //neues array wird updatiert
        this->firstEmpty = number_elems; //first empty wird immer auf die nachste "gultige" position zeigen
    }

    if (isEmpty() == true) //fall wo wir keine elemente schon haben
    {
        this->head = 1; //neues head wird auf 1
        this->elems[head].info.first = e;
        this->elems[head].info.second = p; //wir settieren die values
        this->firstEmpty = 2; //first empty wird 2, weil 2 die nachste "gultige" position ist
        this->elems[head].next = -1; // ende des array wird auf -1 pointieren
    } else { //fall wo wir 1 oder mehrere elemente schon haben
        int previous = -2; //Konvention um uns zu helfen
        int current = this->head;
        while (current != -1 && this->rel(this->elems[current].info.second, p) == true) {
            //wir uberprufen immer ob wir nicht das ende "erreichen", und wir machen diesen weile so lange die relation GULTIG ist
            previous = current; //mit previous und current gehen wir durch den Array
            current = this->elems[current].next; //wir gehen bis wir die ende erreichen, or bis die Relation nicht mehr gultig ist
        }

        int neu_elem = this->firstEmpty;
        this->firstEmpty = this->elems[this->firstEmpty].next; // auf first empty fugen wir den neuen element, und dann verandern wir den first empty

        this->elems[neu_elem].info.first = e;
        this->elems[neu_elem].info.second = p; //initializierung des wertes
        this->elems[neu_elem].next = -1; //next ist -1 weil er das letzt hinzugefugtes element ist

        if (previous == -2) { //ist in die while schleife nicht hineingedringen
            this->elems[neu_elem].next = this->head; // wenn die relation nicht gut ist, dann "tauschen" sich die 2
            this->head = neu_elem;
        } else {
            this->elems[neu_elem].next = current; //auf position neu_elem (letzte gultige position) tuen wir den letzten element
            this->elems[previous].next = neu_elem; //previous.next hat den next, die vorherige position wo wir den wert hinzugefugt haben
        }
    }
    this->nrElems++;
}

//throws exception if the queue is empty
Element PriorityQueue::top() const { // θ(1)
    //TODO - Implementation
    if (isEmpty()) //fall wo unser array leer ist
        throw exception();
    else {
        return this->elems[head].info; //head ist immer unser element mit die hochste prioritat
    }

    return NULL_TELEM;
}

Element PriorityQueue::pop() { //θ(1)*
    //TODO - Implementation
    if (isEmpty()) //fall wo unser array leer ist
        throw exception();
    else {
        auto valori_head = this->elems[head].info; //valori_head nimmt unser initialen head
        this->head = this->elems[head].next; // unser initialer head wir zu head.next (element wo head pointiert)

        if (this->cap==this->nrElems*4) {
            int neue_kapazitat = this->cap / 2; //neue kapazitat ist alte kapazitat /2
            SLLA *new_elems = new SLLA[neue_kapazitat]; //neues array
            for (int idx = 0; idx < this->cap; idx++) {
                //wir addieren die alte elemente in den neuen array
                new_elems[idx].info = this->elems[idx].info;
                new_elems[idx].next = this->elems[idx].next;

            }

            new_elems[neue_kapazitat - 1].next = -1; //letzes wert pointiert auf -1
            int number_elems = this->cap; //so wiele elemente wie kapazitat
            delete[] this->elems; //loschen den alten array, den wir nicht mehr brauchen
            this->cap = neue_kapazitat; //neue kapazitat updatieren
            this->elems = new_elems; //neues array wird updatiert
            this->firstEmpty = number_elems; //first empty wird immer auf die nachste "gultige" position zeigen

        }
        return valori_head; //returnieren den initialen head
    }
    return NULL_TELEM;
};

bool PriorityQueue::isEmpty() const { //θ(1)
    //TODO - Implementation
    if (this->head == -1) //head -1 bedeutet dass es empty ist
        return true;
    return false;
};


PriorityQueue::~PriorityQueue() { //θ(1)
    //TODO - Implementation
    delete[] this->elems; // destruktor


};
