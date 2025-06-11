#pragma once
#include "iterateur.hpp"
#include "noeud.hpp"
#include "gsl/gsl_assert"


template<typename T> class Iterateur;

template<typename T>

class ListeLiee
{
	friend class Iterateur<T>;
public:
	using iterator = Iterateur<T>;  // Définit un alias au type, pour que ListeLiee<T>::iterator corresponde au type de son itérateur.

	//TODO: La construction par défaut doit créer une liste vide valide.
	ListeLiee() : tete_(nullptr), queue_(nullptr), taille_(0) {}
	~ListeLiee()
	{
		while (tete_ != nullptr) {
			Noeud<T>* suivant = tete_->suivant_;
			delete tete_;  
			tete_ =suivant;  
		}
		taille_ = 0;
		//TODO: Enlever la tête à répétition jusqu'à ce qu'il ne reste aucun élément.
		// Pour enlever la tête, 
		// 1. La tête doit devenir le suivant de la tête actuelle.
		// 2. Ne pas oublier de désallouer le noeud de l'ancienne tête (si pas fait automatiquement).
	}

	bool estVide() const  { return taille_ == 0; }
	unsigned size() const { return taille_; }
	//NOTE: to_address (C++20) permet que ce même code fonctionne que vous utilisiez des pointeurs bruts ou intelligents (ça prend le pointeur brut associé au pointeur intelligent, s'il est intelligent).
	iterator begin() { return { tete_ }; }
	iterator end() { return { nullptr }; }

	// Ajoute à la fin de la liste.
	void push_back(const T& item)
	{
		auto* nouveau = new Noeud<T>{ item, nullptr, queue_ }; 
		if (estVide()) {
			tete_ = queue_ = nouveau;
		}
		else {
			queue_->suivant_ = nouveau;
			nouveau->precedent_ = queue_;	
			queue_ = nouveau;  
		}
		taille_++;
		//TODO: Vous devez créer un nouveau noeud en mémoire.
		//TODO: Si la liste était vide, ce nouveau noeud est la tête et la queue;
		// autrement, ajustez la queue et pointeur(s) adjacent(s) en conséquence.
	}

	// Insère avant la position de l'itérateur.
	iterator insert(iterator it, const T& item)
	{
		Noeud<T>* courant = it.position_;
		Noeud<T>* precedent = it.precedent_;
		auto* nouveau = new Noeud<T>{ item, courant, precedent };

		if (precedent != nullptr)
			precedent->suivant_ = nouveau;
		else
			tete_ = nouveau;

		if (courant != nullptr)
			courant->precedent_ = nouveau;
		else
			queue_ = nouveau;

		taille_++;
		return iterator{ nouveau };
		//NOTE: Pour simplifier, vous n'avez pas à supporter l'insertion à la fin (avant "past the end"),
		// ni l'insertion au début (avant la tête), dans cette méthode.
		//TODO:
		// 1. Créez un nouveau noeud initialisé avec item.
		// 2. Modifiez les attributs suivant_ et precedent_ du nouveau noeud
		//    afin que le nouveau noeud soit lié au noeud précédent et suivant
		//    à l'endroit où il est inséré selon notre itérateur.
		// 3. Modifiez l'attribut precedent_ du noeud après la position d'insertion
		//    (l'itérateur) afin qu'il pointe vers le noeud créé.
		// 4. Modifiez l'attribut suivant_ du noeud avant la position d'insertion
		//    (précédent de l'itérateur) afin qu'il point vers le noeud créé.
		// 5. Incrémentez la taille de la liste.
		// 6. Retournez un nouvel itérateur initialisé au nouveau noeud.
	}

	// Enlève l'élément à la position it et retourne un itérateur vers le suivant.
	iterator erase(iterator it)
	{
		Noeud<T>* courant = it.position_;
		Expects(courant != nullptr);
		Noeud<T>* precedent = courant->precedent_;
		Noeud<T>* suivant = courant->suivant_;

		if (precedent != nullptr)
			precedent->suivant_ = suivant;
		else
			tete_ = suivant;
		if (suivant != nullptr)
			suivant->precedent_ = precedent;
		else
			queue_ = precedent;
		delete courant;
		taille_--;
		return iterator{ suivant};
		//TODO: Enlever l'élément à la position de l'itérateur.
		//  1. Le pointeur vers le Noeud à effacer est celui dans l'itérateur.
		//  2. Modifiez l'attribut suivant_ du noeud précédent pour que celui-ci
		//     pointe vers le noeud suivant la position de l'itérateur (voir 1.).
		//  3. Modifiez l'attribut precedent_ du noeud suivant la position de
		//     l'itérateur pour que celui-ci pointe vers le noeud précédent
		//     de la position de l'itérateur (voir 1.).
		//  4. Désallouez le Noeud à effacer (voir 1.).
		//  5. Décrémentez la taille de la liste
		//  6. Retournez un itérateur vers le suivant du Noeud effacé.
		//TODO: On veut supporter d'enlever le premier élément de la liste,
		//  donc en 2. il se peut qu'il n'y ait pas de précédent et alors c'est
		//  la tête de liste qu'il faut ajuster.
		//NOTE: On ne demande pas de supporter d'effacer le dernier élément (c'est similaire au cas pour enlever le premier).
	}

private:
	gsl::owner<Noeud<T>*> tete_ = nullptr;  //NOTE: Vous pouvez changer le type si vous voulez.
	Noeud<T>* queue_;
	unsigned taille_;
};
