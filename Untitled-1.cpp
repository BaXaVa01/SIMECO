// Quisiera declararle mi amor, pero solo se declarar variables

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstdlib>
#include <algorithm>
#include <fstream> // Para std::ifstream y std::ofstream
#include <sstream> // Para std::istringstream
#include "Guardado.cpp"

using namespace std;

string filename="C:\\Users\\david\\OneDrive\\Escritorio\\SIMECOGPT\\output\\usuarios\\davide-patino\\animales\\ciclo0.bin";




enum estaciones
{
    Primavera,
    Verano,
    Otonio,
    Invierno
};

enum class Genero
{
    Macho,
    Hembra
};

enum class TipoDesastre
{
    Incendio,
    Inundacion,
    Sequia,
    Huracan
};

class Especie
{
public:
    string nombre;
    int poblacionInicial;
    int poblacion;

    Especie(string nombre, int poblacionInicial) : nombre(nombre), poblacionInicial(poblacionInicial), poblacion(poblacionInicial) {}
};

class Recursos
{
public:
    int agua;
    int carrona;
    int carne;
    int vegetacion;
    int vegetacionConsumida; // Necesitas llevar un registro de la vegetación consumida

    Recursos(int agua, int carrona, int carne, int vegetacion)
        : agua(agua), carrona(carrona), carne(carne), vegetacion(vegetacion), vegetacionConsumida(0) {}

    void actualizarRecursos(estaciones estacion)
    {
        // Tengo que poner un nivel maximo de vegetacion
         int nivelMaxVegetacion = 100000;
         int nivelMaxAgua = 10000;

        // switch(estacion) {
        //     case Primavera:

        //     case Verano:

        //     case Otonio:

        //     case Invierno:
        // }
    }
};
// como me gusta mi novia
class Ecosistema
{
public:
    vector<Especie> especies;
    Recursos recursosIniciales;
    Recursos recursosActuales;

    Ecosistema( vector<Especie> &especies,  Recursos &recursos)
        : especies(especies), recursosIniciales(recursos), recursosActuales(recursos) {}
};

// Mejor empiezo con los animales en general

class Especies
{
public:
    // Atributos peso = kg, consumo = kg/semana, edad = semanas
    int peso;      // [1]Peso minimo [2] Pedo medio [3] Peso maximo
    float consumo; // [1] Consumo minimo [2] Consumo medio [3] Consumo maximo
    bool edadRep;  // [1] Edad minima de reproduccion [2] Edad maxima de reproduccion Trabajaremos este apartado en semanas
    int edadMax;   // Edad maxima de vida
};
// Empecemos con los venados

class Venado : public Especies
{
public:
    Venado() {}
    Venado(Genero genero, int edadInicial) : genero(genero), edad(edadInicial)
    {
        if (genero == Genero::Macho)
        {
            iniciarMacho();
        }
        else
        {
            iniciarHembra();
        }
    }

    friend std::ostream &operator<<(std::ostream &os,  Venado &venado)
    {
        os << venado.edad << " " << venado.nivelHambre << " "
           << venado.nivelSed << " " << static_cast<int>(venado.genero) << " "
           << venado.vivo;
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Venado &venado)
    {
        int genero;
        is >> venado.edad >> venado.nivelHambre >> venado.nivelSed >> genero >> venado.vivo;
        venado.genero = static_cast<Genero>(genero);
        return is;
    }

    // SACADO TOTALMENTE DE CHAT GPT
    // NI LA PUTA MENOR IDEA DE QUE ES ESTO
    //  ructor de Movimiento
    Venado(Venado &&other) noexcept
        : Especies(std::move(other)), // Asume que Especies tiene un ructor de movimiento
          edad(other.edad),
          nivelHambre(other.nivelHambre),
          nivelSed(other.nivelSed),
          genero(other.genero),
          vivo(other.vivo)
    {
        // Puedes dejar a `other` en un estadoVivo válido pero "vacío" si es necesario
    }
    // TAMPOCO SE QUE ES ESTO
    // PERO AHORA FUNCIONA EL CODIGO :D
    //  Operador de Asignación de Movimiento
    
    // Venado &operator=(Venado &&other) noexcept
    // {
    //     if (this != &other)
    //     {
    //         Especies::operator=(std::move(other)); // Asume que Especies tiene un operador de asignación de movimiento
    //         edad = other.edad;
    //         nivelHambre = other.nivelHambre;
    //         nivelSed = other.nivelSed;
    //         genero = other.genero;
    //         vivo = other.vivo;
    //         // Puedes dejar a `other` en un estadoVivo válido pero "vacío" si es necesario
    //     }
    //     return *this;
    // }
    Venado(const Venado& other) 
        : Especies(other), // Llamada al constructor de copia de la clase base, si existe
          edad(other.edad),
          nivelHambre(other.nivelHambre),
          nivelSed(other.nivelSed),
          genero(other.genero),
          vivo(other.vivo),
          contadorEmbarazos(other.contadorEmbarazos),
          cicloRep(other.cicloRep),
          edadMax(other.edadMax),
          embarazada(other.embarazada)
    {
        // Aquí puedes añadir cualquier lógica adicional necesaria para la copia
    }

    Genero determinarGenero()
    {
        return genero;
    }

    void envejecer(estaciones estacion, vector<Venado> &venados)
    {
        edad++;
        if (edad > edadMax)
        {
            vivo = false;
            return;
        }

        actualizarValores();
    }
    bool estadoVivo()
    {
        return vivo;
    }
    void consumirRecursos(Recursos &recursos)
    {
        recursos.vegetacion -= consumo;
        nivelHambre += 1;
        recursos.agua -= consumo / 2;
    }

    bool EdadrepT()
    {
        return edadRep;
    }

private:
    int contadorEmbarazos = 0;
    estaciones cicloRep = Otonio;
     int edadMax = 234;
    int edad;
    int nivelHambre = 0; // Se medira en 0 o 1, cada vez que come se le suma 1, cada semana que pasa se le resta 1. Si llega a numeros negativos muere
    int nivelSed = 1;
    Genero genero;
    bool vivo = true;
    bool embarazada = false;

    void iniciarMacho()
    {
        // Cervatillo
        if (edad >= 0 && edad <= 30)
        {
            peso = 4.0f + 1.5f * edad;
            consumo = (44 / 100) * peso;
            edadRep = false;
            return;
        }
        // Adolescente
        if (edad > 30 && edad <= 78)
        {
            peso = 4.0f + 1.6f * 29 + 0.5f * (edad - 29);
            consumo = (45 / 100) * peso;
            edadRep = false;
            return;
        }
        // Adulto
        if (edad > 78)
        {
            peso = 4.0f + 2.0f * 29 + 0.44f * 29 + (edad - 78);
            if (peso > 136)
            {
                peso = 136;
            }
            consumo = (44 / 100) * peso;
            edadRep = true;
            return;
        }
        // edadRep= 104;
        // edadRep[1] = 234;
        // que cagada que no la pueda ver los jueves :(
    }
    void iniciarHembra()
    {
        // Cervatillo
        if (edad >= 0 && edad <= 30)
        {
            peso = 3.5f + 1.3f * edad;
            consumo = (44 / 100.0f) * peso;
            edadRep = false;
            return;
        }
        // Adolescente
        if (edad > 30 && edad <= 78)
        {
            peso = 3.5f + 1.2f * 30 + 0.5f * (edad - 30);
            consumo = (45 / 100.0f) * peso;
            edadRep = false;
            return;
        }
        // Adulto
        if (edad > 78)
        {
            peso = 3.5f + 1.2f * 30 + 0.4f * 48 + 0.3f * (edad - 78);
            if (peso > 110)
            {
                peso = 110;
            }
            consumo = (44 / 100.0f) * peso;
            edadRep = true;
            return;
        }
    }
    void actualizarValores()
    {
        if (genero == Genero::Macho)
        {
            iniciarMacho();
        }
        else
        {
            iniciarHembra();
        }
    }
};

class Puma : public Especies
{
public:
    Puma() {}
    Puma(Genero genero, int edadInicial) : genero(genero), edad(edadInicial)
    {
        if (genero == Genero::Macho)
        {
            iniciarMacho();
        }
        else
        {
            iniciarHembra();
        }
    }

    friend std::ostream &operator<<(std::ostream &os,  Puma &puma)
    {
        os << puma.edad << " " << static_cast<int>(puma.genero) << " "
           << puma.vivo; // Asegúrate de agregar aquí todos los campos relevantes
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Puma &puma)
    {
        int genero;
        is >> puma.edad >> genero >> puma.vivo; // Asegúrate de leer aquí todos los campos relevantes
        puma.genero = static_cast<Genero>(genero);
        return is;
    }
    void envejecer()
    {

        edad++;
        if (edad >= edadMax)
        {
            vivo = false;
        }

        actualizarValores();
    }
    bool EdadRepT()
    {
        return edadRep;
    }

private:
     int cicloRep = 2;  // 1= Primavera, 2= Verano, 3= Otoño, 4= Invierno
     int edadMax = 156; // Semanas
    int edad;
    Genero genero;
    bool vivo = true;

    void iniciarMacho()
    {
        // Cachorro
        if (edad >= 0 && edad <= 26)
        {
            peso = 5.0f + 1.4f * edad;
            consumo = (25.0f / 100) * peso;
            return;
        }
        // Adolescente
        if (edad > 26 && edad <= 58)
        {
            peso = 5.0f + 1.5f * 26 + 0.8f * (edad - 26);
            if (peso > 75)
            {
                peso = 75;
            }
            consumo = (23.0f / 100) * peso;
            return;
        }
        // Adulto
        if (edad > 58)
        {
            peso = 5.0f + 2.0f * 26 + 0.8f * 32 + 0.2f * (edad - 58);
            if (peso > 110)
            {
                peso = 110;
            }
            consumo = (21.0f / 100) * peso;
            return;
        }
    }

    void iniciarHembra()
    {
        // Cachorro
        if (edad >= 0 && edad <= 26)
        {
            peso = 4.0f + 1.7f * edad;
            consumo = (24.0f / 100) * peso;
            return;
        }
        // Adolescente
        if (edad > 26 && edad <= 58)
        {

            peso = 4.0f + 0.8f * 26 + 0.6f * (edad - 26);
            if (peso > 35)
            {
                peso = 35;
            }
            consumo = (22.0f / 100) * peso;
            return;
        }
        // Adulto
        if (edad > 58)
        {
            peso = 4.0f + 1.7f * 26 + 0.6f * 32 + 0.15f * (edad - 58);
            if (peso > 60)
            {
                peso = 60;
            }
            consumo = (20.0f / 100) * peso;
            return;
        }
    }

    void actualizarValores()
    {
        if (genero == Genero::Macho)
        {
            iniciarMacho();
        }
        else
        {
            iniciarHembra();
        }
    }
};
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// APARTADO DE ACTUALIZACION DE RECURSOS

void actualizarCarne(vector<Venado> &venados, Recursos &recursos)
{
    int contadorCarneVenados = 0;
    for (auto &venado : venados)
    {
        contadorCarneVenados += venado.peso;
    }
    recursos.carne = contadorCarneVenados;
}

void reproducirseP(vector<Puma> &pumas)
{
    for (auto &Hembra : pumas)
    {
        if (Hembra.EdadRepT())
        {
            for (int criasp = 0; criasp < (rand() % 3) + 1; criasp++)
            {
                Genero nuevoGeneroP = (rand() % 2 == 0) ? Genero::Macho : Genero::Hembra;
                pumas.push_back(move(Puma(nuevoGeneroP, 0)));
                // venados.push_back(Venado(Genero::Hembra, 120));
            }
            return;
        }
    }
}
void reproducirseV(vector<Venado> &venados, estaciones estacion)
{
    // Encontrar una hembra disponible para la reproducción

    if (estacion != estaciones::Otonio)
    {
        return;
    }

    for (auto &Hembra : venados)
    {
        if (Hembra.determinarGenero() != Genero::Hembra && !Hembra.EdadrepT())
        {
            continue;
        }
        mt19937 gen(random_device{}());
        uniform_int_distribution<> dis(1, 3);

        for (int criasv = 0; criasv < dis(gen); criasv++)
        {
            Genero nuevoGeneroV = (rand() % 2 == 0) ? Genero::Macho : Genero::Hembra;
            venados.push_back(move(Venado(nuevoGeneroV, 1))); // Se agrega el venado a la lista
        }
    }
}

void alimentarVenados(vector<Venado> &venados, Recursos &recursos)
{
    random_device rd;
    mt19937 gen(rd());

    int demandaTotal = 0;
    for ( auto &venado : venados)
    {
        demandaTotal += venado.consumo;
    }

    if (demandaTotal > recursos.vegetacion)
    {
        shuffle(venados.begin(), venados.end(), gen);

        for (auto &venado : venados)
        {
            if (recursos.vegetacion > 0)
            {
                venado.consumirRecursos(recursos);
            }
            else
            {
                break; // YA no hay para los demas animales
            }
        }
        return;
    }
    else
    {
        for (auto &venado : venados)
        {
            venado.consumirRecursos(recursos);
        }
    }
}
void alimentarPumas(vector<Puma> &pumas, vector<Venado> &venados, Recursos &recursos)
{
    int consumoTotalPumas = 0;
    for ( auto &puma : pumas)
    {
        consumoTotalPumas += puma.consumo; // Asumiendo que 'consumo' es un atributo de Puma
    }

    sort(venados.begin(), venados.end(), []( Venado &a,  Venado &b)
         {
             return a.peso > b.peso; // Ordenar venados por peso, de mayor a menor
         });

    int pesoConsumido = 0;
    auto it = venados.begin();
    while (pesoConsumido < consumoTotalPumas && it != venados.end())
    {
        pesoConsumido += it->peso;
        recursos.carne += it->peso; // Asumiendo que cada venado aporta su peso en carne
        it = venados.erase(it);     // Eliminar venado y avanzar al siguiente
    }
}

void iniciarEspecies(vector<Venado> &venados, vector<Puma> &pumas)
{
    for (int CicloActual = 0; CicloActual < 4; CicloActual++)
    {
        venados.push_back(Venado(Genero::Macho, 120));
        venados.push_back(Venado(Genero::Hembra, 120));
        venados.push_back(Venado(Genero::Hembra, 120));
        venados.push_back(Venado(Genero::Hembra, 120));
        venados.push_back(Venado(Genero::Hembra, 120));
        venados.push_back(Venado(Genero::Hembra, 120));
        venados.push_back(Venado(Genero::Hembra, 120));
    }
    for (int CicloActual = 0; CicloActual < 1; CicloActual++)
    {
        pumas.push_back(Puma(Genero::Hembra, 26));
        pumas.push_back(Puma(Genero::Macho, 26));
    }
}
estaciones estacionNum(int ciclo)
{
    int estacion = 0;
    int ciclo2 = ciclo + 4;
    estacion = ciclo2 % 4;
    switch (estacion)
    {
    case 0:
        return Invierno;
    case 1:
        return Primavera;
    case 2:
        return Verano;
    case 3:
        return Otonio;
    }
}
string estacionString(estaciones estacion)
{
    switch (estacion)
    {
    case 0:
        return "PRIMAVERA";
    case 1:
        return "VERANO";
    case 2:
        return "OTONIO";
    case 3:
        return "INVIERNO";
    }
}

void cargarVectores(std::vector<Venado> &venados, std::vector<Puma> &pumas,  std::string &filename);
void guardarVectores( std::vector<Venado> &venados,  std::vector<Puma> &pumas,  std::string &filename);

int main()
{
    vector<Venado> venados; // 10 machos y 10 hembras
    vector<Puma> pumas;     // 1 macho y 1 hembra
    int opcion;
    cout << "1. Cargar datos desde archivo\n";
    cout << "2. Iniciar nueva simulación\n";
    cout << "Seleccione una opción: ";
    cin >> opcion;

    if (opcion == 1)
    {
        // Cargar los datos de los venados y pumas desde un archivo
        cargarVectores(venados, pumas, filename);
    }
    // Hay que incializar y agregar los venados y pumas
    else
    {
        iniciarEspecies(venados, pumas);
    }

    int carneTotal = 0;

    for (auto &venado : venados)
    {
        carneTotal += venado.peso;
    }

    // Se definen los recursos iniciales del ecosistema
    Recursos recursos(100000, 1000, carneTotal, 100000);

    cout << "Cuantos ciclos queres simular?" << endl;
    cout << "NOTA: Tenga en cuenta que el programa iniciara en Primavera automaticamente" << endl;
    int cantidadCiclos, vegetacionConsumida;
    cin >> cantidadCiclos;
    int semanas = cantidadCiclos;
    semanas *= 13;

    estaciones estacion;

    for (int CicloActual = 1; CicloActual <= cantidadCiclos; CicloActual++)
    {
        clearScreen();
        for (auto &venado : venados)
        {
            if (venado.determinarGenero() == Genero::Macho)
            {
                cout << "macho" << venado.peso << endl;
            }
            else
                cout << "Hembra" << venado.peso << endl;
        }

        estacion = estacionNum(CicloActual + 4);
        cout << "Ciclo: " << CicloActual << "        Estacion Actual: " << estacionString(estacion) << endl;
        cout << "Recursos vegetacion: " << recursos.vegetacion << endl;
        cout << "Recursos agua: " << recursos.agua << endl;
        cout << "Carne: " << recursos.carne << endl;
        cout << "Venados: " << venados.size() << endl;
        cout << "Pumas: " << pumas.size() << endl;
        // cout << "Pumas: " << pumas.size() << endl;
        cout << "Presione cualquier tecla para continuar...";
        cin.ignore();
        cin.get();

        for (int semanaActual = 0; semanaActual < 13; semanaActual++)
        {

            alimentarVenados(venados, recursos);

            for (auto &venado : venados)
            {
                // Se actualiza la edad del venado en semanas
                venado.envejecer(estacion, venados);

                // Si el venado muere, se elimina de la lista
                if (!venado.estadoVivo())
                {
                    venados.erase(venados.begin());
                }
                // Si el venado es hembra y esta en edad de reproducirse, se reproduce
            }
            if (semanaActual % 3 == 0)
            {
                alimentarPumas(pumas, venados, recursos);
            }
        }
        reproducirseP(pumas);
        reproducirseV(venados, estacion);
        reproducirseP(pumas);
        actualizarCarne(venados, recursos);
    }
    cout << "¿Desea guardar los datos? (1: Sí, otro: No): ";
    cin >> opcion;

    if (opcion == 1)
    {
        // Guardar los datos de los venados y pumas en un archivo
        guardarVectores(venados, pumas, filename);
        cout << "Datos guardados exitosamente.\n";
    }
    return 0;
}

void guardarVectores( std::vector<Venado> &venados,  std::vector<Puma> &pumas, std::string &filename)
{
    
    std::ofstream archivo(filename, std::ios::binary);
    for (auto &venado : venados)
    {
        archivo << venado << "\n";
    }
    // Insertar un salto de línea para separar los vectores
    archivo << "\n";
    for (auto &puma : pumas)
    {
        archivo << puma << "\n";
    }
}

void cargarVectores( std::vector<Venado> &venados, std::vector<Puma> &pumas,  std::string &filename)
{
    std::ifstream archivo(filename, std::ios::binary);
    std::string linea;

    // Leer el vector de venados
    while (std::getline(archivo, linea))
    {
        if (linea.empty())
        {
            // Salto de línea encontrado, romper el bucle
            break;
        }
        std::istringstream iss(linea);
        Venado Venado;
        if (iss >> Venado)
        {
            venados.push_back(Venado);
        }
    }

    // Leer el vector de pumas
    while (std::getline(archivo, linea))
    {
        std::istringstream iss(linea);
        Puma Puma;
        if (iss >> Puma)
        {
            pumas.push_back(Puma);
        }
    }
}