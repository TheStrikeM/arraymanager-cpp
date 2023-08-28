#include <iostream>
#include <cmath>
using namespace std;

enum PrintType { STRING = 0, COLUMN = 1 };
class ArrayManager {
private:
    int** ptr;
    unsigned int currentLen;
    unsigned int lastIndex;
    bool isSorted = false;

    void setCurrentLen(unsigned int newLen) { currentLen = newLen; }
    void setLastIndex(unsigned int newLastIndex) { lastIndex = newLastIndex; }
    void setIsSorted(bool newSortedStatus) { isSorted = newSortedStatus; }

    void resize(unsigned int newLen) {
        *ptr = (int*) realloc(*ptr, (newLen + 1) * sizeof(int));
        setLastIndex((newLen-1));
        setCurrentLen(newLen);
    }
public:
    [[nodiscard]] unsigned int getLen() const { return currentLen; }
    [[nodiscard]] unsigned int getLastIndex() const { return lastIndex; }
    [[nodiscard]] bool getIsSorted() const { return isSorted; }
    [[nodiscard]] int** getPtr() const { return ptr; }

    ArrayManager(int** ptrArr, unsigned int len) {
        ptr = ptrArr;
        currentLen = len;
        lastIndex = len-1;

        *ptr = static_cast<int *>(malloc((len + 1) * sizeof(int)));
        for (int i = 0; i < len; i++)
            *(*(ptr)+i) = len-i;
    };

    bool operator == (const ArrayManager& arrayManager) const {
        bool flag = true;
        for (int i = 0; i < arrayManager.getLen(); i++)
            if ( *((*arrayManager.getPtr()) + i) != *((*ptr) + i) )
                flag = false;
        return flag;
    }

    ArrayManager& operator + (const ArrayManager& arrayManager) const {
        cout << "test" << endl;
        int* newArr;
        ArrayManager newArrManager(&newArr, currentLen+arrayManager.getLen());
        cout << "test" << endl;
        for (int i = 0; i < currentLen; i++)
            newArrManager.setElToIndex(*((*ptr) + i), i);
        for (unsigned int i = currentLen; i < currentLen+arrayManager.getLen(); i++)
            newArrManager.setElToIndex(*((*arrayManager.getPtr())+i-currentLen), i);
        return const_cast<ArrayManager &>(newArrManager);
    }

    void print(const PrintType type) const {
        if ( type == COLUMN ) {
            cout << "[---------]" << endl;
            for (int i = 0; i < currentLen; i++)
                cout << i << " - " << *((*ptr) + i) << endl;
            cout << "[---------]" << endl;
        }

        if ( type == STRING ) {
            cout << "[";
            for (int i = 0; i < currentLen; i++) {
                if ( i == lastIndex ) {
                    cout << *((*ptr) + i);
                    break;
                }
                cout << *((*ptr) + i) << ", ";
            }
            cout << "]" << endl;
        }
    }

    void clear() { while (currentLen > 0) { pop(); } }

    void add(int newEl) {
        resize(currentLen+1);
        *((*ptr) + lastIndex) = newEl;
    }

    void pop() {
        if ( currentLen == 0 )
            return;
        resize(currentLen-1);
    }

    void addByIndex(int newEl, unsigned int index) {
        resize(currentLen + 1);
        int tmp;
        for (unsigned int i = index; i < currentLen-1; i++) {
            if ( i == index ) {
                tmp = *((*ptr) + (i+1));
                *((*ptr) + (i+1)) = *((*ptr) + i);
                continue;
            }
            int test = *((*ptr) + (i+1));
            *((*ptr) + (i+1)) = tmp;
            tmp = test;
        }
        *((*ptr) + index) = newEl;
    }

    void removeByIndex(unsigned int index) {
        if ( index > lastIndex )
            return;
        for (unsigned int i = index; i < currentLen-1; i++) {
            *((*ptr) + i) = *((*ptr) + (i + 1));
        }
        resize(currentLen-1);
    }

    void setElToIndex(int newEl, unsigned int index) {
        *((*ptr) + index) = newEl;
    }

    void reverse() {
        for (int i = 0; i < currentLen; i++) {
            int symIndex = currentLen - 1 - i;

            if ( i == symIndex )
                break;

            int tmp = *((*ptr)+i);
            *((*ptr) + i) = *((*ptr) + symIndex);
            *((*ptr) + symIndex) = tmp;
        }
    }

    void bubbleSort() {
        int noSwap = 1;
        for (int i = 0; i < currentLen; i++) {
            for (int j = 0; j < (currentLen-1)-i; j++) {
                if ( *((*ptr)+j) > *((*ptr)+(j+1)) ) {
                    int tmp = *((*ptr) + j);
                    *((*ptr) + j) = *((*ptr) + (j + 1));
                    *((*ptr) + (j + 1)) = tmp;
                }
                noSwap = 0;
            }

            if (noSwap == 1)
                break;
        }

        setIsSorted(true);
    }

    void selectionSort() {
        for (int i = 0; i < currentLen; i++) {
            int minEl = INFINITY, locMinEl;
            for (int j = i; j < currentLen; j++) {
                if ( *((*ptr) + j) < minEl ) {
                    minEl = *((*ptr) + j);
                    locMinEl = j;
                }
            }
            int tmp = *((*ptr) + i);
            *((*ptr) + i) = *((*ptr) + locMinEl);
            *((*ptr) + locMinEl) = tmp;
        }

        setIsSorted(true);
    }

    void insertionSort() {
        setIsSorted(true);
    }

    [[nodiscard]] int binarySearch(int searchElement) {
        if ( !getIsSorted() ) {
            cout << "Работает только на отсортированном массиве" << endl;
            return -1;
        }

        if ( searchElement == *((*ptr) + lastIndex)  )
            return lastIndex;

        unsigned int start = 0;
        unsigned int end = currentLen-1;
        unsigned int middle = (start+end)/2;

        while (middle > 0) {
            middle = (start+end)/2;
            if ( searchElement < *((*ptr) + middle) )
                end = middle;
            else if (searchElement > *((*ptr) + middle))
                start = middle;
            else if (searchElement == *((*ptr) + middle))
                return middle;
        }
    }

};

int main() {
//    int* arr;
//    ArrayManager arrManager(&arr, 4);
//    arrManager.add(80);
//    cout << "----------" << endl;
//    arrManager.addByIndex(9, 1);
//    arrManager.setElToIndex(99, arrManager.getLastIndex());
//    arrManager.print(STRING);
//    arrManager.bubbleSort();
//    arrManager.print(STRING);
//    cout << arrManager.binarySearch(99) << endl;
//    cout << arrManager.binarySearch(99);


    int* arr1;
    int* arr2;
    ArrayManager arr1Manager(&arr1, 4), arr2Manager(&arr2, 4);
    arr1Manager.clear();
    arr1Manager.add(389);
    arr1Manager.print(STRING);
    arr2Manager.print(STRING);

//    ArrayManager newArrManager = arr1Manager + arr2Manager;
//    cout << newArrManager.getLen() << "Hello" << endl;
//    newArrManager.print(STRING);
    return 0;
}
