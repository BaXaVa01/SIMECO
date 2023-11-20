#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstdlib>
#include <algorithm>

using namespace std;

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

    Recursos(int agua, int carrona, int carne, int vegetacion) : agua(agua), carrona(carrona), carne(carne), vegetacion(vegetacion) {}
};

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
    int edadRep;   // [1] Edad minima de reproduccion [2] Edad maxima de reproduccion Trabajaremos este apartado en semanas
    int edadMax;   // Edad maxima de vida
    
};
// Empecemos con los venados

class Venado : public Especies
{
public:
    Venado(bool genero, int edadInicial) : genero(genero), edad(edadInicial)
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
        nivelHambre -= 1;
        if(nivelHambre < 0 || nivelSed < 0){
            vivo = false;
        }
        edad++;
        if (edad > edadMax)
        {
            vivo = false;
        }
        cout << peso << endl;
        actualizarValores();
        cout << peso << endl;
    }
    void consumirRecursos(Recursos &recursos)
    {
        recursos.vegetacion -= consumo;
        nivelHambre += 1;
        recursos.agua -= consumo/2;
    }


private:
    const int edadMax = 234;
    int edad;
    int nivelHambre = 0; //Se medira en 0 o 1, cada vez que come se le suma 1, cada semana que pasa se le resta 1. Si llega a numeros negativos muere
    int nivelSed = 1;
    bool genero;
    bool vivo = true;

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
        //
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
        cout << edad << endl;
        cout << peso << endl;
        edad++;
        if (edad >= edadMax)
        {
            vivo = false;
        }

        actualizarValores();
        cout << edad << endl;
        cout << peso << endl;
    }

private:
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

void alimentarVenados(vector<Venado> &venados, Recursos &recursos)
{
    random_device rd;
    mt19937 gen(rd());

    int demandaTotal = 0;
    for(const auto &venado : venados)
    {
        demandaTotal += venado.consumo;
    }

    if(demandaTotal > recursos.vegetacion)
    {
        shuffle(venados.begin(), venados.end(), gen);

        for(auto &venado : venados)
        {
            if(recursos.vegetacion > 0){
                venado.consumirRecursos(recursos);
            }
            else{
                break;//YA no hay para los demas animales
            }
        }
        return;
    }else{
        for(auto &venado : venados)
        {
            venado.consumirRecursos(recursos);
        }
    }
}

int main()
{
    Venado VenadoMacho(true, 30);
    Venado VenadoHembra(false,1);
    VenadoMacho.envejecer();
    VenadoHembra.envejecer();
    vector<Venado> venados;
    venados.push_back(VenadoMacho);
    return 0;
}