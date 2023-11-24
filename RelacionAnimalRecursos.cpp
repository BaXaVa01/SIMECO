// Quisiera declararle mi amor, pero solo se declarar variables

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstdlib>
#include <algorithm>

using namespace std;

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
        const int nivelMaxVegetacion = 100000;
        const int nivelMaxAgua = 10000;

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

    Ecosistema(const vector<Especie> &especies, const Recursos &recursos)
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
    // SACADO TOTALMENTE DE CHAT GPT
    // NI LA PUTA MENOR IDEA DE QUE ES ESTO
    //  Constructor de Movimiento
    Venado(Venado &&other) noexcept
        : Especies(std::move(other)), // Asume que Especies tiene un constructor de movimiento
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
    Venado &operator=(Venado &&other) noexcept
    {
        if (this != &other)
        {
            Especies::operator=(std::move(other)); // Asume que Especies tiene un operador de asignación de movimiento
            edad = other.edad;
            nivelHambre = other.nivelHambre;
            nivelSed = other.nivelSed;
            genero = other.genero;
            vivo = other.vivo;
            // Puedes dejar a `other` en un estadoVivo válido pero "vacío" si es necesario
        }
        return *this;
    }

    Genero determinarGenero()
    {
        return genero;
    }

    void envejecer(estaciones estacion, vector<Venado> &venados)
    {
        // nivelHambre -= 1;
        // nivelSed -= 1;
        // if(nivelHambre < 0 || nivelSed < 0){
        //     vivo = false;
        // }

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
    const int edadMax = 234;
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
    Puma(bool genero, int edadInicial) : genero(genero), edad(edadInicial)
    {
        if (genero)
        {
            iniciarMacho();
        }
        else
        {
            iniciarHembra();
        }
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

private:
    const int cicloRep = 2;  // 1= Primavera, 2= Verano, 3= Otoño, 4= Invierno
    const int edadMax = 156; // Semanas
    int edad;
    bool genero;
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
        if (genero)
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

void reproducirse(vector<Venado> &venados)
{
    // Encontrar una hembra disponible para la reproducción
    for (auto &Hembra : venados)
    {
        if (Hembra.EdadrepT())
        {
            // Crear un nuevo venado con género aleatorio
            // if(contadorEmbarazos == 0){

            //     hembra.contadorEmbarazos++;
            //     Genero nuevoGenero = (rand() % 2 == 0) ? Genero::Macho : Genero::Hembra;
            //     Venado nuevaCria(nuevoGenero, 0);  // Se crea un venado con edad inicial 0

            //     venados.push_back(move(nuevaCria)); // Se agrega el venado a la lista
            //     return;
            // }

            for (int crias = 0; crias < (rand() % 3) + 1; crias++)
            {
                Genero nuevoGenero = (rand() % 2 == 0) ? Genero::Macho : Genero::Hembra;
                Venado nuevaCria(nuevoGenero, 0); // Se crea un venado con edad inicial 0

                venados.push_back(move(nuevaCria)); // Se agrega el venado a la lista
            }
            cout << "Todos" << endl;

            return;
        }
    }
}

void alimentarVenados(vector<Venado> &venados, Recursos &recursos)
{
    random_device rd;
    mt19937 gen(rd());

    int demandaTotal = 0;
    for (const auto &venado : venados)
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
    for (const auto &puma : pumas)
    {
        consumoTotalPumas += puma.consumo; // Asumiendo que 'consumo' es un atributo de Puma
    }

    sort(venados.begin(), venados.end(), [](const Venado &a, const Venado &b)
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
    for (int i = 0; i < 4; i++)
    {

        venados.push_back(Venado(Genero::Hembra, 120));
    }
    for (int i = 0; i < 1; i++)
    {
        pumas.push_back(Puma(true, 26));
        pumas.push_back(Puma(false, 26));
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

int main()
{
    vector<Venado> venados; // 10 machos y 10 hembras
    vector<Puma> pumas;     // 1 macho y 1 hembra

    // Hay que incializar y agregar los venados y pumas
    iniciarEspecies(venados, pumas);
    int carneTotal = 0;

    for (const auto &venado : venados)
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

    for (int i = 1; i <= cantidadCiclos; i++)
    {
        clearScreen();
        estacion = estacionNum(i);
        cout << "Ciclo: " << i << "        Estacion Actual: " << estacion << endl;
        cout << "Recursos vegetacion: " << recursos.vegetacion << endl;
        cout << "Recursos agua: " << recursos.agua << endl;
        cout << "Carne: " << recursos.carne << endl;
        cout << "Venados: " << venados.size() << endl;
        // cout << "Pumas: " << pumas.size() << endl;
        cout << "Presione cualquier tecla para continuar...";
        cin.ignore();
        cin.get();

        for (int i = 0; i < semanas; i++)
        {

            alimentarVenados(venados, recursos);

            for (auto &venado : venados)
            {
                // Se actualiza la edad del venado en semanas
                venado.envejecer(estacion, venados);

                // Si el venado muere, se elimina de la lista
                //  if(venado.estadoVivo()){
                //      venados.erase(venados.begin());
                //  }
                // Si el venado es hembra y esta en edad de reproducirse, se reproduce
            }
            if (i % 13 == 0)
            {
                reproducirse(venados);
            }
            // for(auto &puma : pumas)
            // {
            //     puma.envejecer();
            // }
        }
        vegetacionConsumida -= recursos.vegetacion;
        recursos.vegetacionConsumida = vegetacionConsumida;
    }
    return 0;
}
