QList<QVariant> tmp;
// Информация из изделия "Сигма"
tmp.clear();
tmp<<f.getTime()<<f.getDau()<<f.getMon()<<f.getYear();
tableNumbers.append(0);
data.append(tmp);

// Точка, в которую следует вертолет
tmp.clear();
tmp<<f.getF()<<f.geta()<<f.getL()<<f.getb();
tableNumbers.append(1);
data.append(tmp);

//          
tmp.clear();
tmp<<f.getKOM()<<f.getDal()<<f.getA()<<f.getKk()<<f.getKsbl();
tableNumbers.append(2);
data.append(tmp);

// Реперная точка
tmp.clear();
tmp<<f.getFr()<<f.getar()<<f.getLr()<<f.getbr();
tableNumbers.append(3);
data.append(tmp);

//        
tmp.clear();
tmp<<f.getKomUstReg()<<f.getUC()<<f.getCK()<<f.getRazv()<<f.getKWIT();
tableNumbers.append(4);
data.append(tmp);
