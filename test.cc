#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

int main(){
  int q, m, n;
  cin >> q >> m >> n;

  vector<vector<int>> v(m+n, vector<int>(q, 0));
  unordered_set<int> shared;
  unordered_map<int, int> folder_to_id;
  vector<int> id_to_folder;
  
  for (int i = 0; i < m; ++i){
    int curr, howmany;
    cin >> curr >> howmany;
    int newID = id_to_folder.size();
    folder_to_id[curr] = newID;
    id_to_folder.push_back(curr);

    for (int j = 0; j < howmany; ++j){
      int t;
      cin >> t;
      v[newID][t] = 1;
      shared.insert(newID);
    }
  }
  
  
  for (int i = 0; i < n; ++i){
    int curr, howmany;
    cin >> curr >> howmany;
    int newID = id_to_folder.size();
    folder_to_id[curr] = newID;
    id_to_folder.push_back(curr);

    for (int j = 0; j < howmany; ++j){
      int t;
      cin >> t;
      v[newID][t] = 1;
    }
  }

  int g;
  cin >> g;

  vector<int> parent(m+n, -1);
  for (int i = 0; i < g; ++i){
    int a, b;
    cin >> a >> b;
    parent[folder_to_id[b]] = folder_to_id[a];
  }

  /**
  cout << "--------" << endl;
  for (int i = 0; i < parent.size(); ++i){
    cout << i << ":" << parent[i] << endl;
  }
  **/

  /**
  for (int i = 0; i < m + n; ++i){
    for (int j = 0; j < q; ++j){
      cout << v[i][j] << ":";
    }
    cout << endl;
  }
  cout << endl;
  **/

  vector<int> leaves(m+n, 1);
  for (int i = 0; i < m+n; ++i){
    if (parent[i] != -1){
      leaves[parent[i]] = 0;
    }
  }

  vector<int> res(q, 1);
  vector<int> reslist;
  for (int i = 0; i < m+n; ++i){
    if (leaves[i] == 0){
      continue;
    }
  
    int curr = i;
    while (curr != -1){
      for (int j = 0; j < q; ++j){
	if (v[curr][j] != 0){
	  res[j] = 0;
	}
      }
      curr = parent[curr];
      if (!shared.count(curr)){
	break;
      }
    }

    for (int i = 0; i < q; ++i){
      if (res[i] == 1){
	reslist.push_back(i);
      }
    }
  }

  
  

  cout << "res: " << endl;
  for (auto i : reslist){
    cout << i << " ";
  }
  cout << endl;
  
  
}
