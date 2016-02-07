QList<QVariant> tmp;
// Формуляр радиотехнического объекта
tmp.clear();
tmp<<f.getNumObj()<<f.getTypeIstInfo()<<f.getTypeSignal()<<f.getTsec()<<f.getTmsec();
tableNumbers.append(0);
data.append(tmp);

//     
tmp.clear();
tmp<<f.getTypeRES()<<f.getChastota()<<f.getPolosaChast()<<f.getUrMoshIzl()<<f.getDlitImpuls();
tableNumbers.append(1);
data.append(tmp);

//               
tmp.clear();
tmp<<f.getChastPovtorImpuls()<<f.getKolImpuls()<<f.getImpulsMod()<<f.getPomeha();
tableNumbers.append(2);
data.append(tmp);

//                        
tmp.clear();
tmp<<f.getDMin()<<f.getDMax()<<f.getVVrAnt();
tableNumbers.append(3);
data.append(tmp);
