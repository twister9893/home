#ifndef TSIDATABASEINTERFACE_H
#define TSIDATABASEINTERFACE_H

class TsiDataBaseInterface /*: public TsiBasicInterface*/ {
public:
    TsiDataBaseInterface() {}
    virtual ~TsiDataBaseInterface() {}

    virtual const QString getPluginName() = 0;
};

Q_DECLARE_INTERFACE(TsiDataBaseInterface, "ru.lan.TSI.TsiDataBaseInterface/1.0")

#endif // TSIDATABASEINTERFACE_H
