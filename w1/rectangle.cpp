#include <iostream>
using namespace std;

class Rectangle{
public: 
	
	double surface() const;	
	double getHauteur() const;	
	double getLargeur() const;
	void setHauteur(double h);	
	void setLargeur(double l);
	
private:
	double hauteur_;
	double largeur_;	
 
};

	double Rectangle::surface() const
	{
		return hauteur_ * largeur_;
			
	}
	
	double Rectangle::getHauteur() const 
	{
		return hauteur_;
	}
	
	double Rectangle::getLargeur() const 
	{
		return largeur_;
	}

	void Rectangle::setHauteur(double h)
	{
		hauteur_ = h;
	}
	
	void Rectangle::setLargeur(double l)
	{
		largeur_ = l;
	}	

int main()
{
	Rectangle rect1;
	rect1.setHauteur(3.0);
	rect1.setLargeur(4.0);
	
	cout << "Surface: " << rect1.surface() 
	<<endl;
	return 0;
}
