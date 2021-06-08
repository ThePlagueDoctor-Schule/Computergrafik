
// Fraktale.h: Hauptheaderdatei für die Fraktale-Anwendung
//
#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"       // Hauptsymbole


// CFraktaleApp:
// Siehe Fraktale.cpp für die Implementierung dieser Klasse
//

class CFraktaleApp : public CWinApp
{
public:
	CFraktaleApp() noexcept;


// Überschreibungen
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementierung

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFraktaleApp theApp;
