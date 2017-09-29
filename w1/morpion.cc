#include<iostream>
#include<array>

using namespace std;

enum CouleurCase {VIDE, ROND, CROIX};
typedef array<array<CouleurCase, 3>, 3> Grille;

class JeuMorpion {
	public:
		void initialise() {
			for (auto& ligne : grille) {
				for (auto& kase : ligne) {
					kase = VIDE;
				}
			}
	       	}
		
	bool placer_rond(size_t ligne, size_t colonne) {
		return placer_coup(ligne, colonne, ROND);
	}

	bool placer_croix(size_t ligne, size_t colonne) {
		return placer_coup(ligne, colonne, CROIX);
	}

	CouleurCase get_gagneur(){
		for (size_t i(0); i < grille.size(); i++) {
			if (verifie_ligne(i)) {
				return grille[i][0];
			}
			if (verifie_colonne(i)) {
				return grille[0][i];
			}
		}
		CouleurCase milieu = grille[1][1];
		if (milieu != VIDE) {
			if (verifie_diag_princ()) {return milieu;}
			if (verifie_diag_sec()) {return milieu;}
		}
		return VIDE;
	}
	

	void affiche(){
		cout << endl << "_______" << endl;
		for(auto ligne: grille){
			cout << "|";
			for (auto kase : ligne) {
				cout << kase << "|";
			}
			cout << endl;
			cout << "-------" << endl;
		}
	}

	bool est_plein() {
		for (auto ligne : grille) {
			for (auto kase : ligne) {
				if (kase == VIDE) { return false; }
			}
		}
		return true;
	}

	private:
		/**
		 * Place un coup sur le plateau en position (ligne, colonne).
		 * Ligne et colonne: 0, 1 ou 2.
		 */
		bool placer_coup(size_t ligne, size_t colonne, CouleurCase coup) {
			if (ligne >= grille.size() 
					or colonne >= grille[ligne].size()) {
				cout << "Mauvaise position! " << endl;
				return false;
			}
			if (grille[ligne][colonne] == VIDE) {
				grille[ligne][colonne] = coup;
				return true;
			} else {
				cout << "Case deja occupee!" << endl;
				return false;
			}
		}

		bool verifie_ligne(int i){
			if (grille[i][0] != VIDE) {
				return (grille[i][0] == grille[i][1] and grille[i][0] == grille[i][2]);
			}
			return false;
		}
		
		bool verifie_colonne(int i){
			if (grille[0][i] != VIDE) {
				return (grille[0][i] == grille[1][i] and grille[0][i] == grille[2][i]);
			}
			return false;
		}

		bool verifie_diag_princ(){
			return (grille[0][0] == grille[1][1] and grille[1][1] == grille[2][2]);
		}

		bool verifie_diag_sec() {
			return (grille[0][2] == grille[1][1] and grille[1][1] == grille [2][0]);
		}
		

		Grille grille;

};

int main() {
	JeuMorpion jeu;
	jeu.initialise();
	CouleurCase touche = CROIX;
	while(jeu.get_gagneur() == VIDE and !jeu.est_plein()) {
		jeu.affiche();
		cout << endl << "Touche a " << touche << endl;
		size_t ligne, colonne;
		bool coup_acceptee = false;
		do {
			cout << "Ligne et colonne pour placer votre coup? (0, 1 ou 2?) : ";
			cin >> ligne >> colonne;
			coup_acceptee = (touche == CROIX ? 
					jeu.placer_croix(ligne, colonne) 
					: jeu.placer_rond(ligne, colonne));
			
		}while(!coup_acceptee);
		touche = (touche == CROIX ? ROND : CROIX);
	}
	jeu.affiche();
	CouleurCase gagneur = jeu.get_gagneur();
	cout << endl;
	if (gagneur == VIDE) {
		cout << "Personne a gagne!";
	} else {
		cout << gagneur << " a gagne! ";
	}	
	cout <<endl;
	return 0;
}
