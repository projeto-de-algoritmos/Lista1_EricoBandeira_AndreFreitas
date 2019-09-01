#include <iostream> 
#include <list> 
#include <stack> 
using namespace std; 

class Graph 
{ 
	int V; 
	list<int> *adj; 

	
	void fillOrder(int v, bool visited[], stack<int> &Stack); 

	
	void DFSUtil(int v, bool visited[]); 
public: 
	Graph(int V); 
	void addEdge(int v, int w); 


	void printSCCs(); 


	Graph getTranspose(); 
}; 

Graph::Graph(int V) 
{ 
	this->V = V; 
	adj = new list<int>[V]; 
} 


void Graph::DFSUtil(int v, bool visited[]) 
{ 

	visited[v] = true; 
	cout << v << " "; 

	
	list<int>::iterator i; 
	for (i = adj[v].begin(); i != adj[v].end(); ++i) 
		if (!visited[*i]) 
			DFSUtil(*i, visited); 
} 

Graph Graph::getTranspose() 
{ 
	Graph g(V); 
	for (int v = 0; v < V; v++) 
	{ 
	
		list<int>::iterator i; 
		for(i = adj[v].begin(); i != adj[v].end(); ++i) 
		{ 
			g.adj[*i].push_back(v); 
		} 
	} 
	return g; 
} 

void Graph::addEdge(int v, int w) 
{ 
	adj[v].push_back(w); 
} 

void Graph::fillOrder(int v, bool visited[], stack<int> &Stack) 
{ 

	visited[v] = true; 

	
	list<int>::iterator i; 
	for(i = adj[v].begin(); i != adj[v].end(); ++i) 
		if(!visited[*i]) 
			fillOrder(*i, visited, Stack); 


	Stack.push(v); 
} 


void Graph::printSCCs() 
{ 
	stack<int> Stack; 


	bool *visited = new bool[V]; 
	for(int i = 0; i < V; i++) 
		visited[i] = false; 

	
	for(int i = 0; i < V; i++) 
		if(visited[i] == false) 
			fillOrder(i, visited, Stack); 

	
	Graph gr = getTranspose(); 

	
	for(int i = 0; i < V; i++) 
		visited[i] = false; 

	
	while (Stack.empty() == false) 
	{ 
	
		int v = Stack.top(); 
		Stack.pop(); 

		
		if (visited[v] == false) 
		{ 
			gr.DFSUtil(v, visited); 
			cout << endl; 
		} 
	} 
} 


int main() 
{ 
	int nodes;
  cout<<"Insira o numero de nós que seu grafo terá!"<<endl;
  cin>>nodes;

  int conex;
  cout<<"Insira o numero de conexões que você deseja implementar no seu grafo direcionado!"<<endl;
  cin>>conex;
  
  cout<<"Agora, para cada conexão digite o caminho da seta!"<<endl;
  cout<<"Por exemplo,se o nó 0 é conectado com o nó 5\nPara isso, digite apenas '0 5'\n"<<endl;
  cout<<"Vamos lá!"<<endl;


	Graph g(nodes); 
  int i =0;
  while(conex--){
    i++;
    cout<<"insira a conexão numero "<<i<<endl;
    int a,b;
    cin>>a>>b;
    g.addEdge(a,b); 

  }

	   
	

	cout << "\nAqui estão os componentes fortemente conectados do seu Grafo!\n"; 
	g.printSCCs(); 

	return 0; 
} 
