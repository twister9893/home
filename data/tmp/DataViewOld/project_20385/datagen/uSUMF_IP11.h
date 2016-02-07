QList<QVariant> tmp;
// Команда ЦУ
tmp.clear();
tmp<<f.getNumObj()<<f.getTypeIstInfo()<<f.getSredObslObj();
tableNumbers.append(0);
data.append(tmp);

//     
tmp.clear();
tmp<<f.getPrPrior()<<f.getPrNaznCom()<<f.getPrPazrVozd();
tableNumbers.append(1);
data.append(tmp);
