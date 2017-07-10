#include "tinyxml.h"
#include <iostream>
#include <fstream>
#include <stdio.h>


#define TIXML_USE_STL
using namespace std;
#define N 100


string parseFile(TiXmlElement *x) {

    string value = x->Value();
    string actions = "";


    TiXmlElement *next = x->NextSiblingElement();
    TiXmlElement *child = x->FirstChildElement();

    TiXmlAttribute *attribute = x->FirstAttribute();

    actions += value;
    if (value == "translate" || value == "rotate") {
        if (!strcmp(attribute->Name(), "time")) actions += "1";
    }
    if (value == "translate" || value == "rotate" || value == "scale" || value == "model" || value == "point" || value == "light")
        actions += ' ';

    while (attribute) {
        if(value == "light"){
            if ((string) attribute->Name() == "type" || (string) attribute->Name() == "posX" || (string) attribute->Name() == "posY"
                  || (string) attribute->Name() == "posZ")
                actions += (string) attribute->Value() + ' ';
            else {
                actions += (string) attribute->Name() + "=";
                actions += (string) attribute->Value() + ' ';
            }
        }else {
            if (value == "model") {
                if ((string) attribute->Name() == "file")
                    actions += (string) attribute->Value() + ' ';
                else {
                    actions += (string) attribute->Name() + "=";
                    actions += (string) attribute->Value() + ' ';
                }
            } else {
                if (value == "translate" || value == "rotate" || value == "scale" || value == "point" ||
                    value == "light") {
                    //if(value == "translate" && attribute->Name() == "time") cout << "Entrou";
                    actions += (string) attribute->Value() + ' ';
                } else {
                    //actions += (string) attribute->Name() + '=';
                    actions += (string) attribute->Value();
                }
            }
        }
        attribute = attribute->Next();
    }
    actions += '\n';

    if (child) {
        actions += parseFile(child);
        actions += '/' + value + '\n';
    }
    if (next) actions += parseFile(next);

    return actions;
}

/*
int main(int argc, char **argv) {

    const char *filename;

    filename = argv[1];
    TiXmlDocument file;
    if (!file.LoadFile(filename)) {
        cerr << file.ErrorDesc() << endl;
        return -1;
    }

    TiXmlElement *scene = file.FirstChildElement("scene");
    cout << parseFile(scene);

    //parseFile(argv[1]);
}*/
