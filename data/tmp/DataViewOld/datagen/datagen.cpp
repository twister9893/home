#include "../../include/tinyxml.h"
#include <QString>
#include <QStringList>
#include <QFile>
#include <QDebug>

QString createValidName(const QString& str)
{
    QString fn="";
    int i, rU, rL;
    QString validChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890_";
    QString rusUpper = QString::fromUtf8("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЫЭЮЯ");
    QString rusLower = QString::fromUtf8("абвгдеёжзийклмнопрстуфхцчшщыэюя");
    QStringList latUpper, latLower;
    latUpper <<"A"<<"B"<<"V"<<"G"<<"D"<<"E"<<"E"<<"Zh"<<"Z"<<"I"<<"J"<<"K"<<"L"<<"M"<<"N"
    <<"O"<<"P"<<"R"<<"S"<<"T"<<"U"<<"F"<<"H"<<"C"<<"Ch"<<"Sh"<<"Sh"<<"I"<<"E"<<"Yu"<<"Ya";
    latLower <<"a"<<"b"<<"v"<<"g"<<"d"<<"e"<<"e"<<"zh"<<"z"<<"i"<<"j"<<"k"<<"l"<<"m"<<"n"
    <<"o"<<"p"<<"r"<<"s"<<"t"<<"u"<<"f"<<"h"<<"c"<<"ch"<<"sh"<<"sh"<<"i"<<"e"<<"yu"<<"ya";

    if (str.isEmpty())
        return "noName";
    for (i=0; i < str.size(); ++i)
    {
        if ( validChars.contains(str[i]) )
            fn = fn + str[i];
        else if (str[i] == ' ')
            fn = fn + "_";
        else
        {
            rU = rusUpper.indexOf(str[i]);
            rL = rusLower.indexOf(str[i]);
            if (rU >= 0)
                fn = fn + latUpper[rU];
            else if (rL >= 0)
                fn = fn + latLower[rL];
        }
    }
    return fn;
}

void dumpElems(TiXmlElement* group,QTextStream& generatorStream)
{
	for(TiXmlElement* field=group->FirstChildElement();field;field=field->NextSiblingElement())
	{
		int ccnt=0;
		field->Attribute("childCount",&ccnt);
		if(ccnt) // Если группа
		{
			dumpElems(field,generatorStream);
			continue;
		}
		char name[256]="";
		strcpy(name,field->Attribute("name"));
		generatorStream << "<<f.get" << createValidName(QString::fromUtf8(name)) << "()";
	}
}

int main(int argc, char* argv[])
{
	if(argc<3)
	{
		puts("Usage: datagen infile.xml outfile.cpp");
		return 1;
	}

	TiXmlDocument doc(argv[1]);
	if(!doc.LoadFile())
	{
		printf("datagen: ERROR open %s\n",argv[1]);
		return 1;
	}
	TiXmlElement* root = doc.FirstChildElement();
	if(!root)
	{
		printf("datagen: ERROR no root in %s\n",argv[1]);
		return 1;
	}

	QFile file(argv[2]);
    if (!file.open(QIODevice::WriteOnly))
	{
		printf("datagen: Error open file %s\n",argv[2]);
		return 1;
	}
    QTextStream generatorStream (&file);
    generatorStream.setCodec("UTF-8");

//	generatorStream << "QList<QVariant> data;\n";
	int curg=0;
	generatorStream << "QList<QVariant> tmp;";
	for(TiXmlElement* group=root->FirstChildElement();group;group=group->NextSiblingElement())
	{
		char name[256]="";
		strcpy(name,group->Attribute("name"));

		generatorStream << "\n// " << QString::fromUtf8(name) << "\n";
		generatorStream << "tmp.clear();";
		generatorStream << "\ntmp";

		dumpElems(group,generatorStream);

		generatorStream << ";\ntableNumbers.append(" << curg++ << ");";
		generatorStream << "\ndata.append(tmp);\n";
	}

	return 0;
}
