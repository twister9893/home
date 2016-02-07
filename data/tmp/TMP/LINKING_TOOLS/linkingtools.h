#ifndef LINKINGTOOLS_H
#define LINKINGTOOLS_H

#include <QThread>

#include "formulareditor.h"
#include "ui_linkingtools.h"

class LinkingTools : public QDialog, private Ui::LinkingTools {
        Q_OBJECT
    public:
        explicit LinkingTools(QWidget *parent = 0);

    public slots:
        void slot_openFormularEditor();

    private:
        void loadModules();

        FormularEditor *m_formularEditor;
};

#endif // LINKINGTOOLS_H
