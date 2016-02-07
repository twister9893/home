QList<QVariant> tmp;
// Формуляр радиоизлучающего объекта
tmp.clear();
tmp<<f.getNumObj()<<f.getTypeIstInfo()<<f.getSostIzl()<<f.getPrMobil()<<f.getTsec()<<f.getTmsec();
tableNumbers.append(0);
data.append(tmp);

//                         
tmp.clear();
tmp<<f.getNumRS()<<f.getChastota()<<f.getPolosaChast()<<f.getUrMoshIzl();
tableNumbers.append(1);
data.append(tmp);

//                         
tmp.clear();
tmp<<f.getDMin()<<f.getDMax()<<f.getVVrAnt();
tableNumbers.append(2);
data.append(tmp);
