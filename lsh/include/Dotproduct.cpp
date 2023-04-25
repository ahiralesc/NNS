#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void producto_punto(vector<float> vec1, vector<float> vec2) {
    float producto = 0.0;
    float norma1 = 0.0;
    float norma2 = 0.0;

    // Calcular el producto punto entre los dos vectores
    for (int i = 0; i < vec1.size(); i++) {
        producto += vec1[i] * vec2[i];
        norma1 += vec1[i] * vec1[i];
        norma2 += vec2[i] * vec2[i];
    }

    // Normalizar el producto punto
    float resultado = (producto / (sqrt(norma1) * sqrt(norma2))) - 0.5;

    // Asegurarse de que el resultado esté en el rango [-1,1]
    if (resultado > 1.0) {
        resultado = 1.0;
    } else if (resultado <0) {
        resultado = 0;
    }

    // Imprimir el resultado
    cout << "El resultado del producto punto normalizado es: " << resultado << endl;
}

int main() {
    // Ejemplo de uso de la función
    vector<float> vec1 = {1.0, 2.0, 3.0};
    vector<float> vec2 = {4.0, 5.0, 6.0};
    producto_punto(vec1, vec2);
    return 0;
}
