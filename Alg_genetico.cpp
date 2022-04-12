#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <fstream>
#include <cmath>

using namespace std;

struct Node {
    int x, y;

    Node(int x, int y) : x(x), y(y) {}
};

vector<Node> nodes;
int inicial;

int randomInt(int ini, int fin) {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> randNode(ini, fin);
    return randNode(mt);
}

// Crear nodos random
void createRandom(int n) {
    for (int i = 0; i < n; i++) {
        Node newNode(randomInt(0, 100), randomInt(0, 100));
        nodes.push_back(newNode);
    }
}

// Generar población inicial
vector<int> generateRandomIndividual(int n) {
    vector<int> indices;
    vector<int> individual;
    indices.reserve(n);
    for (int i = 0; i < n; i++) {
        indices.push_back(i);
    }
    indices.erase(indices.begin() + inicial);
    while (!indices.empty()) {
        int x = randomInt(0, (int)indices.size() - 1);
        individual.push_back(indices[x]);
        indices.erase(indices.begin() + x);
    }
    return individual;
}

// Distancia Euclidiana
float Euclidean(Node a, Node b) {
    auto distance = (float)sqrt((pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
    return distance;
}

// Cálculo aptitud(sumar distancias)
float fitness(const vector<int>& individual) {
    float sum = Euclidean(nodes[inicial], nodes[individual[0]]);
    for (int i = 0; i < individual.size() - 1; i++) {
        sum = sum + Euclidean(nodes[individual[i]], nodes[individual[i + 1]]);
    }
    sum = sum + Euclidean(nodes[individual[individual.size() - 1]], nodes[inicial]);
    return sum;
}
vector<int> MBD(vector<int> individual) {
    vector<int> mutated(individual.begin(), individual.end());
    int pos1;
    //do {
        pos1 =randomInt(0, individual.size()-1);
    //} while (/*pos1 == 0 ||*/ pos1 >= individual.size() - 1);

    int pos2;
    do {
        pos2 = randomInt(0, individual.size()-1);
    } while (/*pos2 == 0 || pos2 >= individual.size() - 1 ||*/ pos2 == pos1);

    int minval, maxval;
    if (pos1 < pos2) {
        minval = pos1;
        maxval = pos2;
    }
    else {
        minval = pos2;
        maxval = pos1;
    }
    if (randomInt(0, 1) == 0) {
        mutated.insert(mutated.begin() + minval, mutated[maxval]);
        mutated.erase(mutated.begin() + maxval + 1);
    }
    else {
        mutated.insert(mutated.begin() + maxval + 1, mutated[minval]);
        mutated.erase(mutated.begin() + minval);
    }

    return mutated;
}
// TODO: Media
float average(vector<float> fitnessValues, int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum = sum + fitnessValues[i];
    }
    return sum / (float)n;
}

//// TODO: Mutación Basada en Posición
//vector<int> MBP(const vector<int> &individual) {
//
//}
//
//// TODO: Mutación Basada en Orden
//vector<int> MBO(const vector<int> &individual) {
//
//}

// TODO: Mutación Basada en Desorden
//vector<int> MBD(const vector<int>& individual) {
//    vector<int> mutated(individual.begin(), individual.end());
//    int ini = randomInt(0, (int)mutated.size() - 1);
//    int fin = randomInt(ini, (int)mutated.size() - 1);
//    for (int i = 0; i < (fin - ini) * 2; i++) {
//        int a = randomInt(ini, fin);
//        int b = randomInt(ini, fin);
//        int c = mutated[a];
//        mutated[a] = mutated[b];
//        mutated[b] = c;
//    }
//    return mutated;
//}
vector<int> MBP(vector<int> individual) {
    vector<int> n(individual.begin(),individual.end());
    int pos1;
    //do {
        pos1 = randomInt(0, n.size()-1);
    //} while (pos1 == 0 || pos1 >= n.size() - 1);
    
    int pos2;
    do {
        pos2 = randomInt(0, n.size()-1);
    } while (/*pos2 == 0 || pos2 >= n.size() - 1 ||*/ pos2 == pos1);
    swap(n[pos1], n[pos2]);
    return n;

}
// TODO: Crossover de Orden
void Crossover(vector<vector<int>>& gen, const vector<int>& individual1, const vector<int>& individual2) {

    vector<int> hijo1(individual1.size(), -1);
    vector<int> hijo2(individual2.size(), -1);
    vector<int> visited1(individual1.size() + 1, 0);
    vector<int> visited2(individual2.size() + 1, 0);

    //    vector<int> boleanos = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < individual1.size(); i++) {
        if (randomInt(0, 1)) {
            hijo1[i] = individual2[i];
            visited1[individual2[i]] = 1;

            hijo2[i] = individual1[i];
            visited2[individual1[i]] = 1;
        }
    }

    int iterHijo = 0;
    for (int i : individual1) {
        while (iterHijo < hijo1.size() && hijo1[iterHijo] != -1) {
            iterHijo++;
        }
        if (!visited1[i]) {
            hijo1[iterHijo] = i;
        }
    }

    iterHijo = 0;
    for (int i : individual2) {
        while (iterHijo < hijo1.size() && hijo2[iterHijo] != -1) {
            iterHijo++;
        }
        if (!visited2[i]) {
            hijo2[iterHijo] = i;
            visited2[i] = 1;
        }
    }
    gen.push_back(hijo1);
    gen.push_back(hijo2);
}

void writetxt(string nombre, double nrogen, double amplitud) {
    ofstream myfile;
    myfile.open(nombre + ".txt",ios::app);
    myfile << nrogen << "," << amplitud << "\n";
    myfile.close();
}
void writetxt(string nombre, int nrogen, vector<int> genvals) {
    ofstream myfile;
    myfile.open(nombre + ".txt", ios::app);

    myfile << nrogen << "-";
    myfile << nodes[inicial].x << "," << nodes[inicial].y<<"_";
    
    for (int citie : genvals) {
        myfile << nodes[citie].x << "," << nodes[citie].y << "_";
    }

    myfile << nodes[inicial].x << "," << nodes[inicial].y << "_";
    myfile << "\n";
    myfile.close();
}

int main() {
    int n = 10; // Número de nodos
    int p = 20; // Tamaños de la población
    int g = 50; // Número de generaciones
    int cantEli = 2; // Cantidad Elitismo
    int probCru = (int)round((p - cantEli) * 0.4); // Probabilidad Cruzamiento
    int probMut = p - probCru; // Probabilidad Mutación

    createRandom(n);

    inicial = randomInt(0, n - 1);

    // Generación Población Inicial
    vector<vector<int>> generation;
    generation.reserve(p);
    for (int i = 0; i < p; i++) {
        generation.push_back(generateRandomIndividual(n));
    }

    // Seleccionar nodo Inicial aleatorio

    // Algoritmo genético
    for (int i = 0; i < g; i++) {

        // Calcular la aptitud de cada individuo
        vector<float> fitnessValues(generation.size());
        for (int ind = 0; ind < generation.size(); ind++) {
            fitnessValues[ind] = 1 / fitness(generation[ind]);
        }

        // Selección: Calcular valor esperado y valor Actual
        float media = average(fitnessValues, (int)generation.size());
        multimap<float, vector<int>> VA;
        for (int ind = 0; ind < generation.size(); ind++) {
            VA.insert(pair<float, vector<int>>(fitnessValues[ind] / media, generation[ind]));
        }

        auto best = VA.end();
        best--;

        writetxt("ploting", media,best->first);
        writetxt("showing", i, best->second);


        // Crear la nueva generación
        vector<pair<int, vector<int>>> ordenados;


        for (const auto& indi : VA) {
            if (indi.first > 0) {
                int cant = (int)round(indi.first);
                ordenados.emplace_back(cant, indi.second);
            }
        }
        reverse(ordenados.begin(), ordenados.end());


        vector<vector<int>> newGen;
        // Elitismo
        newGen.push_back(ordenados[0].second);
        newGen.push_back(ordenados[1].second);
        ////        int elite = 0;
        //        int iter = 0;
        //        while (!ordenados.empty() and elite < cantEli) {
        //            newGen.push_back(ordenados[iter].second);
        //            ordenados[iter].first--;
        //            if (ordenados[iter].first == 0) {
        //                ordenados.erase(ordenados.begin() + iter);
        //            } else {
        //                iter++;
        //            }
        //            elite++;
        //        }

                // Operador de cria
        int crias = 0;
        while (!ordenados.empty() and crias < probCru - 1) {
            int iter2 = 0;
            int pares = 0;
            int totalPares = ordenados[0].first;
            while (pares < totalPares and crias < probCru) {
                Crossover(newGen, ordenados[0].second, ordenados[iter2 + 1].second);
                crias += 2;
                ordenados[iter2 + 1].first--;
                ordenados[0].first--;
                if (ordenados[iter2 + 1].first == 0) {
                    ordenados.erase(ordenados.begin() + iter2);
                }
                else {
                    iter2++;
                }
                pares++;
            }
            if (ordenados[0].first == 0) {
                ordenados.erase(ordenados.begin());
            }
        }

        // Operador de mutación
        int iter3 = 0;
        int mutations = 0;
        while (mutations < probMut - 1) {
            for (int j = 0; j < ordenados[iter3].first; j++) {
                newGen.push_back(MBD(ordenados[iter3].second));
                mutations++;
                if (mutations >= probMut) {
                    break;
                }
            }
        }
        generation = newGen;
    }
}
