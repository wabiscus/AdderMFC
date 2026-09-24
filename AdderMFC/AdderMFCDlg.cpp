
// AdderMFCDlg.cpp : fichier d'implémentation
//

#include "pch.h"
#include "framework.h"
#include "AdderMFC.h"
#include "AdderMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// boîte de dialogue CAboutDlg utilisée pour la boîte de dialogue 'À propos de' pour votre application

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

// Implémentation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// boîte de dialogue de CAdderMFCDlg


CAdderMFCDlg::CAdderMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDERMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAdderMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NBR1, m_editValeur1);
	DDX_Control(pDX, IDC_EDIT_NBR2, m_editValeur2);
	DDX_Control(pDX, IDC_STATIC_RESULT, m_staticResultat);
}

BEGIN_MESSAGE_MAP(CAdderMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_BUTTON_EFFACER, &CAdderMFCDlg::OnBnClickedButtonEffacer)
	ON_COMMAND(ID_TOOLS_CALCULER, &CAdderMFCDlg::OnToolsCalculer)
	ON_COMMAND(ID_CONTEXT_CALCULER, &CAdderMFCDlg::OnContextCalculer)
END_MESSAGE_MAP()


// gestionnaires de messages de CAdderMFCDlg

BOOL CAdderMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Ajouter l'élément de menu "À propos de..." au menu Système.

	// IDM_ABOUTBOX doit se trouver dans la plage des commandes système.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Définir l'icône de cette boîte de dialogue.  L'infrastructure effectue cela automatiquement
	//  lorsque la fenêtre principale de l'application n'est pas une boîte de dialogue
	SetIcon(m_hIcon, TRUE);			// Définir une grande icône
	SetIcon(m_hIcon, FALSE);		// Définir une petite icône

	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

void CAdderMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Si vous ajoutez un bouton Réduire à votre boîte de dialogue, vous devez utiliser le code ci-dessous
//  pour dessiner l'icône.  Pour les applications MFC utilisant le modèle Document/Vue,
//  cela est fait automatiquement par l'infrastructure.

void CAdderMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // contexte de périphérique pour la peinture

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrer l'icône dans le rectangle client
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dessiner l'icône
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Le système appelle cette fonction pour obtenir le curseur à afficher lorsque l'utilisateur fait glisser
//  la fenêtre réduite.
HCURSOR CAdderMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAdderMFCDlg::OnBnClickedButtonEffacer()
{
	// On retire le texte des champs de saisie et du résultat
	m_editValeur1.SetWindowText(_T(""));
	m_editValeur2.SetWindowText(_T(""));
	m_staticResultat.SetWindowText(_T(""));

	// On remet le focus sur le premier champ de saisie
	m_editValeur1.SetFocus();
}

void CAdderMFCDlg::Calculer()
{
	CString strValeur1, strValeur2;

	// On récupère les valeurs saisies dans les champs de saisie
	m_editValeur1.GetWindowText(strValeur1);
	m_editValeur2.GetWindowText(strValeur2);	

	// On supprime les espaces inutiles au début et à la fin des chaînes
	strValeur1.Trim();
	strValeur2.Trim();

	// On check si les deux valeurs ne sont pas vides
	if (strValeur1.IsEmpty() || strValeur2.IsEmpty())
	{
		AfxMessageBox(_T("Une des deux valeur est vide"), MB_ICONWARNING);
		return;
	}

	// On définit les pointeurs de fin pour la conversion des chaînes en nombres
	TCHAR* endPtr1 = NULL;
	TCHAR* endPtr2 = NULL;

	// On convertit les chaînes en nombres en double pour pouvoir effectuer l'addition
	double nombre1 = _tcstod(strValeur1, &endPtr1);
	double nombre2 = _tcstod(strValeur2, &endPtr2);

	// On vérifie si la conversion est valide pour les deux nombres
	if (endPtr1 == (LPCTSTR)strValeur1 || *endPtr1 != _T('\0'))
	{
		AfxMessageBox(_T("Le premier nombre n'est pas valide"), MB_ICONERROR);
		return;
	}

	if (endPtr2 == (LPCTSTR)strValeur2 || *endPtr2 != _T('\0'))
	{
		AfxMessageBox(_T("Le deuxième nombre n'est pas valide"), MB_ICONERROR);
		return;
	}

	// On effectue l'addition des deux nombres
	double resultat = nombre1 + nombre2;
	CString affichageResultat;

	// On affiche le résultat dans le contrôle statique
	affichageResultat.Format(_T("%g"), resultat);
	m_staticResultat.SetWindowText(affichageResultat);

	// On prépare le message de log pour l'écriture dans le fichier log.txt
	CString logMessage;
	logMessage.Format(_T("%s + %s = %s"), strValeur1, strValeur2, affichageResultat);

	EcrireLog(logMessage);
}

void CAdderMFCDlg::OnToolsCalculer()
{
	Calculer();
}

void CAdderMFCDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// On crée un menu contextuel à partir du menu de ressources
	CMenu menu;
	if (!menu.LoadMenu(IDR_MENU_CONTEXTUEL))
	{
		AfxMessageBox(_T("Impossible de charger le menu."));
		return;
	}

	// On récupère le sous-menu du menu contextuel
	CMenu* pContextMenu = menu.GetSubMenu(0);

	if (pContextMenu != nullptr)
	{
		// On affiche le menu contextuel à la position du clic droit
		pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

void CAdderMFCDlg::OnContextCalculer()
{
	Calculer();
}

void CAdderMFCDlg::EcrireLog(const CString& logMessage)
{	
	// On récupère le chemin du fichier exécutable de l'application
	TCHAR chemin[MAX_PATH];

	GetModuleFileName(NULL, chemin, MAX_PATH);

	CString fichierLog(chemin);

	// On récupère la position du dernier caractère '\' dans le chemin du fichier exécutable
	int position = fichierLog.ReverseFind(_T('\\'));

	if (position != -1)
	{
		fichierLog = fichierLog.Left(position + 1); // On garde le chemin jusqu'au dernier '\'
	}

	fichierLog += _T("calculs.log");

	CStdioFile fichier;

	// Si le fichier ne peut pas être ouvert, on quitte la fonction
	if (!fichier.Open(fichierLog, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText))
	{
		return;
	}

	fichier.SeekToEnd();

	// On récupère la date et l'heure actuelles pour les inclure dans le log
	CTime maintenant = CTime::GetCurrentTime();

	CString dateHeure = maintenant.Format(_T("%Y-%m-%d %H:%M:%S"));

	CString texte;

	texte.Format(_T("[%s] %s\r\n"), dateHeure, logMessage);

	fichier.WriteString(texte);	
	fichier.Close();
}