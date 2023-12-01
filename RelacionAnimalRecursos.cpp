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

    void actualizarRecursos(estaciones estacion, int vegetacionConsumida)
    {
        // Tengo que poner un nivel maximo de vegetacion
        const int nivelMaxVegetacion = 100000;
        const int nivelMaxAgua = 120000;
        int factorRegeneracion;
        switch (estacion)
        {
        case Primavera:
            agua += 10000;
            if (agua > nivelMaxAgua)
            {
                agua = nivelMaxAgua;
            }

            break;
        case Verano:
            agua += 5000;
            if (agua > agua)
            {
                agua = nivelMaxAgua;
            }
            vegetacion += agua * 0.05f;
            break;
        case Otonio:
            agua += 9000;
            if (agua > nivelMaxAgua)
            {
                agua = nivelMaxAgua;
            }
            vegetacion += agua * 0.1f;
            break;
        case Invierno:
            agua += 25000;
            if (agua > nivelMaxAgua)
            {
                agua = nivelMaxAgua;
            }
            vegetacion += agua * 0.1f;
            break;
        }
        factorRegeneracion = (agua - 3/5 * vegetacion) / vegetacion;
        vegetacion += factorRegeneracion * vegetacionConsumida + 0.3f * vegetacionConsumida;

        if(vegetacion > nivelMaxVegetacion){
            vegetacion = nivelMaxVegetacion;
        }
    }
};
// como me gusta mi novia
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
        edad++;
        if (edad > edadMax || nivelHambre < 0 || nivelSed < 0)
        {
            vivo = false;
            return;
        }
        if (genero == Genero::Macho)
        {
            iniciarMacho();
        }
        else
        {
            iniciarHembra();
        }
    }
    bool estadoVivo()
    {
        return vivo;
    }
    int mostrarEdad()
    {
        return edad;
    }

    void consumirRecursos(Recursos &recursos)
    {
        recursos.vegetacion -= consumo;
        nivelHambre += 1;
        recursos.agua -= consumo / 2;
        nivelSed += 1;
    }

    bool EdadrepT()
    {
        return edadRep;
    }
    void nuevoEstado(bool estado)
    {
        vivo = estado;
    }

private:
    int contadorEmbarazos = 0;
    estaciones cicloRep = Otonio;
    const int edadMax = 234;
    int edad;
    int nivelHambre = 1; // Se medira en 0 o 1, cada vez que come se le suma 1, cada semana que pasa se le resta 1. Si llega a numeros negativos muere
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
};

class Puma : public Especies
{
public:
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

    void envejecer()
    {

        edad++;
        if (edad >= edadMax || nivelHambre < 0 || nivelSed < 0)
        {
            vivo = false;
        }
        nivelHambre -= 1;
        nivelSed -= 1;

        actualizarValores();
    }
    bool EdadRepT()
    {
        return edadRep;
    }
    Genero determinarGenero()
    {
        return genero;
    }
    bool estadoVivo()
    {
        return vivo;
    }
    void nuevoEstado(bool estado)
    {
        vivo = estado;
    }
    void consumirRecursos(int &venado, Recursos &recursos)
    {
        venado -= consumo;
        nivelHambre += 1;
        recursos.agua -= consumo / 2;
        nivelSed += 1;
    }
    float determinarConsumo()
    {
        return consumo;
    }
    int determinarHambre()
    {
        return nivelHambre;
    }
    int mostrarEdad()
    {
        return edad;
    }

private:
    estaciones cicloRep = Invierno; // 1= Primavera, 2= Verano, 3= Otoño, 4= Invierno
    int edadMax = 156;              // Semanas
    int edad;
    int nivelHambre = 2; // Se medira en 0 o 1, cada vez que come se le suma 1, cada semana que pasa se le resta 1. Si llega a numeros negativos muere
    int nivelSed = 2;
    Genero genero;
    bool vivo = true;

    void iniciarMacho()
    {
        // Cachorro
        if (edad >= 0 && edad <= 26)
        {
            peso = 5.0f + 1.4f * edad;
            consumo = (25.0f / 100) * peso;
            edadRep = false;
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
            edadRep = false;
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
            edadRep = true;
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
            edadRep = false;
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
            edadRep = false;
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

void reproducirseP(vector<Puma> &pumas, estaciones estacion)
{
    if (estacion != estaciones::Otonio)
    {
        return;
    }
    for (auto &Hembra : pumas)
    {
        if (!Hembra.EdadRepT() || Hembra.determinarGenero() != Genero::Hembra)
        {
            continue;
        }

        mt19937 gen(random_device{}());
        uniform_int_distribution<> dis(2, 4);

        for (int criasp = 0; criasp < dis(gen); criasp++)
        {
            Genero nuevoGeneroP = (rand() % 2 == 0) ? Genero::Macho : Genero::Hembra;
            pumas.push_back(move(Puma(nuevoGeneroP, 1)));
        }
    }
}
void reproducirseV(vector<Venado> &venados, estaciones estacion)
{
    if (estacion != estaciones::Otonio)
    {
        return;
    }
    // Encontrar una hembra disponible para la reproducción
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
    for (const auto &venado : venados)
    {
        demandaTotal += venado.consumo;
    }

    if (demandaTotal >= recursos.vegetacion)
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
                venado.nuevoEstado(false);
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
    // Ordenar los venados por peso, de mayor a menor
    sort(venados.begin(), venados.end(), [](const Venado &a, const Venado &b)
         { return a.peso > b.peso; });

    auto venado = venados.begin();

    for (auto &puma : pumas)
    {
        if (venado == venados.end())
            break; // No hay más venados

        int consumoNecesario = puma.determinarConsumo();

        while (consumoNecesario > 0 && venado != venados.end())
        {
            // Marcar venado como consumido
            venado->nuevoEstado(false);

            // Calcular la carne disponible del venado
            int pesoDisponible = venado->peso;
            recursos.carrona += pesoDisponible * 0.25f; // 25% se convierte en carrona
            pesoDisponible *= 0.75f;                    // 75% disponible para los pumas

            if (pesoDisponible >= consumoNecesario)
            {
                // Si hay suficiente carne, el puma consume lo necesario
                puma.consumirRecursos(consumoNecesario, recursos);
                pesoDisponible -= consumoNecesario;
                consumoNecesario = 0;

                // Pasar el exceso al siguiente puma
                if (pesoDisponible > 0 && &puma != &pumas.back())
                {
                    pumas[&puma - &pumas[0] + 1].consumirRecursos(pesoDisponible, recursos);
                }
            }
            else
            {
                // Si no hay suficiente carne, el puma consume lo que hay
                puma.consumirRecursos(pesoDisponible, recursos);
                consumoNecesario -= pesoDisponible;
                pesoDisponible = 0;
            }

            if (pesoDisponible == 0)
            {
                // Pasar al siguiente venado si este ya fue totalmente consumido
                venado++;
            }
        }
    }
}
void iniciarEspecies(vector<Venado> &venados, vector<Puma> &pumas)
{
    for (int CicloActual = 0; CicloActual < 50; CicloActual++)
    {
        venados.push_back(Venado(Genero::Hembra, 120));
        venados.push_back(Venado(Genero::Macho, 120));
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

// class Especie
// {
// public:
//     vector<Venado> venados;
//     vector<Puma> pumas;

//     Especie(vector<Venado> &venados, vector<Puma> &pumas)
//         : venados(venados), pumas(pumas) {}
// };

// class Ecosistema {
// private:
//     Ecosistema(int venados, int pumas, Recursos &recursos)
//         :recursosIniciales(recursos), recursosActuales(recursos), pVenados(venados), pPumas(pumas) {}

//     int pVenados;
//     int pPumas;
//     Recursos recursosIniciales;
//     Recursos recursosActuales;

//     // Constructor privado

//     // Copia y asignación privados para prevenir múltiples instancias
//     // Ecosistema( Ecosistema&);
//     // Ecosistema& operator=(Ecosistema&);

// public:
//     // Método para acceder a la instancia del Singleton
//     static Ecosistema& getInstance(int venados, int pumas, Recursos &recursos) {
//         static Ecosistema instancia(venados, pumas, recursos);
//         return instancia;
//     }
//     const Recursos& getRecursosActuales() const {
//         return recursosActuales;
//     }
//     const Recursos& getRecursosIniciales() const{
//         return recursosIniciales;
//     }
//     int poblacionVenados(){
//         return pVenados;
//     }
//     int poblacionPumas(){
//         return pPumas;
//     }
//     void actualizarRecursos(Recursos &recursos) {
//         recursosActuales = recursos;
//     }

//     void actualizarRecursosInicial(Recursos &recursos) {
//         recursosIniciales = recursos;
//     }

class Ecosistema
{
public:
    int pVenados;
    int pPumas;
    Recursos recursosIniciales;
    Recursos recursosActuales;

    Ecosistema(int venados, int pumas, Recursos &recursos)
        : recursosIniciales(recursos), recursosActuales(recursos), pVenados(venados), pPumas(pumas) {}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Ecosistema& ecosistemaGlobal =  Ecosistema::getInstance(poblacionVenados, poblacionPumas, recursosIniciales);

int mainRelacionAnimalRecurso(string usuario, vector<Venado> &venados, vector<Puma> &pumas, Ecosistema &ecosistema,Extractordatos &extract)
{
    // Se definen los recursos iniciales del ecosistema

    cout << "Cuantos ciclos queres simular?" << endl;
    cout << "NOTA: Tenga en cuenta que el programa iniciara en Primavera automaticamente" << endl;
    int cantidadCiclos;
    cin >> cantidadCiclos;
    int vegetacionConsumida = ecosistema.recursosActuales.vegetacion;

    estaciones estacion;
    int CicloActual = 1;
    for (CicloActual; CicloActual <= cantidadCiclos; CicloActual++)
    {
        clearScreen();
        estacion = estacionNum(CicloActual + 4);

        for (int semanaActual = 0; semanaActual < 13; semanaActual++)
        {

            alimentarVenados(venados, ecosistema.recursosActuales);
            alimentarPumas(pumas, venados, ecosistema.recursosActuales);
            auto it = venados.begin();
            while (it != venados.end())
            {
                // Se actualiza la edad del venado en semanas
                it->envejecer(estacion, venados);

                if (!it->estadoVivo())
                {

                    it = venados.erase(it);
                    extract.contadorMuerteV++;
                }
                else
                {
                    ++it;
                }
            }
            auto eso = pumas.begin();
            while (eso != pumas.end())
            {
                eso->envejecer();

                if (eso->estadoVivo() == false)
                {
                    pumas.erase(eso);
                    extract.contadorMuerteP++;
                }
                else
                {
                    ++eso;
                }
            }
        }
        vegetacionConsumida -= ecosistema.recursosActuales.vegetacion;
        reproducirseP(pumas, estacion);
        reproducirseV(venados, estacion);
        actualizarCarne(venados, ecosistema.recursosActuales);
        ecosistema.recursosActuales.actualizarRecursos(estacion, vegetacionConsumida);
    }

    return 0;
}

bool contieneGuion(const string &token)
{
    return token.find('-') != string::npos;
}

bool eFNumero(const string &str)
{
    if (str.empty())
    {
        return false;
    }
    size_t inicio = (str[0] == '-') ? 1 : 0;
    return str.find_first_not_of("0123456789", inicio) == string::npos;
}

void LeerAnimal(const string &fileName, vector<Venado> &Lvenados, vector<Puma> &Lpumas)
{
    ifstream file(fileName);
    if (!file.is_open())
    {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    vector<int> datosAnimales;
    size_t conteoComas = 0;
    size_t indicePumas; // Índice para el cambio a pumas
    string line;
    bool comas=false;
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;
        while (getline(ss, token, ','))
        {

            if (contieneGuion(token))
            {
                indicePumas = conteoComas; // Cada par de datos está separado por una coma
                comas=true;
                continue;
            }

            if (eFNumero(token))
            {
                try
                {
                    datosAnimales.push_back(stoi(token));
                    if (!comas)
                    {
                        conteoComas++;
                    }
                    
                }
                catch (const std::invalid_argument &e)
                {
                    cerr << "Invalid argument: " << token << endl;
                    return;
                }
            }
        }
    }

    file.close();

    // Construir objetos Venado y Puma a partir de datosAnimales
    for (size_t i = 0; i < datosAnimales.size(); i += 2)
    {
        int edad = datosAnimales[i];
        int genero = datosAnimales[i + 1];

        if (i >= indicePumas)
        {
            if (genero == 0)
            {
                Lpumas.push_back(Puma(Genero::Macho, edad));
            }
            else
            {
                Lpumas.push_back(Puma(Genero::Hembra, edad));
            }
        }
        else
        {
            if (genero == 0)
            {
                Lvenados.push_back(Venado(Genero::Macho, edad));
            }
            else
            {
                Lvenados.push_back(Venado(Genero::Hembra, edad));
            }
        }
    }
}