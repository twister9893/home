#include "enumerationelement.h"

EnumerationElement::EnumerationElement(int code, QString acronym, QString transcript) {
    setCode(code);
    setAcronym(acronym);
    setTranscript(transcript);
}

void EnumerationElement::setCode(int code) {
    m_code = code;
}

void EnumerationElement::setAcronym(QString acronym) {
    m_acronym = acronym;
}

void EnumerationElement::setTranscript(QString trascript) {
    m_transcript = trascript;
}

int EnumerationElement::getCode() {
    return m_code;
}

QString EnumerationElement::getAcronym() {
    return m_acronym;
}

QString EnumerationElement::getTranscript() {
    return m_transcript;
}
