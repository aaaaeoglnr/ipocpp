#include <iostream>
using namespace std;

/*******************************************
 * Complétez le programme à partir d'ici.
 *******************************************/
class Tirelire{


	public: 
		double getMontant(){
			return montant;
		}

		void afficher() {
			cout << "Vous ";
			if (montant > 0) {
				cout << " avez :" << montant
					<< " euros dans votre tirelire.";
			} else {
				cout << "etes sans le sou.";
			}
			cout << endl;
		}

		void secouer(){
			if (montant > 0) { 
				cout << "Bing bing" << endl;
			}
		}

		void remplir (double m){
			if (m > 0) {
				montant += m;
			}
		}

		void vider() {
			montant = 0.0;
		}

		void puiser(double m) {
			if (m >= 0) {
				if (m > montant) {
					montant = 0.0;
				} else {
					montant -= m;
				}
			}
		}

		bool montant_suffisant(double budget, double& solde){
			if (budget <= 0) {
				solde = montant;
				return true;
			} else {
				solde = montant - budget;
				if (solde < 0) {
					solde = -solde;
					return false;
				} else {
					return true;
				}				
				
			}
		}

		double calculerSolde(double budget){
			if (budget <= 0) {
				return montant;
			}
			return montant - budget;
		}

	private:
		double montant;
};

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Tirelire piggy;

  piggy.vider();
  piggy.secouer();
  piggy.afficher();

  piggy.puiser(20.0);
  piggy.secouer();
  piggy.afficher();

  piggy.remplir(550.0);
  piggy.secouer();
  piggy.afficher();

  piggy.puiser(10.0);
  piggy.puiser(5.0);
  piggy.afficher();

  cout << endl;

  // le budget de vos vacances de rève.
  double budget;

  cout << "Donnez le budget de vos vacances : ";
  cin >> budget;

  // ce qui resterait dans la tirelire après les
  // vacances
  double solde(0.0);

  if (piggy.montant_suffisant(budget, solde)) {
    cout << "Vous êtes assez riche pour partir en vacances !"
         << endl
         << "Il vous restera " << solde << " euros"
         << " à la rentrée." << endl << endl;
    piggy.puiser(budget);
  } else {
    cout << "Il vous manque " << solde << " euros"
         << " pour partir en vacances !" << endl << endl;
  }
  return 0;
}
