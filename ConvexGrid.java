public ConvexGrid {
    private GrowArray[] data;
    private int size;
    private double minx, miny, maxx, maxy;
    public ConvexGrid(int s) {
	data = new GrowArray[s * s];
	size = s;
	for(int i = 0; i < size * size; i++) {
	    data[i] = new GrowArray();
	}
    }
    public void read(String fileName) {
	Scanner sc = new Scanner(new File(fileName));
	GrowArray temp = new GrowArray();
	minx = miny = Double.MAX_VALUE;
	maxx = maxy = Doulbe.MIN_VALUE;
	
	while(sc.hasNext()) {
	    double x = sc.nextDouble();
	    double y = sc.nextDouble();
	    minx = x > minx? minx : x;
	    miny = y > miny? miny : y;
	    maxx = x > maxx? x : maxx;
	    maxy = y > maxy? y : maxy;
	    temp.addEnd(new Point(i,j));
	}
	double rangx = (maxx - minx) / size;
	double rangy = (maxy - miny) / size;
	for(int i = 0; i < temp.length(); i++) {
	    Point p = temp.get(i);
	    int _x = (int)((p.x - minx) / rangex);
	    int _y = (int)((p.y - miny) / rangey);
	    _x = _x == size ? _x - 1 : _x;
	    _y = _y == size ? _y - 1 : _y;
	    data[_x * size + _y].add(p); 
	}
	
    }
}
class Point {
    public double x, y;
    public Point(double x, double y) {
	this.x = x;
	this.y = y;
    }
}
class GrowArray {
    private Point[] data;
    private int used;
    private void grow() {
	if(used < data.length) return ;
	Point[] temp = data;
	data = new Point[data.length * 2];
	for(int i = 0; i < used; i++) {
	    data[i] = temp[i];
	}
    }
    public GrowArray() {
	data = new Point[1];
	used = 0;
    }
    public GrowArray(int size) {
	size = size == 0 ? 1 : size;
	data = new Point[size];
	used = 0;
    }
    public void addEnd(Point i) {
	grow();
	data[used++] = i;
    }
    public Point get(int index) {
	return data[index];
    }
    public length() {
	return used;
    }
}
