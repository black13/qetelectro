#ifndef BORNE_H
	#define BORNE_H
	#define TAILLE_BORNE 4
	#include <QtWidgets>
	#include <QtXml/QtXml>
	class Conductor;
	class Element;
	class Schema;
	/**
	Class modeling the "terminal" of a device, that is to say a
	connection possible for a Driver.
	*/
	class Terminal : public QGraphicsItem {
		public:
		// enum defining the orientation of the terminal
		enum Orientation {Nord, Sud, Est, Ouest};
		
		// allows to cast a QGraphicsItem in Terminal with qgraphicsitem_cast
		enum { Type = UserType + 1002 };
    	virtual int type() const { return Type; }
		
		// constructeurs
		Terminal();
		Terminal(QPointF,      Terminal::Orientation, Element * = 0, Schema * = 0);
		Terminal(qreal, qreal, Terminal::Orientation, Element * = 0, Schema * = 0);
		
		// destructeur
		~Terminal();
		
		// implementation des methodes virtuelles pures de QGraphicsItem
		void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
		QRectF boundingRect() const;
		
		// Methods of handling drivers related to this terminal
		bool addConducteur(Conductor *);
		void removeConducteur(Conductor *);
		inline int nbConducteurs() { return(liste_conducteurs.size()); }
		
		// read methods
		QList<Conductor *> conducteurs() const; 
		Terminal::Orientation orientation() const;
		inline QPointF amarrageConducteur() const { return(mapToScene(amarrage_conducteur)); }
		void updateConducteur();
		
		// methods relating to import / export in XML format
		static bool valideXml(QDomElement  &);
		bool        fromXml  (QDomElement  &);
		QDomElement toXml    (QDomDocument &);
		
		// event management methods
		void hoverEnterEvent  (QGraphicsSceneHoverEvent *);
		void hoverMoveEvent   (QGraphicsSceneHoverEvent *);
		void hoverLeaveEvent  (QGraphicsSceneHoverEvent *);
		void mousePressEvent  (QGraphicsSceneMouseEvent *);
		void mouseMoveEvent   (QGraphicsSceneMouseEvent *);
		void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
		
		private:
		// pointer to the schema type QGraphicsscene (avoids some caste internally)
		Schema *schema_scene;
		// coordinates mooring points
		QPointF amarrage_conducteur;
		QPointF amarrage_elmt;
		// Orientation of the terminal
		Terminal::Orientation sens;
		// list of conductors linked at this terminal
		QList<Conductor *> liste_conducteurs;
		// pointer to a rectangle corresponding to the bounding rect;allows you to calculate the bounding rect only once;the pointer is because the compilo requires a constable method
		QRectF *br;
		Terminal *terminal_precedente;
		bool hovered;
		// Method initiating the different members of the terminal
		void initialise(QPointF, Terminal::Orientation);
		// different colors that can be used for the "hover" effect
		QColor couleur_hovered;
		QColor couleur_neutre;
		QColor couleur_autorise;
		QColor couleur_prudence;
		QColor couleur_interdit;
	};
#endif
