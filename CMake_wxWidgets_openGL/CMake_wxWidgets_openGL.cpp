#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <GL/gl.h>

// The main application class derived from wxApp. This class is responsible
// for initializing the application and creating the main frame.
class MyApp : public wxApp
{
public:
    // Override the OnInit method to initialize the main frame.
    bool OnInit() override;
};

// This macro implements the main application class and starts the application.
wxIMPLEMENT_APP(MyApp);

// MyGLCanvas is a custom class derived from wxGLCanvas that handles
// OpenGL rendering. It provides methods for rendering and handling
// paint and resize events.
class MyGLCanvas : public wxGLCanvas
{
public:
    // Constructor to initialize the OpenGL canvas.
    MyGLCanvas(wxWindow* parent);

    // Method to render the OpenGL scene.
    void Render();

private:
    // Event handler for paint events.
    void OnPaint(wxPaintEvent& event);

    // Event handler for resize events.
    void OnResize(wxSizeEvent& event);

    // OpenGL context needed for rendering.
    wxGLContext* m_context;

    // Declare the event table to map events to their handlers.
    wxDECLARE_EVENT_TABLE();
};

// Define the event table for MyGLCanvas to handle paint and resize events.
wxBEGIN_EVENT_TABLE(MyGLCanvas, wxGLCanvas)
EVT_PAINT(MyGLCanvas::OnPaint)
EVT_SIZE(MyGLCanvas::OnResize)
wxEND_EVENT_TABLE()

// MyFrame is the main application window class derived from wxFrame.
// It creates and manages the menu, status bar, and the OpenGL canvas.
class MyFrame : public wxFrame
{
public:
    // Constructor to initialize the main frame.
    MyFrame();

private:
    // Event handler for the "Hello" menu item.
    void OnHello(wxCommandEvent& event);

    // Event handler for the "Exit" menu item.
    void OnExit(wxCommandEvent& event);

    // Event handler for the "About" menu item.
    void OnAbout(wxCommandEvent& event);

    // Event handler for the "OpenGL" menu item.
    void OnOpenGL(wxCommandEvent& event);

    // OpenGL canvas object.
    MyGLCanvas* m_glCanvas;

    // Declare the event table to map events to their handlers.
    wxDECLARE_EVENT_TABLE();
};

// Enum for menu item IDs.
enum
{
    ID_Hello = 1,
    ID_OpenGL = 2 // ID for OpenGL menu item.
};

// Define the event table for MyFrame to handle menu events.
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(ID_Hello, MyFrame::OnHello)
EVT_MENU(wxID_EXIT, MyFrame::OnExit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_MENU(ID_OpenGL, MyFrame::OnOpenGL) // Bind the OpenGL menu item to its handler.
wxEND_EVENT_TABLE()

// Implementation of the OnInit method to initialize the main frame.
// This method is called when the application starts.
bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

// Constructor for MyFrame to create the main application window.
MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Hello World OpenGL", wxDefaultPosition, wxSize(800, 600))
{
    // Create the "File" menu.
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    // Create the "View" menu and add the OpenGL item.
    wxMenu* menuView = new wxMenu;
    menuView->Append(ID_OpenGL, "&OpenGL", "OpenGL view");

    // Create the "Help" menu.
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    // Create the menu bar and append the menus.
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuView, "&View");
    menuBar->Append(menuHelp, "&Help");

    // Set the menu bar for the frame.
    SetMenuBar(menuBar);

    // Create the status bar to display messages.
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    // Create the OpenGL canvas but don't show it initially.
    m_glCanvas = new MyGLCanvas(this);
    m_glCanvas->Hide();
}

// Event handler for the "Exit" menu item. This closes the application.
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

// Event handler for the "About" menu item. This shows an About dialog.
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
}

// Event handler for the "Hello" menu item. This logs a message.
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

// Event handler for the "OpenGL" menu item. This shows the OpenGL canvas.
void MyFrame::OnOpenGL(wxCommandEvent& event)
{
    m_glCanvas->Show(true);
    Layout(); // Update the layout to accommodate the shown canvas.
}

// Implementation of the MyGLCanvas constructor to initialize the OpenGL canvas.
// This constructor creates the OpenGL context.
MyGLCanvas::MyGLCanvas(wxWindow* parent)
    : wxGLCanvas(parent, wxID_ANY, nullptr)
{
    m_context = new wxGLContext(this);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

// Method to render the OpenGL scene. This method is called to draw the scene.
void MyGLCanvas::Render()
{
    SetCurrent(*m_context);
    wxPaintDC(this);

    // Clear the screen with a black background.
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a simple colored triangle.
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.5f, -0.5f);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0.5f, -0.5f);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.0f, 0.5f);
    glEnd();

    glFlush();
    SwapBuffers();
}

// Event handler for paint events. This method is called when the canvas needs
// to be repainted.
void MyGLCanvas::OnPaint(wxPaintEvent& event)
{
    Render();
}

// Event handler for resize events. This method is called when the canvas is
// resized. It adjusts the OpenGL viewport to match the new size.
void MyGLCanvas::OnResize(wxSizeEvent& event)
{
    int width, height;
    GetClientSize(&width, &height);
    if (height == 0)
        height = 1;
    glViewport(0, 0, width, height);

    Refresh(); // Trigger a paint event to redraw the scene.
}
