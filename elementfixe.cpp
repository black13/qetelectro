#include "elementfixe.h"
/**
constructor
*/
ElementFixe::ElementFixe(QGraphicsItem *parent, Schema *scene) : Element(parent, scene) {
}

/**
	@return the minimum number of terminals that the element can have
*/
int ElementFixe::nbBornesMin() const {
	return(nbBornes());
}

/**
	@return Le nombre maximal de bornes que l'element peut avoir
*/
int ElementFixe::nbBornesMax() const {
	return(nbBornes());
}

/**
	XML Import Method.This method is called during the import of XML content (paste, import, file opening ...) so that the element can manage itself the importation of its terminals.Here, as this class is characterized by a fixed number of terminals, the implementation requires to find exactly its terminals in the XML file.
	@param e XML element to analyze.
	@Param table_id_adr reference to the correspondence table between the IDS of the XML file and the addresses in memory.If import succeeds, you have to add the good couples (id, address).
	@return true if the import has managed, false otherwise
	
 */
bool ElementFixe::fromXml(QDomElement &e, QHash<int, Borne *> &table_id_adr) {
/*
 the terminals will now be listed to associate their id to their real address
 this census will be used when placing the wires
*/
	
	QList<QDomElement> liste_bornes;
 	// course of the children of the element
	for (QDomNode enfant = e.firstChild() ; !enfant.isNull() ; enfant = enfant.nextSibling()) {
	 // we are interested in the XML element "limits"
		QDomElement bornes = enfant.toElement();
		if (bornes.isNull() || bornes.tagName() != "bornes") continue;
		// browse the children of the "terminals" XML element
		for (QDomNode node_borne = bornes.firstChild() ; !node_borne.isNull() ; node_borne = node_borne.nextSibling()) {
		// we are interested in the "bound" XML element
			QDomElement borne = node_borne.toElement();
			if (!borne.isNull() && Borne::valideXml(borne)) liste_bornes.append(borne);
		}
	}
	
	QHash<int, Borne *> priv_id_adr;
	int bornes_non_trouvees = 0;
	foreach(QGraphicsItem *qgi, childItems()) {
		if (Borne *p = qgraphicsitem_cast<Borne *>(qgi)) {
			bool borne_trouvee = false;
			foreach(QDomElement qde, liste_bornes) {
				if (p -> fromXml(qde)) {
					priv_id_adr.insert(qde.attribute("id").toInt(), p);
					borne_trouvee = true;
					break;
				}
			}
			if (!borne_trouvee) ++ bornes_non_trouvees;
		}
	}
	
	if (bornes_non_trouvees > 0) {
		return(false);
	} else {
	// check that the id / adr associations do not conflict with table_id_adr
		foreach(int id_trouve, priv_id_adr.keys()) {
			if (table_id_adr.contains(id_trouve)) {
	 		// this element has an id which is already referenced (= conflict)
				return(false);
			}
		}
		// copy of id / adr associations
		foreach(int id_trouve, priv_id_adr.keys()) {
			table_id_adr.insert(id_trouve, priv_id_adr.value(id_trouve));
		}
	}
	
	return(true);
}
