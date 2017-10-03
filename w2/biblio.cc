#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*******************************************
 * Completez le programme a partir d'ici.
 *******************************************/
class Auteur{

	public:
		Auteur(string n, bool p = false)
			:nom(n), prime(p)
		{}

		Auteur(Auteur const&) = delete;

		string getNom() const {
			return nom;
		}

		bool getPrix() const {
			return prime;
		}

	private:
		string nom;
		bool prime;
		
};

class Oeuvre{

	public:
		Oeuvre(string t, const Auteur& a, string l)
		:titre(t), auteur(a), langue(l)
		{}

		Oeuvre(Oeuvre const&) = delete;

		string getTitre() const{
			return titre;
		}

		const Auteur& getAuteur()const {
			return auteur;
		}

		string getLangue() const{
			return langue;
		}

		void affiche(){
			cout <<titre <<", " << auteur.getNom() <<", en "
				<< langue;
		}

		~Oeuvre(){
			cout<< "L'oeuvre \""
			       	<<titre<<", "
				<< auteur.getNom() << ", en " << langue 
				<<"\" n'est plus disponible." << endl;
		}

	private:
		string titre;
		const Auteur& auteur;
	       	string langue;
};

class Exemplaire{

	public:
		Exemplaire(Oeuvre const& o)
			:oeuvre(o)
		{
			cout << "Nouvel exemplaire de : "
			       << oeuvre.getTitre() << ", "
			       << oeuvre.getAuteur().getNom() << ", en "
			       << oeuvre.getLangue() << endl;
		}
		Exemplaire(Exemplaire const& e)
		:oeuvre(e.oeuvre)
		{
			cout << "Copie d'un exemplaire de : "
				<<oeuvre.getTitre() << ", "
				<<oeuvre.getAuteur().getNom() <<", en "
				<<oeuvre.getLangue() <<endl;
		}

		~Exemplaire()
		{
			cout << "Un exemplaire de \"" << oeuvre.getTitre() 
				<< ", " << oeuvre.getAuteur().getNom() 
				<< ", en " << oeuvre.getLangue() 
				<< "\" a été jeté !" << endl;
		}

		Oeuvre const& getOeuvre() {
			return oeuvre;
		}

		void affiche(){
			cout << "Exemplaire de : " << oeuvre.getTitre() 
				<< ", " << oeuvre.getAuteur().getNom() 
				<< ", en " << oeuvre.getLangue(); 
		}

	private:
		Oeuvre const& oeuvre;

};

class Bibliotheque{
	public:
		Bibliotheque(string n)
			: nom(n)
		{
			cout << "La bibliothèque " << nom
				<< " est ouverte !" << endl;
		}

		string getNom(){
			return nom;
		}

		void stocker(Oeuvre const& oeuvre, unsigned int n=1)
		{
			for (; n > 0; n--) {
				Exemplaire* ptr = new Exemplaire(oeuvre);
				exemplaires.push_back(ptr);

			} 
		}	

		void lister_exemplaires(string langue = "")
		{
			if (langue != "") {
				for (auto e : exemplaires) {
					if (e->getOeuvre().getLangue() == langue) {
						e->affiche();
						cout << endl;
					}
				}
			} else {
				for (auto e : exemplaires){
					e->affiche();
					cout << endl;
				}
			}
		}

		unsigned int compter_exemplaires(Oeuvre const& oeuvre)
		{
			unsigned int comptees(0);
			for (auto e : exemplaires) {
				if (e->getOeuvre().getTitre() == oeuvre.getTitre()) {
					comptees++;
				}
			}
			return comptees;
		}

		void afficher_auteurs(bool primes = false)
		{
			if (primes) {
				for (auto e : exemplaires) {					 
					if (e->getOeuvre().getAuteur().getPrix()){
						cout << e->getOeuvre().getAuteur().getNom() << endl;
					}

				}
			} else {
				for (auto e : exemplaires) {
					cout << e->getOeuvre().getAuteur().getNom() << endl;

				}
			}
		}

		~Bibliotheque()
		{
			cout << "La bibliothèque " << nom 
				<< " ferme ses portes," << endl;
			cout << "et détruit ses exemplaires: " << endl;
			for (auto & e : exemplaires){
				delete e;
				e = nullptr;
			}
			
		
			
				exemplaires.clear();
				
			
		}

	private:
		string nom;
		vector<Exemplaire*> exemplaires;


};



/*******************************************
 * Ne rien modifier apres cette ligne.
 *******************************************/

int main()
{
  Auteur a1("Victor Hugo"),
         a2("Alexandre Dumas"),
         a3("Raymond Queneau", true);

  Oeuvre o1("Les Misérables"           , a1, "français" ),
         o2("L'Homme qui rit"          , a1, "français" ),
         o3("Le Comte de Monte-Cristo" , a2, "français" ),
         o4("Zazie dans le métro"      , a3, "français" ),
         o5("The Count of Monte-Cristo", a2, "anglais" );

  Bibliotheque biblio("municipale");
  biblio.stocker(o1, 2);
  biblio.stocker(o2);
  biblio.stocker(o3, 3);
  biblio.stocker(o4);
  biblio.stocker(o5);

  cout << "La bibliothèque " << biblio.getNom()
       << " offre les exemplaires suivants :" << endl;
  biblio.lister_exemplaires();

  const string langue("anglais");
  cout << " Les exemplaires en "<< langue << " sont :" << endl;
  biblio.lister_exemplaires(langue);

  cout << " Les auteurs à succès sont :" << endl;
  biblio.afficher_auteurs(true);

  cout << " Il y a " << biblio.compter_exemplaires(o3) << " exemplaires de "
       << o3.getTitre() << endl;

  return 0;
}
