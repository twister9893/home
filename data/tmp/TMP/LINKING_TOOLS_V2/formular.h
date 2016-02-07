class Formular {
public:
    Formular();
    Formular(char *data);
    Formular(Formular &formular);
    ~Formular();
    
    void setField(QVariant field, QString name);
    void setField(QVariant field, int number);
    
    QVariant getField(QString name);
    QVariant getField(uint number);
}