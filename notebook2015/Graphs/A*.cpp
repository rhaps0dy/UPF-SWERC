int N = 1000; // numero de nodos
typedef set<pair<int,int> > S;  // cola de prioridad
vector<pair<int,int> > V[1000];  // lista de adyacencia (coste, vecino)

int heuristic(int from, int to) { // heurística de "from" a "to"
    return 0;
}

int Astar(int from, int to) {
    set<int> open;        // lista abierta de nodos activos
    set<int> closed;      // lista cerrada de nodos ya procesados
    map<int,int> fscore;  // coste real + heurística
    map<int,int> gscore;  // coste real
    S queue;              // cola de prioridad (coste, nodo)
    map<int,int> parent;  // para reconstruir el camino
  
    open.insert( from );
    fscore[ from ] = heuristic( from, to );
    gscore[ from ] = 0;
    queue.insert( make_pair( fscore[ from ], from ) );
  
    while (closed.find(to) == closed.end()) {
    
        pair<int,int> p = *queue.begin();
        open.erase(p.second);
        closed.insert(p.second);
        queue.erase(queue.begin());
    
        for (unsigned i = 0; i < V[ p.second ].size(); ++i){
      
            int neigh = V[ p.second ][i].second;
            int g = gscore[ p.second ] + V[ p.second ][i].first;
            int f = g + heuristic( neigh, to );
      
            if ( (open.find( neigh ) == open.end() && closed.find( neigh ) == closed.end() ) || f < fscore[ neigh ] )
            {
                open.erase( neigh );
                queue.erase( make_pair( fscore[ neigh ], neigh ) );
                parent[ neigh ] = p.second;
                fscore[ neigh ] = f;
                gscore[ neigh ] = g;
                open.insert( neigh );
                queue.insert( make_pair( fscore[ neigh ], neigh ) );
            }
        }
    }
  
    // reconstruir camino por "parent" si hace falta
    int actual = to;
  
    list<int> l;
    list<int>::iterator il;
  
    while ( parent[ actual ] != from ) {
        l.push_front( actual );
        actual = parent[ actual ];
    }

    l.push_front( actual );
    l.push_front( parent[ actual ] );
  
    cout<< "Path = [";
  
    for (il = l.begin(); il != l.end(); il++){
        if( *il == to ){
          cout<< *il<<"] with cost ";
          break;
        }
        cout<< *il<<", ";
    }
    return gscore[ to ];
}

int main(){
    N = 3;
    V[0].push_back( make_pair( 1, 1 ) );
    V[1].push_back( make_pair( 2, 2 ) );
    cout<< Astar( 0, 2 ) <<endl;
    return 0;
}
