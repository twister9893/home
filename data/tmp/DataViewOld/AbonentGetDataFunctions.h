#ifndef ABONENTGETDATAFUNCTIONS_H
#define ABONENTGETDATAFUNCTIONS_H

#include "../include/sysmath.h"

#include "../include/abon/SUGET.h"
#include "../include/abon/Suget_WIXDR.h"

#include "../include/abon/GNOM.h"
#include "../include/abon/Gnom.h"

#include "../include/abon/SUMF.h"
#include "../include/abon/SUMF_Header.h"
#include "../include/abon/SUMF_IP1.h"
#include "../include/abon/SUMF_IP2.h"
#include "../include/abon/SUMF_IP3.h"
#include "../include/abon/SUMF_IP4.h"
#include "../include/abon/SUMF_IP41.h"
#include "../include/abon/SUMF_IP44.h"
#include "../include/abon/SUMF_IP45.h"
#include "../include/abon/SUMF_IP6.h"
#include "../include/abon/SUMF_IP8.h"
#include "../include/abon/SUMF_IP10.h"
#include "../include/abon/SUMF_IP11.h"
#include "../include/abon/SUMF_IP12.h"
#include "../include/abon/SUMF_IP34.h"

#include "../include/abon/MUS.h"
//#include "../include/abon/MUS_Header.h"
//#include "../include/abon/MUS_IP3	.h"
#include "../include/abon/MUS_IP37.h"
#include "../include/abon/MUS_IP40.h"
#include "../include/abon/MUS_IP60.h"
#include "../include/abon/MUS_IP61.h"


#include "../include/abon/SSPK.h"
#include "../include/abon/SSPK_DSSGM.h"
#include "../include/abon/SSPK_DTSSK.h"
#include "../include/abon/SSPK_DTSSV.h"
#include "../include/abon/SSPK_DTSSP.h"

#include "../include/abon/MR231.h"
#include "../include/abon/MR231_Sost.h"
#include "../include/abon/MR231_Targ.h"

#include "../include/abon/SOEJ.h"
#include "../include/abon/SOEJ_Header.h"
#include "../include/abon/SOEJ_ToSIGMA.h"
#include "../include/abon/SOEJ_FromSigma.h"

#include "../include/abon/PAKET.h"
#include "../include/abon/PAKET_OUT.h"
#include "../include/abon/PAKET_IN.h"

#include "../include/abon/MINOTAVR.h"
#include "../include/abon/MINOTAVR_Header.h"
#include "../include/abon/MINOTAVR_1001.h"
#include "../include/abon/MINOTAVR_1002.h"
#include "../include/abon/MINOTAVR_1003.h"
#include "../include/abon/MINOTAVR_1004.h"
#include "../include/abon/MINOTAVR_1005.h"
#include "../include/abon/MINOTAVR_1006.h"
#include "../include/abon/MINOTAVR_1007.h"
#include "../include/abon/MINOTAVR_2001.h"
#include "../include/abon/MINOTAVR_2002.h"
#include "../include/abon/MINOTAVR_2003.h"
#include "../include/abon/MINOTAVR_2004.h"
#include "../include/abon/MINOTAVR_2005.h"
#include "../include/abon/MINOTAVR_2006.h"
#include "../include/abon/MINOTAVR_2007.h"
#include "../include/abon/MINOTAVR_2008.h"
#include "../include/abon/MINOTAVR_2009.h"

extern "C"
{
	#include "../include/sysprog.h"
	#include "../soprdir/adapeth.h"
}

#include <QDateTime>
#include <QDebug>

enum
{
	ABON_MR231_Sost = 0,
	ABON_MR231_Targ,
	ABON_GNOM,

	ABON_MINOTAVR_1001,
	ABON_MINOTAVR_1002,
	ABON_MINOTAVR_1003,
	ABON_MINOTAVR_1004,
	ABON_MINOTAVR_1005,
	ABON_MINOTAVR_1006,
	ABON_MINOTAVR_1007,
	ABON_MINOTAVR_2001,
	ABON_MINOTAVR_2002,
	ABON_MINOTAVR_2003,
	ABON_MINOTAVR_2004,
	ABON_MINOTAVR_2005,
	ABON_MINOTAVR_2006,
	ABON_MINOTAVR_2007,
	ABON_MINOTAVR_2008,
	ABON_MINOTAVR_2009,

	ABON_MUS_IP1,
	ABON_MUS_IP11,
	ABON_MUS_IP12,
	ABON_MUS_IP2,
	ABON_MUS_IP3,
	ABON_MUS_IP37,
	ABON_MUS_IP4,
	ABON_MUS_IP40,
	ABON_MUS_IP60,
	ABON_MUS_IP61,

	ABON_PAKET_IN,
	ABON_PAKET_OUT,
	ABON_SOEJ_FROMSIGMA,
	ABON_SOEJ_TOSIGMA,
	ABON_SSPK_DSSGM,
	ABON_SSPK_DTSSK,
	ABON_SSPK_DTSSP,
	ABON_SSPK_DTSSV,
	ABON_SUMF_IP1,
	ABON_SUMF_IP10,
	ABON_SUMF_IP11,
	ABON_SUMF_IP12,
	ABON_SUMF_IP2,
	ABON_SUMF_IP34,
	ABON_SUMF_IP35,
	ABON_SUMF_IP4,
	ABON_SUMF_IP41,
	ABON_SUMF_IP42,
	ABON_SUMF_IP43,
	ABON_SUMF_IP44,
	ABON_SUMF_IP45,
	ABON_SUMF_IP6,
	ABON_SUMF_IP61,
	ABON_SUMF_IP8,
	ABON_SUGET
};

#define NSSPK 91
#define NGNOM 92
#define NSoej 90
#define NMtpk 45
#define NPaket 45
#define NMinotavr 34

void uMINOTAVR_1001(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	MINOTAVR *buf;

	if(workPtr->sourList[NMinotavr]->addLen <= 0)
	{
		return;
	}

	buf = (MINOTAVR *)((char*)workPtr->sourList[NMinotavr]->addPtr + 2*sizeof(SHAPethMMO));
	MINOTAVR_1001 f((char*)buf->MINOTAVR_1001, f.getSize());


	receiveTime.setTime_t(buf->arrayTime[1]);

	#include "./datagen/uMINOTAVR_1001.h"

}
void uMINOTAVR_1002(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	MINOTAVR *buf;



	if(workPtr->sourList[NMinotavr]->addLen <= 0)
	{
		return;
	}


	buf = (MINOTAVR *)((char*)workPtr->sourList[NMinotavr]->addPtr + 2*sizeof(SHAPethMMO));
	MINOTAVR_1002 f((char*)buf->MINOTAVR_1002, f.getSize());



	receiveTime.setTime_t(buf->arrayTime[TIME_1002]);

	#include "./datagen/uMINOTAVR_1002.h"

}

void uMINOTAVR_1003(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	MINOTAVR *buf;



	if(workPtr->sourList[NMinotavr]->addLen <= 0)
	{
		return;
	}


	buf = (MINOTAVR *)((char*)workPtr->sourList[NMinotavr]->addPtr + 2*sizeof(SHAPethMMO));
	MINOTAVR_1003 f((char*)buf->MINOTAVR_1003, f.getSize());



	receiveTime.setTime_t(buf->arrayTime[TIME_1003]);

	#include "./datagen/uMINOTAVR_1003.h"

}
void uMINOTAVR_1004(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	MINOTAVR *buf;

	if(workPtr->sourList[NMinotavr]->addLen <= 0)
	{
		return;
	}


	buf = (MINOTAVR *)((char*)workPtr->sourList[NMinotavr]->addPtr + 2*sizeof(SHAPethMMO));
	MINOTAVR_1004 f((char*)buf->MINOTAVR_1004, f.getSize());




	receiveTime.setTime_t(buf->arrayTime[TIME_1004]);

	#include "./datagen/uMINOTAVR_1004.h"

}
void uMINOTAVR_1005(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	MINOTAVR *buf;

	if(workPtr->sourList[NMinotavr]->addLen <= 0)
	{
		return;
	}


	buf = (MINOTAVR *)((char*)workPtr->sourList[NMinotavr]->addPtr + 2*sizeof(SHAPethMMO));
	MINOTAVR_1005 f((char*)buf->MINOTAVR_1005, f.getSize());




	receiveTime.setTime_t(buf->arrayTime[TIME_1005]);

	#include "./datagen/uMINOTAVR_1005.h"

}

void uMINOTAVR_1006(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	MINOTAVR *buf;

	if(workPtr->sourList[NMinotavr]->addLen <= 0)
	{
		return;
	}


	buf = (MINOTAVR *)((char*)workPtr->sourList[NMinotavr]->addPtr + 2*sizeof(SHAPethMMO));
	MINOTAVR_1006 f((char*)buf->MINOTAVR_1006, f.getSize());




	receiveTime.setTime_t(buf->arrayTime[TIME_1006]);

	#include "./datagen/uMINOTAVR_1006.h"

}

void uMINOTAVR_1007(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	MINOTAVR *buf;

	if(workPtr->sourList[NMinotavr]->addLen <= 0)
	{
		return;
	}


	buf = (MINOTAVR *)((char*)workPtr->sourList[NMinotavr]->addPtr + 2*sizeof(SHAPethMMO));
	MINOTAVR_1007 f((char*)buf->MINOTAVR_1007, f.getSize());




	receiveTime.setTime_t(buf->arrayTime[TIME_1007]);

	#include "./datagen/uMINOTAVR_1007.h"

}

void uMINOTAVR_2001(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	MINOTAVR *buf;

	if(workPtr->sourList[NMinotavr]->addLen <= 0)
	{
		return;
	}

	buf = (MINOTAVR *)((char*)workPtr->sourList[NMinotavr]->addPtr + 2*sizeof(SHAPethMMO));
	MINOTAVR_2001 f((char*)buf->MINOTAVR_2001, f.getSize());


	receiveTime.setTime_t(buf->arrayTime[TIME_2001]);

	#include "./datagen/uMINOTAVR_2001.h"

}

void uMINOTAVR_2002(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	MINOTAVR *buf;

	if(workPtr->sourList[NMinotavr]->addLen <= 0)
	{
		return;
	}

	buf = (MINOTAVR *)((char*)workPtr->sourList[NMinotavr]->addPtr + 2*sizeof(SHAPethMMO));
	MINOTAVR_2002 f((char*)buf->MINOTAVR_2002, f.getSize());


	receiveTime.setTime_t(buf->arrayTime[TIME_2002]);

	#include "./datagen/uMINOTAVR_2002.h"

}

void uMINOTAVR_2003(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	MINOTAVR *buf;

	if(workPtr->sourList[NMinotavr]->addLen <= 0)
	{
		return;
	}

	buf = (MINOTAVR *)((char*)workPtr->sourList[NMinotavr]->addPtr + 2*sizeof(SHAPethMMO));
	MINOTAVR_2003 f((char*)buf->MINOTAVR_2003, f.getSize());


	receiveTime.setTime_t(buf->arrayTime[TIME_2003]);

	#include "./datagen/uMINOTAVR_2003.h"

}

void uMINOTAVR_2004(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	MINOTAVR *buf;

	if(workPtr->sourList[NMinotavr]->addLen <= 0)
	{
		return;
	}

	buf = (MINOTAVR *)((char*)workPtr->sourList[NMinotavr]->addPtr + 2*sizeof(SHAPethMMO));
	MINOTAVR_2004 f((char*)buf->MINOTAVR_2004, f.getSize());


	receiveTime.setTime_t(buf->arrayTime[TIME_2004]);

	#include "./datagen/uMINOTAVR_2004.h"

}


void uMINOTAVR_2005(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	MINOTAVR *buf;

	if(workPtr->sourList[NMinotavr]->addLen <= 0)
	{
		return;
	}

	buf = (MINOTAVR *)((char*)workPtr->sourList[NMinotavr]->addPtr + 2*sizeof(SHAPethMMO));
	MINOTAVR_2005 f((char*)buf->MINOTAVR_2005, f.getSize());


	receiveTime.setTime_t(buf->arrayTime[TIME_2005]);

	#include "./datagen/uMINOTAVR_2005.h"

}

void uMINOTAVR_2006(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	MINOTAVR *buf;

	if(workPtr->sourList[NMinotavr]->addLen <= 0)
	{
		return;
	}

	buf = (MINOTAVR *)((char*)workPtr->sourList[NMinotavr]->addPtr + 2*sizeof(SHAPethMMO));
	MINOTAVR_2006 f((char*)buf->MINOTAVR_2006, f.getSize());


	receiveTime.setTime_t(buf->arrayTime[TIME_2006]);

	#include "./datagen/uMINOTAVR_2006.h"

}

void uMINOTAVR_2007(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	MINOTAVR *buf;

	if(workPtr->sourList[NMinotavr]->addLen <= 0)
	{
		return;
	}

	buf = (MINOTAVR *)((char*)workPtr->sourList[NMinotavr]->addPtr + 2*sizeof(SHAPethMMO));
	MINOTAVR_2007 f((char*)buf->MINOTAVR_2007, f.getSize());


	receiveTime.setTime_t(buf->arrayTime[TIME_2007]);

	#include "./datagen/uMINOTAVR_2007.h"

}

void uMINOTAVR_2008(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	MINOTAVR *buf;

	if(workPtr->sourList[NMinotavr]->addLen <= 0)
	{
		return;
	}

	buf = (MINOTAVR *)((char*)workPtr->sourList[NMinotavr]->addPtr + 2*sizeof(SHAPethMMO));
	MINOTAVR_2008 f((char*)buf->MINOTAVR_2008, f.getSize());


	receiveTime.setTime_t(buf->arrayTime[TIME_2008]);

	#include "./datagen/uMINOTAVR_2008.h"

}

void uMINOTAVR_2009(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	MINOTAVR *buf;

	if(workPtr->sourList[NMinotavr]->addLen <= 0)
	{
		return;
	}

	buf = (MINOTAVR *)((char*)workPtr->sourList[NMinotavr]->addPtr + 2*sizeof(SHAPethMMO));
	MINOTAVR_2009 f((char*)buf->MINOTAVR_2009, f.getSize());


	receiveTime.setTime_t(buf->arrayTime[TIME_2009]);

	#include "./datagen/uMINOTAVR_2009.h"

}

void uPAKET_IN(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	PAKET *buf;



	if(workPtr->sourList[NPaket]->addLen <= 0)
	{
		return;
	}


	buf = (PAKET *)((char*)workPtr->sourList[NPaket]->addPtr + 2*sizeof(SHAPethMMO));
	PAKET_IN f((char*)buf->IN_PAKET, f.getSize());



	receiveTime.setTime_t(buf->arrayTime[TIME_IN_PAKET]);

	#include "./datagen/uPAKET_IN.h"


}
void uPAKET_OUT(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{

	PAKET *buf;



	if(workPtr->sourList[NPaket]->addLen <= 0)
	{
		return;
	}


	buf = (PAKET *)((char*)workPtr->sourList[NPaket]->addPtr + 2*sizeof(SHAPethMMO));
	PAKET_OUT f((char*)buf->OUT_PAKET, f.getSize());



	receiveTime.setTime_t(buf->arrayTime[TIME_OUT_PAKET]);

	#include "./datagen/uPAKET_OUT.h"

}
void uSOEJ_TOSIGMA(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	SOEJ *buf;
	SOEJ_Header h;


	if(workPtr->sourList[NSoej]->addLen <= 0)
	{
		return;
	}


	buf = (SOEJ *)((char*)workPtr->sourList[NSoej]->addPtr + 2*sizeof(SHAPethMMO));
	SOEJ_ToSIGMA f((char*)buf->TOSIGMA, f.getSize());



	receiveTime.setTime_t(buf->arrayTime[TIME_TOSIGMA]);

	#include "./datagen/uSOEJ_ToSIGMA.h"

}
void uSOEJ_FROMSIGMA(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	SOEJ *buf;
	SOEJ_Header h;
	//SOURSTRUC *sr = workPtr->sourList[NSoej];

	if(workPtr->sourList[NSoej]->addLen <= 0)
	{
		return;
	}


	buf = (SOEJ *)((char*)workPtr->sourList[NSoej]->addPtr + 2*sizeof(SHAPethMMO));

	SOEJ_FromSigma f((char*)buf->FROMSIGMA, f.getSize());



	receiveTime.setTime_t(buf->arrayTime[TIME_FROMSIGMA]);


	#include "./datagen/uSOEJ_FromSIGMA.h"
}

void uFMR231Sost(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	MR231 *buf;
	if(workPtr->sourList[NPal]->addLen <= 0)
	{
		return;
	}

	buf = (MR231 *)((char*)workPtr->sourList[NPal]->addPtr + 2*sizeof(SHAPethMMO));
	//qDebug() << "str=" << buf;

	FMR231Sost f( (char*)buf->RARSD, f.getSize());


	receiveTime.setTime_t(buf->arrayTime[TIME_RARSD]);

	//! \cond
	#include "./datagen/uFMR231Sost.h"
	//! \endcond

}

void uFMR231Targ(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	MR231 *buf;
	SOURSTRUC *sr = workPtr->sourList[NPal];

	if(sr->addLen <= 0)
	{
		return;
	}

	buf = (MR231 *)((char*)sr->addPtr + 2*sizeof(SHAPethMMO));

	//FMR231Targ f( (char*)buf->RAVHW, f.getSize());

	receiveTime.setTime_t(buf->arrayTime[TIME_RATTM]);

	QList<QVariant> tmp;
	tmp.clear();
	for(int iii = 0; iii <= sr->targMax; iii++)
	{
		TARGSTRUC *tg = &(sr->targList[iii]);
		if(tg && (tg->presSig & 1) && (tg->addPtr))
		{
			FMR231Targ f;
			MR231_Targ *mr231;

			mr231 = (MR231_Targ *)((char*)tg->addPtr + 2*sizeof(SHAPethMMO));
			f.setData( (char*)mr231->RATTM, f.getSize() );


			tmp<<f.getNC()<<f.getDC() << f.getPC() << f.getSC() <<f.getKC()<<f.getDTKS()<<f.getVTKS()<<f.getStC()<<f.getIC();
		}
	}

	tableNumbers.append(0);
	data.append(tmp);
//
//	//! \cond
//	#include "./datagen/uFMR231Targ.h"
//	//! \endcond
}

void uSuget(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	SUGET *buf;
	if(workPtr->sourList[NSuget]->addLen <= 0)
	{
		return;
	}

	buf = (SUGET *)((char*)workPtr->sourList[NSuget]->addPtr + 2*sizeof(SHAPethMMO));
	//qDebug() << "str=" << buf;
	Suget f( (char*)buf->WIXDR, f.getSize());


	receiveTime.setTime_t(buf->arrayTime[0]);


	//! \cond
	#include "./datagen/uSuget.h"
//	data.clear();
//	data<<"11.11";
//	setData(3,data);
	//! \endcond
}

void uGnom(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	GNOM *buf;

	//qDebug() << "gnom 1";

	if(workPtr->sourList[NGNOM]->addLen <= 0)
	{
		return;
	}

	//qDebug() << "gnom 2";

	buf = (GNOM *)((char*)workPtr->sourList[NGNOM]->addPtr + 2*sizeof(SHAPethMMO));
	Gnom f( (char*)buf->IP1, f.getSize());

	//qDebug() << "gnom 3";


	receiveTime.setTime_t(buf->arrayTime[0]);


	//qDebug() << "gnom 4";

	//! \cond
	#include "./datagen/uGnom.h"
	//! \endcond

	//qDebug() << "gnom 5";
}


void uSSPK_DTSSK(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NSSPK]->addLen <= 0)
	{
		return;
	}
	SSPK *buf = (SSPK*)((char*)workPtr->sourList[NSSPK]->addPtr + 2*sizeof(SHAPethMMO));


	receiveTime.setTime_t(buf->arrayTime[1]);


	SSPK_DTSSK f((char*)buf->DTSSK, f.getSize());


	//! \cond
	#include "./datagen/uSSPK_DTSSK.h"
	//! \endcond
}

void uSSPK_DTSSV(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NSSPK]->addLen <= 0)
	{
		return;
	}
	SSPK *buf = (SSPK*)((char*)workPtr->sourList[NSSPK]->addPtr + 2*sizeof(SHAPethMMO));


	receiveTime.setTime_t(buf->arrayTime[2]);


	SSPK_DTSSV f((char*)buf->DTSSV, f.getSize());
	//! \cond
	#include "./datagen/uSSPK_DTSSV.h"
	//! \endcond
}

void uSSPK_DTSSP(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NSSPK]->addLen <= 0)
	{
		return;
	}
	SSPK *buf = (SSPK*)((char*)workPtr->sourList[NSSPK]->addPtr + 2*sizeof(SHAPethMMO));


	receiveTime.setTime_t(buf->arrayTime[3]);


	SSPK_DTSSP f((char*)buf->DTSSP, f.getSize());

	//! \cond
	#include "./datagen/uSSPK_DTSSP.h"
	//! \endcond
}

void uSSPK_DSSGM(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{

	if(workPtr->sourList[NSSPK]->addLen <= 0)
	{
		return;
	}
	SSPK *buf = (SSPK*)((char*)workPtr->sourList[NSSPK]->addPtr + 2*sizeof(SHAPethMMO));


	receiveTime.setTime_t(buf->arrayTime[0]);


	SSPK_DSSGM f((char*)buf->DSSGM, f.getSize());
	//! \cond
	#include "./datagen/uSSPK_DSSGM.h"
	//! \endcond
}



void uSUMF_IP1(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NSUMF]->addLen <= 0)
	{
		return;
	}
	SUMF *ppp = (SUMF *)((char*)workPtr->sourList[NSUMF]->addPtr + 2*sizeof(SHAPethMMO));



	receiveTime.setTime_t(ppp->arrayTime[0]);



	SUMF_Header header;

	header.setData( (const char *)ppp->IP1, header.getSize());
	int count = header.getKolSegm();

	qDebug() << "count segm IP1 = " << count;

	char *ptr1 = (char*)ppp->IP1 + header.getSize();

	QList<QVariant> tmp;
	tmp.clear();
	for(int iii = 0; iii < count; iii++)
	{
		SUMF_IP1 f;
		f.setData( ptr1 + iii*f.getSize(), f.getSize() );
		tmp<<f.getNumObj()<<f.getTsec()<<f.getP()<<f.getD()<<f.getVIzmP()<<f.getVIzmUgMesta()<<f.getUgMesta()<<f.getManevrH();

		//! \cond
		//#include "./datagen/uSUMF_IP1.h"
		//! \endcond
	}

	tableNumbers.append(0);
	data.append(tmp);

}


void uSUMF_IP2(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NSUMF]->addLen <= 0)
	{
		return;
	}
	SUMF *ppp = (SUMF *)((char*)workPtr->sourList[NSUMF]->addPtr + 2*sizeof(SHAPethMMO));



	receiveTime.setTime_t(ppp->arrayTime[0]);



	SUMF_Header header;

	header.setData( (const char *)ppp->IP2, header.getSize());
	int count = header.getKolSegm();

	qDebug() << "count segm IP2 = " << count;

	char *ptr1 = (char*)ppp->IP2 + header.getSize();

	QList<QVariant> tmp;
	tmp.clear();

/*
		SUMF_IP2 f;
		f.setData( ptr1 , f.getSize() );
		data<<f.getNumObj()<<f.getTypeIstInfo()<<f.getPriznObj()<<f.getPriznOpozn()<<f.getPriznKompl();


		setData(0,data);

		data.clear();
		data<<f.getTypeObj()<<f.getPriznSopr()<<f.getPriorSopr()<<f.getPriznEPR();
		setData(tableList[1],data);
*/

	for(int iii = 0; iii < count; iii++)
	{
		SUMF_IP2 f;
		f.setData( ptr1 + iii*f.getSize(), f.getSize() );
		tmp<<f.getNumObj()<<f.getTypeIstInfo()<<f.getPriznOpozn()<<f.getTypeObj()<<f.getClassObj();
	}

	tableNumbers.append(0);
	data.append(tmp);

}


void uSUMF_IP10(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NSUMF]->addLen <= 0)
	{
		return;
	}
	SUMF *ppp = (SUMF *)((char*)workPtr->sourList[NSUMF]->addPtr + 2*sizeof(SHAPethMMO));
	SUMF_IP10 f;


	receiveTime.setTime_t(ppp->arrayTime[9]);


	SUMF_Header header;
	header.setData( (const char *)ppp->IP10, header.getSize());
	qDebug() << "count segm IP10 = " << header.getKolSegm();

	f.setData( (char*)ppp->IP10 + header.getSize(), f.getSize() );
	//! \cond
	#include "./datagen/uSUMF_IP10.h"
	//! \endcond
}

void uSUMF_IP11(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	qDebug() << "!!!!!!!!!!!!!!!!!! addLen segm IP11 = " << workPtr->sourList[NSUMF]->addLen;

	if(workPtr->sourList[NSUMF]->addLen <= 0)
	{
		return;
	}
	SUMF *ppp = (SUMF *)((char*)workPtr->sourList[NSUMF]->addPtr + 2*sizeof(SHAPethMMO));
	SUMF_IP11 f;

	// = QDateTime::currentDateTime();
	receiveTime.setTime_t(ppp->arrayTime[10]);


	SUMF_Header header;
	header.setData( (const char *)ppp->IP11, header.getSize());
	qDebug() << "count segm IP11 = " << header.getKolSegm();

	f.setData( (char*)ppp->IP11 + header.getSize(), f.getSize() );
	qDebug() << "!!!!!!!!!!!  getPrNaznCom=" << f.getPrNaznCom();
	//! \cond
	#include "./datagen/uSUMF_IP11.h"
	//! \endcond
}

void uSUMF_IP12(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NSUMF]->addLen <= 0)
	{
		return;
	}
	SUMF *ppp = (SUMF *)((char*)workPtr->sourList[NSUMF]->addPtr + 2*sizeof(SHAPethMMO));
	SUMF_IP12 f;

	// = QDateTime::currentDateTime();
	receiveTime.setTime_t(ppp->arrayTime[11]);


	SUMF_Header header;
	header.setData( (const char *)ppp->IP12, header.getSize());
	qDebug() << "count segm IP12 = " << header.getKolSegm();

	f.setData( (char*)ppp->IP12 + header.getSize(), f.getSize() );
	//! \cond
	#include "./datagen/uSUMF_IP12.h"
	//! \endcond
}


void uSUMF_IP4(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NSUMF]->addLen <= 0)
	{
		return;
	}
	SUMF *ppp = (SUMF *)((char*)workPtr->sourList[NSUMF]->addPtr + 2*sizeof(SHAPethMMO));
	SUMF_IP4 f;

	// = QDateTime::currentDateTime();
	receiveTime.setTime_t(ppp->arrayTime[3]);


	SUMF_Header header;
	header.setData( (const char *)ppp->IP4, header.getSize());
	qDebug() << "count segm IP4 = " << header.getKolSegm();

	f.setData( (char*)ppp->IP4 + header.getSize(), f.getSize() );
	//! \cond
	#include "./datagen/uSUMF_IP4.h"
	//! \endcond
}

void uSUMF_IP6(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NSUMF]->addLen <= 0)
	{
		return;
	}
	SUMF *ppp = (SUMF *)((char*)workPtr->sourList[NSUMF]->addPtr + 2*sizeof(SHAPethMMO));
	SUMF_IP6 f;

	// = QDateTime::currentDateTime();
	receiveTime.setTime_t(ppp->arrayTime[5]);


	SUMF_Header header;
	header.setData( (const char *)ppp->IP6, header.getSize());
	qDebug() << "count segm IP6 = " << header.getKolSegm();

	f.setData( (char*)ppp->IP6 + header.getSize(), f.getSize() );
	//! \cond
	#include "./datagen/uSUMF_IP6.h"
	//! \endcond
}


void uSUMF_IP41(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NSUMF]->addLen <= 0)
	{
		return;
	}
	SUMF *ppp = (SUMF *)((char*)workPtr->sourList[NSUMF]->addPtr + 2*sizeof(SHAPethMMO));
	SUMF_IP41 f;

	// = QDateTime::currentDateTime();
	receiveTime.setTime_t(ppp->arrayTime[40]);


	SUMF_Header header;
	header.setData( (const char *)ppp->IP41, header.getSize());
	qDebug() << "count segm IP41 = " << header.getKolSegm();
	int count = header.getKolSegm();

	char *ptr1 = (char*)ppp->IP41 + header.getSize();

	//f.setData( (char*)ppp->IP41 + header.getSize(), f.getSize() );
	//! \cond
	//#include "./datagen/uSUMF_IP41.h"
	//! \endcond

	QList<QVariant> tmp;
	tmp.clear();
	for(int iii = 0; iii < count; iii++)
	{
		SUMF_IP41 f;
		f.setData( ptr1 + iii*f.getSize(), f.getSize() );
		tmp<<f.getTypeIstInfo()<<f.getPrVklIskl()<<f.getNumObj()<<f.getTypeSyst();
		//! \cond
		//#include "./datagen/uSUMF_IP1.h"
		//! \endcond
	}

	tableNumbers.append(0);
	data.append(tmp);
}

void uSUMF_IP44(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NSUMF]->addLen <= 0)
	{
		return;
	}
	SUMF *ppp = (SUMF *)((char*)workPtr->sourList[NSUMF]->addPtr + 2*sizeof(SHAPethMMO));
	SUMF_IP44 f;

	// = QDateTime::currentDateTime();
	receiveTime.setTime_t(ppp->arrayTime[43]);


	SUMF_Header header;
	header.setData( (const char *)ppp->IP44, header.getSize());
	qDebug() << "count segm IP44 = " << header.getKolSegm();

	f.setData( (char*)ppp->IP44 + header.getSize(), f.getSize() );
	//! \cond
	#include "./datagen/uSUMF_IP44.h"
	//! \endcond
}


void uSUMF_IP45(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NSUMF]->addLen <= 0)
	{
		return;
	}
	SUMF *ppp = (SUMF *)((char*)workPtr->sourList[NSUMF]->addPtr + 2*sizeof(SHAPethMMO));
	SUMF_IP45 f;

	// = QDateTime::currentDateTime();
	receiveTime.setTime_t(ppp->arrayTime[44]);


	SUMF_Header header;
	header.setData( (const char *)ppp->IP45, header.getSize());
	qDebug() << "count segm IP45 = " << header.getKolSegm();

	f.setData( (char*)ppp->IP45 + header.getSize(), f.getSize() );
	//! \cond
	#include "./datagen/uSUMF_IP45.h"
	//! \endcond
}

void uSUMF_IP8(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	//char *buf;
	if(workPtr->sourList[NSUMF]->addLen <= 0)
	{
		return;
	}
	SUMF *ppp = (SUMF *)((char*)workPtr->sourList[NSUMF]->addPtr + 2*sizeof(SHAPethMMO));
	SUMF_IP8 f;

	// = QDateTime::currentDateTime();
	receiveTime.setTime_t(ppp->arrayTime[7]);


	SUMF_Header header;
	header.setData( (const char *)ppp->IP8, header.getSize());
	qDebug() << "count segm IP8 = " << header.getKolSegm();

	f.setData( (char*)ppp->IP8 + header.getSize(), f.getSize() );
	//! \cond
	#include "./datagen/uSUMF_IP8.h"
	//! \endcond
}


void uSUMF_IP34(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	//char *buf;
	if(workPtr->sourList[NSUMF]->addLen <= 0)
	{
		return;
	}
	SUMF *ppp = (SUMF *)((char*)workPtr->sourList[NSUMF]->addPtr + 2*sizeof(SHAPethMMO));
	SUMF_IP34 f;

	// = QDateTime::currentDateTime();
	receiveTime.setTime_t(ppp->arrayTime[33]);


	SUMF_Header header;
	header.setData( (const char *)ppp->IP34, header.getSize());
	qDebug() << "count segm IP34 = " << header.getKolSegm();

	f.setData( (char*)ppp->IP34 + header.getSize(), f.getSize() );
	//! \cond
	#include "./datagen/uSUMF_IP34.h"
	//! \endcond
}


void uMUS_IP1(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NMUS]->addLen <= 0)
	{

		return;
	}
	MUS *ppp = (MUS *)((char*)workPtr->sourList[NMUS]->addPtr + 2*sizeof(SHAPethMMO));
	SUMF_IP1 f;

	// = QDateTime::currentDateTime();
	receiveTime.setTime_t(ppp->arrayTime[44]);


	SUMF_Header header;
	header.setData( (const char *)ppp->IP1, header.getSize());
	qDebug() << "count segm IP1 = " << header.getKolSegm();

	char* ptr1 = (char*)ppp->IP1 + header.getSize() ;


	QList<QVariant> tmp;
	tmp.clear();
	int count = header.getKolSegm();
	for(int iii = 0; iii < count; iii++)
	{
		SUMF_IP1 f;
		f.setData( ptr1 + iii*f.getSize(), f.getSize() );
		tmp<<f.getNumObj()<<f.getTsec()<<f.getP()<<f.getD()<<f.getVIzmP()<<f.getVIzmUgMesta()<<f.getUgMesta()<<f.getManevrH();

		qDebug() << f.getNumObj()<<f.getTsec()<<f.getP()<<f.getD()<<f.getVIzmP()<<f.getVIzmUgMesta()<<f.getUgMesta()<<f.getManevrH();
		//! \cond
		//#include "./datagen/uSUMF_IP1.h"
		//! \endcond
	}

	tableNumbers.append(0);
	data.append(tmp);

}

void uMUS_IP2(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NMUS]->addLen <= 0)
	{
		return;
	}
	MUS *ppp = (MUS *)((char*)workPtr->sourList[NMUS]->addPtr + 2*sizeof(SHAPethMMO));
	SUMF_IP2 f;

	// = QDateTime::currentDateTime();
	receiveTime.setTime_t(ppp->arrayTime[33]);


	SUMF_Header header;
	header.setData( (const char *)ppp->IP2, header.getSize());
	qDebug() << "count segm IP2 = " << header.getKolSegm();

	f.setData( (char*)ppp->IP2 + header.getSize(), f.getSize() );
	//! \cond
	#include "./datagen/uMUS_IP2.h"
	//! \endcond
}

void uMUS_IP3(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NMUS]->addLen <= 0)
	{
		return;
	}
	MUS *ppp = (MUS *)((char*)workPtr->sourList[NMUS]->addPtr + 2*sizeof(SHAPethMMO));
	SUMF_IP3 f;

	// = QDateTime::currentDateTime();
	receiveTime.setTime_t(ppp->arrayTime[33]);


	SUMF_Header header;
	header.setData( (const char *)ppp->IP3, header.getSize());
	qDebug() << "count segm IP3 = " << header.getKolSegm();

	f.setData( (char*)ppp->IP3 + header.getSize(), f.getSize() );
	//! \cond
	#include "./datagen/uMUS_IP3.h"
	//! \endcond
}

void uMUS_IP4(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NMUS]->addLen <= 0)
	{
		return;
	}
	MUS *ppp = (MUS *)((char*)workPtr->sourList[NMUS]->addPtr + 2*sizeof(SHAPethMMO));
	SUMF_IP4 f;

	// = QDateTime::currentDateTime();
	receiveTime.setTime_t(ppp->arrayTime[33]);


	SUMF_Header header;
	header.setData( (const char *)ppp->IP4, header.getSize());
	qDebug() << "count segm IP4 = " << header.getKolSegm();

	f.setData( (char*)ppp->IP4 + header.getSize(), f.getSize() );
	//! \cond
	#include "./datagen/uMUS_IP4.h"
	//! \endcond
}

void uMUS_IP11(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NMUS]->addLen <= 0)
	{
		return;
	}
	MUS *ppp = (MUS *)((char*)workPtr->sourList[NMUS]->addPtr + 2*sizeof(SHAPethMMO));
	SUMF_IP11 f;

	// = QDateTime::currentDateTime();
	receiveTime.setTime_t(ppp->arrayTime[33]);


	SUMF_Header header;
	header.setData( (const char *)ppp->IP11, header.getSize());
	qDebug() << "count segm IP11 = " << header.getKolSegm();

	f.setData( (char*)ppp->IP11 + header.getSize(), f.getSize() );
	//! \cond
	#include "./datagen/uMUS_IP11.h"
	//! \endcond
}

void uMUS_IP12(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NMUS]->addLen <= 0)
	{
		return;
	}
	MUS *ppp = (MUS *)((char*)workPtr->sourList[NMUS]->addPtr + 2*sizeof(SHAPethMMO));
	SUMF_IP12 f;

	// = QDateTime::currentDateTime();
	receiveTime.setTime_t(ppp->arrayTime[33]);


	SUMF_Header header;
	header.setData( (const char *)ppp->IP12, header.getSize());
	qDebug() << "count segm IP12 = " << header.getKolSegm();

	f.setData( (char*)ppp->IP12 + header.getSize(), f.getSize() );
	//! \cond
	#include "./datagen/uMUS_IP12.h"
	//! \endcond
}

void uMUS_IP37(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NMUS]->addLen <= 0)
	{
		return;
	}
	MUS *ppp = (MUS *)((char*)workPtr->sourList[NMUS]->addPtr + 2*sizeof(SHAPethMMO));
	MUS_IP37 f;

	// = QDateTime::currentDateTime();
	receiveTime.setTime_t(ppp->arrayTime[33]);


	SUMF_Header header;
	header.setData( (const char *)ppp->IP37, header.getSize());
	qDebug() << "count segm IP37 = " << header.getKolSegm();

	f.setData( (char*)ppp->IP37 + header.getSize(), f.getSize() );
	//! \cond
	#include "./datagen/uMUS_IP37.h"
	//! \endcond
}

void uMUS_IP40(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NMUS]->addLen <= 0)
	{
		return;
	}
	MUS *ppp = (MUS *)((char*)workPtr->sourList[NMUS]->addPtr + 2*sizeof(SHAPethMMO));
	MUS_IP40 f;

	// = QDateTime::currentDateTime();
	receiveTime.setTime_t(ppp->arrayTime[33]);


	SUMF_Header header;
	header.setData( (const char *)ppp->IP40, header.getSize());
	qDebug() << "count segm IP40 = " << header.getKolSegm();

	f.setData( (char*)ppp->IP40 + header.getSize(), f.getSize() );
	//! \cond
	#include "./datagen/uMUS_IP40.h"
	//! \endcond
}

void uMUS_IP60(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NMUS]->addLen <= 0)
	{
		return;
	}
	MUS *ppp = (MUS *)((char*)workPtr->sourList[NMUS]->addPtr + 2*sizeof(SHAPethMMO));
	MUS_IP60 f;

	// = QDateTime::currentDateTime();
	receiveTime.setTime_t(ppp->arrayTime[33]);


	SUMF_Header header;
	header.setData( (const char *)ppp->IP60, header.getSize());
	qDebug() << "count segm IP60 = " << header.getKolSegm();

	f.setData( (char*)ppp->IP60 + header.getSize(), f.getSize() );
	//! \cond
	#include "./datagen/uMUS_IP60.h"
	//! \endcond
}

void uMUS_IP61(QList<int> &tableNumbers, QList< QList<QVariant> > &data, QDateTime &receiveTime)
{
	if(workPtr->sourList[NMUS]->addLen <= 0)
	{
		return;
	}
	MUS *ppp = (MUS *)((char*)workPtr->sourList[NMUS]->addPtr + 2*sizeof(SHAPethMMO));
	MUS_IP61 f;

	// = QDateTime::currentDateTime();
	receiveTime.setTime_t(ppp->arrayTime[33]);


	SUMF_Header header;
	header.setData( (const char *)ppp->IP61, header.getSize());
	qDebug() << "count segm IP61 = " << header.getKolSegm();

	f.setData( (char*)ppp->IP61 + header.getSize(), f.getSize() );
	//! \cond
	#include "./datagen/uMUS_IP61.h"
	//! \endcond
}

#endif // ABONENTGETDATAFUNCTIONS_H
