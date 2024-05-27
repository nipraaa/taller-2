#include "SistemaImpl.h"
using namespace std;



int main() {
    SistemaImpl sistema("users.csv"); // Crear instancia de SistemaImpl con la ruta del archivo
    sistema.mostrarMenu(); // Mostrar el menú y gestionar las opciones
    return 0;
}
