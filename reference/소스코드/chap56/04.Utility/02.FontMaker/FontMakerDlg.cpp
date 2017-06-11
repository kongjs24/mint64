/**
 *  file    FontMakerDlg.cpp
 *  date    2009/09/09
 *  author  kkamagui 
 *          Copyright(c)2008 All rights reserved by kkamagui
 *  brief   ��Ʈ�� �����ϴ� Font Maker�� �ٽ� �ҽ� ����
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
	// �����츦 �׸� �� �����ڿ� �ѱ��� ����Ͽ� ������ ������
	else
	{
        CPaintDC dc( this );

        CString clsData;
        SIZE stHangulSize;
		SIZE stEnglishSize;
		CPen clPen( PS_DOT, 1, RGB( 255, 0, 0 ) );
		CPen* pclOldPen;

		// ������ �����ϰ� �����Ͽ� ���ڸ� ǥ���� �� ������ ����� ������ �ʵ��� ��
		dc.SetBkMode( TRANSPARENT );

		// ������ ��Ʈ ����
        dc.SelectObject( &m_clFont );

		// ���� ����
		pclOldPen = dc.SelectObject( &clPen );

		// ��Ʈ ũ�� ����
		GetTextExtentPoint32( dc.m_hDC, "A", 1, &stEnglishSize );
        GetTextExtentPoint32( dc.m_hDC, "��", 2, &stHangulSize );

		// �Ʒ� �� ���ؼ� ���
		dc.MoveTo( 0, 5 );
		dc.LineTo( 1000, 5 );
		dc.MoveTo( 0, 5 + stEnglishSize.cy - 1 );
		dc.LineTo( 1000, 5 + stEnglishSize.cy - 1 );
		// ������ ���
        dc.TextOut( 0, 5, "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ" );
		
		// �Ʒ� �� ���ؼ� ���
		dc.MoveTo( 0, 30 );
		dc.LineTo( 1000, 30 );
		dc.MoveTo( 0, 30 + stHangulSize.cy - 1 );
		dc.LineTo( 1000, 30 + stHangulSize.cy - 1 );
		// �ѱ� ���
        dc.TextOut( 0, 30, "���������������������������� �����ٶ󸶹ٻ������īŸ����" );

		// ��Ʈ�� ũ�⸦ ���
        clsData.Format( "English Font Pixel %dx%d, Hangul Font Pixel %dx%d", 
			stEnglishSize.cx, stEnglishSize.cy, stHangulSize.cx, stHangulSize.cy );
        dc.TextOut( 0, 60, clsData );

		// Pen�� ����
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

    // ���õ� ��Ʈ�� ��ȯ
    dlg.GetCurrentFont( &stLogFont );

	// ��Ʈ ����� 16 �̸� 160���� ����
	stLogFont.lfHeight = dlg.GetSize() / 10;
	if( stLogFont.lfHeight > 16 )
	{
		AfxMessageBox( "��Ʈ ũ��� 16 ũ�� �̻� ������ �� �����ϴ�" );
		return ;
	}

	m_iFontSize = stLogFont.lfHeight;

    m_clFont.DeleteObject();
    if( m_clFont.CreateFontIndirect( &stLogFont ) == FALSE )
    {
        TRACE( "��Ʈ ���� ����\n" );
    }

    // �����츦 ���� �׸�
    Invalidate( TRUE );
}

/**
    �����ڿ� �ϼ��� �ѱ��� ��� �� ����Ͽ� ��Ʈ ���� ���� 
*/
void CFontMakerDlg::OnButtonFontmake() 
{
    CPaintDC dc( this );
    CDC clTempDc;
    CBitmap clBitmap;

    // DC�� �����ؼ� bitmap�� ����
    clTempDc.CreateCompatibleDC( &dc );
    clBitmap.CreateCompatibleBitmap( &clTempDc, 100, 100 );
    clTempDc.SelectObject( &clBitmap );
    clTempDc.SelectObject( &m_clFont );
    
    // �ѱ� ��Ʈ������ ����
    SaveHangulFont( &clTempDc );
    // ���� ��Ʈ������ ����
    SaveEnglishFont( &clTempDc );

    AfxMessageBox( "��Ʈ ������ �������ϴ�." );
}

/**
    �ѱ� ��Ʈ ������ ����
*/
void CFontMakerDlg::SaveHangulFont( CDC* pclTempDC )
{
    int i;
    int j;
    int iCount;
    char vcBuffer[ 2 ];

    // ��Ʈ ������ ����
    if( CreateHangulFontFile() == FALSE )
    {
        return ;
    }

	//=========================================================================
	// ��Ʈ �����͸� ������ ���Ͽ� ����
	//=========================================================================
    //����/���� ���� 0xA4A1 ~ 0xA4D3 ����
    vcBuffer[ 0 ] = ( char )0xA4;
    for( i = 0xA1 ; i <= 0xD3 ; i++ )
    {
        vcBuffer[ 1 ] = i;
        pclTempDC->TextOut( 0, 0, vcBuffer, 2 );

        // ��� �ȼ��� ���ؼ� ��Ʈ����ũ�� ����
        SaveBitMask( pclTempDC, TRUE );
    }

    iCount = 0;
    // �ϼ��� �ѱ� 0xB0A1���� 0xC8FE ����
    for( j = 0xB0 ; j <= 0xC8 ; j++ )
    {
        vcBuffer[ 0 ] = j;
        for( i = 0xA1 ; i <= 0xFE ; i++  )
        {
            vcBuffer[ 1 ] = i;
            pclTempDC->TextOut( 0, 0, vcBuffer, 2 );

            // ��� �ȼ��� ���ؼ� ��Ʈ����ũ�� ����
            SaveBitMask( pclTempDC, TRUE );
            iCount++;
        }
    }

    TRACE( "Total Count = %d\n", iCount );

    // �ڷ� 3ĭ �̵��Ͽ� ,\r\n�� ����
    m_clFile.Seek( -3, SEEK_CUR );
    WriteFontData( "};\r\n" );
    CloseFontFile();
}

/**
    ���� ��Ʈ ������ ����
*/
void CFontMakerDlg::SaveEnglishFont( CDC* pclTempDC )
{
    int i;
    int iCount;
    char cBuffer;

	//=========================================================================
	// ��Ʈ �����͸� ������ ���Ͽ� ����
	//=========================================================================
    // ��Ʈ ������ ����
    if( CreateEnglishFontFile() == FALSE )
    {
        return ;
    }

    iCount = 0;
	// 0~255 ���� ����
    for( i = 0 ; i <= 0xFF ; i++ )
    {
        cBuffer = i;
		pclTempDC->FillSolidRect( 0, 0, 20, 20, RGB( 255, 255, 255 ) );
        pclTempDC->TextOut( 0, 0, &cBuffer, 1 );

        // ��� �ȼ��� ���ؼ� ��Ʈ����ũ�� ����
        SaveBitMask( pclTempDC, FALSE );
        iCount++;
    }

    TRACE( "Total Count = %d\n", iCount );

    // �ڷ� 3ĭ �̵��Ͽ� ,\r\n�� ����
    m_clFile.Seek( -3, SEEK_CUR );
    WriteFontData( "};\r\n" );
    CloseFontFile();
}

/**
    ��Ʈ ����ũ�� ����
*/
void CFontMakerDlg::SaveBitMask( CDC* clTempDc, BOOL bHangul )
{
    int i;
    int j;
    COLORREF stColor;
    unsigned short usBitMask;
	int iFontWidth;

	// �ѱ��̸� ��Ʈ �ʺ� ��ŭ�� ��� �˻��ϰ� �������̸� �ʺ� �ѱ��� ���̹Ƿ�
	// ������ ������
	if( bHangul == TRUE )
	{
		iFontWidth = m_iFontSize;
	}
	else
	{
		iFontWidth = m_iFontSize / 2;
	}

    // ��Ʈ ��Ʈ���� �����Ͽ� ���Ͽ� ����
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
        // BitMask�� ����.
        WriteFontData( usBitMask, bHangul );
        WriteFontData( "," );
    }
    WriteFontData( "\r\n" );
}

/**
    �ѱ� ��Ʈ ������ ����
        ������ ������ ��, C��� �迭�� ����� �߰�
*/
BOOL CFontMakerDlg::CreateHangulFontFile()
{
    char* pcHeader = "// �ڸ� 51�� + �ϼ��� 2350�� ��Ʈ ������, %dx%d pixel \r\n"
        "unsigned short g_vusHangulFont[] = { \r\n";
    char vcBuffer[ 1024 ];

	sprintf( vcBuffer, pcHeader, m_iFontSize, m_iFontSize );
	// ���� ����
    if( m_clFile.Open( "HangulFont.c", CFile::modeCreate | 
        CFile::modeReadWrite ) == FALSE )
    {
        AfxMessageBox( "���� ������ �����߽��ϴ�." );
        return FALSE;
    }
    m_clFile.Write( vcBuffer, strlen( vcBuffer ) );
    return TRUE;
}

/**
    ���� ��Ʈ ������ ����
        ������ ������ ��, C��� �迭�� ����� �߰�
*/
BOOL CFontMakerDlg::CreateEnglishFontFile()
{
    char* pcHeader = "// ������ 256�� ��Ʈ ������, %dx%d pixel \r\n"
        "unsigned char g_vucEnglishFont[] = { \r\n";
    char vcBuffer[ 1024 ];

	sprintf( vcBuffer, pcHeader, m_iFontSize / 2, m_iFontSize );
	// ���� ����
    if( m_clFile.Open( "EnglishFont.c", CFile::modeCreate | 
        CFile::modeReadWrite ) == FALSE )
    {
        AfxMessageBox( "���� ������ �����߽��ϴ�." );
        return FALSE;
    }
    m_clFile.Write( vcBuffer, strlen( vcBuffer ) );
    return TRUE;
}


/**
    Font ���Ͽ� ������ ����
*/
void CFontMakerDlg::WriteFontData( unsigned short usData, BOOL bHangul )
{
    char vcBuffer[ 20 ];

    // �ѱ��� ���� 2byte�� ����� ������ ���� 1byte�� ����
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
    Font ���Ͽ� �����͸� ��
*/
void CFontMakerDlg::WriteFontData( char* pcData )
{
    m_clFile.Write( pcData, strlen( pcData ) );
}

/**
    Font ������ ����
*/
void CFontMakerDlg::CloseFontFile()
{
    m_clFile.Close();
}
