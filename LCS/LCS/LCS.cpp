#include <iostream>

using std::cout;
using std::cin;

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
          rowX + indexX + 1, sizeY, posY, rowY,
          trashhold, score + 1);
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

int main() {
  unsigned short sizeX, sizeY;
  unsigned int *rowX, *trashhold;
  Dictionary *rowY;
  cin >> sizeX;
  rowX = new unsigned int[sizeX];
  for (unsigned short i = 0; i < sizeX; ++i) {
    cin >> rowX[i];
  }
  cin >> sizeY;
  rowY = new Dictionary[sizeY];
  trashhold = new unsigned int[sizeY];
  for (unsigned short i = 0; i < sizeY; ++i) {
    rowY[i].Index = i;
    cin >> rowY[i].Value;
    trashhold[i] = 0;
  }
  Sort(rowY, sizeY);
  cout << FindMaxSubSequence(sizeX, rowX, sizeY, NoBorder, rowY, trashhold, 1);
  delete[] rowX;
  delete[] rowY;
  delete[] trashhold;
  return 0;
}
