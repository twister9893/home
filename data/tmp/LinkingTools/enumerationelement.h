#ifndef ENUMERATIONELEMENT_H
#define ENUMERATIONELEMENT_H

#include <QString>

class EnumerationElement {
    public:
        EnumerationElement(int code = -1, QString acronym = QString(), QString transcript = QString());

        void setCode(int code);
        void setAcronym(QString acronym);
        void setTranscript(QString trascript);

        int getCode();
        QString getAcronym();
        QString getTranscript();

    private:
        int 	m_code;
        QString m_acronym;
        QString m_transcript;
};

#endif // ENUMERATIONELEMENT_H
