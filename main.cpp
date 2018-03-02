#include <iostream>
class PointerPratice {
private:
  char* data;
public:
  PointerPratice(){
    data = new char[40 * 50];
  }
  void fillWithZero() {
    char* p = data;
    for(int i = 0; i < 40 * 50; i++) {
      *(p + i) = 0;
    }
  }
  void setRow(int row, char v) {
    char* p = data;
    p = p + row * 50;
    for(i = 0; i < 50; i++) {
      *(p + i) = v;
    }
  }
};
int main() {
  PointerPratice p;
  p.fillWithZero();
  p.print();
  p.setRow(4, '1');
}
