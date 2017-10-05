#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Pour simplifier
typedef string Forme   ;
typedef string Couleur ;

class Brique
{
private:
  Forme   forme   ;
  Couleur couleur ;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/

  Brique(Forme uneForme, Couleur uneCouleur)
	  :forme(uneForme), couleur(uneCouleur)
  {}

  ostream& afficher(ostream& sortie) const
  {
  	if (couleur != "") {
		sortie << "(" << forme << ", " << couleur << ")";
	} else {
		sortie << forme;
	}
	  return sortie;
  }

};

ostream& operator<<(ostream& sortie, Brique const& brique)
{
	return brique.afficher(sortie);
}

class Construction
{
  friend class Grader;
	
		public:
  		Construction(Brique brique)
		{
			contenu = {{{}}};
			contenu[0][0].push_back(brique);
		}

		ostream& afficher(ostream& sortie) const
		{			
			size_t size = contenu.size();
			if (size != 0) {
				for (size_t i = size; i > 0; --i) {
					sortie << "Couche " << i - 1 << " : " << endl;
					for (auto ligne : contenu[i - 1]) {
						for (auto brique : ligne) {
							cout << brique;
						}
					cout << endl;
					}
				}
			}
			return sortie;
		}
		
		const vector<vector<vector<Brique> > > getContenu() const
		{
			return contenu;
		}

		Construction& operator^=(Construction const& autre)
		{			
			const vector<vector<vector<Brique> > > contenu_autre =
			 autre.getContenu();
			size_t size_autre = contenu_autre.size();
			for (size_t i = 0; i < size_autre; i++) {
					contenu.push_back(contenu_autre[i]);
			}
			return *this;
		}

		Construction& operator-=(Construction const& autre)
		{
			size_t hauteur = contenu.size();
			const vector<vector<vector<Brique> > > contenu_autre = 
			autre.getContenu();
			size_t hauteur_autre = contenu_autre.size();
			if (hauteur_autre >= hauteur) {
				for(size_t i = 0; i < hauteur; i++){
					for (auto ligne : contenu_autre[i]) {
							contenu[i].push_back(ligne);
					}
				}
			}
			return *this;
		}


		Construction& operator+=(Construction const& autre)
		{
			const vector<vector<vector<Brique> > > contenu_autre = 
			autre.getContenu();
			
			size_t hauteur = contenu.size();
			size_t hauteur_autre = contenu_autre.size();
			size_t profondeur = contenu[0].size();
			size_t profondeur_autre = contenu_autre[0].size();
			
			if (hauteur_autre >= hauteur 
			and profondeur_autre >= profondeur) {
				for(size_t i = 0; i < hauteur; i++){
					for (size_t j = 0; j < profondeur; j++) {
						for (size_t k = 0; k 
						< contenu_autre[i][j].size(); k++) {
							contenu[i][j].push_back(
							contenu_autre[i][j][k]);
						}
					}
				}
			}
			return * this;
		}


  	private:
		vector<vector<vector<Brique> > > contenu; 
};

ostream& operator<<(ostream& sortie, Construction const& construction)
{
	return construction.afficher(sortie);
}

const Construction operator+(Construction c1, Construction const& c2){
	return c1 += c2;
}

const Construction operator-(Construction c1, Construction const& c2){
	return c1 -= c2;
}

const Construction operator^(Construction c1, Construction const& c2){
	return c1 ^= c2;
}

const Construction operator*(unsigned int n, Construction const& a)
{	
	Construction b = a;
	for(; n > 1; n--) {
		b += a;
	}
	return b;
}

const Construction operator/(unsigned int n, Construction const& a)
{
	Construction b = a;
	for(; n > 1; n--) {
		b ^= a;
	}
	return b;
}

const Construction operator%(unsigned int n, Construction const& a)
{
	Construction b = a;
	for(; n > 1; n--) {
		b -= a;
	}
	return b;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  // Modèles de briques
  Brique toitD("obliqueD", "rouge");
  Brique toitG("obliqueG", "rouge");
  Brique toitM(" pleine ", "rouge");
  Brique mur  (" pleine ", "blanc");
  Brique vide ("                 ", "");

  unsigned int largeur(4);
  unsigned int profondeur(3);
  unsigned int hauteur(3); // sans le toit

  // on construit les murs
  Construction maison( hauteur / ( profondeur % (largeur * mur) ) );

  // on construit le toit
  Construction toit(profondeur % ( toitG + 2*toitM + toitD ));
  toit ^= profondeur % (vide + toitG + toitD);

  // on pose le toit sur les murs
  maison ^= toit;

  // on admire notre construction
  cout << maison << endl;

  return 0;
}
