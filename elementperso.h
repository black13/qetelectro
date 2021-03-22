#ifndef ELEMENTPERSO_H
	#define ELEMENTPERSO_H
	#include "elementfixe.h"
	#include <QtGui>
	class ElementPerso : public ElementFixe {
		public:
		ElementPerso(QString &, QGraphicsItem * = 0,int * = NULL);
		virtual int nbBornes() const;
		virtual void paint(QPainter *, const QStyleOptionGraphicsItem *);
		QString typeId() { return(nomfichier); }
		QString fichier() { return(nomfichier); }
		bool isNull() { return(elmt_etat != 0); }
		int etat() { return(elmt_etat); }
		QString nom() { return(priv_nom); }
		
		private:
		int elmt_etat; // contains the error code if the instantiation failed or 0 if the instantiation was successful
		QString priv_nom;
		QString nomfichier;
		QPicture dessin;
		bool parseElement(QDomElement &, QPainter &);
		bool parseLigne(QDomElement &, QPainter &);
		bool parseCercle(QDomElement &, QPainter &);
		bool parsePolygone(QDomElement &, QPainter &);
		bool parseBorne(QDomElement &);
		void setQPainterAntiAliasing(QPainter *, bool);
		int attributeIsAnInteger(QDomElement &, QString, int * = NULL);
		int nb_bornes;
	};
#endif
