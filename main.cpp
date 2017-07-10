#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glew.h>
#include <GL/glut.h>

#endif

#include "tinyxml.h"

#include "engine.h"
#include <math.h>
#include <stdio.h>
#include "engine.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <stdlib.h>
#include <IL/il.h>


#define _PI_ 3.14159


float camX = 100, camY = 300, camZ = 150;
int startX, startY, tracking = 0;
int alpha = 0, beta = 80, r = 400;

float px, py, pz, tx, ty, nx, ny, nz;



int nLuz=0;
using namespace std;
string actions;
int noLine=0;
long tempoAtual = 0;
GLuint buffer[3];



GLfloat emissaoD[4] = {0,0,0,1};
GLfloat especularD[4] = {0,0,0,1};
GLfloat ambienteD[4] = {0.2,0.2,0.2,1.0};
GLfloat difusaD[4] = {0.8,0.8,0.8,1.0};
GLfloat shininessD = 0.0;


struct info {

    std::vector<float> pcurva; // pode ser vazio caso o objeto nao tenha translaçao ao longo de uma curva
    int indInit;    // indice do inicio no vbo
    int nVertices;  // numero de vertices para desenhar
    int nPontos;    // numero de vertices da curva
    float tempo;    // caso tenha tempo de translaçao aramazena esse valor  
    GLuint nTexture;
    float difusa[4];
    float ambiente[4];
    float especular[4];
    float emissao[4];
    float shininess;
};

//vetor com estruturas
std::vector<struct info> listInfo;

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if (h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}


int loadTexture(std::string s) {
    unsigned int t, tw, th;
    unsigned char *texData;
    unsigned int texID;

    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilGenImages(1, &t);
    ilBindImage(t);
    ilLoadImage((ILstring) s.c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1, &texID);

    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texID;

}

void getCatmullRomPoint(float gt, float *res, std::vector<float> v, int POINT_COUNT) {
    float t = gt * POINT_COUNT; // this is the real global t
    int index = floor(t);  // which segment
    t = t - index; // where within  the segment


    int ind0_ = (index + POINT_COUNT - 1) % POINT_COUNT;
    int ind1_ = (ind0_ + 1) % POINT_COUNT;
    int ind2_ = (ind1_ + 1) % POINT_COUNT;
    int ind3_ = (ind2_ + 1) % POINT_COUNT;
    // indices store the points
    int ind0 = ind0_ * 3;
    int ind1 = ind1_ * 3;
    int ind2 = ind2_ * 3;
    int ind3 = ind3_ * 3;

    // catmull-rom matrix
    float m[4][4] = {{-0.5f, 1.5f,  -1.5f, 0.5f},
                     {1.0f,  -2.5f, 2.0f,  -0.5f},
                     {-0.5f, 0.0f,  0.5f,  0.0f},
                     {0.0f,  1.0f,  0.0f,  0.0f}};

    res[0] = 0.0;
    res[1] = 0.0;
    res[2] = 0.0;

    float ax[4];
    float ay[4];
    float az[4];

    ax[0] = m[0][0] * v[ind0] + m[0][1] * v[ind1] + m[0][2] * v[ind2] + m[0][3] * v[ind3];
    ax[1] = m[1][0] * v[ind0] + m[1][1] * v[ind1] + m[1][2] * v[ind2] + m[1][3] * v[ind3];
    ax[2] = m[2][0] * v[ind0] + m[2][1] * v[ind1] + m[2][2] * v[ind2] + m[2][3] * v[ind3];
    ax[3] = m[3][0] * v[ind0] + m[3][1] * v[ind1] + m[3][2] * v[ind2] + m[3][3] * v[ind3];

    ay[0] = m[0][0] * v[ind0 + 1] + m[0][1] * v[ind1 + 1] + m[0][2] * v[ind2 + 1] + m[0][3] * v[ind3 + 1];
    ay[1] = m[1][0] * v[ind0 + 1] + m[1][1] * v[ind1 + 1] + m[1][2] * v[ind2 + 1] + m[1][3] * v[ind3 + 1];
    ay[2] = m[2][0] * v[ind0 + 1] + m[2][1] * v[ind1 + 1] + m[2][2] * v[ind2 + 1] + m[2][3] * v[ind3 + 1];
    ay[3] = m[3][0] * v[ind0 + 1] + m[3][1] * v[ind1 + 1] + m[3][2] * v[ind2 + 1] + m[3][3] * v[ind3 + 1];

    az[0] = m[0][0] * v[ind0 + 2] + m[0][1] * v[ind1 + 2] + m[0][2] * v[ind2 + 2] + m[0][3] * v[ind3 + 2];
    az[1] = m[1][0] * v[ind0 + 2] + m[1][1] * v[ind1 + 2] + m[1][2] * v[ind2 + 2] + m[1][3] * v[ind3 + 2];
    az[2] = m[2][0] * v[ind0 + 2] + m[2][1] * v[ind1 + 2] + m[2][2] * v[ind2 + 2] + m[2][3] * v[ind3 + 2];
    az[3] = m[3][0] * v[ind0 + 2] + m[3][1] * v[ind1 + 2] + m[3][2] * v[ind2 + 2] + m[3][3] * v[ind3 + 2];


    res[0] = pow(t, 3) * ax[0] + pow(t, 2) * ax[1] + t * ax[2] + ax[3];
    res[1] = pow(t, 3) * ay[0] + pow(t, 2) * ay[1] + t * ay[2] + ay[3];
    res[2] = pow(t, 3) * az[0] + pow(t, 2) * az[1] + t * az[2] + az[3];


}

void renderCatmullRomCurve(int x) {

// desenhar a curva usando segmentos de reta - GL_LINE_LOOP
    float res[3];

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++) {
        getCatmullRomPoint(i / 100.0, res, listInfo[x].pcurva, listInfo[x].nPontos);
        glVertex3f(res[0], res[1], res[2]);


    }

    glEnd();


}


void prepareVbo(std::string &actions) {
    int t = 1;// variavel que testa se ha 2 model seguidos
    int i = 0;
    int VertexCount = 0;
    std::vector<float> vertices;
    std::vector<float> normais;
    std::vector<float> textura;


    std::stringstream ss(actions);
    std::string newline;

    while (std::getline(ss, newline, '\n')) {

        std::stringstream s1(newline);
        std::string espacos;
        std::getline(s1, espacos, ' ');


        if (espacos == "group") {
            listInfo.push_back(info());
            t = 1;
        }

        if (espacos == "model") {
            if (t == 0) { listInfo.push_back(info()); }

            t = 0;
            listInfo[i].indInit = VertexCount;
            std::getline(s1, espacos, ' ');
            char *file = (char *) espacos.c_str();
            listInfo[i].nVertices = 0;

            ifstream ficheiro;

            ficheiro.open(file);

            if (!ficheiro) {
                return;
            }

            while (!ficheiro.eof()) { // recolher os pontos do ficheiro
                ficheiro >> px >> py >> pz >> tx >> ty >> nx >> ny >> nz;
                vertices.push_back(px);
                vertices.push_back(py);
                vertices.push_back(pz);

                textura.push_back(tx);
                textura.push_back(ty);


                normais.push_back(nx);
                normais.push_back(ny);
                normais.push_back(nz);

                VertexCount++;
                listInfo[i].nVertices++;

            }

            ficheiro.close();
            
            listInfo[i].difusa[0] = 0.8;listInfo[i].difusa[1] = 0.8;listInfo[i].difusa[2] = 0.8;listInfo[i].difusa[3] = 1;
            listInfo[i].ambiente[0] = 0.2;listInfo[i].ambiente[1] = 0.2;listInfo[i].ambiente[2] = 0.2;listInfo[i].ambiente[3] = 1;
            listInfo[i].especular[0] = 0.0;listInfo[i].especular[1] = 0.0;listInfo[i].especular[2] = 0.0;listInfo[i].especular[3] = 1;
            listInfo[i].emissao[0] = 0.0;listInfo[i].emissao[1] = 0.0;listInfo[i].emissao[2] = 0.0;listInfo[i].emissao[3] = 1;
            listInfo[i].shininess= 0.0;

            while (std::getline(s1, espacos, ' ')) {
                string::size_type posicao = espacos.find('=');
                string att = espacos.substr(0, posicao);
                string val = espacos.substr(posicao + 1, espacos.size() - posicao);




                if(att == "texture") listInfo[i].nTexture = loadTexture(val);

                if(att == "diffR") {
                    listInfo[i].difusa[0] = std::strtof((char*)val.c_str(),NULL);
                    listInfo[i].difusa[3] = 1;
                }
                if(att == "diffG") listInfo[i].difusa[1] = std::strtof((char*)val.c_str(),NULL);
                if(att == "diffB") listInfo[i].difusa[2] = std::strtof((char*)val.c_str(),NULL);
               

                if(att == "ambR") {
                    listInfo[i].ambiente[0] = std::strtof((char*)val.c_str(),NULL);
                    listInfo[i].ambiente[3] = 1;
                }
                if(att == "ambG") listInfo[i].ambiente[1] = std::strtof((char*)val.c_str(),NULL);
                if(att == "ambB") listInfo[i].ambiente[2] = std::strtof((char*)val.c_str(),NULL);
               

                if(att == "shin")
                    listInfo[i].shininess = std::strtof((char*)val.c_str(),NULL);

                if(att == "specR") {
                    listInfo[i].especular[0] = std::strtof((char*)val.c_str(),NULL);
                    listInfo[i].especular[3] = 1;
                }
                if(att == "specG") listInfo[i].especular[1] = std::strtof((char*)val.c_str(),NULL);
                if(att == "specB") listInfo[i].especular[2] = std::strtof((char*)val.c_str(),NULL);
                

                if(att == "emisR") {
                    listInfo[i].emissao[0] = std::strtof((char*)val.c_str(),NULL);
                    listInfo[i].emissao[3] = 1;
                }
                if(att == "emisG") listInfo[i].emissao[1] = std::strtof((char*)val.c_str(),NULL);
                if(att == "emisB") listInfo[i].emissao[2] = std::strtof((char*)val.c_str(),NULL);
      
                
            }
            i++;
        }
        //espaco é translate1 significa que e um translate com time e que é seguido de varios points
        if (espacos == "translate1") {
            listInfo[i].nPontos = 0;
            //guardar o tempo
            std::getline(s1, espacos, ' ');
            char *esp = (char *) espacos.c_str();
            listInfo[i].tempo = std::strtof(esp, NULL);

            // ciclo para percorrer os pontos do translate
            while (true) {
                std::getline(ss, newline, '\n'); //troca de linha para o 1º point
                std::stringstream s1(newline);
                std::string espacos;

                if (newline == "/translate") break; // caso chega ao final do translate acaba o ciclo

                std::getline(s1, espacos, ' ');

                std::getline(s1, espacos, ' ');

                char *xx = (char *) espacos.c_str();

                float x = std::strtof(xx, NULL);
                std::getline(s1, espacos, ' ');
                char *yy = (char *) espacos.c_str();
                float y = std::strtof(xx, NULL);

                std::getline(s1, espacos, ' ');
                char *zz = (char *) espacos.c_str();
                float z = std::strtof(xx, NULL);

                listInfo[i].pcurva.push_back(x);
                listInfo[i].pcurva.push_back(y);
                listInfo[i].pcurva.push_back(z);
                listInfo[i].nPontos++;
            }

        }


    }

    glGenBuffers(3, buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * VertexCount * 3, &(vertices[0]), GL_STATIC_DRAW);

    // glGenBuffers(1, buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * VertexCount * 3, &(normais[0]), GL_STATIC_DRAW);

    // glGenBuffers(1, buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * VertexCount * 2, &(textura[0]), GL_STATIC_DRAW);

}

void parseTransltime(int i) {
    if(noLine==0) renderCatmullRomCurve(i);
    else noLine = 0;
    float res[3];

    getCatmullRomPoint(tempoAtual / (1000.0 * listInfo[i].tempo), res, listInfo[i].pcurva, listInfo[i].nPontos);
    glTranslatef(res[0], res[1], res[2]);


}

// t = 0 significa translaçao, t = 1 escala
void parseTranSca(int t, std::stringstream &s1, std::string &espacos) {

    std::getline(s1, espacos, ' ');
    char *esp = (char *) espacos.c_str(); // converte string em char*
    float tx = std::strtof(esp, NULL);
    std::getline(s1, espacos, ' ');
    esp = (char *) espacos.c_str();
    float ty = std::strtof(esp, NULL);
    std::getline(s1, espacos, ' ');
    esp = (char *) espacos.c_str();
    float tz = std::strtof(esp, NULL);

    if (t == 0) glTranslatef(tx, ty, tz);
    else glScalef(tx, ty, tz);
}

// t=0 representa rotaçao temporal t=1 representa uma rotaçao "normal"
void parseRotate(int t, std::stringstream &s1, std::string &espacos) {

    std::getline(s1, espacos, ' ');
    char *esp = (char *) espacos.c_str();
    float firstAt = std::strtof(esp, NULL);
    std::getline(s1, espacos, ' ');
    esp = (char *) espacos.c_str();
    float tx = std::strtof(esp, NULL);
    std::getline(s1, espacos, ' ');
    esp = (char *) espacos.c_str();
    float ty = std::strtof(esp, NULL);
    std::getline(s1, espacos, ' ');
    esp = (char *) espacos.c_str();
    float tz = std::strtof(esp, NULL);
    if (t == 1) glRotatef(firstAt, tx, ty, tz);
    else glRotatef(tempoAtual * (0.36 / firstAt), tx, ty, tz);
}

int draw(int i) {

    glMaterialfv(GL_FRONT, GL_AMBIENT, listInfo[i].ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, listInfo[i].difusa);
    glMaterialfv(GL_FRONT, GL_EMISSION, listInfo[i].emissao);
    glMaterialfv(GL_FRONT, GL_SPECULAR, listInfo[i].especular);
    glMaterialf(GL_FRONT, GL_SHININESS, listInfo[i].shininess);


    glBindTexture(GL_TEXTURE_2D, listInfo[i].nTexture);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
    glNormalPointer(GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);


    glDrawArrays(GL_TRIANGLES, listInfo[i].indInit, listInfo[i].nVertices);
    glBindTexture(GL_TEXTURE_2D, 0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambienteD);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difusaD);
    glMaterialfv(GL_FRONT, GL_EMISSION, emissaoD);
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularD);
    glMaterialf(GL_FRONT, GL_SHININESS, shininessD);
}

void parseLight(std::stringstream &s1, std::string &espacos){
    GLfloat light_position[4];
    std::getline(s1, espacos, ' ');
    if(espacos == "POINT" || espacos == "SPOT") light_position[3] = 1.0;
    if(espacos == "DIRECTIONAL") light_position[3] = 0.0;
    
    
    GLfloat cores_luz[4];
    GLfloat spotDir[3];
    float cutOff; 
    float exponent;
    char* esp;
    std::getline(s1, espacos, ' ');
    esp = (char *) espacos.c_str();
    float xx = std::strtof(esp, NULL);
    std::getline(s1, espacos, ' ');
    esp = (char *) espacos.c_str();
    float yy = std::strtof(esp, NULL);
    std::getline(s1, espacos, ' ');
    esp = (char *) espacos.c_str();
    float zz = std::strtof(esp, NULL);

    light_position[0] = xx;
    light_position[1] = yy;
    light_position[2] = zz;



    while (std::getline(s1, espacos, ' ')){

        string::size_type posicao = espacos.find('=');
        string att = espacos.substr(0, posicao);
        string val = espacos.substr(posicao + 1, espacos.size() - posicao);



        if(att == "diffR") cores_luz[0]=std::strtof((char*)val.c_str(),NULL);
        if(att == "diffG") cores_luz[1]=std::strtof((char*)val.c_str(),NULL);
        if(att == "diffB") cores_luz[2]=std::strtof((char*)val.c_str(),NULL);
        if(att == "diffA") {cores_luz[3]=std::strtof((char*)val.c_str(),NULL);glLightfv(GL_LIGHT0+nLuz, GL_DIFFUSE, cores_luz);}

        if(att == "ambR") cores_luz[0] = std::strtof((char*)val.c_str(),NULL);
        if(att == "ambG") cores_luz[1] = std::strtof((char*)val.c_str(),NULL);
        if(att == "ambB") cores_luz[2] = std::strtof((char*)val.c_str(),NULL);
        if(att == "ambA") {cores_luz[3]=std::strtof((char*)val.c_str(),NULL);glLightfv(GL_LIGHT0+nLuz, GL_AMBIENT, cores_luz);}

        if(att == "specR") cores_luz[0]=std::strtof((char*)val.c_str(),NULL);
        if(att == "specG") cores_luz[1]=std::strtof((char*)val.c_str(),NULL);
        if(att == "specB") cores_luz[2]=std::strtof((char*)val.c_str(),NULL);
        if(att == "specA") {cores_luz[3]=std::strtof((char*)val.c_str(),NULL);glLightfv(GL_LIGHT0+nLuz, GL_SPECULAR, cores_luz);}
        
        if(att == "spotDx") spotDir[0]=std::strtof((char*)val.c_str(),NULL);
        if(att == "spotDy") spotDir[1]=std::strtof((char*)val.c_str(),NULL);
        if(att == "spotDz") {spotDir[2]=std::strtof((char*)val.c_str(),NULL);glLightfv(GL_LIGHT0+nLuz, GL_SPOT_DIRECTION, spotDir);}
        
        if(att == "CutOff") {cutOff=std::strtof((char*)val.c_str(),NULL);glLightf(GL_LIGHT0+nLuz, GL_SPOT_CUTOFF, cutOff);}

        if(att == "Exponent") {exponent=std::strtof((char*)val.c_str(),NULL);glLightf(GL_LIGHT0+nLuz, GL_SPOT_EXPONENT, exponent);}
    }

    glEnable(GL_LIGHT0+nLuz);
    glLightfv(GL_LIGHT0+nLuz, GL_POSITION, light_position);
    nLuz++;

}

void parseString(std::string &actions) {
    int i = 0;
    nLuz =0;
    std::stringstream ss(actions);
    std::string newline;
    while (std::getline(ss, newline, '\n')) {
        if (newline == "group") {
            glPushMatrix();
            //continue;
        }
        if (newline == "/group") {
            glPopMatrix();
            //continue;
        }

	    if(newline == "noLine") {
            noLine=1;
            //continue;
        }
        std::stringstream s1(newline);
        std::string espacos;
        std::getline(s1, espacos, ' ');
        if (espacos == "translate") {
            parseTranSca(0, s1, espacos);
            //continue;
        }
        if(espacos == "light") parseLight(s1,espacos);
        if (espacos == "translate1") {
            parseTransltime(i);
            //continue;
        }
        if (espacos == "rotate1") {
            parseRotate(0, s1, espacos);
            //continue;
        }
        if (espacos == "rotate") {
            parseRotate(1, s1, espacos);
            //continue;
        }
        if (espacos == "scale") {
            parseTranSca(1, s1, espacos);
            //continue;
        }
        if (espacos == "model") {

            draw(i);

            i++;

        }
    }


}


void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera


    glLoadIdentity();
    gluLookAt(camX, camY, camZ,
              0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);




    //(GL_FRONT, GL_LINE);
    //glPolygonMode(GL_BACK, GL_LINE);

    tempoAtual = glutGet(GLUT_ELAPSED_TIME);

    parseString(actions);


    // End of frame
    glutSwapBuffers();
}

void processMouseButtons(int button, int state, int xx, int yy) {

    if (state == GLUT_DOWN) {
        startX = xx;
        startY = yy;
        if (button == GLUT_LEFT_BUTTON)
            tracking = 1;
        else if (button == GLUT_RIGHT_BUTTON)
            tracking = 2;
        else
            tracking = 0;
    } else if (state == GLUT_UP) {
        if (tracking == 1) {
            alpha += (xx - startX);
            beta += (yy - startY);
        } else if (tracking == 2) {

            r -= yy - startY;
            if (r < 3)
                r = 3.0;
        }
        tracking = 0;
    }
    glutPostRedisplay();
}


void processMouseMotion(int xx, int yy) {

    int deltaX, deltaY;
    int alphaAux, betaAux;
    int rAux;

    if (!tracking)
        return;

    deltaX = xx - startX;
    deltaY = yy - startY;

    if (tracking == 1) {


        alphaAux = alpha + deltaX;
        betaAux = beta + deltaY;

        if (betaAux > 85.0)
            betaAux = 85.0;
        else if (betaAux < -85.0)
            betaAux = -85.0;

        rAux = r;
    } else if (tracking == 2) {

        alphaAux = alpha;
        betaAux = beta;
        rAux = r - deltaY;
        if (rAux < 3)
            rAux = 3;
    }
    camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    camY = rAux * sin(betaAux * 3.14 / 180.0);
    glutPostRedisplay();
}


int main(int argc, char **argv) {

    const char *filename;

    filename = argv[1];
    TiXmlDocument file;
    if (!file.LoadFile(filename)) {

        cerr << file.ErrorDesc() << endl;
        return -1;
    }
    TiXmlElement *scene = file.FirstChildElement("scene");
    actions = parseFile(scene);
    //cout << actions;



// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI-UM");
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glewInit();
    prepareVbo(actions);
// Required callback registry
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

// Callback registration for keyboard processing

    glutMouseFunc(processMouseButtons);
    glutMotionFunc(processMouseMotion);



//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glEnableClientState(GL_VERTEX_ARRAY);

// init GLEW
    glewInit();



    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glEnable(GL_LIGHTING);

//    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0, 0, 0, 0);

    

    glEnable(GL_TEXTURE_2D);

// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
