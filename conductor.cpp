#include <QtDebug>
#include "conductor.h"
#include "element.h"
#include "debug.h"
/**
	Constructor
	@param p1 first terminal to which the driver is linked
	@param p2 second terminal to which the driver is linked
	@Param Parent Element of the driver (0 by default)
	@Param Scene QGraphicsscene in which the driver belongs
*/
Conductor::Conductor(Terminal *p1, Terminal* p2, Element *parent, QGraphicsScene *scene) : QGraphicsPathItem(parent) {
	trace_msg("");
	// terminals that the conductor connects
	terminal1 = p1;
	terminal2 = p2;
	// add the conductor to the list of conductors for each of the two terminals
	bool ajout_p1 = terminal1 -> addConducteur(this);
	bool ajout_p2 = terminal2 -> addConducteur(this);
	// en cas d'echec de l'ajout (conducteur deja existant notamment)
	if (!ajout_p1 || !ajout_p2) return;
	destroyed = false;
	// the driver is represented by a fine line
	QPen t;
	t.setWidthF(1.0);
	setPen(t);
	// Calculation of driver rendering
	calculateConductor();
}

/**
	Updates the graphical representation of the driver.
	@param rect rectangle to update
*/
void Conductor::update(const QRectF &rect = QRectF()) {
	calculateConductor();
	QGraphicsPathItem::update(rect);
}

/**
	Updates the graphical representation of the driver.
	@param x rectangle abscissa to update
	@param y ordinate rectangle to update
	@param width rectangle length to update
	@param height rectangle height to be updated
*/
void Conductor::update(qreal x, qreal y, qreal width, qreal height) {
	calculateConductor();
	QGraphicsPathItem::update(x, y, width, height);
}

 /**
	Driver's destroyer.Before being destroyed, the driver removes terminals
	to which he is linked.
 */
 /* Driver::~Driver () {

}*/

/**
	Update the qpainterpath constituting the driver to get
	A driver only composed of lines connecting the two terminals.
*/
void Conductor::calculateConductor() {
	QPainterPath t;
	trace_msg("");
	QPointF p1 = terminal1 -> amarrageConducteur();
	QPointF p2 = terminal2 -> amarrageConducteur();
	
	QPointF depart, arrivee;
	Terminal::Orientation ori_depart, ori_arrivee;
	// distinguishes the departure from the arrival: the trip is always from left to right
	if (p1.x() <= p2.x()) {
		depart      = mapFromScene(p1);
		arrivee     = mapFromScene(p2);
		ori_depart  = terminal1 -> orientation();
		ori_arrivee = terminal2 -> orientation();
	} else {
		depart      = mapFromScene(p2);
		arrivee     = mapFromScene(p1);
		ori_depart  = terminal2 -> orientation();
		ori_arrivee = terminal1 -> orientation();
	}
	
	// Beginning of the trip
	t.moveTo(depart);
	if (depart.y() < arrivee.y()) {
		// downhide
		if ((ori_depart == Terminal::Nord && (ori_arrivee == Terminal::Sud || ori_arrivee == Terminal::Ouest)) || (ori_depart == Terminal::Est && ori_arrivee == Terminal::Ouest)) {
		// case � 3 �
			qreal ligne_inter_x = (depart.x() + arrivee.x()) / 2.0;
			t.lineTo(ligne_inter_x, depart.y());
			t.lineTo(ligne_inter_x, arrivee.y());
		} else if ((ori_depart == Terminal::Sud && (ori_arrivee == Terminal::Nord || ori_arrivee == Terminal::Est)) || (ori_depart == Terminal::Ouest && ori_arrivee == Terminal::Est)) {
 // case   4  
			qreal ligne_inter_y = (depart.y() + arrivee.y()) / 2.0;
			t.lineTo(depart.x(), ligne_inter_y);
			t.lineTo(arrivee.x(), ligne_inter_y);
		} else if ((ori_depart == Terminal::Nord || ori_depart == Terminal::Est) && (ori_arrivee == Terminal::Nord || ori_arrivee == Terminal::Est)) {
			t.lineTo(arrivee.x(), depart.y()); // cas « 2 »
		} else t.lineTo(depart.x(), arrivee.y()); // cas « 1 »
	} else {
		// rising path
		if ((ori_depart == Terminal::Ouest && (ori_arrivee == Terminal::Est || ori_arrivee == Terminal::Sud)) || (ori_depart == Terminal::Nord && ori_arrivee == Terminal::Sud)) {
		// case � 3 �
			qreal ligne_inter_y = (depart.y() + arrivee.y()) / 2.0;
			t.lineTo(depart.x(), ligne_inter_y);
			t.lineTo(arrivee.x(), ligne_inter_y);
		} else if ((ori_depart == Terminal::Est && (ori_arrivee == Terminal::Ouest || ori_arrivee == Terminal::Nord)) || (ori_depart == Terminal::Sud && ori_arrivee == Terminal::Nord)) {
		// case � 4 �
			qreal ligne_inter_x = (depart.x() + arrivee.x()) / 2.0;
			t.lineTo(ligne_inter_x, depart.y());
			t.lineTo(ligne_inter_x, arrivee.y());
		} else if ((ori_depart == Terminal::Ouest || ori_depart == Terminal::Nord) && (ori_arrivee == Terminal::Ouest || ori_arrivee == Terminal::Nord)) {
			t.lineTo(depart.x(), arrivee.y()); // cas « 2 »
		} else t.lineTo(arrivee.x(), depart.y()); // cas « 1 »
	}
 // end of trip
	t.lineTo(arrivee);
	setPath(t);
}

/**

Draw the driver without antialiasing.
@param qp The QPainter to use to draw the conductor
@param qsogi Style options for the driver
@param qw The QWidget on which we draw
*/
void Conductor::paint(QPainter *qp, const QStyleOptionGraphicsItem *qsogi, QWidget *qw) {
	trace_msg("");
	qp -> save();
	qp -> setRenderHint(QPainter::Antialiasing,          false);
	qp -> setRenderHint(QPainter::TextAntialiasing,      false);
	qp -> setRenderHint(QPainter::SmoothPixmapTransform, false);
	QGraphicsPathItem::paint(qp, qsogi, qw);
	qp -> restore();
}

/**
Indicates whether two Terminal orientations are on the same axis (Vertical / Horizontal).
@param a Terminal's first orientation
@param b The second orientation of Terminal
@return A boolean is true if both terminal orientations are on the same axis
*/
bool Conductor::surLeMemeAxe(Terminal::Orientation a, Terminal::Orientation b) {
	if ((a == Terminal::Nord || a == Terminal::Sud) && (b == Terminal::Nord || b == Terminal::Sud)) return(true);
	else if ((a == Terminal::Est || a == Terminal::Ouest) && (b == Terminal::Est || b == Terminal::Ouest)) return(true);
	else return(false);
}

/**
	Indicates whether a terminal orientation is horizontal (East / West).
	@Param has the orientation of terminal
	@return true if the terminal orientation is horizontal, false otherwise
*/
bool Conductor::estHorizontale(Terminal::Orientation a) {
	return(a == Terminal::Est || a == Terminal::Ouest);
}

/**
	Indicates whether a terminal orientation is vertical (North / South).
	@Param has the orientation of terminal
	@Param has the orientation of terminal
	@return True if the orientation of terminal is vertical, false otherwise
*/
bool Conductor::estVerticale(Terminal::Orientation a) {
	return(a == Terminal::Nord || a == Terminal::Sud);
}

/**
Method of preparation to the destruction of the driver;The driver is detached from his two terminals
*/
void Conductor::destroy() {
	destroyed = true;
	terminal1 -> removeConducteur(this);
	terminal2 -> removeConducteur(this);
}

/**
	ELEMENT VALIDATION METHOD XML
	@param e an element XML Sense represents a driver
	@return True if the XML element represents a driver well;false otherwise
*/
bool Conductor::valideXml(QDomElement &e){
	// verify the name of the tag
	if (e.tagName() != "conductor") return(false);
	
	// check the presence of minimum attributes
	if (!e.hasAttribute("terminal1")) return(false);
	if (!e.hasAttribute("terminal2")) return(false);
	
	bool conv_ok;
	// Parse the abscissa
	e.attribute("terminal1").toInt(&conv_ok);
	if (!conv_ok) return(false);
	
	// Parse ordinate
	e.attribute("terminal2").toInt(&conv_ok);
	if (!conv_ok) return(false);
	return(true);
}
