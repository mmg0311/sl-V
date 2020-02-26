#include<iostream>
#include<vector>
#include<map>
using namespace std;

void bellman_ford(map<char,vector<pair<int,char>>> &m,vector<char> &v,int e){
   map<char,int> dist;
   map<char,bool> visited;
   int min = INT8_MAX;
   char src,src1;
   cout << "Enter source : ";
   cin >> src;
   int count = v.size();
   for(int i = 0; i < v.size() ; i++){
       if(v[i] == src){
           dist[src] = 0;
           visited[src] = true;
       }else{
           dist[v[i]] = INT8_MAX;
           visited[v[i]] = false; 
       }
   }
   for(auto d: dist){
            cout << "(" << d.first << "," << d.second << ") ";
    }
   cout << "\nStep 1 :\n";
   for(int i = 0; i < v.size() ; i++){
        cout << "source : " << src << endl;
        visited[src] = true;
        vector<pair<int,char>> p = m[src];
        for(auto d : p){
            if(d.first + dist[src] < dist[d.second]) {
                dist[d.second] = d.first + dist[src];
                if(min > dist[d.second]){
                    min = dist[d.second];
                    src1 = d.second;
                }
            }
        }
        if(src == src1){
            int mm = INT8_MAX;
            for(int i = 0; i < v.size() ;  i++){
                if(mm > dist[v[i]] && !visited[v[i]]){
                    src = v[i];
                }
            }
        }else{
            src = src1;
        }
        cout << "visited : ";
        for(auto visit : visited){
            cout << "(" << visit.first << ","  << visit.second << ")";
        }
        cout << endl;
        cout << "distances :"; 
        for(auto d: dist){
            cout << "(" << d.first << "," << d.second << ") ";
        }
        cout << endl;
   }
    cout << "Step 2 (checking the negative cycle):\n" ;
    for(int i = 0; i < v.size() ; i++){
        vector<pair<int,char>> p = m[src];
        for(auto d : p){
            if(d.first + dist[src] < dist[d.second]) {
                dist[d.second] = d.first + dist[src];
                cout << "NEGATIVE CYCLE \n";
                return;
            }
        }
        for(auto d: dist){
            cout << "(" << d.first << "," << d.second << ") ";
        }
        cout << endl;
    }
}

int main(){
    map<char,vector<pair<int,char>>> m;
    int n,e,w;
    char temp,temp2;
    vector<char> v;
    cout << "Enter the number of vertices : ";
    cin >> n;
    cout << "Enter the number of edges : ";
    cin >> e;
    cout << "Enter the vertices :";
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        v.push_back(temp);
    }
    cout << "Enter the weights of edges ";
    // for(int i = 0 ; i < n ; i++){
    //     for(int j = 0 ; j < n ; j++){
    //         if(i != j){
    //             cout << v[i] << "->" << v[j] << " : ";
    //             cin >> w;
    //             if(w != 0){
    //                 m[v[i]].push_back(make_pair(w,v[j]));
    //             }
    //         }
    //     }
    // }
    for(int i = 0 ; i < e ; i++){
        cin >> temp >> temp2 >> w;
        m[temp].push_back(make_pair(w,temp2));
    }
    for(map<char , vector< pair<int, char > > >::iterator it = m.begin() ; it != m.end() ; it++){
        cout << it->first << ":";
        vector<pair<int,char>> p = it->second;
        for(auto d : p){
            cout << "(" << d.first << "," << d.second << ") " ; 
        }
        cout << endl;
    }

    bellman_ford(m,v,e);
}   



//    for(map<char , vector< pair<int, char > > >::iterator it = m.begin() ; it != m.end() ; it++){
//         vector<pair<int,char>> p = it->second;
//         for(auto d : p){
//             if(d.first + dist[it->first] < dist[d.second]) {
//                 dist[d.second] = d.first + dist[it->first];
//             }
//         }
//         for(auto d: dist){
//             cout << "(" << d.first << "," << d.second << ") ";
//         }
//         cout << endl;
//     }

// for(map<char , vector< pair<int, char > > >::iterator it = m.begin() ; it != m.end() ; it++){
    //     vector<pair<int,char>> p = it->second;
    //     for(auto d : p){
    //         if(d.first + dist[it->first] < dist[d.second]) {
    //             dist[d.second] = d.first + dist[it->first];
    //             cout << "NEGATIVE CYCLE \n";
    //             return;
    //         }
    //     }
    //     for(auto d: dist){
    //         cout << "(" << d.first << "," << d.second << ") ";
    //     }
    //     cout << endl;
    // }