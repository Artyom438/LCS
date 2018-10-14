// BS.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <conio.h>

using std::cin;
using std::cout;

struct Dictionary {
public:
  unsigned short Index;
  unsigned int Value;
};

void Sort(Dictionary *a, const unsigned short length) {
  Dictionary toReplace;
  for (unsigned short max, now, sorted = 0; sorted < length; ++sorted) {
    max = 0;
    for (now = 1; now < length - sorted; ++now){
      if (a[now].Value > a[max].Value)
        max = now;
    }
    toReplace.Value = a[length - sorted].Value;
    toReplace.Index = a[length - sorted].Index;
    a[length - sorted].Value = a[max].Value;
    a[length - sorted].Index = a[max].Index;
    a[max].Value = toReplace.Value;
    a[max].Index = toReplace.Index;
  }
}

/*unsigned int **CreateSortedArray(unsigned int *arrayToSort,
  const unsigned short length)
{
  unsigned int **SortedArray = new unsigned int *[length];
  unsigned int min = UINT_MAX, minCount = 0, *minAddress = NULL;
  for (unsigned int i = 0; i < length; ++i) {
    for (unsigned int j = 0; j < length; ++j) {
      if (arrayToSort[j] < min && min>=arr) {
        min = arrayToSort[j];
        minAddress = arrayToSort + j;
        minCount = 1;
      }
      else {
        if (arrayToSort[j] == min) {
          ++minCount;
        }
      }
    }
    SortedArray[i] = minAddress;
  }
  return SortedArray;
}*/

int main()
{
  unsigned short k = 15;
  Dictionary *rowY = new Dictionary[k];
  srand(time(NULL));
  for (unsigned short i = 0; i < k; ++i) {
    rowY[i].Value = rand() % 10;
    rowY[i].Index = i;
    cout << rowY[i].Value << ' ';
  }
  cout << '\n';
  Sort(rowY, k);
  for (unsigned short i = 0; i < k; ++i)
    cout << rowY[i].Value << ' ';
  cout << '\n';
  delete[] rowY;
  _getch();
  return 0;
}

