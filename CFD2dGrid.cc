#include <iostream>
#include <list>
using namespace std;

class Grid2d{
private:
  double* g;
  double* gNext;
  double c1;
  double c2;
  uint32_t rows;
  uint32_t cols;
  int dirs[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
public:
  Grid2d(uint32_t i, uint32_t j, double val = 0) : rows(i), cols(j) {       //CONSTRUCTOR
    g = new double[rows * cols];
    gNext = new double[rows * cols];
    for(int p = 0; p < i * j; p++)
      g[p] = val;
    c1 = 0.4;
    c2 = 0.2;
  }

  ~Grid2d(){                                                                     //DESTRUCTOR
    delete []g; 
  }

  Grid2d(const Grid2d& orig){                                                    //COPY CONSTRUCTOR
    g = new double[orig.rows * orig.cols];
    rows = orig.rows;
    cols = orig.cols;
    for(int p = 0; p < rows * cols; p++)
      g[p] = orig.g[p];
  }

  Grid2d& operator =(const Grid2d& orig){                                        //OPERATOR =
    Grid2d copy(orig);
    swap(copy.g,g);
    swap(copy.rows,rows);
    swap(copy.cols,cols);
  }

  void startPoint(uint32_t i, uint32_t j, double conc){
      g[i*cols + j] = conc;
   }

  void specPoint(uint32_t i, uint32_t j) const {
    cout <<  g[i*cols + j] << '\n';
  }
  
  void diffuse() {
    for(int i = 0; i < rows; i++) {
      for(int j = 0; j < cols; j++) {
	double cur = c1 * g[i * cols + j];
	for(auto dir : dirs) {
	  int x = i + dir[0];
	  int y = j + dir[1];
	  if(x >= 0 && x < rows && y >= 0 && y < cols)
	    cur += c2 * g[x * cols + y];
	}
	gNext[i * cols + j] = cur;
      }
    }
    double* temp = g;
    g = gNext;
    gNext = temp;
    
  }
  friend ostream& operator << (ostream& s, const Grid2d& grid);  
};

ostream& operator << (ostream& s, const Grid2d& grid){
  for(int p = 0; p < grid.rows * grid.cols; p++){
    if( p != 0 && p % grid.cols == 0)
      s << '\n';
    s << grid.g[p] << '\t';
  }
  return s << '\n';  
}




int main() {
  Grid2d grid(10, 10);
  // cout << grid; 
  grid.startPoint(0,0,5);
  grid.startPoint(9,9,5);
  cout << grid;
  grid.specPoint(0,0);
  for(int i = 0; i < 10; i++) {
    grid.diffuse();
    cout << grid << endl;
  }
 
  /*
  g.printInitGrid();
  g.printGrid();
  g.printFinalGrid();*/
  
}
