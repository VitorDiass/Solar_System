#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define _USE_MATH_DEFINES

#include <math.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;
float p[3];
typedef struct controlP {
    float x, y, z;
} pontos;

float n[3];
std::vector<int> patch;
std::vector<struct controlP> points;


void readFile(char *ficheiro) {

    std::string line, value;
    int i, valores, nControlPoints, nPatch;
    ifstream file;

    file.open(ficheiro);

    if (!file) exit(0);

    file >> nPatch; // Le o numero de patches, logo a 1ª linha do ficheiro

    //Percorre todos os patches separando as strings por '\n'  e depois cada patch separa por ','
    for (i = 0; i < nPatch + 1; i++) {
        getline(file, line, '\n');
        std::stringstream ss(line);

        while (std::getline(ss, value, ',')) {
            patch.push_back(std::atoi(value.c_str()));
        }
    }

    std::getline(file, line, '\n'); // Neste momento a linha passou para o numero de pontos de controlo

    nControlPoints = std::atoi(line.c_str()); // Converter o numero de pontos de controlo para int

    //Ler desde o numero de controll Points ate ao fim
    i = 0;
    float x, y, z;

    while (std::getline(file, line, '\n')) {
        std::stringstream ss(line);
        std::getline(ss, value, ',');
        x = std::atof(value.c_str());
        std::getline(ss, value, ',');
        y = std::atof(value.c_str());
        std::getline(ss, value, ',');
        z = std::atof(value.c_str());

        points.push_back(controlP());
        points[i].x = x;
        points[i].y = y;
        points[i++].z = z;


    }


}

void cross(float *a, float *b, float *res) { 
    res[0] = a[1]*b[2] - a[2]*b[1]; 
    res[1] = a[2]*b[0] - a[0]*b[2]; 
    res[2] = a[0]*b[1] - a[1]*b[0];
}

void normalize(float *a) { 
    float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    if(l==0) l=1; 
    a[0] = a[0]/l; 
    a[1] = a[1]/l; 
    a[2] = a[2]/l;
}


void procPatch(int i, int j, int tLevel, int iterador) {

    float u = ((float) i) / tLevel;
    float v = ((float) j) / tLevel;

    float m[4][4] = {{-1.0f, 3.0f, -3.0f, 1.0f},
                     {3.0f,  -6.0f, 3.0f, 0.0f},
                     {-3.0f, 3.0f, 0.0f,  0.0f},
                     {1.0f,  0.0f, 0.0f,  0.0f}
    };

    float res[4][3],resD[4][3]; 
    float t2[3],t1[3],pD[3];
    float ax[4],utx[4];
    float ay[4],uty[4];
    float az[4],utz[4];


    for (int i = 0; i < 4; i++) {

        ax[0] = m[0][0] * points[patch[iterador]].x + m[0][1] * points[patch[iterador + 1]].x
                + m[0][2] * points[patch[iterador + 2]].x + m[0][3] * points[patch[iterador + 3]].x;

        ax[1] = m[1][0] * points[patch[iterador]].x + m[1][1] * points[patch[iterador + 1]].x +
                m[1][2] * points[patch[iterador + 2]].x
                + m[1][3] * points[patch[iterador + 3]].x;

        ax[2] = m[2][0] * points[patch[iterador]].x + m[2][1] * points[patch[iterador + 1]].x
                + m[2][2] * points[patch[iterador + 2]].x + m[2][3] * points[patch[iterador + 3]].x;

        ax[3] = m[3][0] * points[patch[iterador]].x + m[3][1] * points[patch[iterador + 1]].x
                + m[3][2] * points[patch[iterador + 2]].x + m[3][3] * points[patch[iterador + 3]].x;

        ay[0] = m[0][0] * points[patch[iterador]].y + m[0][1] * points[patch[iterador + 1]].y +
                m[0][2] * points[patch[iterador + 2]].y
                + m[0][3] * points[patch[iterador + 3]].y;

        ay[1] = m[1][0] * points[patch[iterador]].y + m[1][1] * points[patch[iterador + 1]].y +
                m[1][2] * points[patch[iterador + 2]].y
                + m[1][3] * points[patch[iterador + 3]].y;

        ay[2] = m[2][0] * points[patch[iterador]].y + m[2][1] * points[patch[iterador + 1]].y
                + m[2][2] * points[patch[iterador + 2]].y + m[2][3] * points[patch[iterador + 3]].y;

        ay[3] = m[3][0] * points[patch[iterador]].y + m[3][1] * points[patch[iterador + 1]].y +
                m[3][2] * points[patch[iterador + 2]].y
                + m[3][3] * points[patch[iterador + 3]].y;

        az[0] = m[0][0] * points[patch[iterador]].z + m[0][1] * points[patch[iterador + 1]].z +
                m[0][2] * points[patch[iterador + 2]].z
                + m[0][3] * points[patch[iterador + 3]].z;

        az[1] = m[1][0] * points[patch[iterador]].z + m[1][1] * points[patch[iterador + 1]].z +
                m[1][2] * points[patch[iterador + 2]].z
                + m[1][3] * points[patch[iterador + 3]].z;

        az[2] = m[2][0] * points[patch[iterador]].z + m[2][1] * points[patch[iterador + 1]].z +
                m[2][2] * points[patch[iterador + 2]].z
                + m[2][3] * points[patch[iterador + 3]].z;

        az[3] = m[3][0] * points[patch[iterador]].z + m[3][1] * points[patch[iterador + 1]].z +
                m[3][2] * points[patch[iterador + 2]].z
                + m[3][3] * points[patch[iterador + 3]].z;


        iterador += 4;

         

        p[0] = pow(u, 3) * ax[0] + pow(u, 2) * ax[1] + u * ax[2] + ax[3];
        p[1] = pow(u, 3) * ay[0] + pow(u, 2) * ay[1] + u * ay[2] + ay[3];
        p[2] = pow(u, 3) * az[0] + pow(u, 2) * az[1] + u * az[2] + az[3];

        pD[0] = 3.0*pow(u,2) * ax[0] + 2.0*u*ax[1] + ax[2];
        pD[1] = 3.0*pow(u,2) * ay[0] + 2.0*u*ay[1] + ay[2];
        pD[2] = 3.0*pow(u,2) * az[0] + 2.0*u*az[1] + az[2];
        // UMP
        res[i][0] = p[0];
        res[i][1] = p[1];
        res[i][2] = p[2];
        // derivada(U)*M*P
        resD[i][0] = pD[0];
        resD[i][1] = pD[1];
        resD[i][2] = pD[2];
    }

    

    // calculo M*Res

    ax[0] = m[0][0] * res[0][0] + m[0][1] * res[1][0] + m[0][2] * res[2][0] + m[0][3] * res[3][0];
    ax[1] = m[1][0] * res[0][0] + m[1][1] * res[1][0] + m[1][2] * res[2][0] + m[1][3] * res[3][0];
    ax[2] = m[2][0] * res[0][0] + m[2][1] * res[1][0] + m[2][2] * res[2][0] + m[2][3] * res[3][0];
    ax[3] = m[3][0] * res[0][0] + m[3][1] * res[1][0] + m[3][2] * res[2][0] + m[3][3] * res[3][0];

    ay[0] = m[0][0] * res[0][1] + m[0][1] * res[1][1] + m[0][2] * res[2][1] + m[0][3] * res[3][1];
    ay[1] = m[1][0] * res[0][1] + m[1][1] * res[1][1] + m[1][2] * res[2][1] + m[1][3] * res[3][1];
    ay[2] = m[2][0] * res[0][1] + m[2][1] * res[1][1] + m[2][2] * res[2][1] + m[2][3] * res[3][1];
    ay[3] = m[3][0] * res[0][1] + m[3][1] * res[1][1] + m[3][2] * res[2][1] + m[3][3] * res[3][1];

    az[0] = m[0][0] * res[0][2] + m[0][1] * res[1][2] + m[0][2] * res[2][2] + m[0][3] * res[3][2];
    az[1] = m[1][0] * res[0][2] + m[1][1] * res[1][2] + m[1][2] * res[2][2] + m[1][3] * res[3][2];
    az[2] = m[2][0] * res[0][2] + m[2][1] * res[1][2] + m[2][2] * res[2][2] + m[2][3] * res[3][2];
    az[3] = m[3][0] * res[0][2] + m[3][1] * res[1][2] + m[3][2] * res[2][2] + m[3][3] * res[3][2];
    // Ponto na superficie 
    p[0] = pow(v, 3) * ax[0] + pow(v, 2) * ax[1] + v * ax[2] + ax[3];
    p[1] = pow(v, 3) * ay[0] + pow(v, 2) * ay[1] + v * ay[2] + ay[3];
    p[2] = pow(v, 3) * az[0] + pow(v, 2) * az[1] + v * az[2] + az[3];


    // tangente 1 
    //calculo de M*derivada(u)*M*P
    utx[0]=m[0][0] * resD[0][0] + m[0][1] * resD[1][0] + m[0][2] * resD[2][0] + m[0][3] * resD[3][0];
    utx[1]=m[1][0] * resD[0][0] + m[1][1] * resD[1][0] + m[1][2] * resD[2][0] + m[1][3] * resD[3][0];
    utx[2]=m[2][0] * resD[0][0] + m[2][1] * resD[1][0] + m[2][2] * resD[2][0] + m[2][3] * resD[3][0];
    utx[3]=m[3][0] * resD[0][0] + m[3][1] * resD[1][0] + m[3][2] * resD[2][0] + m[3][3] * resD[3][0];


    uty[0]=m[0][0] * resD[0][1] + m[0][1] * resD[1][1] + m[0][2] * resD[2][1] + m[0][3] * resD[3][1];
    uty[1]=m[1][0] * resD[0][1] + m[1][1] * resD[1][1] + m[1][2] * resD[2][1] + m[1][3] * resD[3][1];
    uty[2]=m[2][0] * resD[0][1] + m[2][1] * resD[1][1] + m[2][2] * resD[2][1] + m[2][3] * resD[3][1];
    uty[3]=m[3][0] * resD[0][1] + m[3][1] * resD[1][1] + m[3][2] * resD[2][1] + m[3][3] * resD[3][1];


    utz[0]=m[0][0] * resD[0][2] + m[0][1] * resD[1][2] + m[0][2] * resD[2][2] + m[0][3] * resD[3][2];
    utz[1]=m[1][0] * resD[0][2] + m[1][1] * resD[1][2] + m[1][2] * resD[2][2] + m[1][3] * resD[3][2];
    utz[2]=m[2][0] * resD[0][2] + m[2][1] * resD[1][2] + m[2][2] * resD[2][2] + m[2][3] * resD[3][2];
    utz[3]=m[3][0] * resD[0][2] + m[3][1] * resD[1][2] + m[3][2] * resD[2][2] + m[3][3] * resD[3][2]; 
    
    
    t1[0]= pow(v, 3) * utx[0] + pow(v, 2) * utx[1] + v * utx[2] + utx[3];
    t1[1]= pow(v, 3) * uty[0] + pow(v, 2) * uty[1] + v * uty[2] + uty[3];
    t1[2]= pow(v, 3) * utz[0] + pow(v, 2) * utz[1] + v * utz[2] + utz[3];



    // tangente 2


    t2[0]=3*pow(v,2)*ax[0] + 2*v*ax[1] + ax[2];
    t2[1]=3*pow(v,2)*ay[0] + 2*v*ay[1] + ay[2];
    t2[2]=3*pow(v,2)*az[0] + 2*v*az[1] + az[2];

    // calculo da normal 
   

  
    cross(t1,t2,n); 
    normalize(n);

}


void planovertxE(float cx, float y, float z, FILE*f){
    float n[3];
    n[0]=-1;
    n[1]=0;
    n[2]=0;
    normalize(n);

    fprintf(f, "%f 0 %f 0 0 %f %f %f\n%f %f %f 0 1 %f %f %f\n%f %f %f 1 1 %f %f %f\n", cx, z/2,n[0],n[1],n[2], cx , y, z/2,n[0],n[1],n[2],cx,y,-z/2,n[0],n[1],n[2]);
    fprintf(f, "%f %f %f 1 1 %f %f %f\n%f 0 %f 1 0 %f %f %f\n%f 0 %f 0 0 %f %f %f\n",cx, y,-z/2,n[0],n[1],n[2],cx,-z/2,n[0],n[1],n[2],cx, z/2, n[0],n[1],n[2]);

}


void planovertxD(float cx, float y, float z, FILE*f){
    float n[3];
    n[0]=1;
    n[1]=0;
    n[2]=0;
    normalize(n);
    fprintf(f, "%f 0 %f 1 0 %f %f %f\n%f %f %f 1 1 %f %f %f\n%f %f %f 0 1 %f %f %f\n", cx, -z/2,n[0],n[1],n[2], cx , y, -z/2,n[0],n[1],n[2], cx, y, z/2,n[0],n[1],n[2]);
    fprintf(f, "%f %f %f 0 1 %f %f %f\n%f 0 %f 0 0 %f %f %f\n%f 0 %f 1 0 %f %f %f\n",cx, y, z/2,n[0],n[1],n[2],cx,z/2,n[0],n[1],n[2],cx, -z/2,n[0],n[1],n[2]);

}



void planovertzF(float x, float y, float cz, FILE*f){
    float n[3];
    n[0]=0;
    n[1]=0;
    n[2]=1;
    normalize(n);
    fprintf(f, "%f 0 %f 0 0 %f %f %f\n%f 0 %f  1 0 %f %f %f\n%f %f %f  1 1 %f %f %f\n",-x/2,cz,n[0],n[1],n[2],x/2,cz,n[0],n[1],n[2],x/2,y,cz,n[0],n[1],n[2]);
    fprintf(f, "%f %f %f 1 1 %f %f %f\n%f %f %f 0 1 %f %f %f\n%f 0 %f 0 0 %f %f %f\n",x/2,y,cz,n[0],n[1],n[2],-x/2,y,cz,n[0],n[1],n[2],-x/2,cz,n[0],n[1],n[2]);

}

void planovertzT(float x, float y, float cz, FILE*f){
    float n[3];
    n[0]=0;
    n[1]=0;
    n[2]=-1;
    normalize(n);
    fprintf(f, "%f 0 %f 0 0 %f %f %f\n%f %f %f 0 1 %f %f %f\n%f %f %f 1 1 %f %f %f\n",-x/2,cz,n[0],n[1],n[2],-x/2,y,cz,n[0],n[1],n[2],x/2,y,cz,n[0],n[1],n[2]);
    fprintf(f, "%f %f %f 1 1 %f %f %f\n%f 0 %f 1 0 %f %f %f\n%f 0 %f 0 0 %f %f %f\n",x/2,y,cz,n[0],n[1],n[2],x/2,cz,n[0],n[1],n[2],-x/2,cz,n[0],n[1],n[2]);

}

void planoC(float x, float y, float z ,FILE*f){
    float n[3];
    n[0]=0;
    n[1]=1;
    n[2]=0;
    normalize(n);
    fprintf(f, "%f %f %f 1 1 %f %f %f\n%f %f %f 0 1 %f %f %f\n%f %f %f 0 0 %f %f %f\n", x/2,y,-z/2,n[0],n[1],n[2],-x/2,y,-z/2,n[0],n[1],n[2],-x/2,y,z/2,n[0],n[1],n[2]);
    fprintf(f, "%f %f %f 1 0 %f %f %f\n%f %f %f 1 1 %f %f %f\n%f %f %f 0 0 %f %f %f\n", x/2,y,z/2,n[0],n[1],n[2],x/2,y,-z/2,n[0],n[1],n[2],-x/2,y,z/2,n[0],n[1],n[2]);
}


void planoB(float x, float y, float z ,FILE*f){
    float n[3];
    n[0]=0;
    n[1]=-1;
    n[2]=0;
    normalize(n);
    fprintf(f, "%f %f %f 0 0 %f %f %f\n%f %f %f 0 1 %f %f %f\n%f %f %f 1 1 %f %f %f\n", -x/2,y,z/2,n[0],n[1],n[2],-x/2,y,-z/2,n[0],n[1],n[2],x/2,y,-z/2,n[0],n[1],n[2]);
    fprintf(f, "%f %f %f 1 1 %f %f %f\n%f %f %f 1 0 %f %f %f\n%f %f %f 0 0 %f %f %f\n", x/2,y,-z/2,n[0],n[1],n[2],x/2,y,z/2,n[0],n[1],n[2],-x/2,y,z/2,n[0],n[1],n[2]);


}

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("Argumentos inválidos!\n");
        return -1;
    }

    if (strcmp(argv[1], "Plane") == 0) {
        if (argc != 4) {
            printf("Argumentos inválidos!\n");
            return -1;
        }
        FILE *f;
        f = fopen(argv[3], "w");
        if (f == NULL) return -1;
        float x = atof(argv[2]);
        planoC(x, 0, x, f);
        fclose(f);
    }


    if (strcmp(argv[1], "Box") == 0) {
        if (argc != 6 && argc != 7) {
            printf("Argumentos inválidos!\n");
            return -1;
        }
        float x = atof(argv[2]);
        float y = atof(argv[3]);
        float z = atof(argv[4]);
        if (argc == 7) {
            int divi = atoi(argv[5]);
            float xs = x / divi;
            float ys = y / divi;
            FILE *f;
            f = fopen(argv[6], "w");
            if (f == NULL) return -1;
            while (xs < x) {
                planovertxE(-x / 2 + xs, y, z, f);
                xs += x / divi;
            }

            while (ys < y) {
                planoC(x, ys, z, f);
                ys += y / divi;
            }

            planovertxE(-x / 2, y, z, f);
            planovertxD(x / 2, y, z, f);
            planovertzF(x, y, z / 2, f);
            planovertzT(x, y, -z / 2, f);
            planoB(x, 0, z, f);
            planoC(x, y, z, f);
            fclose(f);
        } else {
            if (argc != 6) return -1;
            FILE *f;
            f = fopen(argv[5], "w");
            if (f == NULL) return -1;
            planovertxE(-x / 2, y, z, f);
            planovertxD(x / 2, y, z, f);
            planovertzF(x, y, z / 2, f);
            planovertzT(x, y, -z / 2, f);
            planoB(x, 0, z, f);
            planoC(x, y, z, f);
            fclose(f);
        }

    }

   if(strcmp(argv[1],"Cone")==0) {
        if (argc != 7) {printf("Argumentos invalidos\n");return -1;}
        float alpha = 0.0f;
	float r = 0.2;
        float x, z, tx, ty;
        float n[3];
        float height = atof(argv[3]);
        int stacks = atoi(argv[5]), slices = atoi(argv[4]);
        float h = height / stacks;
        float radius = atof(argv[2]);
        FILE* f;
        f=fopen(argv[6],"w");
        if(f==NULL) return -1;
        if (stacks == 0) {
            h = height;
            stacks = 1;
        }

        float alt = 0.0f;
        float raio1 = 0.0f;
        float raio2 = (radius * h) / height;
        float ang = (2 * M_PI) / (float) slices;
  for (int i = 0; i < slices; i++) {
            n[0]=0;
            n[1]=-1;
            n[2]=0;
           
            fprintf(f,"%f 0 %f %f %f %f %f %f\n",radius * sin(alpha), radius * cos(alpha),0.8+r * sin(alpha + ang),0.2+r * cos(alpha + ang),n[0],n[1],n[2]);
            fprintf(f,"0 0 0 0.8 0.2 %f %f %f\n", n[0],n[1],n[2]);
            fprintf(f,"%f 0 %f %f %f %f %f %f\n",radius * sin(alpha + ang), radius * cos(alpha + ang),0.8+r * sin(alpha),0.2+r * cos(alpha), n[0],n[1],n[2]);
            alpha += ang;
        }


        for (int i = 0; i < stacks; i++) {
            alpha = 0;
            for (int j = 0; j < slices; j++) {


                x = raio1 * sin(alpha);
                z = raio1 * cos(alpha);
                tx = j*1.0/slices;
                ty = 1-i*0.6/stacks;
                
                n[0] = x *height/radius;
                n[1] = radius/height;
                n[2] = z *height/radius;
                normalize(n);
                fprintf(f,"%f %f %f %f %f %f %f %f \n", x, height - alt, z,tx, ty,n[0],n[1],n[2]);

                x = raio2 * sin(alpha);
                z = raio2 * cos(alpha);

                tx = j*1.0/slices;
                ty = 1-((i*0.6+0.6)/stacks);
              
                n[0] = x *height/radius;
                n[1] = radius/height;
                n[2] = z *height/radius;
                normalize(n);
                fprintf(f,"%f %f %f %f %f %f %f %f \n",x, height - alt - h, z,tx,ty,n[0],n[1],n[2]);

                x = raio2 * sin(alpha + ang);
                z = raio2 * cos(alpha + ang);

                tx = (j*1.0+1.0)/slices;
                ty = 1-((i*0.6+0.6)/stacks);
                
                n[0] = x *height/radius;
                n[1] = radius/height;
                n[2] = z *height/radius;
                normalize(n);
                fprintf(f,"%f %f %f %f %f %f %f %f \n",x, height - alt - h, z,tx,ty,n[0],n[1],n[2]);

                x = raio1 * sin(alpha);
                z = raio1 * cos(alpha);
                tx = j*1.0/slices;
                ty = 1-(i*0.6/stacks);
               
                n[0] =x *height/radius;
                n[1] = radius/height;
                n[2] = z *height/radius;
                normalize(n);
                fprintf(f,"%f %f %f %f %f %f %f %f \n",x, height - alt, z,tx, ty,n[0],n[1],n[2]);

                x = raio2 * sin(alpha + ang);
                z = raio2 * cos(alpha + ang);
                tx = j*1.0/slices + (1.0/slices);
                ty = 1-((i*0.6+0.6)/stacks);
               
                n[0] = x *height/radius;
                n[1] = radius/height;
                n[2] = z *height/radius;
                normalize(n);
                fprintf(f,"%f %f %f %f %f %f %f %f \n",x, height - alt - h,z,tx,ty,n[0],n[1],n[2]);

                x = raio1 * sin(alpha + ang);
                z = raio1 * cos(alpha + ang);
                tx = (j*1.0+1.0)/slices;
                ty = 1-((i*0.6)/stacks);
             

                n[0] = x *height/radius;
                n[1] = radius/height;
                n[2] = z *height/radius;
                normalize(n);
                fprintf(f,"%f %f %f %f %f %f %f %f \n",x, height - alt, z,tx,ty,n[0],n[1],n[2]);

                alpha += ang;
            }
            alt += h;
            raio1 = raio2;
            raio2 = radius * (alt + h) / height;

        }
        fclose(f);
    }


    if(strcmp(argv[1],"Sphere")==0){
            if(argc != 6){printf("Argumentos inválidos!\n");return -1;}
        float raiod = atof(argv[2]);
        int slices = atoi(argv[3]);
        int stacks = atoi(argv[4]);
        FILE *f;
        f=fopen(argv[5],"w");
        if(f==NULL) return -1;
        float alpha;
        float anga= (2*M_PI)/(float)slices;
        float beta = M_PI/2.0;
        float angb=-(M_PI/stacks);
        int i,j;float x,y,z,nx,ny,nz,tx,ty;
        for(i=0;i<stacks;i++){
            alpha=0;
            for(j=0;j<slices;j++){
                x=raiod*cos(beta)*sin(alpha);
                y=raiod*sin(beta);
                z=raiod*cos(beta)*cos(alpha);
                nx = cos(beta)*sin(alpha);
                ny = sin(beta);
                nz = cos(beta)*cos(alpha);
                tx = j*1.0/slices;
                ty = 1-i*1.0/stacks;
                fprintf(f, "%f %f %f %f %f %f %f %f\n",x,y,z, tx, ty, nx, ny, nz);
                x=raiod*cos(beta+angb)*sin(alpha);
                y=raiod*sin(beta+angb);
                z=raiod*cos(beta+angb)*cos(alpha);
                nx = cos(beta+angb)*sin(alpha);
                ny = sin(beta+angb);
                nz = cos(beta+angb)*cos(alpha);
                tx = j*1.0/slices;
                ty = 1-((i*1.0+1.0)/stacks);
                fprintf(f, "%f %f %f %f %f %f %f %f\n",x,y,z, tx, ty, nx, ny, nz);
                x=raiod*cos(beta+angb)*sin(alpha+anga);
                y=raiod*sin(beta+angb);
                z=raiod*cos(beta+angb)*cos(alpha+anga);
                nx = cos(beta+angb)*sin(alpha+anga);
                ny = sin(beta+angb);
                nz = cos(beta+angb)*cos(alpha+anga);
                tx = (j*1.0+1.0)/slices ;
                ty = 1-((i*1.0+1.0)/stacks);
                fprintf(f, "%f %f %f %f %f %f %f %f\n",x,y,z, tx, ty, nx, ny, nz);
                x=raiod*cos(beta)*sin(alpha);
                y=raiod*sin(beta);
                z=raiod*cos(beta)*cos(alpha);
                nx = cos(beta)*sin(alpha);
                ny = sin(beta);
                nz = cos(beta)*cos(alpha);
                tx = j*1.0/slices;
                ty = 1-(i*1.0/stacks);
                fprintf(f, "%f %f %f %f %f %f %f %f\n",x,y,z, tx, ty, nx, ny, nz);
                x=raiod*cos(beta+angb)*sin(alpha+anga);
                y=raiod*sin(beta+angb);
                z=raiod*cos(beta+angb)*cos(alpha+anga);
                nx = cos(beta+angb)*sin(alpha+anga); 
                ny = sin(beta+angb);
                nz = cos(beta+angb)*cos(alpha+anga);
                tx = j*1.0/slices + (1.0/slices);
                ty = 1-((i*1.0+1.0)/stacks);
                fprintf(f, "%f %f %f %f %f %f %f %f\n",x,y,z, tx, ty, nx, ny, nz);

                x=raiod*cos(beta)*sin(alpha+anga);
                y=raiod*sin(beta);
                z=raiod*cos(beta)*cos(alpha+anga);
                nx = cos(beta)*sin(alpha+anga);
                ny = sin(beta);
                nz = cos(beta)*cos(alpha+anga);
                tx = (j*1.0+1.0)/slices;
                ty = 1-((i*1.0)/stacks);
                fprintf(f, "%f %f %f %f %f %f %f %f\n",x,y,z, tx, ty, nx, ny, nz);

                alpha+=anga;
            }
            beta+=angb;

        }
        fclose(f);

    }


    if (strcmp(argv[1], "Torus") == 0) {
        if (argc != 7) {
            printf("Argumentos inválidos!\n");
            return -1;
        }

        float innerRadius = atof(argv[2]), outterRadius = atof(argv[3]);
        int sides = atoi(argv[4]), rings = atoi(argv[5]);
        float beta = (2 * M_PI) / rings;
        float alpha = (2 * M_PI) / sides, angH = 0, angV = 0, px, py, pz,s,t;
        FILE *f;
        f = fopen(argv[6], "w");
        if (f == NULL) return -1;
        for (int i = 0; i < rings; i++) {
            for (int j = 0; j < sides; j++) {
                px = (outterRadius + (innerRadius * cos(angH))) * cos(angV + beta);
                py = (outterRadius + (innerRadius * cos(angH))) * sin(angV + beta);
                pz = innerRadius * sin(angH);
                n[0] = cos(angH) * cos(angV + beta);
                n[1] = cos(angH) * sin(angV + beta);
                n[2] = sin(angH);
                s=(j*1.0)/sides; 
                t=(i+1.0)/rings;
                fprintf(f,"%f %f %f %f %f %f %f %f \n",px,py,pz,s,t,n[0],n[1],n[2]);
                
                px = (outterRadius + (innerRadius * cos(angH + alpha))) * cos(angV + beta);
                py = (outterRadius + (innerRadius * cos(angH + alpha))) * sin(angV + beta);
                pz = innerRadius * sin(angH + alpha);
                n[0] = cos(angH+alpha) * cos(angV + beta);
                n[1] = cos(angH+alpha) * sin(angV + beta);
                n[2] = sin(angH+alpha);
                s=(j+1.0)/sides; 
                t=(i+1.0)/rings;
                fprintf(f,"%f %f %f %f %f %f %f %f \n",px,py,pz,s,t,n[0],n[1],n[2]);
                
                px = (outterRadius + (innerRadius * cos(angH))) * cos(angV);
                py = (outterRadius + (innerRadius * cos(angH))) * sin(angV);
                pz = innerRadius * sin(angH);
                n[0]=cos(angH) * cos(angV);
                n[1]=cos(angH) * sin(angV);
                n[2]=sin(angH);
                s=(j*1.0)/sides; 
                t=(i*1.0)/rings;
                fprintf(f,"%f %f %f %f %f %f %f %f \n",px,py,pz,s,t,n[0],n[1],n[2]);
                
                px = (outterRadius + (innerRadius * cos(angH + alpha))) * cos(angV);
                py = (outterRadius + (innerRadius * cos(angH + alpha))) * sin(angV);
                pz = innerRadius * sin(angH + alpha);
                n[0]=cos(angH+alpha)*cos(angV);
                n[1]=cos(angH+alpha)*sin(angV);
                n[2]=sin(angH+alpha);
                s=(j+1.0)/sides; 
                t=(i*1.0)/rings;
                
                fprintf(f,"%f %f %f %f %f %f %f %f \n",px,py,pz,s,t,n[0],n[1],n[2]);
               
                px = (outterRadius + (innerRadius * cos(angH))) * cos(angV);
                py = (outterRadius + (innerRadius * cos(angH))) * sin(angV);
                pz = innerRadius * sin(angH);
                n[0] = cos(angH) * cos(angV);
                n[1] = cos(angH) * sin(angV);
                n[2] = sin(angH);
                s=(j*1.0)/sides; 
                t=(i*1.0)/rings;
                fprintf(f,"%f %f %f %f %f %f %f %f \n",px,py,pz,s,t,n[0],n[1],n[2]);
               
                px = (outterRadius + (innerRadius * cos(angH + alpha))) * cos(angV + beta);
                py = (outterRadius + (innerRadius * cos(angH + alpha))) * sin(angV + beta);
                pz = innerRadius * sin(angH + alpha);
                n[0] = cos(angH+alpha) * cos(angV + beta);
                n[1] = cos(angH+alpha) * sin(angV + beta);
                n[2] = sin(angH+alpha);
                s=(j+1.0)/sides; 
                t=(i+1.0)/rings;
                fprintf(f,"%f %f %f %f %f %f %f %f \n",px,py,pz,s,t,n[0],n[1],n[2]);
               
                angH += alpha;
            }
            angV += beta;
        }
        fclose(f);
    }

    if (!strcmp(argv[1], "Bezier")) {
        if (argc != 5) {
            printf("Argumentos Insuficientes\n");
            return -1;
        }

        int tLevel = atoi(argv[3]);

	float s,t;
        readFile(argv[2]);

        FILE *f;
        f = fopen(argv[4], "w");

        for (int h = 0; h < patch.size(); h += 16) {
            for (int i = 0; i < tLevel; i++) {
                for (int j = 0; j < tLevel; j++) {
                    procPatch(i, j, tLevel, h);
                    s= j*1.0/tLevel; 
                    t= i*1.0/tLevel;
                    fprintf(f,"%f %f %f %f %f %f %f %f \n", p[0], p[1], p[2],s,t,n[0],n[1],n[2]);

                    procPatch(i, j + 1, tLevel, h);
                    s= j+1.0/tLevel; 
                    t= i*1.0/tLevel;
                    fprintf(f,"%f %f %f %f %f %f %f %f \n", p[0], p[1], p[2],s,t,n[0],n[1],n[2]);

                    procPatch(i + 1, j, tLevel, h);
                    s= j*1.0/tLevel; 
                    t= i+1.0/tLevel;
                    fprintf(f,"%f %f %f %f %f %f %f %f \n", p[0], p[1], p[2],s,t,n[0],n[1],n[2]);


                    procPatch(i, j + 1, tLevel, h);
                    s= j+1.0/tLevel; 
                    t= i*1.0/tLevel;
                    fprintf(f,"%f %f %f %f %f %f %f %f \n", p[0], p[1], p[2],s,t,n[0],n[1],n[2]);

                    procPatch(i + 1, j + 1, tLevel, h);
                    s= j+1.0/tLevel;
                    t= i+1.0/tLevel;
                    fprintf(f,"%f %f %f %f %f %f %f %f \n", p[0], p[1], p[2],s,t,n[0],n[1],n[2]);

                    procPatch(i + 1, j, tLevel, h);
                    s= j*1.0/tLevel; 
                    t= i+1.0/tLevel;
                    fprintf(f,"%f %f %f %f %f %f %f %f \n", p[0], p[1], p[2],s,t,n[0],n[1],n[2]);

                }

            }

        }
        fclose(f); 


    }


    return 1;
}
