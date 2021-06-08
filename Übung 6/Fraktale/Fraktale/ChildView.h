
// ChildView.h: Schnittstelle der CChildView-Klasse
//


#pragma once


// CChildView-Fenster

class CChildView : public CWnd
{
// Konstruktion
public:
	CChildView();

// Attribute
public:
	double m_minx;
	double m_deltax;

	double m_miny;
	double m_deltay;

	int m_width;
	int m_height;

	CDC m_DC;
// Vorgänge
public:

// Überschreibungen
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementierung
public:
	virtual ~CChildView();

	// Generierte Funktionen für die Meldungstabellen
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	void GLInit(int Breite, int Hoehe, int Modus);
	void Achsenkreuz(float l);
	void Bunter_Einheitswuerfel();
	afx_msg void OnAufgabe1Diagonale();
	afx_msg void OnAufgabe1Julia();
	void JuliaMalen();
	void BrotMalen();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnAufgabe2Mandelbrot();
	afx_msg void OnVektorenQuadrat();
	afx_msg void OnVektorenQuadrat2();
	afx_msg void OnVektorenQuadtratrot();
	afx_msg void OnVektorenWuerfel1();
	afx_msg void OnVektorenWuerfel2();
	afx_msg void OnVektorenWuerfel3();
	afx_msg void OnOpenglEinheitsw();
	afx_msg void OnOpenglStachel();
};

