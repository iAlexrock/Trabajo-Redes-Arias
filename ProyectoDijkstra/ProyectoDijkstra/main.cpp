//Hecho por: Alejandro Arias 20180120


#include<iostream>
#include <ctime>
#include <iomanip>
using namespace std;
//#define infinito =9999;
//creando los valores globales
int v, costos[50][50], nodinicio, distancias[50], recorrido[50];  //vertice, matriz costos, vertice de inicio, distancias a partir del nodo inicial, recorrido o seguimiento de los nodos
bool visitado[50] ;//comprueba si es que el nodo ha sido visitado, permitiendo que se visiten todos los nodos y sus costos, inicializa en 0 = falso

void inicializarvalores() {
	//la teoria de dijkstra indica que el nodo inicial tiene distancia 0 hacia si mismo	
	//Aquellos nodos que esten conectados con el inicial mantienen por mientras distancia
	//aquellos nodos que no esten conectados con el inicial tienen una distancia infinita o extremadamente grande
	for (int i = 0; i < v; i++) {
		recorrido[i] = i;
		if (costos[nodinicio][i] < 9999) {
			distancias[i] = costos[nodinicio][i];
			recorrido[i] = nodinicio;
		}
		else
			distancias[i] = 9999;
	}
	distancias[nodinicio] = 0;
	visitado[nodinicio] = true; //se presupone que el nodo inicio ya ha sido visitado, por eso se obtienen las distancias base
	recorrido[nodinicio] = -1; //Se pone -1 para que indique que es el nodo inicial, y que la recursiva no sea infinita
}
int obtenercercano() {	
	int nodomenor= 0;	
	int dminima=9999;	 //distancia minima posible
	for (int i = 0; i < v; i++) {
		if (visitado[i] == false && distancias[i] < dminima) {
			dminima = distancias[i]; // el valor de dminima va reduciendose a medida que encuentra menores valores 
			nodomenor = i;					
		}		
	}	
	return nodomenor;
}

void calculardistancias() { //hace dijkstra
	for (int i = 0; i < v; i++) { 
		int nodomenor = obtenercercano();	
		visitado[nodomenor] = true;			
		for (int j = 0; j < v; j++) { //relajacion
			if (costos[nodomenor][j] !=  9999 && distancias[nodomenor] + costos[nodomenor][j] < distancias[j]) {
				distancias[j] = distancias[nodomenor] + costos[nodomenor][j];	
				recorrido[j] = nodomenor;  
			}
		}	
	}
}

void recursiva(int x) {	//Permite obtener el recorrido de todos los nodos desde el inicial de manera recursiva
	if (recorrido[x] == -1) {
		cout <<  x + 1 << endl;
	}
	else {
		cout << x +1 << "<--" << " ";
		recursiva(recorrido[x]);
	}
}

void impresiones() { 
	//imprime una columna con los nodos, otra con la distancia mínima obtenida y finalmente una columna con el recorrido
	cout << "Nodo" << "\t\t" << "Distancia Min" << "\t\t" << "Recorrido" << endl;

	for (int i = 0; i < v; i++) {
		cout << i + 1 << "\t\t" << distancias[i] << "\t\t"; 
		recursiva(i);
	}
}

int main() {
	clock_t start, end;
	cout << "Insertar numero de nodos: ";
	cin >> (v);
	cout << "Ingresar matriz de costos: " << endl;
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			cin >> costos[i][j]; 
			//Ambos for permiten que al pegar la matriz se vaya creando de manera automática la matriz costos 
		}
	}
	cout << "Ingresar el nodo inicial: ";
	cin >> nodinicio;
	nodinicio = nodinicio - 1;
	start = clock();
	inicializarvalores();
	calculardistancias();
	impresiones();	
	end = clock();

	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout << "La duracion de la ejecucion fue de: " << fixed << time_taken << setprecision(5);
	return 0;
}