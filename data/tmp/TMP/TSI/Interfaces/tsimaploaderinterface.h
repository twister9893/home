#ifndef TSIMAPLOADERINTERFACE_H
#define TSIMAPLOADERINTERFACE_H

class TsiMapLoaderInterface : public TsiBasicInterface {
public:
    TsiMapLoaderInterface() {}
    virtual ~TsiMapLoaderInterface() {}
};

Q_DECLARE_INTERFACE(TsiMapLoaderInterface, "ru.lan.TSI.TsiMapLoaderInterface/1.0")

#endif // TSIMAPLOADERINTERFACE_H
