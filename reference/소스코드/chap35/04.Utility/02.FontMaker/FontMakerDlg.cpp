/**
 *  file    FontMakerDlg.cpp
 *  date    2009/09/09
 *  author  kkamagui 
 *          Copyright(c)2008 All rights reserved by kkamagui
 *  brief   占쏙옙트占쏙옙 占쏙옙占쏙옙占싹댐옙 Font Maker占쏙옙 占쌕쏙옙 占쌀쏙옙 占쏙옙占쏙옙
 */
// FontMakerDlg.cpp : implementation file
//

#include "StdAfx.h"
#include "FontMaker.h"
#include "FontMakerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontMakerDlg dialog

CFontMakerDlg::CFontMakerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFontMakerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFontMakerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFontMakerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFontMakerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFontMakerDlg, CDialog)
	//{{AFX_MSG_MAP(CFontMakerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FONTSELECT, OnButtonFontselect)
	ON_BN_CLICKED(IDC_BUTTON_FONTMAKE, OnButtonFontmake)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontMakerDlg message handlers

void func1()
{

}

BOOL CFontMakerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_iFontSize = 0;

	func1();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFontMakerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFontMakerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	// 占쏙옙占쏙옙占쎌를 占쌓몌옙 占쏙옙 占쏙옙占쏙옙占쌘울옙 占싼깍옙占쏙옙 占쏙옙占쏙옙臼占?占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙
	else
	{
        CPaintDC dc( this );

        CString clsData;
        SIZE stHangulSize;
		SIZE stEnglishSize;
		CPen clPen( PS_DOT, 1, RGB( 255, 0, 0 ) );
		CPen* pclOldPen;

		// 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占싹곤옙 占쏙옙占쏙옙占싹울옙 占쏙옙占쌘몌옙 표占쏙옙占쏙옙 占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占?占쏙옙占쏙옙占쏙옙 占십듸옙占쏙옙 占쏙옙
		dc.SetBkMode( TRANSPARENT );

		// 占쏙옙占쏙옙占쏙옙 占쏙옙트 占쏙옙占쏙옙
        dc.SelectObject( &m_clFont );

		// 占쏙옙占쏙옙 占쏙옙占쏙옙
		pclOldPen = dc.SelectObject( &clPen );

		// 占쏙옙트 크占쏙옙 占쏙옙占쏙옙
		GetTextExtentPoint32( dc.m_hDC, "A", 1, &stEnglishSize );
        GetTextExtentPoint32( dc.m_hDC, "占쏙옙", 2, &stHangulSize );

		// 占싣뤄옙 占쏙옙 占쏙옙占쌔쇽옙 占쏙옙占?
		dc.MoveTo( 0, 5 );
		dc.LineTo( 1000, 5 );
		dc.MoveTo( 0, 5 + stEnglishSize.cy - 1 );
		dc.LineTo( 1000, 5 + stEnglishSize.cy - 1 );
		// 占쏙옙占쏙옙占쏙옙 占쏙옙占?
        dc.TextOut( 0, 5, "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ" );
		
		// 占싣뤄옙 占쏙옙 占쏙옙占쌔쇽옙 占쏙옙占?
		dc.MoveTo( 0, 30 );
		dc.LineTo( 1000, 30 );
		dc.MoveTo( 0, 30 + stHangulSize.cy - 1 );
		dc.LineTo( 1000, 30 + stHangulSize.cy - 1 );
		// 占싼깍옙 占쏙옙占?
        dc.TextOut( 0, 30, "占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쌕라마바삼옙占쏙옙占쏙옙占식ヅ몌옙占쏙옙占? );

		// 占쏙옙트占쏙옙 크占썩를 占쏙옙占?
        clsData.Format( "English Font Pixel %dx%d, Hangul Font Pixel %dx%d", 
			stEnglishSize.cx, stEnglishSize.cy, stHangulSize.cx, stHangulSize.cy );
        dc.TextOut( 0, 60, clsData );

		// Pen占쏙옙 占쏙옙占쏙옙
		dc.SelectObject( pclOldPen );
    }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFontMakerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFontMakerDlg::OnButtonFontselect() 
{
    CFontDialog dlg;
    LOGFONT stLogFont;
    CPaintDC dc( this );

    if( dlg.DoModal() != IDOK )
    {
        return ;
    }

    // 占쏙옙占시듸옙 占쏙옙트占쏙옙 占쏙옙환
    dlg.GetCurrentFont( &stLogFont );

	// 占쏙옙트 占쏙옙占쏙옙占쏘가 16 占싱몌옙 160占쏙옙占쏙옙 占쏙옙占쏙옙
	stLogFont.lfHeight = dlg.GetSize() / 10;
	if( stLogFont.lfHeight > 16 )
	{
		AfxMessageBox( "占쏙옙트 크占쏙옙占?16 크占쏙옙 占싱삼옙 占쏙옙占쏙옙占쏙옙 占쏙옙 占쏙옙占쏙옙占싹댐옙" );
		return ;
	}

	m_iFontSize = stLogFont.lfHeight;

    m_clFont.DeleteObject();
    if( m_clFont.CreateFontIndirect( &stLogFont ) == FALSE )
    {
        TRACE( "占쏙옙트 占쏙옙占쏙옙 占쏙옙占쏙옙\n" );
    }

    // 占쏙옙占쏙옙占쎌를 占쏙옙占쏙옙 占쌓몌옙
    Invalidate( TRUE );
}

/**
    占쏙옙占쏙옙占쌘울옙 占싹쇽옙占쏙옙 占싼깍옙占쏙옙 占쏙옙占?占쏙옙 占쏙옙占쏙옙臼占?占쏙옙트 占쏙옙占쏙옙 占쏙옙占쏙옙 
*/
void CFontMakerDlg::OnButtonFontmake() 
{
    CPaintDC dc( this );
    CDC clTempDc;
    CBitmap clBitmap;

    // DC占쏙옙 占쏙옙占쏙옙占쌔쇽옙 bitmap占쏙옙 占쏙옙占쏙옙
    clTempDc.CreateCompatibleDC( &dc );
    clBitmap.CreateCompatibleBitmap( &clTempDc, 100, 100 );
    clTempDc.SelectObject( &clBitmap );
    clTempDc.SelectObject( &m_clFont );
    
    // 占싼깍옙 占쏙옙트占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙
    SaveHangulFont( &clTempDc );
    // 占쏙옙占쏙옙 占쏙옙트占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙
    SaveEnglishFont( &clTempDc );

    AfxMessageBox( "占쏙옙트 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙占싹댐옙." );
}

/**
    占싼깍옙 占쏙옙트 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙
*/
void CFontMakerDlg::SaveHangulFont( CDC* pclTempDC )
{
    int i;
    int j;
    int iCount;
    char vcBuffer[ 2 ];

    // 占쏙옙트 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙
    if( CreateHangulFontFile() == FALSE )
    {
        return ;
    }

	//=========================================================================
	// 占쏙옙트 占쏙옙占쏙옙占싶몌옙 占쏙옙占쏙옙占쏙옙 占쏙옙占싹울옙 占쏙옙占쏙옙
	//=========================================================================
    //占쏙옙占쏙옙/占쏙옙占쏙옙 占쏙옙占쏙옙 0xA4A1 ~ 0xA4D3 占쏙옙占쏙옙
    vcBuffer[ 0 ] = ( char )0xA4;
    for( i = 0xA1 ; i <= 0xD3 ; i++ )
    {
        vcBuffer[ 1 ] = i;
        pclTempDC->TextOut( 0, 0, vcBuffer, 2 );

        // 占쏙옙占?占싫쇽옙占쏙옙 占쏙옙占쌔쇽옙 占쏙옙트占쏙옙占쏙옙크占쏙옙 占쏙옙占쏙옙
        SaveBitMask( pclTempDC, TRUE );
    }

    iCount = 0;
    // 占싹쇽옙占쏙옙 占싼깍옙 0xB0A1占쏙옙占쏙옙 0xC8FE 占쏙옙占쏙옙
    for( j = 0xB0 ; j <= 0xC8 ; j++ )
    {
        vcBuffer[ 0 ] = j;
        for( i = 0xA1 ; i <= 0xFE ; i++  )
        {
            vcBuffer[ 1 ] = i;
            pclTempDC->TextOut( 0, 0, vcBuffer, 2 );

            // 占쏙옙占?占싫쇽옙占쏙옙 占쏙옙占쌔쇽옙 占쏙옙트占쏙옙占쏙옙크占쏙옙 占쏙옙占쏙옙
            SaveBitMask( pclTempDC, TRUE );
            iCount++;
        }
    }

    TRACE( "Total Count = %d\n", iCount );

    // 占쌘뤄옙 3칸 占싱듸옙占싹울옙 ,\r\n占쏙옙 占쏙옙占쏙옙
    m_clFile.Seek( -3, SEEK_CUR );
    WriteFontData( "};\r\n" );
    CloseFontFile();
}

/**
    占쏙옙占쏙옙 占쏙옙트 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙
*/
void CFontMakerDlg::SaveEnglishFont( CDC* pclTempDC )
{
    int i;
    int iCount;
    char cBuffer;

	//=========================================================================
	// 占쏙옙트 占쏙옙占쏙옙占싶몌옙 占쏙옙占쏙옙占쏙옙 占쏙옙占싹울옙 占쏙옙占쏙옙
	//=========================================================================
    // 占쏙옙트 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙
    if( CreateEnglishFontFile() == FALSE )
    {
        return ;
    }

    iCount = 0;
	// 0~255 占쏙옙占쏙옙 占쏙옙占쏙옙
    for( i = 0 ; i <= 0xFF ; i++ )
    {
        cBuffer = i;
		pclTempDC->FillSolidRect( 0, 0, 20, 20, RGB( 255, 255, 255 ) );
        pclTempDC->TextOut( 0, 0, &cBuffer, 1 );

        // 占쏙옙占?占싫쇽옙占쏙옙 占쏙옙占쌔쇽옙 占쏙옙트占쏙옙占쏙옙크占쏙옙 占쏙옙占쏙옙
        SaveBitMask( pclTempDC, FALSE );
        iCount++;
    }

    TRACE( "Total Count = %d\n", iCount );

    // 占쌘뤄옙 3칸 占싱듸옙占싹울옙 ,\r\n占쏙옙 占쏙옙占쏙옙
    m_clFile.Seek( -3, SEEK_CUR );
    WriteFontData( "};\r\n" );
    CloseFontFile();
}

/**
    占쏙옙트 占쏙옙占쏙옙크占쏙옙 占쏙옙占쏙옙
*/
void CFontMakerDlg::SaveBitMask( CDC* clTempDc, BOOL bHangul )
{
    int i;
    int j;
    COLORREF stColor;
    unsigned short usBitMask;
	int iFontWidth;

	// 占싼깍옙占싱몌옙 占쏙옙트 占십븝옙 占쏙옙큼占쏙옙 占쏙옙占?占싯삼옙占싹곤옙 占쏙옙占쏙옙占쏙옙占싱몌옙 占십븝옙 占싼깍옙占쏙옙 占쏙옙占싱므뤄옙
	// 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙
	if( bHangul == TRUE )
	{
		iFontWidth = m_iFontSize;
	}
	else
	{
		iFontWidth = m_iFontSize / 2;
	}

    // 占쏙옙트 占쏙옙트占쏙옙占쏙옙 占쏙옙占쏙옙占싹울옙 占쏙옙占싹울옙 占쏙옙占쏙옙
    for( j = 0 ; j < m_iFontSize ; j++ )
    {
        usBitMask = 0;
        for( i = 0 ; i < iFontWidth ; i++ )
        {
            stColor = clTempDc->GetPixel( i, j );
            if( stColor != 0xFFFFFF )
            {
                usBitMask |= ( 0x01 << ( iFontWidth - 1 - i ) );
            }
        }
        // BitMask占쏙옙 占쏙옙占쏙옙.
        WriteFontData( usBitMask, bHangul );
        WriteFontData( "," );
    }
    WriteFontData( "\r\n" );
}

/**
    占싼깍옙 占쏙옙트 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙
        占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙, C占쏙옙占?占썼열占쏙옙 占쏙옙占쏙옙占?占쌩곤옙
*/
BOOL CFontMakerDlg::CreateHangulFontFile()
{
    char* pcHeader = "// 占쌘몌옙 51占쏙옙 + 占싹쇽옙占쏙옙 2350占쏙옙 占쏙옙트 占쏙옙占쏙옙占쏙옙, %dx%d pixel \r\n"
        "unsigned short g_vusHangulFont[] = { \r\n";
    char vcBuffer[ 1024 ];

	sprintf( vcBuffer, pcHeader, m_iFontSize, m_iFontSize );
	// 占쏙옙占쏙옙 占쏙옙占쏙옙
    if( m_clFile.Open( "HangulFont.c", CFile::modeCreate | 
        CFile::modeReadWrite ) == FALSE )
    {
        AfxMessageBox( "占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쌩쏙옙占싹댐옙." );
        return FALSE;
    }
    m_clFile.Write( vcBuffer, strlen( vcBuffer ) );
    return TRUE;
}

/**
    占쏙옙占쏙옙 占쏙옙트 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙
        占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙, C占쏙옙占?占썼열占쏙옙 占쏙옙占쏙옙占?占쌩곤옙
*/
BOOL CFontMakerDlg::CreateEnglishFontFile()
{
    char* pcHeader = "// 占쏙옙占쏙옙占쏙옙 256占쏙옙 占쏙옙트 占쏙옙占쏙옙占쏙옙, %dx%d pixel \r\n"
        "unsigned char g_vucEnglishFont[] = { \r\n";
    char vcBuffer[ 1024 ];

	sprintf( vcBuffer, pcHeader, m_iFontSize / 2, m_iFontSize );
	// 占쏙옙占쏙옙 占쏙옙占쏙옙
    if( m_clFile.Open( "EnglishFont.c", CFile::modeCreate | 
        CFile::modeReadWrite ) == FALSE )
    {
        AfxMessageBox( "占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쌩쏙옙占싹댐옙." );
        return FALSE;
    }
    m_clFile.Write( vcBuffer, strlen( vcBuffer ) );
    return TRUE;
}


/**
    Font 占쏙옙占싹울옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙
*/
void CFontMakerDlg::WriteFontData( unsigned short usData, BOOL bHangul )
{
    char vcBuffer[ 20 ];

    // 占싼깍옙占쏙옙 占쏙옙占쏙옙 2byte占쏙옙 占쏙옙占쏙옙占?占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 1byte占쏙옙 占쏙옙占쏙옙
	if( bHangul == TRUE )
	{
		sprintf( vcBuffer, "0x%04X", usData );
	}
	else
	{
		sprintf( vcBuffer, "0x%02X", usData & 0xFF );
	}

    m_clFile.Write( vcBuffer, strlen( vcBuffer ) );
}

/**
    Font 占쏙옙占싹울옙 占쏙옙占쏙옙占싶몌옙 占쏙옙
*/
void CFontMakerDlg::WriteFontData( char* pcData )
{
    m_clFile.Write( pcData, strlen( pcData ) );
}

/**
    Font 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙
*/
void CFontMakerDlg::CloseFontFile()
{
    m_clFile.Close();
}
