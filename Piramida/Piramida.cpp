/*************************************************************************************/
//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj� osi  
//  uk�adu wsp�rzednych
/*************************************************************************************/
#include "stdafx.h"

/*************************************************************************************/
// Funkcja rysuj�ca osie uk�adu wsp�rz�dnych




typedef GLfloat point3[3];
static GLfloat theta[] = { 0.0, 0.0, 0.0 }; // trzy k�ty obrotu

GLfloat x = 0;
GLfloat y = 0;
GLfloat a = 5;
GLfloat H = a*2;

void spin()
{

	//theta[0] -= 0.1;
	//if (theta[0] > 360.0) theta[0] -= 360.0;

	theta[2] -= 0.1;
	if (theta[2] > 360.0) theta[2] -= 360.0;

	glutPostRedisplay(); //od�wie�enie zawarto�ci aktualnego okna
}


void piramida(GLfloat x, GLfloat y, GLfloat H, GLfloat Z0, int depth, GLfloat a){


	if (depth > 1) {
		piramida(x -(a/ 2), y +(a/ 2) ,H / 2, Z0, depth - 1,a/2);
		piramida(x+(a / 2), y +(a/ 2), H / 2, Z0, depth - 1,a/2);
		piramida(x +(a/ 2), y-(a / 2), H / 2, Z0, depth - 1,a/2);
		piramida(x-(a / 2), y-(a / 2), H / 2, Z0, depth - 1,a/2);
		piramida(x , y , H / 2, Z0 - (H / 2), depth - 1,a/2);

	}
	else {

		point3 A = { x - a, y + a, -Z0};
		point3 B = { x + a, y + a, -Z0};
		point3 D = { x - a, y - a, -Z0};
		point3 C = { x + a, y - a, -Z0};
		point3 E = { x , y, -Z0 + H };

		glColor3f(0.0f, 1.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3f(A[0], A[1], A[2]);
		glVertex3f(B[0], B[1], B[2]);
		glVertex3f(C[0], C[1], C[2]);
		glVertex3f(D[0], D[1], D[2]);
		glEnd();


		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3f(A[0], A[1], A[2]);
		glVertex3f(B[0], B[1], B[2]);
		glVertex3f(E[0], E[1], E[2]);
		glEnd();

		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3f(B[0], B[1], B[2]);
		glVertex3f(C[0], C[1], C[2]);
		glVertex3f(E[0], E[1], E[2]);
		glEnd();

		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3f(C[0], C[1], C[2]);
		glVertex3f(D[0], D[1], D[2]);
		glVertex3f(E[0], E[1], E[2]);
		glEnd();

		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3f(D[0], D[1], D[2]);
		glVertex3f(A[0], A[1], A[2]);
		glVertex3f(E[0], E[1], E[2]);
		glEnd();

	}

	return;
}

void Axes(void)
{
	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	// pocz�tek i koniec obrazu osi x

	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0,  5.0, 0.0 };
	// pocz�tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0,  5.0 };
	//  pocz�tek i koniec obrazu osi y
	glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
	glBegin(GL_LINES); // rysowanie osi x
	glVertex3fv(x_min);
	glVertex3fv(x_max);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
	glBegin(GL_LINES);  // rysowanie osi y
	glVertex3fv(y_min);
	glVertex3fv(y_max);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
	glBegin(GL_LINES); // rysowanie osi z
	glVertex3fv(z_min);
	glVertex3fv(z_max);
	glEnd();
}
/*************************************************************************************/
// Funkcja okre�laj�ca co ma by� rysowane (zawsze wywo�ywana gdy trzeba 
// przerysowa� scen�)

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz�cym

	glLoadIdentity();
	// Czyszczenie macierzy bie��cej
	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wy�ej

	glRotatef(-90.0f, 1.0, 0.0, 0.0);

	glRotatef(theta[1], 0.0, 1.0, 0.0);

	glRotatef(theta[2], 0.0, 0.0, 1.0);
	//tu rysujemy
	piramida(x,y,H,5,7,a);

	glFlush();
	// Przekazanie polece� rysuj�cych do wykonania

	glutSwapBuffers();
	//
}

/*************************************************************************************/
// Funkcja ustalaj�ca stan renderowania


void MyInit(void)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	// Kolor czyszc�cy (wype�nienia okna) ustawiono na czarny
}
/*************************************************************************************/
// Funkcja ma za zadanie utrzymanie sta�ych proporcji rysowanych 
// w przypadku zmiany rozmiar�w okna.
// Parametry vertical i horizontal (wysoko�� i szeroko�� okna) s� 
// przekazywane do funkcji za ka�dym razem gdy zmieni si� rozmiar okna.

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio  okre�laj�cej proporcj�
	// wymiar�w okna 
	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
		vertical = 1;
	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielko�ciokna okna widoku (viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)  
	glMatrixMode(GL_PROJECTION);
	// Prze��czenie macierzy bie��cej na macierz projekcji 
	glLoadIdentity();
	// Czyszcznie macierzy bie��cej            
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wsp�czynnika  proporcji okna
	// Gdy okno nie jest kwadratem wymagane jest okre�lenie tak zwanej
	// przestrzeni ograniczaj�cej pozwalaj�cej zachowa� w�a�ciwe
	// proporcje rysowanego obiektu.
	// Do okreslenia przestrzeni ograniczj�cej s�u�y funkcja
	// glOrtho(...)            
	if (horizontal <= vertical)
		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);
	else
		glOrtho(-7.5*AspectRatio, 7.5*AspectRatio, -7.5, 7.5, 10.0, -10.0);
	glMatrixMode(GL_MODELVIEW);
	// Prze��czenie macierzy bie��cej na macierz widoku modelu                                   
	glLoadIdentity();
	// Czyszcenie macierzy bie��cej
}
/*************************************************************************************/
// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli

//Obs�uga klawiszy

void main(int argc, char **argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(500, 500);

	glutCreateWindow("Uk�ad wsp�rz�dnych 3-D");

	glutDisplayFunc(RenderScene);
	// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn�
	// (callback function).  Bedzie ona wywo�ywana za ka�dym razem 
	// gdy zajdzie potrzba przeryswania okna 
	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn�
	// zazmiany rozmiaru okna      
	MyInit();
	// Funkcja MyInit() (zdefiniowana powy�ej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przyst�pieniem do renderowania
	glEnable(GL_DEPTH_TEST);
	// W��czenie mechanizmu usuwania powierzchni niewidocznych
	glutIdleFunc(spin);

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}
/*************************************************************************************/
