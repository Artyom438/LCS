// LCS.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

const short NotFound = -1;
const short NoBorder = -1;

struct Dictionary {
public:
  unsigned short Index;
  unsigned int Value;
};

void Sort(Dictionary *row, const unsigned short length) {
  Dictionary toReplace;
  for (unsigned short max, now, sorted = 0; sorted < length; ++sorted) {
    max = 0;
    for (now = 1; now < length - sorted; ++now) {
      if (row[now].Value > row[max].Value) {
        max = now;
      }
      else {
        if (row[now].Value == row[max].Value &&
          row[now].Index > row[max].Index) {
          max = now;
        }
      }
    }
    toReplace.Value = row[length - sorted - 1].Value;
    toReplace.Index = row[length - sorted - 1].Index;
    row[length - sorted - 1].Value = row[max].Value;
    row[length - sorted - 1].Index = row[max].Index;
    row[max].Value = toReplace.Value;
    row[max].Index = toReplace.Index;
  }
}

short Search(const Dictionary *sortedRow, const unsigned short length,
  const unsigned int toFind, const short lowerBorder) {
  unsigned short first = 0;
  unsigned short last = length;
  while (first < last) {
    unsigned short mid = first + (last - first) / 2;
    if (toFind < sortedRow[mid].Value ||
      (toFind == sortedRow[mid].Value && lowerBorder < sortedRow[mid].Index))
      last = mid;
    else
      first = mid + 1;
  }
  if (last < length && sortedRow[last].Value == toFind) {
    return sortedRow[last].Index;
  }
  else {
    return NotFound;
  }
}

unsigned short FindMaxSubSequence(const unsigned int sizeX,
  const unsigned int *rowX, const unsigned int sizeY,
  const short lowerBorderY, const Dictionary *rowY,
  unsigned int *trashhold, const unsigned short score) {
  unsigned short res = 0;
  short posY;
  for (unsigned short len, indexX = 0; indexX < sizeX; ++indexX) {
    posY = Search(rowY, sizeY, rowX[indexX], lowerBorderY);
    if (posY != NotFound) {
      if (score > trashhold[posY]) {
        trashhold[posY] = score;
        len = 1 + FindMaxSubSequence(sizeX - indexX - 1,
          rowX + indexX + 1, sizeY/* - indexY - 1*/, posY, rowY/* + indexY + 1*/,
          trashhold/* + indexY + 1*/, score + 1);
        if (len > res) {
          res = len;
        }
      }
    }
    while (indexX < sizeX && rowX[indexX] == rowX[indexX + 1])
      ++indexX;
  }
  return res;
}

void RunTests()
{
  unsigned short n, k, checkAns, res;
  unsigned int *x, *trashhold;
  Dictionary *y;
  ifstream fIn("Input.txt");
  /*if (fIn.is_open())
  cout << "ok\n";
  else
  cout << "Bad file\n";*/
  while (!fIn.eof())
  {
    fIn >> n;
    x = new unsigned int[n];
    for (unsigned short i = 0; i < n; ++i)
      fIn >> x[i];
    fIn >> k;
    y = new Dictionary[k];
    trashhold = new unsigned int[k];
    for (unsigned short i = 0; i < k; ++i) {
      y[i].Index = i;
      fIn >> y[i].Value;
    }
    Sort(y, k);
    fIn >> checkAns;
    cout << "n: " << n << " k: " << k << "\nX:\n";
    for (unsigned short i = 0; i < n; ++i)
      cout << x[i] << ' ';
    cout << "\nY:\n";
    for (unsigned short i = 0; i < k; ++i) {
      cout << y[i].Value << ' ';
      trashhold[i] = 0;
    }
    res = FindMaxSubSequence(n, x, k, NoBorder, y, trashhold, 1);
    cout << "\nTrashhold:\n";
    for (unsigned short i = 0; i < k; ++i) {
      cout << trashhold[i] << ' ';
    }
    cout << "\nCheck: " << checkAns << "\nRes: "
      << res << "\n\n";
    if (res != checkAns) { 
      cout << "Wrong answer!!!!!!!\nPress any key to accept suck...";
      _getch();
    }
    delete[] x;
    delete[] y;
    delete[] trashhold;
  }
  fIn.close();
  cout << "ok";
}
int main()
{
  RunTests();
  /*unsigned short n, k;
  unsigned int *x, *y;
  cin >> n;
  x = new unsigned int[n];
  for (unsigned short i = 0; i < n; ++i)
    cin >> x[i];
  cin >> k;
  y = new unsigned int[k];
  for (unsigned short i = 0; i < k; ++i)
    cin >> y[i];
  cout << FindMaxSubSequence(n, x, k, y);
  delete[] x;
  delete[] y;*/
  _getch();
  return 0;
}