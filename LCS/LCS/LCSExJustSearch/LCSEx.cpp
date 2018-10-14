#include <iostream>

using std::cout;
using std::cin;

unsigned short FindMaxSubSequence(const unsigned int sizeX,
  const unsigned int *rowX, const unsigned int sizeY,
  const unsigned int *rowY, unsigned int *trashhold,
  const unsigned short score) {
  unsigned short res = 0;
  for (unsigned short len, indexY, indexX = 0; indexX < sizeX; ++indexX) {
    for (indexY = 0; indexY < sizeY; ++indexY) {
      if (rowX[indexX] == rowY[indexY] && score > trashhold[indexY]) {
        trashhold[indexY] = score;
        len = 1 + FindMaxSubSequence(sizeX - indexX - 1,
          rowX + indexX + 1, sizeY - indexY - 1, rowY + indexY + 1,
          trashhold + indexY + 1, score + 1);
        if (len > res) {
          res = len;
        }
        break;
      }
    }
  }
  return res;
}

int main() {
  unsigned short sizeX, sizeY;
  unsigned int *rowX, *rowY, *trashhold;
  cin >> sizeX;
  rowX = new unsigned int[sizeX];
  for (unsigned short i = 0; i < sizeX; ++i) {
    cin >> rowX[i];
  }
  cin >> sizeY;
  rowY = new unsigned int[sizeY];
  trashhold = new unsigned int[sizeY];
  for (unsigned short i = 0; i < sizeY; ++i) {
    cin >> rowY[i];
    trashhold[i] = 0;
  }
  cout << FindMaxSubSequence(sizeX, rowX, sizeY, rowY, trashhold, 1);
  delete[] rowX;
  delete[] rowY;
  delete[] trashhold;
  return 0;
}
