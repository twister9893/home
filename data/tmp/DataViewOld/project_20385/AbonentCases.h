#ifndef ABONENTCASES_H
#define ABONENTCASES_H

switch(m_additionalInfo.toInt())
{

	case ABON_MINOTAVR_1001:
	{
		qDebug()<<"MINOTAVR_1001";
		uMINOTAVR_1001(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;
	case ABON_MINOTAVR_1002:
	{
		qDebug()<<"MINOTAVR_1002";
		uMINOTAVR_1002(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;
	case ABON_MINOTAVR_1003:
	{
		qDebug()<<"MINOTAVR_1003";
		uMINOTAVR_1003(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;
	case ABON_MINOTAVR_1004:
	{
		qDebug()<<"MINOTAVR_1004";
		uMINOTAVR_1004(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;
	case ABON_MINOTAVR_1005:
	{
		qDebug()<<"MINOTAVR_1005";
		uMINOTAVR_1005(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;
	case ABON_MINOTAVR_1006:
	{
		qDebug()<<"MINOTAVR_1006";
		uMINOTAVR_1006(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;
	case ABON_MINOTAVR_1007:
	{
		qDebug()<<"MINOTAVR_1007";
		uMINOTAVR_1007(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_MINOTAVR_2001:
	{
		qDebug()<<"MINOTAVR_2001";
		uMINOTAVR_2001(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;
	case ABON_MINOTAVR_2002:
	{
		qDebug()<<"MINOTAVR_2002";
		uMINOTAVR_2002(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;
	case ABON_MINOTAVR_2003:
	{
		qDebug()<<"MINOTAVR_2003";
		uMINOTAVR_2003(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;
	case ABON_MINOTAVR_2004:
	{
		qDebug()<<"MINOTAVR_2004";
		uMINOTAVR_2004(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;
	case ABON_MINOTAVR_2005:
	{
		qDebug()<<"MINOTAVR_2005";
		uMINOTAVR_2005(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;
	case ABON_MINOTAVR_2006:
	{
		qDebug()<<"MINOTAVR_2006";
		uMINOTAVR_2006(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;
	case ABON_MINOTAVR_2007:
	{
		qDebug()<<"MINOTAVR_2007";
		uMINOTAVR_2007(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;
	case ABON_MINOTAVR_2008:
	{
		qDebug()<<"MINOTAVR_2008";
		uMINOTAVR_2008(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;
	case ABON_MINOTAVR_2009:
	{
		qDebug()<<"MINOTAVR_2009";
		uMINOTAVR_2009(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_PAKET_IN:
	{
		qDebug()<<"PAKET_IN";
		uPAKET_IN(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;
	case ABON_PAKET_OUT:
	{
		qDebug()<<"PAKET_OUT";
		uPAKET_OUT(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;


	case ABON_SOEJ_FROMSIGMA:
	{
		qDebug()<<"SOEJ_FROMSIGMA";
		uSOEJ_FROMSIGMA(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;


	case ABON_SOEJ_TOSIGMA:
	{
		qDebug()<<"SOEJ_TOSIGMA";
		uSOEJ_TOSIGMA(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}

	}
	break;

	case ABON_SUMF_IP1:
	{
		qDebug() << "SUMF_IP1";
		uSUMF_IP1(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;


	case ABON_SUMF_IP2:
	{
		qDebug() << "SUMF_IP2";
		uSUMF_IP2(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_SUMF_IP4:
	{
		qDebug() << "SUMF_IP4";
		uSUMF_IP4(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_SUMF_IP41:
	{
		qDebug() << "SUMF_IP41";
		uSUMF_IP41(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_SUMF_IP45:
	{
		qDebug() << "SUMF_IP45";
		uSUMF_IP45(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_SUMF_IP44:
	{
		qDebug() << "SUMF_IP44";
		uSUMF_IP44(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_SUMF_IP6:
	{
		qDebug() << "SUMF_IP6";
		uSUMF_IP6(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;


	case ABON_SUMF_IP8:
	{
		qDebug() << "SUMF_IP8";
		uSUMF_IP8(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_SUMF_IP10:
	{
		qDebug() << "SUMF_IP10";
		uSUMF_IP10(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_SUMF_IP11:
	{
		qDebug() << "SUMF_IP11";
		uSUMF_IP11(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_SUMF_IP34:
	{
		qDebug() << "SUMF_IP34";
		uSUMF_IP34(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_SUMF_IP12:
	{
		qDebug() << "SUMF_IP12";
		uSUMF_IP12(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_SSPK_DTSSK:
	{
		qDebug() << "SSPK_DTSSK";
		uSSPK_DTSSK(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_SSPK_DTSSV:
	{
		qDebug() << "SSPK_DTSSV";
		uSSPK_DTSSV(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_SSPK_DTSSP:
	{
		qDebug() << "SSPK_DTSSP";
		uSSPK_DTSSP(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_SSPK_DSSGM:
	{
		qDebug() << "SSPK_DSSGM";
		uSSPK_DSSGM(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;


	case ABON_SUGET:
	{
		qDebug() << "Suget";
		uSuget(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_GNOM:
	{
		qDebug() << "Gnom";
		uGnom(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_MR231_Sost:
	{
		uFMR231Sost(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_MR231_Targ:
	{
		uFMR231Targ(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_MUS_IP1:
	{
		qDebug() << "uMUS_IP1";
		uMUS_IP1(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_MUS_IP2:
	{
		qDebug() << "uMUS_IP2";
		uMUS_IP2(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_MUS_IP3:
	{
		qDebug() << "uMUS_IP3";
		uMUS_IP3(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_MUS_IP4:
	{
		qDebug() << "uMUS_IP4";
		uMUS_IP4(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_MUS_IP11:
	{
		qDebug() << "uMUS_IP11";
		uMUS_IP11(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_MUS_IP12:
	{
		qDebug() << "uMUS_IP12";
		uMUS_IP12(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_MUS_IP37:
	{
		qDebug() << "uMUS_IP37";
		uMUS_IP37(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_MUS_IP40:
	{
		qDebug() << "uMUS_IP40";
		uMUS_IP40(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_MUS_IP60:
	{
		qDebug() << "uMUS_IP60";
		uMUS_IP60(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	case ABON_MUS_IP61:
	{
		qDebug() << "uMUS_IP61";
		uMUS_IP61(tableNumbers, data, receiveTime);
		for(int i = 0; i < tableNumbers.count(); i++) {
			emit gotData(tableNumbers.at(i), data.at(i), receiveTime);
		}
	}
	break;

	default: {
		return false;
	}
}
return true;

#endif // ABONENTCASES_H
