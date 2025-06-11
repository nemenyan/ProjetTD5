#pragma once
#include "noeud.hpp"
#include "gsl/gsl_assert"
template<typename T>
class Iterateur
{
	friend class ListeLiee<T>;
public:
	//TODO: Constructeur(s).
	Iterateur(Noeud<T>* position, Noeud<T>* precedent = nullptr)
		: position_(position), precedent_(precedent) {
	}

	void avancer()
	{
		Expects(position_ != nullptr);
		//TODO: changez la position de l'itérateur pour le noeud suivant
		precedent_ = position_;
		position_ = position_->suivant_;
	}
	void reculer()
	{
		//NOTE: On ne demande pas de supporter de reculer à partir de l'itérateur end().
		Expects(position_ != nullptr);
		//TODO: Changez la position de l'itérateur pour le noeud précédent
		position_ = precedent_;
	}
	T& operator*()
	{
		return position_->valeur_;
	}
	T* operator->() {
		Expects(position_ != nullptr);
		return &(position_->valeur_);
	}
	const T* operator->() const {
		Expects(position_ != nullptr);
		return &(position_->valeur_);
	}


	Iterateur<T>& operator++()  // a voir si necessaire
	{
		avancer();
		return *this;
	}
	//TODO: Ajouter ce qu'il manque pour que les boucles sur intervalles fonctionnent sur une ListeLiee.
	
	bool operator!=(const Iterateur<T>& it) const { return !(*this == it); }
	
	bool operator==(const Iterateur<T>& it) const {
		return position_ == it.position_;
	}

private:
	Noeud<T>* position_ = nullptr;
	Noeud<T>* precedent_ = nullptr;
};
