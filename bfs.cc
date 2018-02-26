int dirs[][] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
void diffuse(int x, int y) {
  // uint32_t rows, cols;
  // double* g;
  list<pair<int, int>> queue;
  queue.push_back(make_pair(x, y));
  while(!queue.empty()) {
    pair<int, int> coordination = queuq.front();
    queue.pop_front();
    int count = 0;
    for(auto dir : dirs) {
      int curX = coordination.first + dir[0];
      int curY = coordination.second + dir[1];
      if(curX < 0 || curY < 0 ||
	 curX >= rows || curY >= cols ||
	 g[curX * cols + curY] >=
	 g[coordination.first * cols + coordination.second])
	continue;
      g[curX * cols + curY] = c1 * g[coordination.first * cols + coordination.second];
      count++;
    }
    g[coordination.first * cols + coordination.second] = count * c1 * g[curX * cols + curY];
  }
}
