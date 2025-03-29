#include<iostream>
#include<concepts>

template <typename T> requires std::floating_point<T>		//Impongo il vincolo che T debba essere un tipo floating-point, un numero a virgola mobile

class complex_number {
private:		//Questi memebri sono privati, NON accessibili direttamente dall'esterno
	T real;		//Memorizzo la parte reale
	T imag;		//Memorizzo la parte immaginaria
	
public:
// Costruttore di default
	complex_number() : real(0), imag(0) {}		//Inizializzo il numero complesso a (0,0)
	
// Costruttore con un solo parametro
	explicit complex_number(T a) : real(a), imag(0) {}		//Inizializzo la parte reale con a
															//explicit evita conversioni implicite indesiderate

// Costruttore con due parametri	
	complex_number (T a, T b) : real(a), imag(b) {}			//Inizializzo la parte reale con a e con b la parte immaginaria
	
// Metodo per ottenere la parte reale
	T rp(void) const {		//const perchè non viene modificato lo stato dell'oggetto
		return real;		//rp() restituisce la parte reale di un numero complesso
	}
	
// Metodo per ottenere la parte immaginaria
	T ip(void) const {		//const perchè non viene modificato lo stato dell'oggetto
		return imag;		//ip() restituisce la parte immaginaria di un numero complesso
	}
	
// Metodo per ottenere il coniugato
	complex_number<T> conjugate(void) const {		//const perchè non viene modificato lo stato dell'oggetto
		return complex_number<T>(real, -imag);		//Viene restituito il complesso coniugato, il numero con parte immaginaria opposta
	}
	
// Operatore += per i numeri complessi
	complex_number& operator+=(const complex_number& other) {
		real += other.real;		//Sommo la parte reale di other alla parte reale dell'oggetto 
		imag += other.imag;		//Sommo la parte immaginaria di other alla parte immaginaria dell'oggetto 
		return *this;			//Restituisce il numero aggiornato. *this consente concatenazioni 
	}
	
// Operatore + per i numeri complessi(usando l'operatore definito sopra)
	complex_number operator+(const complex_number& other) const {		//const perchè non viene modificato lo stato dell'oggetto
        complex_number result = *this;		//Copio l'oggetto corrente
        result += other;					//Uso l'operatore += già definito(uso += per evitare duplicazione di codice
        return result;						//Restituisce il risuktato aggiornato
    }
	
// Operatore *= per i numeri complessi
	complex_number& operator*=(const complex_number& other) {
        T a1 = real;
        T b1 = imag;
        T a2 = other.real;
        T b2 = other.imag;
        real = a1 * a2 - b1 * b2;		//Calcolo la parte reale 
        imag = a1 * b2 + b1 * a2;		//Calcolo la parte immaginaria
        return *this;				//Restituisce il numero aggiornato. *this consente concatenazioni 
	}
	
// Operatore * per i numeri complessi(usando l'operatore definito sopra e lo stesso metodo di +) 
	complex_number operator*(const complex_number& other) const {
        complex_number result = *this;
        result *= other;
        return result;
    }
	
// Operatori += e + tra un complesso e uno scalare(a destra)
	   complex_number& operator+=(const T& other) {
        real += other;		//Aggiungo solo lo scalare alla parte reale
        return *this;
	}
	
	complex_number operator+(const T& other) const {
        complex_number result = *this;
        result += other;
        return result;		//STESSO METODO utilizzato in precedenza
    }
	
// Operatori *= e * tra un complesso e uno scalare(a destra)
	   complex_number& operator*=(const T& other) {
        real *= other;		//Moltiplico la parte reale con lo scalare
		imag *= other;		//Moltiplico la parte immaginaria con lo scalare
        return *this;
	}
	
	complex_number operator*(const T& other) const {
        complex_number result = *this;
        result *= other;
        return result;		//STESSO METODO utilizzato in precedenza
    }
};

//Operatori con commutatività(somma e prodotto di uno scalare a sinistra del numero complesso)
template<typename T> requires std::floating_point<T>
complex_number<T> operator+(const T& scalar, const complex_number<T>& c) {
    return c + scalar;		//Riutilizzo l'operatore già definito dentro la classe
}

template<typename T> requires std::floating_point<T>
complex_number<T> operator*(const T& scalar, const complex_number<T>& c) {
    return c * scalar;		//Riutilizzo l'operatore già definito dentro la classe
}

// Overload per l'operatore di stampa <<
template<typename T> requires std::floating_point<T>
std::ostream& operator<<(std::ostream& os, const complex_number<T>& c) {		//os è lo stream di output. Uso un riferimento(&) per evitare la copia dello stream che sarebbe inefficiente. Uso const per evitare copie inutili e garantire che la funzione non vada a moodificare c
    if (c.ip() != 0)									//Se la parte immaginaria è diversa da zero si deve stampare, se no si stampa solo la parte reale				
		if(c.ip() > 0)									//Se la parte immaginaria è maggiore di zero si stampa + davanti, se no -
			if(c.ip() != 1)								//Se la parte immaginaria è uguale a 1 si stampa solo i
				os << c.rp() << "+" << c.ip()<< "i";
			else
				os << c.rp() << "+i";
		else
			if(c.ip()!=-1)
				os << c.rp() << "" <<c.ip()<<"i";
			else
				os << c.rp() << "-i";
    else
        os << c.rp();

    return os;
}