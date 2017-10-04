#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Flacon
{
private:
  string nom;
  double volume;
  double pH;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
#define BONUS
	Flacon(string n, double v, double ph)
	:nom(n), volume(v), pH(ph)
	{}

	ostream& etiquette(ostream& sortie) const
	{
		sortie << nom <<" : "<<volume <<" ml, pH "<< pH;
		return sortie;
	}

	Flacon& operator += (Flacon const& f)
	{	
	       	nom += " + " + f.getNom();
	
		double volumeF = f.getVolume();
		pH = -log10(((volume * pow(10, -pH)) 
					+ (volumeF * pow(10, -f.getpH()))) 
				/ (volume + volumeF)
				); 
		volume += f.getVolume();
		return *this;
	}

	string getNom() const 
	{
		return nom;
	}

	double getVolume() const
	{
		return volume;
	}

	double getpH() const
	{
		return pH;
	}

	
};


ostream& operator<<(ostream& sortie, Flacon const& f)
{
	return f.etiquette(sortie);
}

const Flacon operator+(Flacon f1, Flacon const& f2)
{
	return f1 += f2;
}


/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void afficher_melange(Flacon const& f1, Flacon const& f2)
{
  cout << "Si je mélange " << endl;
  cout << "\t\"" << f1 << "\"" << endl;
  cout << "avec" << endl;
  cout << "\t\"" << f2 << "\"" << endl;
  cout << "j'obtiens :" << endl;
  cout << "\t\"" << (f1 + f2) << "\"" << endl;
}

int main()
{
  Flacon flacon1("Eau", 600.0, 7.0);
  Flacon flacon2("Acide chlorhydrique", 500.0, 2.0);
  Flacon flacon3("Acide perchlorique",  800.0, 1.5);

  afficher_melange(flacon1, flacon2);
  afficher_melange(flacon2, flacon3);

  return 0;

}
