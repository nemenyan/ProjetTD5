#pragma once
#include <gsl/pointers>
template<typename T> class ListeLiee;
template<typename T> class Iterateur;

template<typename T>
class Noeud
{
	friend class ListeLiee<T>;
	friend class Iterateur<T>;
public:
	//TODO: Constructeur(s).
	Noeud(const T& valeur, Noeud<T>* suivant =nullptr, Noeud<T>* precedent = nullptr) : valeur_(valeur), suivant_(suivant), precedent_(precedent) {}
private:
	//TODO: Attributs d'un noeud.
	T valeur_;
	Noeud<T>* suivant_ = nullptr;
	Noeud<T>* precedent_ = nullptr;	
};
