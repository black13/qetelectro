#ifndef DEL_H
	#define DEL_H
	#include "elementfixe.h"
	/**
	This HERITE class of the fixed class to define a
	Diode ElectroLuminescente
	*/
	class DEL : public ElementFixe {
		public:
		DEL(QGraphicsItem * = 0, Schema * = 0);
		virtual int nbBornes() const;
		void paint(QPainter *, const QStyleOptionGraphicsItem *);
		QString typeId();
		QString  nom() { return("DEL"); }
	};
#endif
