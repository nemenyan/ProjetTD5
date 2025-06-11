#include "Personnage.hpp"
#include "Heros.hpp"
#include "Vilain.hpp"
#include "VilainHeros.hpp"
#include "ListeLiee.hpp"
#include <fstream>
#include <vector>
#include <set>
#include <functional>
#include "cppitertools/range.hpp"
#include "bibliotheque_cours.hpp"
using namespace std;
using namespace iter;

using UInt8  = uint8_t;
using UInt16 = uint16_t;

UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read(reinterpret_cast<char*>(&texte[0]), streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}

template <typename T>
vector<T> lireFichier(istream& fichier)
{
	vector<T> elements;
	for ([[maybe_unused]] int i : range(lireUint16(fichier)))
		elements.push_back(T(fichier));
	return elements;
}

ifstream ouvrirLectureFichierBinaire(const string& nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	return fichier;
}

// Permet d'avoir une référence non-const à un objet temporaire.
template <typename T> T& temporaireModifiable(T&& objet) { return objet; }

template <typename T>
vector<T> lireFichier(const string& nomFichier)
{
	return lireFichier<T>(temporaireModifiable(
		ouvrirLectureFichierBinaire(nomFichier)));
}

template <typename T>
Iterateur<T> trouverParNom(ListeLiee<T>& liste, const string& nom)
{
	Iterateur<T> fin = liste.end();
	for (Iterateur<T> pos = liste.begin(); pos != fin; pos.avancer()) {
		if ((*pos).getNom() == nom)
			return pos;
	}
	return fin;
}


int main()
{
	#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
	#pragma endregion
	
	// Trait de separation
	static const string trait =
		"═════════════════════════════════════════════════════════════════════════";

	static const string separateurSections = "\033[95m" + trait + "\033[0m\n";
	static const string separateurElements = "\033[33m" + trait + "\033[0m\n";

	//{ Solutionnaire du TD4:
	vector<Heros> heros = lireFichier<Heros>("heros.bin");
	vector<Vilain> vilains = lireFichier<Vilain>("vilains.bin");
	vector<unique_ptr<Personnage>> personnages;  // Doit être des pointeurs pour le polymorphisme, l'énoncé ne force pas les unique_ptr.

	//#if 1 //TODO: Vous n'avez pas à conserver ces affichages pour le TD5, ils sont pour le solutionnaire du TD4:
	//cout << separateurSections << "Heros:" << endl;
	//for (auto& h : heros) {
	//	cout << separateurElements;
	//	h.changerCouleur(cout, 0);
	//	h.afficher(cout);
	//}

	//cout << separateurSections << "Vilains:" << endl;
	//for (auto& v : vilains) {
	//	cout << separateurElements;
	//	v.changerCouleur(cout, 0);
	//	v.afficher(cout);
	//}

	//for (auto& h : heros)
	//	personnages.push_back(make_unique<Heros>(h));

	//for (auto& v : vilains)
	//	personnages.push_back(make_unique<Vilain>(v));

	//personnages.push_back(make_unique<VilainHeros>(vilains[1], heros[2]));

	//cout << separateurSections << "Personnages:" << endl;
	//for (auto& p : personnages) {
	//	cout << separateurElements;
	//	p->changerCouleur(cout, 0);
	//	p->afficher(cout);
	//}
	//cout << separateurSections << "Un autre vilain heros (exemple de l'énoncé du TD):" << endl;
	//VilainHeros kefkaCrono(vilains[2], heros[0]);
	//kefkaCrono.changerCouleur(cout,1);
	//kefkaCrono.afficher(cout);
	//#endif
	////}
	
	//TODO: Transférez les héros du vecteur heros dans une ListeLiee.
	ListeLiee<Heros> listeHeros;
	for (auto& h : heros) {
		listeHeros.push_back(h);
	}
	
	//TODO: Créez un itérateur sur la liste liée à la position du héros Alucard
	// Servez-vous de la fonction trouverParNom définie plus haut

	Iterateur<Heros> itAlucard = trouverParNom(listeHeros, "Alucard");

	
	//TODO: Servez-vous de l'itérateur créé précédemment pour trouver l'héroine Aya Brea,
	// en sachant qu'elle se trouve plus loin dans la liste.
	Iterateur<Heros> itAyaBrea = itAlucard;
	while (itAyaBrea != listeHeros.end() && (*itAyaBrea).getNom() != "Aya Brea") {
		itAyaBrea.avancer();
	}
	//TODO: Ajouter un hero bidon à la liste avant Aya Brea en vous servant de l'itérateur.
	//TODO: Assurez-vous que la taille de la liste est correcte après l'ajout.

	Heros heroBidon("Neme", "Osu", "Aucun ennemi");
	listeHeros.insert(itAyaBrea, heroBidon);
	cout << "Taille apres ajout: " << listeHeros.size() << endl;
	
	//TODO: Reculez votre itérateur jusqu'au héros Mario et effacez-le en utilisant l'itérateur, puis affichez le héros suivant dans la liste (devrait êter "Naked Snake/John").
	//TODO: Assurez-vous que la taille de la liste est correcte après le retrait.
	Iterateur<Heros> itMario = trouverParNom(listeHeros, "Mario");
	if (itMario != listeHeros.end()) {
		Iterateur<Heros> itSuivant = listeHeros.erase(itMario);
		cout << "Heros suivant apres suppression de Mario : " << (*itSuivant).getNom() << endl;
	}
	cout << "\nTaille apres suppression : " << listeHeros.size() << endl;

	//TODO: Effacez le premier élément de la liste.
	listeHeros.erase(listeHeros.begin());
	cout << "\nTaille apres suppression du premier element : " << listeHeros.size() << endl;

	//TODO: Affichez votre liste de héros en utilisant un itérateur. La liste débute
	// avec le héros Randi et n'a pas Mario.
	// Servez-vous des methodes begin et end de la liste...
	cout << "\nListe finale des heros :" << endl;
	for (Iterateur<Heros> it = listeHeros.begin(); it != listeHeros.end(); it.avancer()) {
		string nom = (*it).getNom();
		cout << "- " << (nom.empty() ? "[NOM VIDE]" : nom) << endl;
	}

	cout << "\nListe finale des heros :" << endl;
	for (Iterateur<Heros> it = listeHeros.begin(); it != listeHeros.end(); it.avancer()) {
		cout << "- " << (*it).getNom() << endl;
	}

	//TODO: Refaite le même affichage mais en utilisant une simple boucle "for" sur intervalle.
	cout << separateurSections << "\nListe des heros avec boucle for:" << endl;
	for (Heros& h : listeHeros) {
		cout << separateurElements;
		h.afficher(cout);
	}


	//TODO: Utilisez un conteneur pour avoir les héros en ordre alphabétique (voir point 2 de l'énoncé).
	auto comparerParNom = [](const Heros& a, const Heros& b) {
		return a.getNom() < b.getNom();
		};

	set<Heros, decltype(comparerParNom)> herosTries(comparerParNom);

	for (Heros& h : listeHeros)
		herosTries.insert(h);

	cout << separateurSections << "Heros en ordre alphabétique :" << endl;
	for (const Heros& h : herosTries) {
		cout << separateurElements;
		h.afficher(cout);
	}
	//TODO: Assurez-vous de n'avoir aucune ligne non couverte dans les classes pour la liste liée.  Il peut y avoir des lignes non couvertes dans les personnages...
	cout << separateurSections << "Fin du programme." << endl;
	if (!listeHeros.estVide())
		cout << "Premier heros actuel : " << (*listeHeros.begin()).getNom() << endl;
	cout << "Taille finale de la liste : " << listeHeros.size() << endl;
	
	
	// 2.2 Recherche d'un héros par nom dans le set
	auto itTrouve = herosTries.find(Heros("Alucard", "", "")); // Nom identique suffisant car trié par nom

	if (itTrouve != herosTries.end()) {
		cout << "Heros trouve dans set : " << endl;
		itTrouve->changerCouleur(cout, 1);
		itTrouve->afficher(cout);
	}

	/*
	Complexité de la recherche : O(log n) en moyenne
	En effet, set est implémenté en arbre binaire de recherche qui donne une recherche logarithmique.
	*/

	/*
	2.3 Quel conteneur est plus rapide pour une recherche par nom ?

	Réponse : le set est plus rapide.
	En effet, le ListeLiee parcours chaque élément un par un (complexité O(n)),
	alors que le set est trié automatiquement et utilise une structure qui
	permet des recherches en O(log n). En conclusion, le set est plus efficace
	que le ListeLiee pour les recherches de nom.

	*/


}
