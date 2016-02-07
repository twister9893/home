/****************************/
/*       tmplprog.cpp      	*/
/****************************/
#include <QtGui/QApplication>
#include <sys/types.h>
#include <linux/unistd.h>
//#include <QTextCodec>

#include "dataviewprog.h"

static	DTW startDialog			= NULL;

static bool runMainWindow		= false;

static void pressMouseITS(PressMouseITS* p)
{
	if((p->button & Button1))
	{
		fprintf(stdout, "skol targ %d, %d\n", p->target.sour, p->target.targ);
	}
}


int main (int argc, char **argv)
{
	//QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	//QTextCodec::setCodecForCStrings(codec);
	//QTextCodec::setCodecForLocale(codec);
	//QTextCodec::setCodecForTr(codec);
	taskList[0]=0;
	taskList[1]=iTP_Task;
	taskList[2]=bTP_Task;
	
	if(setProg(argc,argv,(void**)taskList, taskListLen, noDF, noLF))
	{
		return 1;
	}
	return 0;
}
/*==========================*/

static void functionTask(TRANDATA *trnptr, UCHAR numb)
{
	MESS_TMPL_STRUC *dataPtr = (MESS_TMPL_STRUC*)trnptr;
	
	fprintf(stdout, "Tmplprog. net mess.\n");

	switch(dataPtr->messType)
	{
		case mess_Start:
		{
			fprintf(stdout, "Get mess start.\n");
		
		}
		break;
		
		case mess_Stop:
		{
			fprintf(stdout, "Get mess stop.\n");
		}
		break;
	}
}

static void closeCurrentWidget(int ID)
{
	diCloseCurrentWindow();
}


static int count_thread1 = 0;

void thread_func(int number = 0)
{
	int argc = 1;
	
	char *argv[] = {"./12345", "-display", "192.168.1.104:1.0"};

	QApplication a(argc, argv);

	setlocale(LC_NUMERIC, "C");
	
	QDomDocument configDoc = parseXmlFile("../data/sopr/dataviewConfig.xml");
	QDomElement abonentListConfig = configDoc.firstChildElement().firstChildElement("abonentList");
	if(abonentListConfig.isNull()) {
		QMessageBox::critical(NULL, QString::fromUtf8("Ошибка"), QString::fromUtf8("Ошибка чтения настроечного файла"));
		return;
	}
	QDir directory(abonentListConfig.attribute("directory", "./"), abonentListConfig.attribute("filter", "*-View.xml"), QDir::Name, QDir::Readable);
	AbonentList *abonentList = new AbonentList(directory.entryInfoList(QDir::Files | QDir::Readable, QDir::Name), abonentListConfig.attribute("groupSeparator", " "));
	abonentList->move(1200, 10);
	abonentList->resize(diGetMaxWidthWindow(), diGetSplit()*2 - 50);
	int result = abonentList->exec();

	if(result == QDialog::Accepted) {
		QDomElement dataViewConfig = configDoc.firstChildElement().firstChildElement("dataView");
		DataView *dataView = new DataView(abonentList->getViewFile());
		AbonentNetworkTool *networkTool = new AbonentNetworkTool(dataView);

		QObject::connect(networkTool, SIGNAL(gotData(int,QList<QVariant>,QDateTime)), dataView, SLOT(slot_setData(int,QList<QVariant>,QDateTime)));
		QObject::connect(networkTool, SIGNAL(gotData(int,QList<QVariant>,QDateTime)), dataView, SLOT(slot_updateGeometry()));

		networkTool->setAdditionalInfo(QVariant(abonentList->getAbonent()));
		networkTool->start(dataViewConfig.attribute("updateInterval", "1000").toInt());

		dataView->show();
	} else {
		//Тут мог бы быть выход
	}
	cout << "dataviewprog.e exit with code:" << a.exec() << endl;
}

void setRunMainWindow()
{
	runMainWindow = true;
}


static void buttonPusk(int ID)
{
	cout << "create thread" << endl;
	//count_thread1++;
	//boost::thread *my_thread1 = new boost::thread(&thread_func, count_thread1);
	//list_threads.push_back(my_thread1);

	cout << "after start" << endl;
}

void thread_func2(int number = 0)
{
	//thread_func(1);
	buttonPusk(1);
	/*
	//int argc = 3;
	int argc = 1;

	char *argv[] = {"./12345", "-display", "192.168.1.104:1.0"};

	QApplication a(argc, argv);

	QMainWindow win;

	win.resize(300, 300);
	win.move(200, 200);
	win.show();

	a.exec();
	*/

}

static bool isRunLoopTask = true;

void buttonStop(int ID)
{

	if(isRunLoopTask)
	{
		if(contTran(offTask, numbList[1], noData)->report != yesCom )
		{
			printf("Error tmplprog. Then stop loop mudule.\n");
		}
	}
	else
	{
		if(contTran(onTask, numbList[1], noData)->report != yesCom )
		{
			printf("Error tmplprog. Then start loop mudule.\n");
		}
	}
	
	isRunLoopTask = !isRunLoopTask;
}

static void newDialog()
{
	fprintf(stdout, "newDialog begin\n");
	thread_func(1);
	fprintf(stdout, "newDialog end\n");
}


static void functionNoData()
{
}

static void functionPPV(TRANDATA *trnptr, UCHAR numb)
{
}

StartInterface 
(
	"tmplprog", 
	iTP_Task, 
	0, 
	newDialog, 
	functionTask, 
	functionTask, 
	functionNoData, 
	functionPPV,
	NULL
)

	Handler(ID_Button_PUSK,			buttonPusk)
	Handler(ID_Button_STOP,			buttonStop)
	Handler(ID_StartDialog,			closeCurrentWidget)
	PressMouseITS(pressMouseITS)

FinishInterface((TASKDATA*(*)(UCHAR))TP_Param)

/*==========================*/
TASKDATA *bTP_Task (UCHAR initNumb)
{
	while((boxList[1]=contTran(startTask,initNumb,0)))
	{
	/*..........................*/

		if(runMainWindow)
		{
			cout << "Run main window" << endl;

			thread_func(1);

			runMainWindow = false;
		}

	/*..........................*/
	}
	numbList[1]=initNumb;
	return 0;
}

/*==========================*/
TASKDATA *TP_Param (UCHAR initNumb)
{
	if(!initNumb) return 0;
	/*..........................*/
	if((dataList[0]=(TASKDATA*)allocShm(sizeof(TASKDATA))) <= 0)
		return 0;
	dataList[0]->inDataLen = sizeof(INDATA);
	if((dataList[0]->inDataPtr=allocShm(dataList[0]->inDataLen)) <= 0)
		return 0;
	dataList[0]->outDataLen		= 0;
	dataList[0]->outDataPtr		= 0;
	dataList[0]->paramListLen	= 1;
	if((dataList[0]->paramList=(PARAMFORM*)allocShm(dataList[0]->paramListLen*sizeof(PARAMFORM)))<=0)
	{
		return 0;
	}
	strcpy(dataList[0]->paramList[0].paramName,"Regim(1-4)");
	dataList[0]->paramList[0].paramType			= 'i';
	dataList[0]->paramList[0].presSig				= 0;
	dataList[0]->paramList[0].paramCharQuan	= 1;
	dataList[0]->paramList[0].minValue			= 1;
	dataList[0]->paramList[0].maxValue			= 4;
	dataList[0]->paramList[0].defValue			= 0;
	dataList[0]->paramList[0].inDataPtr			= &((INDATA*)dataList[0]->inDataPtr)->Regim;
	/*..........................*/
	return dataList[0];
}

/****************************/
/*   end tmplprog.c         */
/****************************/
