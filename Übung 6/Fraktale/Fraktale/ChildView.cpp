
// ChildView.cpp: Implementierung der CChildView-Klasse
//

#include "pch.h"
#include "framework.h"
#include "Fraktale.h"
#include "ChildView.h"
#include "Vector2.h"
#include "Vector3.h"

#include <gl\GL.h>
#include <gl\GLU.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_AUFGABE1_DIAGONALE, &CChildView::OnAufgabe1Diagonale)
	ON_COMMAND(ID_AUFGABE1_JULIA, &CChildView::OnAufgabe1Julia)
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_AUFGABE2_MANDELBROT, &CChildView::OnAufgabe2Mandelbrot)
	ON_COMMAND(ID_VEKTOREN_QUADRAT, &CChildView::OnVektorenQuadrat)
	ON_COMMAND(ID_VEKTOREN_QUADRAT2, &CChildView::OnVektorenQuadrat2)
	ON_COMMAND(ID_VEKTOREN_QUADTRATROT, &CChildView::OnVektorenQuadtratrot)
	ON_COMMAND(ID_VEKTOREN_WUERFEL1, &CChildView::OnVektorenWuerfel1)
	ON_COMMAND(ID_VEKTOREN_WUERFEL2, &CChildView::OnVektorenWuerfel2)
	ON_COMMAND(ID_VEKTOREN_WUERFEL3, &CChildView::OnVektorenWuerfel3)
	ON_COMMAND(ID_OPENGL_EINHEITSW, &CChildView::OnOpenglEinheitsw)
	ON_COMMAND(ID_OPENGL_STACHEL, &CChildView::OnOpenglStachel)
END_MESSAGE_MAP()



// CChildView-Meldungshandler

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // Gerätekontext zum Zeichnen

	dc.BitBlt(0, 0, m_width, m_height, &m_DC, 0, 0, SRCCOPY);
	
	// TODO: Fügen Sie hier Ihren Meldungshandlercode ein.
	
	// Rufen Sie nicht CWnd::OnPaint() zum Zeichnen von Nachrichten auf
}



void CChildView::OnAufgabe1Diagonale()
{
	CRect rp, rc;

	GetClientRect(&rc);
	GetParent()->GetWindowRect(&rp);

	int diffx = rp.Width() - rc.Width();
	int diffy = rp.Height() - rc.Height();


	GetParent()->SetWindowPos(NULL, 50, 30, 700+diffx, 700+diffy, SWP_SHOWWINDOW);
	UpdateWindow();
	// TODO: Fügen Sie hier Ihren Befehlshandlercode ein.
	CDC* pDC = GetDC();
	for(int ii=0; ii < 700; ii++)
		pDC->SetPixel(ii, ii, RGB(255, 0, 0));
}

bool Julia = false;

void CChildView::OnAufgabe1Julia()
{
	CRect rp, rc;

	Julia = true;

	m_minx = -1.6;
	m_deltax = 3.2;
	m_miny = -1.6;
	m_deltay = 3.2;

	GetClientRect(&rc);
	GetParent()->GetWindowRect(&rp);

	int diffx = rp.Width() - rc.Width();
	int diffy = rp.Height() - rc.Height();


	GetParent()->SetWindowPos(NULL, 50, 30, 700 + diffx, 700 + diffy, SWP_SHOWWINDOW);
	UpdateWindow();

	JuliaMalen();

}
#define NMAX 255
void CChildView::JuliaMalen()
{
	CDC* pDC = GetDC();
	for (int xi = 0; xi < 700; xi++)
	{
		for (int yi = 0; yi < 700; yi++)
		{
			double xd = m_minx + xi * m_deltax / 700.;
			double yd = m_miny + yi * m_deltay / 700.;
			int k;
			double a = xd, b = yd, an = a, bn = b;
			for (k = 0; k < NMAX; k++)
			{
				an = a*a - b*b - 0.75;
				bn = 2 * a*b + 0.06;
				if (an * an + bn * bn > 4)
					break;
				a = an;
				b = bn;
			}
			if (k < NMAX)
			{
				pDC->SetPixel(xi, yi, RGB(k%255, 0, 0));
				if (k < 25)
					pDC->SetPixel(xi, yi, RGB(0, 0, 0));
			}
			else
				pDC->SetPixel(xi, yi, RGB(0, 0, 0));
		}
	}
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Fügen Sie hier Ihren Meldungshandlercode ein, und/oder benutzen Sie den Standard.

	CWnd::OnLButtonUp(nFlags, point);
	double xd = m_minx + point.x * m_deltax / 700.;
	double yd = m_miny + point.y * m_deltay / 700.;

	m_deltax = m_deltax / 2;
	m_deltay = m_deltay / 2;

	m_minx = xd - m_deltax / 2;
	m_miny = yd - m_deltay / 2;

	if (Julia == true)
		JuliaMalen();
	else
		BrotMalen();
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Fügen Sie hier Ihren Meldungshandlercode ein, und/oder benutzen Sie den Standard.

	CWnd::OnRButtonUp(nFlags, point);
	double xd = m_minx + point.x * m_deltax / 700.;
	double yd = m_miny + point.y * m_deltay / 700.;

	m_deltax = m_deltax * 2;
	m_deltay = m_deltay * 2;

	m_minx = xd - m_deltax / 2;
	m_miny = yd - m_deltay / 2;

	if (Julia == true)
		JuliaMalen();
	else
		BrotMalen();
}


void CChildView::OnAufgabe2Mandelbrot()
{
	CRect rp, rc;

	Julia = false;

	m_minx = -2.0;
	m_deltax = 2.5;
	m_miny = -1.25;
	m_deltay = 2.5;

	GetClientRect(&rc);
	GetParent()->GetWindowRect(&rp);

	int diffx = rp.Width() - rc.Width();
	int diffy = rp.Height() - rc.Height();


	GetParent()->SetWindowPos(NULL, 50, 30, 700 + diffx, 700 + diffy, SWP_SHOWWINDOW);
	UpdateWindow();

	BrotMalen();
}

void CChildView::BrotMalen()
{
	CDC* pDC = GetDC();
	for (int xi = 0; xi < 700; xi++)
	{
		for (int yi = 0; yi < 700; yi++)
		{
			double xd = m_minx + xi * m_deltax / 700.;
			double yd = m_miny + yi * m_deltay / 700.;
			int k;
			double a = 0, b = 0, an = a, bn = b;
			for (k = 0; k < NMAX; k++)
			{
				an = a * a - b * b + xd;
				bn = 2 * a * b + yd;
				if (an * an + bn * bn > 4)
					break;
				a = an;
				b = bn;
			}
			if (k < NMAX)
			{
				pDC->SetPixel(xi, yi, RGB(6*k % 255, 0, 0));
			}
			else
				pDC->SetPixel(xi, yi, RGB(0, 0, 0));
		}
	}
}


void CChildView::OnVektorenQuadrat()
{
	// TODO: Fügen Sie hier Ihren Befehlshandlercode ein.
	Vector2 Quadrat[4];
	Quadrat[0] = Vector2(50, 50);
	Quadrat[1] = Vector2(150, 50);
	Quadrat[2] = Vector2(150, 150);
	Quadrat[3] = Vector2(50, 150);

	CDC* pDC = GetDC();
	//Qadrat malen
	pDC->MoveTo(Quadrat[3].vek[0], Quadrat[3].vek[1]);
	for (int ii = 0; ii < 4; ii++)
		pDC->LineTo(Quadrat[ii].vek[0], Quadrat[ii].vek[1]);

	Matrix2 TransMat;
	TransMat.setTrans(-100, -100);
	// Quadrat verschieben in den Ursprung

	Matrix2 RotMat;
	RotMat.setRot(10);
	//Quadrat rotieren

	Matrix2 TransMatR;
	TransMatR.setTrans(100, 100);
	// Quadrat verschieben in die Szene

	Matrix2 TMat = TransMatR * RotMat * TransMat;
	for (int ii = 0; ii < 4; ii++)
	{
		Quadrat[ii] = TMat * Quadrat[ii];
	}
	pDC->MoveTo(Quadrat[3].vek[0], Quadrat[3].vek[1]);
	for (int ii = 0; ii < 4; ii++)
		pDC->LineTo(Quadrat[ii].vek[0], Quadrat[ii].vek[1]);
}



void CChildView::OnVektorenQuadrat2()
{
	// TODO: Fügen Sie hier Ihren Befehlshandlercode ein.
	Vector2 Quadrat[4];
	Quadrat[0] = Vector2(50, 50);
	Quadrat[1] = Vector2(150, 50);
	Quadrat[2] = Vector2(150, 150);
	Quadrat[3] = Vector2(50, 150);

	CRect rect;
	GetClientRect(&rect);
	m_width = rect.Width();
	m_height = rect.Height();

	CDC* pDC = GetDC();
	//Qadrat malen
	CBitmap bm;
	bm.CreateCompatibleBitmap(pDC, m_width, m_height);

	m_DC.CreateCompatibleDC(pDC);
	m_DC.SelectObject(&bm);



	Matrix2 TM;
	TM.setTrans(1, 1);
	for (int anim = 0; anim < 200; anim++)
	{
		m_DC.FillSolidRect(rect, RGB(255, 255, 0));
		for (int ii = 0; ii < 4; ii++)
		{
			Quadrat[ii] = TM * Quadrat[ii];
		}
		m_DC.MoveTo(Quadrat[3].vek[0], Quadrat[3].vek[1]);
		for (int ii = 0; ii < 4; ii++)
			m_DC.LineTo(Quadrat[ii].vek[0], Quadrat[ii].vek[1]);
		pDC->BitBlt(0,0, m_width, m_height, &m_DC, 0,0, SRCCOPY);
		Sleep(20);
		if (GetAsyncKeyState(VK_ESCAPE))
			break;
	}
}


void CChildView::OnVektorenQuadtratrot()
{
	// TODO: Fügen Sie hier Ihren Befehlshandlercode ein.
	Vector2 Quadrat[4];
	Quadrat[0] = Vector2(550, 250);
	Quadrat[1] = Vector2(650, 250);
	Quadrat[2] = Vector2(650, 350);
	Quadrat[3] = Vector2(550, 350);

	CRect rect;
	GetClientRect(&rect);
	m_width = rect.Width();
	m_height = rect.Height();

	CDC* pDC = GetDC();
	//Qadrat malen
	CBitmap bm;
	bm.CreateCompatibleBitmap(pDC, m_width, m_height);

	m_DC.CreateCompatibleDC(pDC);
	m_DC.SelectObject(&bm);

	Matrix2 TransMat;
	TransMat.setTrans(-600, -300);
	// Quadrat verschieben in den Ursprung

	Matrix2 RotMat;
	RotMat.setRot(0.1);
	//Quadrat rotieren

	Matrix2 TransMatR;
	TransMatR.setTrans(600, 300);
	// Quadrat verschieben in die Szene

	Matrix2 TM = TransMatR * RotMat * TransMat;
	for (int anim = 0; anim < 200; anim++)
	{
		m_DC.FillSolidRect(rect, RGB(255, 255, 255));
		for (int ii = 0; ii < 4; ii++)
		{
			Quadrat[ii] = TM * Quadrat[ii];
		}
		m_DC.MoveTo(Quadrat[3].vek[0], Quadrat[3].vek[1]);
		for (int ii = 0; ii < 4; ii++)
			m_DC.LineTo(Quadrat[ii].vek[0], Quadrat[ii].vek[1]);
		pDC->BitBlt(0, 0, m_width, m_height, &m_DC, 0, 0, SRCCOPY);
		Sleep(500);
		if (GetAsyncKeyState(VK_ESCAPE))
			break;
	}
}


void CChildView::OnVektorenWuerfel1()
{
	// TODO: Fügen Sie hier Ihren Befehlshandlercode ein.
	Vector3 Cube[8];

	Cube[0] = Vector3(50, 50, -50);
	Cube[1] = Vector3(150, 50, -50);
	Cube[2] = Vector3(150, 150, -50);
	Cube[3] = Vector3(50, 150, -50);

	Cube[4] = Vector3(50, 50, 50);
	Cube[5] = Vector3(150, 50, 50);
	Cube[6] = Vector3(150, 150, 50);
	Cube[7] = Vector3(50, 150, 50);

	CRect rect;
	GetClientRect(&rect);
	m_width = rect.Width();
	m_height = rect.Height();

	CDC* pDC = GetDC();
	CBitmap bm;
	bm.CreateCompatibleBitmap(pDC, m_width, m_height);

	m_DC.DeleteDC();
	m_DC.CreateCompatibleDC(pDC);
	m_DC.SelectObject(&bm);

	Matrix3 T, TR, RZ, RX;
	T.setTrans(-100, -100, 0);
	TR.setTrans(100, 100, 0);
	RZ.setRotZ(20);
	RX.setRotX(30);

	for (int i = 0; i < 8; i++)
	{
		Cube[i] = TR*RX*RZ*T*Cube[i];
	}

	m_DC.FillSolidRect(rect, RGB(255, 255, 255));
	//Wuerfel malen
	//hinten
	m_DC.MoveTo(Cube[3].vek[0], Cube[3].vek[1]);
	for (int i = 0; i < 4; i++)
	{
		m_DC.LineTo(Cube[i].vek[0], Cube[i].vek[1]);
	}
	//vorne
	m_DC.MoveTo(Cube[7].vek[0], Cube[7].vek[1]);
	for (int i = 4; i < 8; i++)
	{
		m_DC.LineTo(Cube[i].vek[0], Cube[i].vek[1]);
	}
	//hinten nach vorne

	for (int i = 0; i < 4; i++)
	{
		m_DC.MoveTo(Cube[i].vek[0], Cube[i].vek[1]);
		m_DC.LineTo(Cube[i+4].vek[0], Cube[i+4].vek[1]);
	}

	pDC->BitBlt(0, 0, m_width, m_height, &m_DC, 0, 0, SRCCOPY);
	ReleaseDC(pDC);
}


void CChildView::OnVektorenWuerfel2()
{
	// TODO: Fügen Sie hier Ihren Befehlshandlercode ein.
	Vector3 Cube[8];

	Cube[0] = Vector3(50, 50, -50);
	Cube[1] = Vector3(150, 50, -50);
	Cube[2] = Vector3(150, 150, -50);
	Cube[3] = Vector3(50, 150, -50);

	Cube[4] = Vector3(50, 50, 50);
	Cube[5] = Vector3(150, 50, 50);
	Cube[6] = Vector3(150, 150, 50);
	Cube[7] = Vector3(50, 150, 50);

	CRect rect;
	GetClientRect(&rect);
	m_width = rect.Width();
	m_height = rect.Height();

	CDC* pDC = GetDC();
	CBitmap bm;
	bm.CreateCompatibleBitmap(pDC, m_width, m_height);

	m_DC.DeleteDC();
	m_DC.CreateCompatibleDC(pDC);
	m_DC.SelectObject(&bm);

	Matrix3 T, TR, RZ, RX, Persp;

	T.setTrans(-100, -100, 0);
	TR.setTrans(100, 100, 0);
	RZ.setRotZ(20);
	RX.setRotX(30);

	Persp.setPersp(200);

	for (int i = 0; i < 8; i++)
	{
		Cube[i] = Persp * RX * RZ * T * Cube[i];
		double scalar = Cube[i].getHom();
		Cube[i] = Cube[i] * (1. / scalar);
		Cube[i] = TR * Cube[i];
	}

	m_DC.FillSolidRect(rect, RGB(255, 255, 255));
	//Wuerfel malen
	//hinten
	m_DC.MoveTo(Cube[3].vek[0], Cube[3].vek[1]);
	for (int i = 0; i < 4; i++)
	{
		m_DC.LineTo(Cube[i].vek[0], Cube[i].vek[1]);
	}
	//vorne
	m_DC.MoveTo(Cube[7].vek[0], Cube[7].vek[1]);
	for (int i = 4; i < 8; i++)
	{
		m_DC.LineTo(Cube[i].vek[0], Cube[i].vek[1]);
	}
	//hinten nach vorne

	for (int i = 0; i < 4; i++)
	{
		m_DC.MoveTo(Cube[i].vek[0], Cube[i].vek[1]);
		m_DC.LineTo(Cube[i + 4].vek[0], Cube[i + 4].vek[1]);
	}
	pDC->BitBlt(0, 0, m_width, m_height, &m_DC, 0, 0, SRCCOPY);
	ReleaseDC(pDC);
}


void CChildView::OnVektorenWuerfel3()
{
	// TODO: Fügen Sie hier Ihren Befehlshandlercode ein.
	Vector3 Cube[8];

	Cube[0] = Vector3(50, 50, -50);
	Cube[1] = Vector3(150, 50, -50);
	Cube[2] = Vector3(150, 150, -50);
	Cube[3] = Vector3(50, 150, -50);

	Cube[4] = Vector3(50, 50, 50);
	Cube[5] = Vector3(150, 50, 50);
	Cube[6] = Vector3(150, 150, 50);
	Cube[7] = Vector3(50, 150, 50);

	CRect rect;
	GetClientRect(&rect);
	m_width = rect.Width();
	m_height = rect.Height();

	CDC* pDC = GetDC();
	CBitmap bm;
	bm.CreateCompatibleBitmap(pDC, m_width, m_height);

	m_DC.DeleteDC();
	m_DC.CreateCompatibleDC(pDC);
	m_DC.SelectObject(&bm);

	Matrix3 T, TR, RZ, RX, Persp;
	T.setTrans(-100, -100, 0);
	TR.setTrans(100, 100, 0);
	RZ.setRotZ(0.1);
	RX.setRotX(0.1);

	for (int anim = 0; anim < 200; anim++)
	{
		m_DC.FillSolidRect(rect, RGB(255, 255, 255));
		for (int i = 0; i < 8; i++)
		{
			Cube[i] = TR * RX * RZ * T * Cube[i];
		}
		m_DC.MoveTo(Cube[3].vek[0], Cube[3].vek[1]);
		for (int i = 0; i < 4; i++)
		{
			m_DC.LineTo(Cube[i].vek[0], Cube[i].vek[1]);
		}
		//vorne
		m_DC.MoveTo(Cube[7].vek[0], Cube[7].vek[1]);
		for (int i = 4; i < 8; i++)
		{
			m_DC.LineTo(Cube[i].vek[0], Cube[i].vek[1]);
		}
		//hinten nach vorne

		for (int i = 0; i < 4; i++)
		{
			m_DC.MoveTo(Cube[i].vek[0], Cube[i].vek[1]);
			m_DC.LineTo(Cube[i + 4].vek[0], Cube[i + 4].vek[1]);
		}
		pDC->BitBlt(0, 0, m_width, m_height, &m_DC, 0, 0, SRCCOPY);
		Sleep(500);
		if (GetAsyncKeyState(VK_ESCAPE))
			break;
	}
}




void CChildView::GLInit(int Breite, int Hoehe, int Modus)
{
	static HDC         hdc;
	static HGLRC       hglrc;
	int         iPixelFormat;
	HWND hwnd = GetSafeHwnd();


	static PIXELFORMATDESCRIPTOR pfd =	//pfd legt das Aussehen der Szene fest
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,						//Versionsnummer
		PFD_DRAW_TO_WINDOW |	//pfd muss Windows unterstьtzen
		PFD_SUPPORT_OPENGL |	//pfd muss OpenGL unterstьtzen
		PFD_DOUBLEBUFFER ,		//Doppelpuffer wird unterstьtzt
		PFD_TYPE_RGBA,			//RGBA-Farbformat auswдhlen
		32,						//Bit-Farbtiefe
		0, 0, 0, 0, 0, 0,		//Farbbits werden ignoriert
		0,						//kein Alphapuffer
		0,						//Schiebebit ignoriert
		0,						//kein Ansammlungspuffer
		0, 0, 0, 0,				//Ansammlungsbits werden ignoriert
		16,						//16bit Z-Puffer (Tiefenpuffer)
		16,						//Masken-Puffer
		0,						//keinen Hilfs-Puffer
		PFD_MAIN_PLANE,			//Festlegung der Zeichenebene (Hauptebene)
		0,						//reserviert
		0, 0, 0					//Ebenenmasken werden ignoriert 
	};
	CDC* pDC = GetDC();
	CRect gesamt, client;
	GetWindowRect(&gesamt);
	GetClientRect(&client);
	int diff_x = gesamt.Width() - client.Width();
	int diff_y = gesamt.Height() - client.Height();
	m_height = Hoehe;
	m_width = Breite;

	switch (Modus)
	{
	case 1:  // Modus 1 -> Initialisierung

		// ---------- FenstergrцЯe
		GetParent()->SetWindowPos(&wndTop,
			50, 50, m_height + diff_x, m_width + diff_y, 0);
		//		GetParent()->ShowWindow(SW_NORMAL);
		GetParent()->RedrawWindow();
		// ------ Device Context
		hdc = pDC->GetSafeHdc();

		// ------ Pixelformat einstellen (OpenGL-fдhig)
		iPixelFormat = ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, iPixelFormat, &pfd);

		// ----  Rendering-Context erstellen und zuweisen
		hglrc = wglCreateContext(hdc);
		if (hglrc == NULL) { SetWindowText(CString("Fehler beim RC !")); Sleep(2000); }
		wglMakeCurrent(hdc, hglrc);
		break;

	case 0:  // Modus 0 -> Beenden
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hglrc);

		ReleaseDC(pDC);
		break;
	}
	return;

}

void CChildView::Bunter_Einheitswuerfel()
{
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);          // grьn bei z = -0.5
	glNormal3f(0, 0, -1);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);

	glColor3f(1, 0, 0);        // rot bei z = 0.5
	glNormal3f(0, 0, 1);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);

	glColor3f(1, 0.75, 0.25);  // orange bei y = -0.5
	glNormal3f(0, -1, 0);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);

	glColor3f(0, 0, 1);          // blau bei y = 0.5
	glNormal3f(0, 1, 0);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);

	glColor3f(1, 0, 1);          // lila bei x =  0.5
	glNormal3f(-1, 0, 0);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);

	glColor3f(1, 1, 0);          // gelb bei x = -0.5
	glNormal3f(1, 0, 0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();
}

void CChildView::Achsenkreuz(float l)
{
	GLfloat Pfeil = (float)0.05;

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(-l, 0, 0);  // Achsen
	glVertex3f(l, 0, 0);

	glVertex3f(0, -l, 0);
	glVertex3f(0, l, 0);

	glVertex3f(0, 0, -l);
	glVertex3f(0, 0, l);

	glVertex3f(l, 0, 0);  // Pfeile
	glVertex3f(l - Pfeil, Pfeil, 0);

	glVertex3f(l, 0, 0);
	glVertex3f(l - Pfeil, -Pfeil, 0);

	glVertex3f(0, l, 0);  // Pfeile
	glVertex3f(0, l - Pfeil, Pfeil);

	glVertex3f(0, l, 0);
	glVertex3f(0, l - Pfeil, -Pfeil);

	glVertex3f(0, 0, l);  // Pfeile
	glVertex3f(Pfeil, 0, l - Pfeil);

	glVertex3f(0, 0, l);
	glVertex3f(-Pfeil, 0, l - Pfeil);
	glEnd();
}

void CChildView::OnOpenglEinheitsw()
{
	// TODO: Fügen Sie hier Ihren Befehlshandlercode ein.
	GLInit(700, 700, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glFrustum(-1, 1, -1, 1, 1.5, 6);
	gluLookAt(1, 1, 3, 0, 0, 0, 0, 1, 0);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.5, 0.5, 0.5, 0.0);

	for (int anim = 0; anim < 200; anim++)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		Achsenkreuz(1.2);
		Bunter_Einheitswuerfel();

		glRotated(anim, 1, 0, 0);
		glTranslatef(0.75, 0, 0);
		glScaled(0.5, 0.5, 0.5);
		Bunter_Einheitswuerfel();
		glLoadIdentity();
		
		glRotated(anim, 0, 1, 0);
		glTranslatef(0, 0.75, 0);
		glScaled(0.5, 0.5, 0.5);
		Bunter_Einheitswuerfel();
		glLoadIdentity();

		glRotated(anim, 0, 0, 1);
		glTranslatef(0, 0, 0.75);
		glScaled(0.5, 0.5, 0.5);
		Bunter_Einheitswuerfel();
		glLoadIdentity();

		SwapBuffers(wglGetCurrentDC());
		Sleep(100);
		if (GetAsyncKeyState(VK_ESCAPE))
			break;
	}
	GLInit(0, 0, 0);
}

#define MAX_TEILCHEN 100000
void CChildView::OnOpenglStachel()
{
	// TODO: Fügen Sie hier Ihren Befehlshandlercode ein.
	GLInit(700, 700, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glFrustum(-1, 1, -1, 1, 1.5, 6);
	gluLookAt(1, 1, 3, 0, 0, 0, 0, 1, 0);

//	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	//Beleuchtung
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat params[4] = { 1.0, 1.5, 2.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, params);
	//Material
	// Gold
	GLfloat  GAmbient[4] = { 0.25f, 0.20f, 0.07f, 1.0 };
	GLfloat  GDiffuse[4] = { 0.75f, 0.61f, 0.23f, 1.0 };
	GLfloat  GSpecular[4] = { 0.63f, 0.56f, 0.37f, 1.0 };
	GLfloat  GShininess = 51;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, GAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, GDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, GSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GShininess);

	long t2, t1 = clock();
	float fps = 0.0;
	int tanz = 2000;
	int anim = 0;

	while (tanz < MAX_TEILCHEN)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < tanz; i++)
		{
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glRotated(rand() % 360, 0, 0, 1);
			glRotated(rand() % 360, 0, 1, 0);
			glTranslatef(0.0, 0, 0.8);

			glScaled(0.1, 0.1, 0.1);
			glNormal3f(0.0, 0.0, 1.0);
			glBegin(GL_TRIANGLES);
			glVertex3f(-0.5, -0.5, 0);
			glVertex3f(0.5, -0.5, 0);
			glVertex3f(-0.5, 0.5, 0);
			glEnd();
		}
		SwapBuffers(wglGetCurrentDC());
		if (GetAsyncKeyState(VK_ESCAPE))
			break;
		anim++;
		if (anim % 20 == 0)
		{
			t2 = clock();
			if (t2 - t1 != 0)
				fps = 20. / (t2 - t1) * CLOCKS_PER_SEC;
			t1 = t2;
			CString txt;
			txt.Format("Teilchen: %d fps: %5.2f", tanz, fps);
			GetParent()->SetWindowText(txt);
			tanz += 1000;
		}
	}
	

	GLInit(0, 0, 0);
}
