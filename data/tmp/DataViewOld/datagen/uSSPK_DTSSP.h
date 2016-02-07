QList<QVariant> tmp;
// Параметры захода на посадку
tmp.clear();
tmp<<f.getDg()<<f.getHotn();
tableNumbers.append(0);
data.append(tmp);

//                      
tmp.clear();
tmp<<f.getVsbl()<<f.getVzotn();
tableNumbers.append(1);
data.append(tmp);

//                   
tmp.clear();
tmp<<f.getAum();
tableNumbers.append(2);
data.append(tmp);

//                     
tmp.clear();
tmp<<f.getdx()<<f.getdz();
tableNumbers.append(3);
data.append(tmp);

//                     
tmp.clear();
tmp<<f.getPR()<<f.getx()<<f.getKWIT();
tableNumbers.append(4);
data.append(tmp);
