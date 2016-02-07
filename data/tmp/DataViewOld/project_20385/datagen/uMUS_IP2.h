QList<QVariant> tmp;
// Характеристики объекта
tmp.clear();
tmp<<f.getNumObj()<<f.getTypeIstInfo()<<f.getPriznObj()<<f.getPriznOpozn()<<f.getPriznKompl();
tableNumbers.append(0);
data.append(tmp);

//          
tmp.clear();
tmp<<f.getTypeObj()<<f.getPriznSopr()<<f.getPriorSopr()<<f.getPriznEPR();
tableNumbers.append(1);
data.append(tmp);
