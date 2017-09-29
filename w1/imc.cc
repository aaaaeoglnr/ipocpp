#include <iostream>
using namespace std;

/*****************************************************
 * Compléter le code à partir d'ici
 *****************************************************/
class Patient{
	public:
		void init(double p, double t) {
			if (p > 0 and t > 0) {
				masse = p;
				hauteur = t;
			} else {
				masse = 0;
				hauteur = 0;
			}
		}
		
		void afficher(){
			cout << "Patient : " << masse << " kg pour "
				<< hauteur <<" m";
			cout << endl;
		}

		double imc(){
			if (hauteur == 0) { return 0; }
			return masse / (hauteur * hauteur);
		}

		double poids() {
			return masse;
		}

		double taille(){
			return hauteur;
		}
	private:
		double masse;
		double hauteur;
};
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Patient quidam;
  double poids, taille;
  do {
    cout << "Entrez un poids (kg) et une taille (m) : ";
    cin >> poids >> taille;
    quidam.init(poids, taille);
    quidam.afficher();
    cout << "IMC : " << quidam.imc() << endl;
  } while (poids * taille != 0.0);
  return 0;
}
